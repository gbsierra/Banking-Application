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
            else {
                acc->BankAccount::withdraw(amount);
                std::cout << "\nAmount Withdrawn from account" << std::endl;

                // 1. Read the entire file into a vector of strings.
                 std::ifstream inFile("imgui/BankData.txt");

                 std::vector<std::string> lines;
                 std::string line;
                 while (std::getline(inFile, line)) {
                     lines.push_back(line);
                 }
                 inFile.close();

                 // 2. Find and remove the old account entry.
                 int idToRemove = acc->getId();
                 lines.erase(std::remove_if(lines.begin(), lines.end(),
                     [idToRemove](const std::string& currentLine) {
                         std::istringstream iss(currentLine);
                         std::string firstName, lastName;
                         int id;
                         iss >> firstName >> lastName >> id;
                         return id == idToRemove;
                     }),
                     lines.end());

                 // 3. Append the updated account information.
                 std::ofstream outFile("imgui/BankData.txt"); // Open in write mode, which overwrites

                 // Break the full name back into first and last names
                 std::istringstream iss(accountName);
                 std::string firstName, lastName;
                 iss >> firstName >> lastName;

                 int id = acc->getId();
                 double updatedBalance = acc->getAccountBalance();

                 outFile << firstName << " " << lastName << " "
                     << id << " "
                     << accountNumber << " "
                     << updatedBalance << std::endl;

                 // 4. Write all the remaining lines back to the file.
                 for (const auto& remainingLine : lines) {
                     outFile << remainingLine << std::endl;
                 }

                 outFile.close();
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

            // 1. Read the entire file into a vector of strings.
            std::ifstream inFile("imgui/BankData.txt");

            std::vector<std::string> lines;
            std::string line;
            while (std::getline(inFile, line)) {
                lines.push_back(line);
            }
            inFile.close();

            // 2. Find and remove the old account entry.
            int idToRemove = acc->getId();
            lines.erase(std::remove_if(lines.begin(), lines.end(),
                [idToRemove](const std::string& currentLine) {
                    std::istringstream iss(currentLine);
                    std::string firstName, lastName;
                    int id;
                    iss >> firstName >> lastName >> id;
                    return id == idToRemove;
                }),
                lines.end());

            // 3. Append the updated account information.
            std::ofstream outFile("imgui/BankData.txt"); // Open in write mode, which overwrites

            // Break the full name back into first and last names
            std::istringstream iss(accountName);
            std::string firstName, lastName;
            iss >> firstName >> lastName;

            int id = acc->getId();
            acc->deposit(amount);
            double updatedBalance = acc->getAccountBalance();

            outFile << firstName << " " << lastName << " "
                << id << " "
                << accountNumber << " "
                << updatedBalance << std::endl;

            // 4. Write all the remaining lines back to the file.
            for (const auto& remainingLine : lines) {
                outFile << remainingLine << std::endl;
            }

            outFile.close();

            found = true;
            std::cout << "\nAmount deposited into account" << std::endl;
            std::cout << "Press Enter to continue..." << std::endl;
            std::cin.ignore();
            std::cin.get();
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

    if (id < 100000 || id > 999999) { // Ensure ID is a 6-digit number
        std::cout << "Error: ID must be a 6-digit number.\n";
        return;
    }

    // Input and validation for account number
    std::cout << "Enter New Account Number: ";
    std::cin >> accountNumber;

    if (accountNumber < 1000 || accountNumber > 9999) { // Ensure account number is a 4-digit number
        std::cout << "Error: Account number must be a 4-digit number.\n";
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
// Function to remove an account
void Bank::removeAccount(const int id) {
    bool accountFound = false;

    // Remove from vector
    auto it = std::remove_if(accountsVector.begin(), accountsVector.end(),
        [&id, &accountFound](const std::shared_ptr<BankAccount>& account) {
            if (account->getId() == id) {
                accountFound = true;
                return true;
            }
            return false;
        });
    accountsVector.erase(it, accountsVector.end());

    if (!accountFound) {
        std::cout << "Account ID " << id << " not found in memory.\n";
    }

    // Open the file for reading and writing
    std::ifstream inFile("imgui/BankData.txt");
    std::ofstream outFile("imgui/BankData_temp.txt", std::ios::trunc);

    if (!inFile.is_open() || !outFile.is_open()) {
        std::cerr << "Error opening file for reading or writing.\n";
        return;
    }

    std::string line;
    while (std::getline(inFile, line)) {
        std::istringstream iss(line);

        std::string firstName, lastName, accountNumber;
        int currentId;
        double balance;

        // Parse the line
        if (iss >> firstName >> lastName >> currentId >> accountNumber >> balance) {
            // Only write to temp file if the current ID doesn't match the one to be removed
            if (currentId != id) {
                outFile << line << "\n";
            }
            else {
                // Account found and removed (skip writing this line)
                accountFound = true;
            }
        }
        else {
            // If there's an error parsing the line, preserve it (optional)
            outFile << line << "\n";
        }
    }

    inFile.close();
    outFile.close();

    // Replace old file with the new one
    if (std::remove("imgui/BankData.txt") != 0 || std::rename("imgui/BankData_temp.txt", "imgui/BankData.txt") != 0) {
        std::cerr << "Error replacing the old file.\n";
    }
    else if (accountFound) {
        std::cout << "Account ID " << id << " removed successfully.\n";
    }
}


// sort accounts
void Bank::sort(std::vector<std::shared_ptr<BankAccount>> &accountsVector){
}