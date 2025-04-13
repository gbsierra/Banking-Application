// *********************************************
// Date: 4/11/2025
// Description:
//   Practice with object oriented design
// *********************************************
#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <memory>
#include <cstdlib> //for exit
#include "BankAccount.h"

// Bank Class Header ( Simulates a Bank, storing Bank Accounts in a vector. Provides an API for customer interaction via ATM like functions )
class Bank{
private:
  std::shared_ptr<BankAccount> bptr; // consider deleting
  std::vector<std::shared_ptr<BankAccount>> accountsVector;

public:
  Bank(std::string filename);	     // constructor that reads from .txt file by calling the fillVector method to populate the database
  void withdraw();                                                      // withdraw amount
  void viewBalance();                                                   // check balance
  void deposit();                                                       // deposit amount
  void fillVector (std::ifstream &input);								// helper function
  std::string printVector();											// admin function print all accounts
  std::string printDeposits();											// admin function print all deposits
  std::string printWithdrawals();										// admin function print all withdrawals
  void addAccount();													// admin function add account
  void removeAccount(const int id);										// function remove account
  std::string sort();													// sort accounts
};