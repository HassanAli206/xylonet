#include <iostream>
#include "src/Transaction.h"
#include "src/User.h"
#include "src/Network.h"

using namespace std;

int main() {
    // Initialize network
    Network network;

    // Predefine users
    vector<User> predefinedUsers = {
        User("HassanAli", "password1", "hassan@example.com", 1000.0),
        User("MudasirShah", "password2", "mudasir@example.com", 1500.0),
        User("RabbiaJamil", "password3", "rabbia@example.com", 2000.0),
        User("User4", "password4", "user4@example.com", 800.0),
        User("User5", "password5", "user5@example.com", 900.0),
        User("User6", "password6", "user6@example.com", 1100.0),
        User("User7", "password7", "user7@example.com", 700.0),
        User("User8", "password8", "user8@example.com", 600.0),
        User("User9", "password9", "user9@example.com", 1000.0),
        User("User10", "password10", "user10@example.com", 1200.0)
    };

    // Add predefined users to the network
    for (const auto& user : predefinedUsers) {
        network.addUser(user);
    }

    // Show users in the network
    cout << "Welcome to the Xylonet Transaction System!" << endl;
    cout << "Here are the users currently in the network:" << endl;
    network.listUsers();

    // Prompt for login
    string username, password;
    cout << "\nPlease log in to continue." << endl;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    // Validate login
    if (network.loginUser(username, password)) {
        cout << "\nLogin successful!" << endl;

        // Display user information
        User* loggedInUser = network.getUser(username);
        cout << "Looking for user: " << username << endl;
        if (loggedInUser) {
            cout << "User found: " << loggedInUser->getUsername() << endl;
            cout << "Welcome, " << loggedInUser->getUsername() << "!" << endl;
            cout << "Email: " << loggedInUser->getEmail() << endl;
            cout << "Wallet Balance: " << loggedInUser->getWalletBalance() << " units." << endl;

            // Debugging message to verify the loop
            cout << "Entering menu loop..." << endl;

            // Allow user to perform tasks
            char choice;
            do {
                cout << "\nAvailable actions:" << endl;
                cout << "1. Send a transaction" << endl;
                cout << "2. View wallet balance" << endl;
                cout << "3. Logout" << endl;
                cout << "Enter your choice: ";
                cin >> choice;

                switch (choice) {
                case '1': {
                    // Send a transaction
                    string recipientUsername;
                    double amount;

                    cout << "Enter the username of the recipient: ";
                    cin >> recipientUsername;
                    cout << "Enter the amount to transfer: ";
                    cin >> amount;

                    if (network.transferFunds(loggedInUser->getUsername(), recipientUsername, amount)) {
                        cout << "Transaction successful!" << endl;
                    }
                    else {
                        cout << "Transaction failed!" << endl;
                    }

                    break;
                }
                case '2':
                    // Display wallet balance
                    cout << "Your current wallet balance is: " << loggedInUser->getWalletBalance() << " units." << endl;
                    break;
                case '3':
                    // Logout
                    cout << "Logging out..." << endl;
                    break;
                default:
                    cout << "Invalid choice! Please try again." << endl;
                    break;
                }
            } while (choice != '3');
        }
        else {
            cout << "User not found!" << endl;
        }
    }
    else {
        cout << "\nLogin failed! Please check your credentials and try again." << endl;
    }

    return 0;
}
