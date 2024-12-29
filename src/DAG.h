#ifndef DAG_H
#define DAG_H

#include <vector>
#include <memory>
#include <map>
#include <stdexcept>
#include <unordered_set>

#include "Transaction.h"

class DAG {
private:
    std::map<std::string, std::shared_ptr<Transaction>> transactions;

    bool isCyclic(const std::shared_ptr<Transaction>& txn, const std::shared_ptr<Transaction>& parentTxn,
        std::unordered_set<std::string> visited);

public:
    std::shared_ptr<Transaction> createTransaction(const std::string& id, const std::string& sender,
        const std::string& receiver, double amount, double fee, const std::string& signature,
        const std::string& parentId = "");

    const std::map<std::string, std::shared_ptr<Transaction>>& getTransactions() const;

    std::shared_ptr<Transaction> getTransactionById(const std::string& id) const;

    void addTransaction(const std::shared_ptr<Transaction>& txn);
};

#endif // DAG_H
