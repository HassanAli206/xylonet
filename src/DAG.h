#ifndef DAG_H
#define DAG_H

#include "Transaction.h"
#include <map>
#include <memory>
#include <string>
#include <vector>
#include <unordered_set>

class DAG {
private:
    std::map<std::string, std::shared_ptr<Transaction>> transactions;

    bool isCyclic(const std::shared_ptr<Transaction>& txn, const std::shared_ptr<Transaction>& parentTxn,
        std::unordered_set<std::string> visited);

public:
    // Create a new transaction and add it to the DAG
    std::shared_ptr<Transaction> createTransaction(const std::string& id, const std::string& sender,
        const std::string& receiver, double amount, double fee, const std::string& signature,
        const std::string& parentId);

    // Get all transactions in the DAG
    const std::map<std::string, std::shared_ptr<Transaction>>& getTransactions() const;

    // Get a specific transaction by its ID
    std::shared_ptr<Transaction> getTransactionById(const std::string& id) const;

    // Add a transaction to the DAG
    void addTransaction(const std::shared_ptr<Transaction>& txn);

    // Calculate the balance of a user based on transactions
    double calculateBalance(const std::string& userId) const;

    // Get the ancestry of a specific transaction (parent transactions)
    std::vector<std::shared_ptr<Transaction>> getAncestry(const std::shared_ptr<Transaction>& txn) const;

    // Get the descendants of a specific transaction (child transactions)
    std::vector<std::shared_ptr<Transaction>> getDescendants(const std::shared_ptr<Transaction>& txn) const;

    // Add funds to a user's wallet (creates a deposit transaction)
    void addFundsToUser(const std::string& userId, double amount);

    // Subtract funds from a user's wallet (creates a withdrawal transaction)
    bool subtractFundsFromUser(const std::string& userId, double amount);
};

#endif // DAG_H
