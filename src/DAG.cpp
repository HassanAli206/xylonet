#include "DAG.h"
#include <stdexcept>

std::shared_ptr<Transaction> DAG::createTransaction(const std::string& id, const std::string& sender,
    const std::string& receiver, double amount, double fee, const std::string& signature,
    const std::string& parentId) {

    std::vector<std::shared_ptr<Transaction>> parentRefs;
    if (!parentId.empty()) {
        auto parentTxn = getTransactionById(parentId);  // Will throw an exception if parentId is not found.
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

double DAG::calculateBalance(const std::string& userId) const {
    double balance = 0.0;

    for (const auto& [txnId, txn] : transactions) {
        if (txn->getSender() == userId) {
            balance -= txn->getAmount();
        }
        else if (txn->getReceiver() == userId) {
            balance += txn->getAmount();
        }
    }

    return balance;
}

std::vector<std::shared_ptr<Transaction>> DAG::getAncestry(const std::shared_ptr<Transaction>& txn) const {
    std::vector<std::shared_ptr<Transaction>> ancestry;

    for (const auto& parent : txn->getParentReferences()) {
        ancestry.push_back(parent);
        auto parentAncestry = getAncestry(parent);
        ancestry.insert(ancestry.end(), parentAncestry.begin(), parentAncestry.end());
    }

    return ancestry;
}

std::vector<std::shared_ptr<Transaction>> DAG::getDescendants(const std::shared_ptr<Transaction>& txn) const {
    std::vector<std::shared_ptr<Transaction>> descendants;

    for (const auto& [txnId, candidateTxn] : transactions) {
        for (const auto& parent : candidateTxn->getParentReferences()) {
            if (parent->getId() == txn->getId()) {
                descendants.push_back(candidateTxn);
                auto childDescendants = getDescendants(candidateTxn);
                descendants.insert(descendants.end(), childDescendants.begin(), childDescendants.end());
            }
        }
    }

    return descendants;
}

// New method to add funds to a user’s wallet (updates the user's balance)
void DAG::addFundsToUser(const std::string& userId, double amount) {
    if (amount <= 0) {
        throw std::invalid_argument("Amount to deposit must be positive.");
    }

    // Create a deposit transaction (without a fee)
    std::string txnId = "deposit" + std::to_string(std::time(nullptr)); // Unique transaction ID
    auto txn = createTransaction(txnId, "", userId, amount, 0.0, "", "");

    // You can implement further logic here (e.g., adding a deposit record or logging)
}

// New method to subtract funds from a user’s wallet (checks for sufficient balance)
bool DAG::subtractFundsFromUser(const std::string& userId, double amount) {
    if (amount <= 0) {
        throw std::invalid_argument("Amount to withdraw must be positive.");
    }

    // Check if the user has sufficient funds
    double currentBalance = calculateBalance(userId);
    if (currentBalance < amount) {
        throw std::invalid_argument("Insufficient funds for withdrawal.");
    }

    // Create a withdrawal transaction (with a fee, if needed)
    std::string txnId = "withdraw" + std::to_string(std::time(nullptr)); // Unique transaction ID
    auto txn = createTransaction(txnId, userId, "", amount, 0.0, "", "");

    // You can implement further logic here (e.g., logging withdrawal)
    return true;
}
