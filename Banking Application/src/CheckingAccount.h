#pragma once
// *********************************************
// Date: 4/11/2025
// Description:
//   Practice with object oriented design
// *********************************************
#pragma once
#include "BankAccount.h"

// CheckingAccount Class - Inherits UserAccount
class CheckingAccount : public BankAccount {
public:
	const static double MIN_BALANCE_CHECKING;
public:
	CheckingAccount();
	CheckingAccount(std::string accountName, int id, int accountNumber, double accountBalance, char accountType);
	std::string toString() const override;
	bool withdraw(double amount) override;
	void deposit(double amount) override;
	// virtual bool operator==(shared_ptr<CheckingAccount> a );
};