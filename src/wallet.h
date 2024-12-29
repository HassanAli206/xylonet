#ifndef WALLET_H
#define WALLET_H

#include <vector>
#include <memory>
#include <string>
#include "Transaction.h"

class Wallet {
private:
    double balance;
    std::vector<std::shared_ptr<Transaction>> transactionHistory;

public:
    Wallet(double initialBalance = 0.0);

    double getBalance() const;

    void deposit(double amount);
    void withdraw(double amount);
    void addFunds(double amount);
    bool deductFunds(double amount);

    bool transferFunds(Wallet& recipient, double amount, const std::string& senderUsername, const std::string& recipientUsername);
    void recordTransaction(const std::shared_ptr<Transaction>& txn);
    const std::vector<std::shared_ptr<Transaction>>& getTransactionHistory() const;
    void viewTransactionHistory() const;
};

#endif // WALLET_H
