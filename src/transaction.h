#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <ctime>
#include <vector>
#include <memory>

class Transaction {
private:
    std::string id;
    std::string sender;
    std::string receiver;
    double amount;
    double fee;
    std::time_t timestamp;
    std::string signature;
    std::vector<std::shared_ptr<Transaction>> parentReferences;
    bool isValidated;

public:
    Transaction() : id(""), sender(""), receiver(""), amount(0.0), fee(0.0),
        timestamp(0), signature(""), isValidated(false) {
    }

    Transaction(const std::string& id, const std::string& sender, const std::string& receiver, double amount, double fee,
        std::time_t timestamp, const std::string& signature, const std::vector<std::shared_ptr<Transaction>>& parentReferences = {});

    void print() const;

    std::string getId() const;
    std::string getSender() const;
    std::string getReceiver() const;
    double getAmount() const;
    double getFee() const;
    std::time_t getTimestamp() const;
    std::vector<std::shared_ptr<Transaction>> getParentReferences() const;
    bool getValidationStatus() const;

    void validate();

    void invalidate();
};

#endif // TRANSACTION_H
