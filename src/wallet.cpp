#include "wallet.h"
#include <iostream>
#include <stdexcept>
#include <ctime>  // For generating unique transaction IDs

// Constructor that initializes Wallet with userId and DAG reference
Wallet::Wallet(const std::string& userId, DAG& dag)
    : userId(userId), dag(dag) {
}

double Wallet::getBalance() const {
    return dag.calculateBalance(userId);  // Assuming this method calculates the current balance for the user
}

void Wallet::viewTransactionHistory() const {
    auto transactions = dag.getTransactions();  // Get all transactions from DAG
    std::cout << "Transaction History for User: " << userId << "\n";
    for (const auto& txn : transactions) {
        if (txn.second->getSender() == userId || txn.second->getReceiver() == userId) {
            txn.second->print();  // Print transaction details
        }
    }
}


void Wallet::transferFunds(Wallet& recipient, double amount, const std::string& senderUsername, const std::string& recipientUsername) {
    if (amount <= 0) {
        throw std::invalid_argument("Transfer amount must be positive.");
    }

    if (getBalance() < amount) {
        throw std::invalid_argument("Insufficient funds for transfer.");
    }

    std::string txnId = "txn" + std::to_string(std::time(nullptr));  // Create a unique transaction ID based on time
    dag.createTransaction(txnId, senderUsername, recipientUsername, amount, 0.0, "signature", "");  // Create the transaction in the DAG
}

// Deposit funds to this wallet (for this example, it's a direct deposit without using transactions)
void Wallet::deposit(double amount) {
    if (amount <= 0) {
        throw std::invalid_argument("Deposit amount must be positive.");
    }
    // Assuming you can directly add funds to the user's balance in DAG (this is for simplicity)
    dag.addFundsToUser(userId, amount);
    std::cout << "Successfully deposited " << amount << " to wallet." << std::endl;
}

// Withdraw funds from this wallet (checks balance and modifies DAG accordingly)
bool Wallet::withdraw(double amount) {
    if (amount <= 0) {
        throw std::invalid_argument("Withdrawal amount must be positive.");
    }

    if (getBalance() < amount) {
        std::cout << "Insufficient funds for withdrawal." << std::endl;
        return false;  // Insufficient funds
    }

    // Assuming you can reduce funds for the user in the DAG (this is for simplicity)
    dag.subtractFundsFromUser(userId, amount);
    std::cout << "Successfully withdrew " << amount << " from wallet." << std::endl;
    return true;
}
