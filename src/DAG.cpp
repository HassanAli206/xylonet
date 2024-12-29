#include "DAG.h"

std::shared_ptr<Transaction> DAG::createTransaction(const std::string& id, const std::string& sender,
    const std::string& receiver, double amount, double fee, const std::string& signature,
    const std::string& parentId) {

    std::vector<std::shared_ptr<Transaction>> parentRefs;
    if (!parentId.empty()) {
        auto parentTxn = getTransactionById(parentId);
        parentRefs.push_back(parentTxn);
    }

    auto txn = std::make_shared<Transaction>(id, sender, receiver, amount, fee, std::time(nullptr), signature, parentRefs);

    addTransaction(txn);

    return txn;
}

const std::map<std::string, std::shared_ptr<Transaction>>& DAG::getTransactions() const {
    return transactions;
}

std::shared_ptr<Transaction> DAG::getTransactionById(const std::string& id) const {
    auto it = transactions.find(id);
    if (it == transactions.end()) {
        throw std::invalid_argument("Transaction not found.");
    }
    return it->second;
}

void DAG::addTransaction(const std::shared_ptr<Transaction>& txn) {
    if (transactions.find(txn->getId()) != transactions.end()) {
        throw std::invalid_argument("Transaction already exists.");
    }

    for (const auto& parentTxn : txn->getParentReferences()) {
        if (transactions.find(parentTxn->getId()) == transactions.end()) {
            throw std::invalid_argument("Parent transaction not found.");
        }

        if (isCyclic(txn, parentTxn, {})) {
            throw std::invalid_argument("Cycle detected in the DAG.");
        }
    }

    transactions[txn->getId()] = txn;
}

bool DAG::isCyclic(const std::shared_ptr<Transaction>& txn, const std::shared_ptr<Transaction>& parentTxn,
    std::unordered_set<std::string> visited) {

    if (txn->getId() == parentTxn->getId()) {
        return true;
    }

    if (visited.find(parentTxn->getId()) != visited.end()) {
        return false;
    }

    visited.insert(parentTxn->getId());
    for (const auto& ref : parentTxn->getParentReferences()) {
        if (isCyclic(txn, ref, visited)) {
            return true;
        }
    }

    return false;
}
