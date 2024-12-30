#include <iostream>
#include <limits>
#include "src/Transaction.h"
#include "src/User.h"
#include "src/network.h"  // Assuming Network is a class for managing users
#include "src/xylonet.h"

using namespace std;

// Helper function to display the main menu for logged-in users
void displayMainMenu(const User& user) {
    cout << "\n\t\t=============================================" << endl;
    cout << "\t\t Welcome, " << user.getUsername() << "!" << endl;
    cout << "\t\t=============================================" << endl;
    cout << "Email: " << user.getEmail() << endl;
    cout << "Wallet Balance: " << user.getWalletBalance() << " units." << endl;

    cout << "\n\t\t=============================================" << endl;
    cout << "\t\t Please choose an action:" << endl;
    cout << "\t\t 1. Transfer Money" << endl;
    cout << "\t\t 2. View Previous Transactions" << endl;
    cout << "\t\t 3. Logout" << endl;
    cout << "\t\t 4. Exit" << endl;
    cout << "\t\t=============================================" << endl;
}

// Helper function to handle login
bool login(Network& network, User*& loggedInUser) {
    string username, password;
    int loginAttempts = 0;

    while (loginAttempts < 3) {
        cout << "\nEnter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;

        if (network.loginUser(username, password)) {
            loggedInUser = network.getUser(username);
            return true;
        }
        else {
            cout << "\nInvalid credentials. Please try again.\n";
            loginAttempts++;
        }
    }

    cout << "\nToo many failed attempts. Please try again later.\n";
    return false;
}

// Helper function to create a new user account
void createAccount(Network& network, DAG& dag) {
    string username, password, email;
    double initialBalance;

    cout << "\n=== Create Account ===" << endl;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;
    cout << "Enter email: ";
    cin >> email;

    cout << "Enter initial balance: ";
    while (!(cin >> initialBalance) || initialBalance < 0) {
        cout << "Invalid balance. Please enter a positive value: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // Create a new User with DAG reference
    User newUser(username, password, email, initialBalance, dag);

    if (network.addUser(newUser)) {
        cout << "\nAccount created successfully! You can now log in.\n";
    }
    else {
        cout << "\nFailed to create account. Username might already exist.\n";
    }
}

// Main program logic
int main() {
    // Initialize DAG first, and then pass it to Network
    DAG dag;

    // Create Network object with the DAG instance passed to it
    Network network(dag);

    // Predefine users with the DAG reference
    vector<User> predefinedUsers = {
        User("HassanAli", "password1", "hassan@example.com", 1000.0, dag),
        User("MudasirShah", "password2", "mudasir@example.com", 1500.0, dag),
        User("RabbiaJamil", "password3", "rabbia@example.com", 2000.0, dag),
        User("User4", "password4", "user4@example.com", 800.0, dag),
        User("User5", "password5", "user5@example.com", 900.0, dag),
        User("User6", "password6", "user6@example.com", 1100.0, dag),
        User("User7", "password7", "user7@example.com", 700.0, dag),
        User("User8", "password8", "user8@example.com", 600.0, dag),
        User("User9", "password9", "user9@example.com", 1000.0, dag),
        User("User10", "password10", "user10@example.com", 1200.0, dag)
    };

    // Add predefined users to the network
    for (const auto& user : predefinedUsers) {
        network.addUser(user);
    }

    while (true) {
        // Show welcome screen
        cout << "\n\t\t=============================================" << endl;
        cout << "\t\t Welcome to the Xylonet Transaction System!" << endl;
        cout << "\t\t=============================================" << endl;

        cout << "\n\t\t=============================================" << endl;
        cout << "\t\t 1. Log In" << endl;
        cout << "\t\t 2. Create Account" << endl;
        cout << "\t\t 3. Exit" << endl;
        cout << "\t\t=============================================" << endl;

        int choice;
        cout << "Enter your choice: ";
        while (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        if (choice == 1) {
            User* loggedInUser = nullptr;
            if (login(network, loggedInUser)) {
                while (true) {
                    displayMainMenu(*loggedInUser);

                    int action;
                    cout << "Enter your choice: ";
                    while (!(cin >> action)) {
                        cout << "Invalid input. Please enter a number: ";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }

                    if (action == 1) {
                        // Call transfer function
                        createTransactionExample(*loggedInUser, network);
                    }
                    else if (action == 2) {
                        // Display previous transactions
                        cout << "\nPrevious Transactions:" << endl;
                        loggedInUser->listTransactions();
                    }
                    else if (action == 3) {
                        // Logout
                        cout << "\nLogging out..." << endl;
                        break;
                    }
                    else if (action == 4) {
                        // Exit the application
                        cout << "\nExiting the system. Goodbye!" << endl;
                        return 0;
                    }
                    else {
                        cout << "\nInvalid choice! Please try again." << endl;
                    }
                }
            }
        }
        else if (choice == 2) {
            // Create account
            createAccount(network, dag);
        }
        else if (choice == 3) {
            // Exit the application
            cout << "\nExiting the system. Goodbye!" << endl;
            break;
        }
        else {
            cout << "\nInvalid choice! Please try again." << endl;
        }
    }

    return 0;
}
