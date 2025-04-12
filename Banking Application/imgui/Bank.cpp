// *********************************************
// Date: 4/11/2025
// Description:
//   Practice with object oriented design
// *********************************************
#include "Bank.h"
#include <cctype>
#include <string>

// constructor that reads from .txt file by calling the fillVector method to populate the database
Bank::Bank(std::string filename){
    std::ifstream file(filename);
    if(!file.is_open()){
        std::cout << "Unable to open file!" << std::endl;
        std::exit(1);
    }
    fillVector(file);
}
// withdraw amount
void Bank::withdraw(){

    std::string accountName;
    int accountNumber;
    double amount;
    
    std::cout << "What is the Account First Name ? ";
    std::cin >> accountName;

    std::cout << "What is the Account Last Name ? ";
    std::string temp;
    std::cin >> temp;
    accountName += " " + temp;

    std::cout << "What is the account Number ? ";
    std::cin >> accountNumber;

    std::cout << "What is the dollar amount ? ";
    std::cin >> amount;

    bool found = false;
    for(const std::shared_ptr<BankAccount>& acc : accountsVector){
        if(acc->getAccountName()==accountName && acc->getAccountNumber()==accountNumber){
            if(amount > acc->getAccountBalance()){
                std::cout << "\nInsufficient Funds" << std::endl;
            }
            else{
                acc->BankAccount::withdraw(amount);
                std::cout << "\nAmount Withdrawn from account" << std::endl;
            }
            found = true;
            std::cout << "Press Enter to continue..." << std::endl;
            std::cin.ignore();
            std::cin.get();
            break;
        }
    }
    if(!found){
        std::cout << "\n\nAccount not found!" << std::endl;
        std::cout << "Press Enter to continue..." << std::endl;
        std::cin.ignore();
        std::cin.get();
    }

}
// check balance (will be updated to viewAccount which will have more stuff)
void Bank::viewBalance(){
    std::string accountName;
    int accountNumber;

    std::cout << "What is the Account First Name ? ";
    std::cin >> accountName;

    std::cout << "What is the Account Last Name ? ";
    std::string temp;
    std::cin >> temp;
    accountName += " " + temp;

    std::cout << "What is the account Number ?";
    std::cin >> accountNumber;

    //std::cout << accountName << " " << accountNumber << std::endl;
    bool found = false;
    //std::cout << "Size accountsVector: " << accountsVector.size() << std::endl;
    //for all the BankAccount shared pointers in accountsVector,
    for(const std::shared_ptr<BankAccount>& acc : accountsVector){
        //std::cout << "Expected Name: " << accountName << ", Found Name: " << acc->BankAccount::getAccountName() << std::endl;
        //std::cout << "Expected Number: " << accountNumber << ", Found Number: " << acc->BankAccount::getAccountNumber() << std::endl;
        //std::cout << "Checking account: " << acc->BankAccount::getAccountName() << " " << acc->BankAccount::getAccountNumber() << std::endl;

        //if name and number matches
        if(acc->BankAccount::getAccountName()==accountName && acc->BankAccount::getAccountNumber()==accountNumber){
            std::cout << "\n---------------------------------" << std::endl;
            std::cout << "Account Name: " << accountName << std::endl;
            std::cout << "Account Number: " << accountNumber << std::endl;
            std::cout << "Account Balance: " << acc->getAccountBalance() << std::endl;
            std::cout << "---------------------------------" << std::endl;

            found = true;
            break;
        }

    }
    if(!found){
        std::cout << "Account not found!" << std::endl;
    }
}
// deposit amount
void Bank::deposit(){

    std::string accountName;
    int accountNumber;
    double amount;
    
    std::cout << "What is the Account First Name ? ";
    std::cin >> accountName;

    std::cout << "What is the Account Last Name ? ";
    std::string temp;
    std::cin >> temp;
    accountName += " " + temp;

    std::cout << "What is the account Number ? ";
    std::cin >> accountNumber;

    std::cout << "What is the dollar amount ? ";
    std::cin >> amount;

    bool found = false;
    for(const std::shared_ptr<BankAccount>& acc : accountsVector){
        if(acc->getAccountName()==accountName && acc->getAccountNumber()==accountNumber){ 
            acc->deposit(amount);
            std::cout << "\nAmount deposited into account" << std::endl;
            std::cout << "Press Enter to continue..." << std::endl;
            std::cin.ignore();
            std::cin.get();

            found = true;
            break;
        }
    }
    if(!found){
        std::cout << "\n\nAccount not found!" << std::endl;
        std::cout << "Press Enter to continue..." << std::endl;
        std::cin.ignore();
        std::cin.get();
    }

}
// helper function
void Bank::fillVector(std::ifstream &input){
    if (!input.is_open()) {
        std::cout << "Error: Failed to open file!" << std::endl;
        return;
    }

    std::string line;
    while(std::getline(input, line)){
        std::istringstream iss(line);
        std::string accountName;
        std::string first, last;
        int id;
        int accountNumber;
        double accountBalance;
        if(iss >> first >> last >> id >> accountNumber >> accountBalance){
            accountsVector.push_back( std::make_shared<BankAccount>((first + " " + last), id, accountNumber, accountBalance) );
        }
        else {
            std::cout << "Error filling vector!" << std::endl;
        }
    }
}
// admin function print all accounts
std::string Bank::printVector(){
    std::ostringstream oss;
    for (const auto& acc : accountsVector) {
        oss << acc->toString() << "\n";
    }
    return oss.str();
}
// admin function add account
void Bank::addAccount() {
    std::string first, last;
    int id;
    int accountNumber;

    // Prompt user for input
    // Input and validation for first name
    std::cout << "Enter New Customer first name: ";
    std::cin >> first;
    for (char c : first) {
        if (!std::isalpha(c)) {
            std::cout << "Error: First name must contain only alphabetic characters.\n";
            return;
        }
    }

    // Input and validation for last name
    std::cout << "Enter New Customer last name: ";
    std::cin >> last;
    for (char c : last) {
        if (!std::isalpha(c)) {
            std::cout << "Error: Last name must contain only alphabetic characters.\n";
            return;
        }
    }

    // Input and validation for ID
    std::cout << "Enter New Customer ID: ";
    std::cin >> id;

    if (id < 1000 || id > 9999) { // Ensure ID is a 4-digit number
        std::cout << "Error: ID must be a 4-digit number.\n";
        return;
    }

    // Input and validation for account number
    std::cout << "Enter New account number: ";
    std::cin >> accountNumber;

    if (accountNumber < 100000 || accountNumber > 999999) { // Ensure account number is a 6-digit number
        std::cout << "Error: Account number must be a 6-digit number.\n";
        return;
    }



    // Add account to the vector
    accountsVector.push_back(std::make_shared<BankAccount>((first + " " + last), id, accountNumber, 0.0));

    // Open a file to save account information
    std::ofstream outFile("imgui/BankData.txt", std::ios::app);
    if (outFile.is_open()) {
        outFile << first << " " << last << " " << id << " " << accountNumber << " 0.0\n";
        outFile.close();
    }
    else {
        std::cout << "Error opening file!" << std::endl;
    }
}
// sort accounts
void Bank::sort(std::vector<std::shared_ptr<BankAccount>> &accountsVector){
}