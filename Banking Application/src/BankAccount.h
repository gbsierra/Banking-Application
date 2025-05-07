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
    char accountType;

public:
    // -- Constructors -- 
    BankAccount();                                                                                             // default constructor
    BankAccount(std::string accountName, int id, int accountNumber, double accountBalance, char accountType);  // custom constructor
    /*copy constructor
    BankAccount(BankAccount& other); */
    

    // -- Accessors -- 
    std::string getAccountName() const;         // display account name
    int getAccountNumber() const;               // display account number
    double getAccountBalance() const;           // display account balance
    int getId() const;                          // get account ID
    char getAccountType() const;                // display account type

    
    // -- Mutators --
    void setAccountBalance(double accountBalance);  // set account balance


    virtual std::string toString() const;           // display the string representation of the bank account
    virtual bool withdraw(double amount);           // withdraw the amount if possible
    virtual void deposit(double amount);            // deposit amount and include rewards if any
    int getCount();                                 // display the number of existing bank accounts
    bool equals(BankAccount other) const;           // check if duplicate account exists

    //helper methods
    virtual void addReward(double amount);          // add reward
    std::string fixPoint(std::string number) const{
        int i = number.find('.');
        return number.substr(0, i + 3);
    }

};
