// *********************************************
// Date: 4/11/2025
// Description:
//   Practice with object oriented design
// *********************************************
#include "SavingsAccount.h"
#include <iostream>

SavingsAccount::SavingsAccount() : BankAccount() {
}
SavingsAccount::SavingsAccount(std::string accountName, int id, int accountNumber, double accountBalance, char accountType) : BankAccount(accountName, id, accountNumber, accountBalance, accountType) {
    //regular constructor
}
std::string SavingsAccount::toString() const{
    return "Account Name: " + getAccountName() + "\n" +
        "Account Number: " + std::to_string(getAccountNumber()) + "\n" +
        "Account Balance: " + fixPoint(std::to_string(getAccountBalance())) + "\n" +
        "Account Type: Savings \n";
}
bool SavingsAccount::withdraw(double amount) {
    int temp = getAccountBalance() - amount;
    if (temp > MIN_BALANCE) {
        setAccountBalance(temp);
        return true;
    }
    return false;
}
void SavingsAccount::deposit(double amount) {
    // deposit
    setAccountBalance(getAccountBalance() + amount);
    // check if eligible for reward
    if (amount >= 1000) {
        addReward(amount);
    }
}