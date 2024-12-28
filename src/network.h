#ifndef NETWORK_H
#define NETWORK_H

#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>
#include "User.h"

using namespace std;

class Network {
private:
    vector<User> users;  // Store user objects
    unordered_map<string, User*> userMap;  // Map for quick user access
    unordered_map<string, vector<string>> connections;  // Adjacency list for connections

public:
    // Add a user to the network and connect them to all existing users
    void addUser(const User& user) {
        cout << "Adding user: " << user.getUsername() << endl;
        string username = user.getUsername();

        // Add user to the users list and initialize connections
        users.push_back(user);
        connections[username] = {};  // Initialize empty connections

        // Connect this user to all existing users without printing connection messages
        for (const auto& existingUser : users) {
            string existingUsername = existingUser.getUsername();
            if (existingUsername != username) {
                connections[username].push_back(existingUsername);
                connections[existingUsername].push_back(username);
            }
        }
    }

    // List all users in the network
    void listUsers() const {
        cout << "Users in the Network:" << endl;
        for (const auto& user : users) {
            cout << user.getUsername() << endl;
        }
    }

    // Login user by username and password
    bool loginUser(const string& username, const string& password) {
        for (const auto& user : users) {
            if (user.getUsername() == username) {
                if (user.validateLogin(username, password)) {
                    return true;
                }
                else {
                    cout << "Password mismatch for user: " << username << endl;
                    return false;
                }
            }
        }
        cout << "Username not found!" << endl;
        return false;
    }

    // Send a message to a connected user
    void sendMessage(const string& fromUsername, const string& toUsername, const string& message) {
        if (connections[fromUsername].empty()) {
            cout << fromUsername << " has no connections to send messages!" << endl;
            return;
        }

        if (find(connections[fromUsername].begin(), connections[fromUsername].end(), toUsername) != connections[fromUsername].end()) {
            cout << fromUsername << " sent a message to " << toUsername << ": " << message << endl;
        }
        else {
            cout << "Users are not connected!" << endl;
        }
    }

    // Transfer funds between users
    bool transferFunds(const string& senderUsername, const string& recipientUsername, double amount) {
        User* sender = getUser(senderUsername);
        User* recipient = getUser(recipientUsername);

        if (!sender) {
            cout << "Sender not found in the network!" << endl;
            return false;
        }
        if (!recipient) {
            cout << "Recipient not found in the network!" << endl;
            return false;
        }

        if (sender->getWallet().transferFunds(recipient->getWallet(), amount, senderUsername, recipientUsername)) {
            cout << "Funds transferred successfully from " << senderUsername << " to " << recipientUsername << "!" << endl;
            return true;
        }
        else {
            cout << "Transfer failed!" << endl;
            return false;
        }
    }


    // Retrieve user object by username
    User* getUser(const string& username) {
        for (auto& user : users) {
            if (user.getUsername() == username) {
                return &user;  // Return the address of the user
            }
        }
        return nullptr;
    }
};

#endif
