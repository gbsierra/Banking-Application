// *********************************************
// Date: 4/11/2025
// Description:
//   Practice with object oriented design
// *********************************************
#pragma once
#include "BankAccount.h" 

// SavingsAccount Class - Inherits UserAccount
class SavingsAccount : public BankAccount {
	//const static double MIN_BALANCE;
public:
	SavingsAccount();
	SavingsAccount(std::string accountName, int id, int accountNumber, double accountBalance, char accountType);
	std::string toString() const override;
	bool withdraw(double amount) override;
	void deposit(double amount) override;
	//virtual bool operator==(shared_ptr<SavingsAccount> a );
};