#ifndef WALLET_H
#define WALLET_H

#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include "Transaction.h"  // Include the Transaction class

using namespace std;

// Wallet class to handle user's wallet and transactions
class Wallet {
private:
    double balance;  // Wallet balance
    vector<Transaction> transactionHistory;  // History of transactions

public:
    // Constructor to initialize balance with optional initial value
    Wallet(double initialBalance = 0.0) : balance(initialBalance) {}

    // Function to add funds to the wallet
    bool addFunds(double amount) {
        if (amount <= 0) {
            cout << "Amount must be positive!" << endl;
            return false;
        }
        balance += amount;
        transactionHistory.emplace_back(DEPOSIT, amount);  // Record the deposit transaction
        cout << "Successfully added " << amount << " to your wallet!" << endl;
        return true;
    }

    // Function to deduct funds from the wallet
    bool deductFunds(double amount) {
        if (amount <= 0) {
            cout << "Amount must be positive!" << endl;
            return false;
        }
        if (balance < amount) {
            cout << "Insufficient balance!" << endl;
            return false;
        }
        balance -= amount;
        transactionHistory.emplace_back(WITHDRAWAL, amount);  // Record the withdrawal transaction
        cout << "Successfully withdrew " << amount << " from your wallet!" << endl;
        return true;
    }

    // Function to transfer funds to another wallet
    bool transferFunds(Wallet& recipient, double amount, const string& senderUsername, const string& receiverUsername) {
        if (deductFunds(amount)) {
            recipient.addFunds(amount);
            transactionHistory.emplace_back(TRANSFER, amount, senderUsername, receiverUsername);  // Record the transfer
            cout << "Transferred " << amount << " to " << receiverUsername << " successfully!" << endl;
            return true;
        }
        return false;
    }

    // Function to view current wallet balance
    double getBalance() const {
        return balance;
    }

    // Function to view transaction history
    void viewTransactionHistory() const {
        if (transactionHistory.empty()) {
            cout << "No transactions yet." << endl;
            return;
        }
        cout << "Transaction History:" << endl;
        for (const auto& transaction : transactionHistory) {
            transaction.displayTransaction();
        }
    }
};

#endif
