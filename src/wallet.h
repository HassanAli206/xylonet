#ifndef WALLET_H
#define WALLET_H

#include <string>
#include <memory>
#include "DAG.h"

class Wallet {
private:
    std::string userId;
    DAG& dag;  // Reference to DAG object for transaction management

public:
    // Constructor to initialize Wallet with userId and DAG reference
    Wallet(const std::string& userId, DAG& dag);

    // Get the current balance of the wallet
    double getBalance() const;

    // View the transaction history for this wallet
    void viewTransactionHistory() const;

    // Transfer funds to another wallet
    void transferFunds(Wallet& recipient, double amount, const std::string& senderUsername, const std::string& recipientUsername);

    // Deposit funds to this wallet
    void deposit(double amount);

    // Withdraw funds from this wallet
    bool withdraw(double amount);
};

#endif // WALLET_H
