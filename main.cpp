#include <iostream>
#include "src/Transaction.h"
#include "src/User.h"
#include "src/Network.h"  // Assuming Network is a class for managing users
#include "src/xylonet.h"
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

        // Get logged-in user
        User* loggedInUser = network.getUser(username);
        cout << "Looking for user: " << username << endl;
        if (loggedInUser) {
            cout << "User found: " << loggedInUser->getUsername() << endl;
            cout << "Welcome, " << loggedInUser->getUsername() << "!" << endl;
            cout << "Email: " << loggedInUser->getEmail() << endl;
            cout << "Wallet Balance: " << loggedInUser->getWalletBalance() << " units." << endl;

            // Now we call the modified createTransactionExample
            createTransactionExample(*loggedInUser, network);
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
