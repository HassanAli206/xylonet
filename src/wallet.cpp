#include "Wallet.h"
#include <stdexcept>
#include <iostream>

Wallet::Wallet(double initialBalance) : balance(initialBalance) {}

double Wallet::getBalance() const {
    return balance;
}

void Wallet::deposit(double amount) {
    if (amount <= 0) throw std::invalid_argument("Deposit amount must be positive.");
    balance += amount;
}

void Wallet::withdraw(double amount) {
    if (amount <= 0 || amount > balance) throw std::invalid_argument("Invalid withdrawal amount.");
    balance -= amount;
}

void Wallet::addFunds(double amount) {
    if (amount <= 0) throw std::invalid_argument("Amount to add must be positive.");
    balance += amount;
}

bool Wallet::deductFunds(double amount) {
    if (amount <= 0 || amount > balance) {
        return false;
    }
    balance -= amount;
    return true;
}

bool Wallet::transferFunds(Wallet& recipient, double amount, const std::string& senderUsername, const std::string& recipientUsername) {
    auto txn = std::make_shared<Transaction>(/* required parameters */);
    withdraw(amount);
    recipient.deposit(amount);
    recordTransaction(txn);
    recipient.recordTransaction(txn);
    return true;
}

void Wallet::recordTransaction(const std::shared_ptr<Transaction>& txn) {
    transactionHistory.push_back(txn);
}

const std::vector<std::shared_ptr<Transaction>>& Wallet::getTransactionHistory() const {
    return transactionHistory;
}

void Wallet::viewTransactionHistory() const {
    if (transactionHistory.empty()) {
        std::cout << "No transactions found." << std::endl;
        return;
    }
    std::cout << "Transaction History:" << std::endl;
    for (const auto& txn : transactionHistory) {
        txn->print();
    }
}
