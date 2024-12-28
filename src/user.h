#ifndef USER_H
#define USER_H

#include <iostream>
#include <algorithm>  // For transform function

#include <string>
#include "Wallet.h"  // Include the Wallet class

using namespace std;

// User class to handle user-related functionality
class User {
private:
    string username;
    string password;
    string email;
    Wallet wallet;  // Each user has an associated wallet

public:
    // Constructor with initial wallet balance
    User(string username, string password, string email, double initialBalance = 0.0)
        : username(username), password(password), email(email), wallet(initialBalance) {
    }

    // Getters for user details
    string getUsername() const {
        return username;
    }

    string getEmail() const {
        return email;
    }

    double getWalletBalance() const {
        return wallet.getBalance();
    }

    // Function to display user information
    void displayUserInfo() const {
        cout << "Username: " << username << endl;
        cout << "Email: " << email << endl;
        cout << "Wallet Balance: " << wallet.getBalance() << endl;
    }

    // Function to validate user's login credentials

    bool validateLogin(const string& inputUsername, const string& inputPassword) const {
        // Copy the stored values to temporary variables for case-insensitive comparison
        string storedUsername = username;  // This is the const member
        string storedPassword = password;  // This is the const member

        // Convert both to lowercase for case-insensitive comparison
        transform(storedUsername.begin(), storedUsername.end(), storedUsername.begin(), ::tolower);
        string lowerInputUsername = inputUsername;
        transform(lowerInputUsername.begin(), lowerInputUsername.end(), lowerInputUsername.begin(), ::tolower);

        transform(storedPassword.begin(), storedPassword.end(), storedPassword.begin(), ::tolower);
        string lowerInputPassword = inputPassword;
        transform(lowerInputPassword.begin(), lowerInputPassword.end(), lowerInputPassword.begin(), ::tolower);

        // Compare the lowercase versions
        return (storedUsername == lowerInputUsername && storedPassword == lowerInputPassword);
    }

    // Wallet functionalities
    Wallet& getWallet() {
        return wallet;  // Provide access to the wallet for transactions
    }

    // Function to deposit funds into the user's wallet
    void depositToWallet(double amount) {
        wallet.addFunds(amount);
        cout << "Successfully deposited " << amount << " to wallet." << endl;
    }

    // Function to withdraw funds from the user's wallet
    bool withdrawFromWallet(double amount) {
        if (wallet.deductFunds(amount)) {
            cout << "Successfully withdrew " << amount << " from wallet." << endl;
            return true;
        }
        else {
            cout << "Insufficient funds for withdrawal!" << endl;
            return false;
        }
    }

    // Function to view transaction history
    void viewWalletTransactions() const {
        cout << "Transaction History for " << username << ":" << endl;
        wallet.viewTransactionHistory();
    }
};

#endif
