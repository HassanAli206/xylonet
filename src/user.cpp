#include "Wallet.h"
#include "User.h"
#include <iostream>
#include <memory>
#include <algorithm>

User::User(const std::string& username, const std::string& password, const std::string& email, double initialBalance, DAG& dag)
    : username(username), password(password), email(email), wallet(username, dag) {
}

Wallet& User::getWallet() {
    return wallet;
}

std::string User::getUsername() const {
    return username;
}

std::string User::getEmail() const {
    return email;
}

double User::getWalletBalance() const {
    return wallet.getBalance();
}

void User::displayUserInfo() const {
    std::cout << "Username: " << username << std::endl;
    std::cout << "Email: " << email << std::endl;
    std::cout << "Wallet Balance: " << wallet.getBalance() << std::endl;
}

bool User::validateLogin(const std::string& inputUsername, const std::string& inputPassword) const {
    std::string storedUsername = username;
    std::string storedPassword = password;

    // Convert to lowercase to perform case-insensitive comparison
    std::transform(storedUsername.begin(), storedUsername.end(), storedUsername.begin(), ::tolower);
    std::string lowerInputUsername = inputUsername;
    std::transform(lowerInputUsername.begin(), lowerInputUsername.end(), lowerInputUsername.begin(), ::tolower);

    std::transform(storedPassword.begin(), storedPassword.end(), storedPassword.begin(), ::tolower);
    std::string lowerInputPassword = inputPassword;
    std::transform(lowerInputPassword.begin(), lowerInputPassword.end(), lowerInputPassword.begin(), ::tolower);

    return (storedUsername == lowerInputUsername && storedPassword == lowerInputPassword);
}

void User::depositToWallet(double amount) {
    try {
        wallet.deposit(amount); // Updated method to use deposit
        std::cout << "Successfully deposited " << amount << " to wallet." << std::endl;
    }
    catch (const std::invalid_argument& e) {
        std::cout << e.what() << std::endl;
    }
}

bool User::withdrawFromWallet(double amount) {
    if (wallet.withdraw(amount)) { // Updated method to use withdraw
        std::cout << "Successfully withdrew " << amount << " from wallet." << std::endl;
        return true;
    }
    else {
        std::cout << "Insufficient funds for withdrawal!" << std::endl;
        return false;
    }
}

// Renamed method to reflect its purpose more clearly
void User::listTransactions() const {
    std::cout << "Transaction History for " << username << ":" << std::endl;
    wallet.viewTransactionHistory(); // Assuming this method prints transaction details
}
