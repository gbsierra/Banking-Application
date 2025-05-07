// *********************************************
// Date: 4/11/2025
// Description:
//   Practice with object oriented design
// *********************************************
#include "BankAccount.h"
#include <iomanip>
#include <sstream>


//static vars
const double BankAccount::MIN_BALANCE = 9.99;
const double BankAccount::REWARD_RATE = .04; // 4% reward rate
const double BankAccount::MIN_REWARD_AMOUNT = 1000; // 1000$ min deposit for reward rate
int BankAccount::count = 0;

// -- Constructors -- 
BankAccount::BankAccount(){
    accountName = "";
    accountNumber = 0;
    accountBalance = 0;
    id = 0;
    count++;
}
// custom constructor
BankAccount::BankAccount(std::string accountName, int id, int accountNumber, double accountBalance, char accountType){
    this->accountName = accountName;
    this->accountNumber = accountNumber;
    this->id = id;
    this->accountBalance = accountBalance;
    this->accountType = accountType;
    count++;
}
/* copy constructor
BankAccount::BankAccount(BankAccount& other){
    this->accountName = other.accountName;
    this->accountNumber = other.accountNumber;
    this->id = other.id;
    this->accountBalance = other.accountBalance;
}*/

// -- Accessors -- 
std::string BankAccount::getAccountName() const {
    return this->accountName;
}
// display account number
int BankAccount::getAccountNumber() const {
    return this->accountNumber;
}
// display account balance
double BankAccount::getAccountBalance() const {
    return this->accountBalance;
}
// get account ID
int BankAccount::getId() const {
    return this->id;
}
// get account type
char BankAccount::getAccountType() const{
    return this->accountType;
}
// -- Mutator -- cannot change number and accountName, setting balance may be needed by admin
void BankAccount::setAccountBalance(double accountBalance){
    this->accountBalance = accountBalance;
}


// display the string representation of the bank account
std::string BankAccount::toString() const{
    std::ostringstream stream;
    stream.imbue(std::locale("")); //add commas
    stream << std::fixed<< std::setprecision(2) << this->getAccountBalance();
    std::string bal = stream.str();
     return ("Account Name: " + this->getAccountName() + "\n"
               + "Account Number: " + std::to_string(this->getAccountNumber()) + "\n"
               + "Account Balance: " + bal + "$\n");
}
// withdraw the amount if possible
bool BankAccount::withdraw(double amount){
    if(this->accountBalance>amount){
        this->accountBalance = this->accountBalance-amount;
        return true;
    }
    return false;
}
// display the number of existing bank accounts
int BankAccount::getCount(){
    return this->count;
}
// deposit amount and include rewards if any
void BankAccount::deposit(double amount){
    if(amount>=MIN_REWARD_AMOUNT){
        addReward(amount);
    }
    this->accountBalance = this->accountBalance + amount;
}
// check if duplicate account exists
bool BankAccount::equals(BankAccount other) const{
    return (this->accountNumber==other.accountNumber && this->id == other.id);
}
// private helper functions to add reward and
void BankAccount::addReward(double amount){
    this->accountBalance = this->accountBalance + amount*REWARD_RATE;
}


          