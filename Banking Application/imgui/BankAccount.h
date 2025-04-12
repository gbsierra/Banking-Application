// *********************************************
// Date: 4/11/2025
// Description:
//   Practice with object oriented design
// *********************************************
#pragma once
#include <string>
#include <iostream>

// BankAccount Class Header
class BankAccount {
public:
    static int count;   // count of how many bank account objects are created
    const static double MIN_BALANCE;
    const static double REWARD_RATE;
    const static double MIN_REWARD_AMOUNT;

private:
    int accountNumber, id;
    std::string accountName;
    double accountBalance;

public:
    // -- Constructors -- 
    BankAccount();                                                                              // default constructor
    BankAccount(std::string accountName, int id, int accountNumber, double accountBalance);     // custom constructor
    /*copy constructor
    BankAccount(BankAccount& other); */
    

    // -- Accessors -- 
    std::string getAccountName() const;  // display account name
    int getAccountNumber() const;        // display account number
    double getAccountBalance() const;    // display account balance
    
    // -- Mutators -- ,cannot change number and accountName, balance may be needed by admin
    void setAccountBalance(double accountBalance);


    std::string toString() const;             // display the string representation of the bank account
    bool withdraw(double amount);       //withdraw the amount if possible
    int getCount();                     // display the number of existing bank accounts
    void deposit(double amount);        // deposit amount and include rewards if any
    bool equals(BankAccount other) const;     // check if duplicate account exists

private:
    void addReward(double amount);      // private helper functions to add reward and
    int getId() const;                        // get account ID

};
