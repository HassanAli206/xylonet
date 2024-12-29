#include "Transaction.h"
#include <iostream>
#include <iomanip> 
#include <time.h>

Transaction::Transaction(const std::string& id, const std::string& sender, const std::string& receiver,
    double amount, double fee, std::time_t timestamp, const std::string& signature,
    const std::vector<std::shared_ptr<Transaction>>& parentReferences)
    : id(id), sender(sender), receiver(receiver), amount(amount), fee(fee),
    timestamp(timestamp), signature(signature), parentReferences(parentReferences), isValidated(false) {
}

void Transaction::print() const {
    std::cout << "Transaction ID: " << id << "\n";
    std::cout << "Sender: " << sender << "\n";
    std::cout << "Receiver: " << receiver << "\n";
    std::cout << "Amount: " << amount << "\n";
    std::cout << "Fee: " << fee << "\n";

    std::tm tm;
    localtime_s(&tm, &timestamp);
    std::cout << "Timestamp: " << std::put_time(&tm, "%Y-%m-%d %H:%M:%S") << "\n";

    std::cout << "Signature: " << signature << "\n";

    if (!parentReferences.empty()) {
        std::cout << "Parent Transaction IDs: ";
        for (const auto& parent : parentReferences) {
            std::cout << parent->getId() << " ";
        }
        std::cout << "\n";
    }

    std::cout << "\n";
}

// Getters
std::string Transaction::getId() const { return id; }
std::string Transaction::getSender() const { return sender; }
std::string Transaction::getReceiver() const { return receiver; }
double Transaction::getAmount() const { return amount; }
double Transaction::getFee() const { return fee; }
std::time_t Transaction::getTimestamp() const { return timestamp; }

std::vector<std::shared_ptr<Transaction>> Transaction::getParentReferences() const {
    return parentReferences;
}

bool Transaction::getValidationStatus() const { return isValidated; }

void Transaction::validate() {
    isValidated = true;
}

void Transaction::invalidate() {
    isValidated = false;
}
