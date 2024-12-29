#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <iostream>
#include <string>
#include <vector>
#include <ctime>  // For timestamp functionality

using namespace std;

// Enum for transaction type
enum TransactionType {
    DEPOSIT,
    WITHDRAWAL,
    TRANSFER
};

// Class to represent a transaction
class Transaction {
private:
    TransactionType type;
    double amount;
    string sender;
    string receiver;
    time_t timestamp;

public:
    // Constructor for deposit and withdrawal (no sender/receiver needed)
    Transaction(TransactionType type, double amount, string sender = "", string receiver = "") {
        this->type = type;
        this->amount = amount;
        this->sender = sender;
        this->receiver = receiver;
        this->timestamp = time(nullptr);  // Get the current time as timestamp
    }

    // Function to display the transaction details
    void displayTransaction() const {
        cout << "Transaction Type: ";
        switch (type) {
        case DEPOSIT: cout << "Deposit"; break;
        case WITHDRAWAL: cout << "Withdrawal"; break;
        case TRANSFER: cout << "Transfer from " << sender << " to " << receiver; break;
        }
        cout << "\nAmount: " << amount << endl;
        cout << "Timestamp: " << ctime(&timestamp);  // Print the formatted date and time
    }

    // Getter functions
    TransactionType getType() const {
        return type;
    }

    double getAmount() const {
        return amount;
    }

    string getSender() const {
        return sender;
    }

    string getReceiver() const {
        return receiver;
    }

    time_t getTimestamp() const {
        return timestamp;
    }
};

// Class to handle all transactions
class TransactionManager {
private:
    vector<Transaction> transactions;  // List to store all transactions

public:
    // Function to add a transaction to the history
    void addTransaction(TransactionType type, double amount, string sender = "", string receiver = "") {
        Transaction newTransaction(type, amount, sender, receiver);
        transactions.push_back(newTransaction);
        cout << "Transaction added successfully!" << endl;
    }

    // Function to display all transactions in the history
    void viewTransactionHistory() const {
        if (transactions.empty()) {
            cout << "No transactions available!" << endl;
            return;
        }

        cout << "Transaction History:" << endl;
        for (const auto& transaction : transactions) {
            transaction.displayTransaction();
        }
    }

    // Function to validate a transaction (could be expanded for additional rules later)
    bool validateTransaction(double amount, double balance, TransactionType type) {
        if (type == WITHDRAWAL && amount > balance) {
            cout << "Insufficient balance!" << endl;
            return false;
        }
        if (amount <= 0) {
            cout << "Amount must be greater than zero!" << endl;
            return false;
        }
        return true;
    }
};

#endif
