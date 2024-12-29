#include <iostream>
#include "DAG.h"
#include "Transaction.h"
#include "User.h"
#include "Wallet.h"
#include "Network.h"
#include "xylonet.h"

// Function to simulate transaction creation for a logged-in user
void createTransactionExample(User& loggedInUser, Network& network) {
    try {
        // Show logged-in user information
        std::cout << "Logged in user: " << loggedInUser.getUsername() << "\n";
        std::cout << "Email: " << loggedInUser.getEmail() << "\n";
        std::cout << "Wallet Balance: " << loggedInUser.getWalletBalance() << " units.\n";

        // Get another user to interact with (for transaction purposes)
        std::string recipientUsername;
        std::cout << "Enter the recipient username: ";
        std::cin >> recipientUsername;

        User* recipient = network.getUser(recipientUsername);
        if (!recipient) {
            std::cout << "Recipient not found in the network!\n";
            return;
        }

        // Amount to transfer
        double amount;
        std::cout << "Enter the amount to transfer: ";
        std::cin >> amount;

        // Attempt to transfer funds
        Wallet& senderWallet = loggedInUser.getWallet();
        Wallet& recipientWallet = recipient->getWallet();

        if (senderWallet.transferFunds(recipientWallet, amount, loggedInUser.getUsername(), recipient->getUsername())) {
            std::cout << "Transaction successful!\n";

            // Create a new transaction and print it
            DAG transactionGraph;
            auto txn = transactionGraph.createTransaction("txn1", loggedInUser.getUsername(), recipient->getUsername(), amount, 0.5, "signature1");
            txn->print();
        }
        else {
            std::cout << "Transaction failed due to insufficient funds.\n";
        }

        // Display updated user info after transaction
        loggedInUser.displayUserInfo();
        recipient->displayUserInfo();

    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}
