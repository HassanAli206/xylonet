#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
#include "Wallet.h"

using namespace std;

class User {
private:
    std::string username;
    std::string password;
    std::string email;
    Wallet wallet;

public:
    // Constructor
    User(const std::string& username, const std::string& password, const std::string& email, double initialBalance, DAG& dag);

    // Getter methods
    Wallet& getWallet();
    std::string getUsername() const;
    std::string getEmail() const;
    double getWalletBalance() const;

    // Method to display user info
    void displayUserInfo() const;

    // Method to validate login credentials
    bool validateLogin(const std::string& inputUsername, const std::string& inputPassword) const;

    // Methods for wallet operations
    void depositToWallet(double amount);
    bool withdrawFromWallet(double amount);

    // Method to list wallet transactions
    void listTransactions() const;
};

#endif // USER_H
