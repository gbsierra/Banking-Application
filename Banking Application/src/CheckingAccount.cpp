// *********************************************
// Date: 4/11/2025
// Description:
//   Practice with object oriented design
// *********************************************
#include "CheckingAccount.h"
//#include "Helper.h"
#include<iostream>

CheckingAccount::CheckingAccount() : BankAccount() {
}
CheckingAccount::CheckingAccount(std::string accountName, int id, int accountNumber, double accountBalance, char accountType) : BankAccount(accountName, id, accountNumber, accountBalance, accountType) {
};
std::string CheckingAccount::toString() const{
    return  "Account Name: " + getAccountName() + "\n" +
        "Account Number: " + std::to_string(getAccountNumber()) + "\n" +
        "Account Balance: " + fixPoint(std::to_string(getAccountBalance())) + "\n" +
        "Account Type: Checking \n";
}
bool CheckingAccount::withdraw(double amount) {  //overrides useraccount method to permit any number of withdrawals, keeping the miminum balance.
    int temp = getAccountBalance() - amount;
    if (temp > MIN_BALANCE) {
        setAccountBalance(temp);
        return true;
    }
    return false;
}
void CheckingAccount::deposit(double amount) {
    // if amount not negative, deposit
    if (amount > 0) {
        setAccountBalance(getAccountBalance() + amount);
    }
}
const double CheckingAccount::MIN_BALANCE_CHECKING = 99.99;