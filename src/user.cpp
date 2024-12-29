#include "User.h"
#include <iostream>
#include <memory>
#include <algorithm>

User::User(const std::string& username, const std::string& password, const std::string& email, double initialBalance)
    : username(username), password(password), email(email), wallet(initialBalance) {
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

    std::transform(storedUsername.begin(), storedUsername.end(), storedUsername.begin(), ::tolower);
    std::string lowerInputUsername = inputUsername;
    std::transform(lowerInputUsername.begin(), lowerInputUsername.end(), lowerInputUsername.begin(), ::tolower);

    std::transform(storedPassword.begin(), storedPassword.end(), storedPassword.begin(), ::tolower);
    std::string lowerInputPassword = inputPassword;
    std::transform(lowerInputPassword.begin(), lowerInputPassword.end(), lowerInputPassword.begin(), ::tolower);

    return (storedUsername == lowerInputUsername && storedPassword == lowerInputPassword);
}

void User::depositToWallet(double amount) {
    wallet.addFunds(amount);
    std::cout << "Successfully deposited " << amount << " to wallet." << std::endl;
}

bool User::withdrawFromWallet(double amount) {
    if (wallet.deductFunds(amount)) {
        std::cout << "Successfully withdrew " << amount << " from wallet." << std::endl;
        return true;
    }
    else {
        std::cout << "Insufficient funds for withdrawal!" << std::endl;
        return false;
    }
}

void User::viewWalletTransactions() const {
    std::cout << "Transaction History for " << username << ":" << std::endl;
    wallet.viewTransactionHistory();
}
