# Xylonet

Xylonet is a C++ based Directed Acyclic Graph (DAG)-based system that simulates a decentralized transaction and wallet management system. It is designed as the core infrastructure for a blockchain-like application, providing the foundation for transaction creation, wallet management, and graph-based transaction validation. 

## Features

- **Transaction Creation**: Create transactions that are represented as nodes in the DAG.
- **Wallet Management**: Manage wallets, including the balance and transaction history.
- **Graph Construction**: Maintain the DAG structure where each transaction is linked to previous ones.
- **Transaction Validation**: Validate transactions through signature verification and checking wallet balances.
- **Double Spending Prevention**: Ensure no funds are spent multiple times.
- **Consensus Mechanism**: Implement a decentralized consensus for transaction validation.
- **Immutability**: Ensure the integrity and immutability of transactions once added to the DAG.
- **Data Persistence**: Store transaction data for future reference.

## Getting Started

Follow the instructions below to set up Xylonet on your local machine for development and testing.

### Prerequisites

- **C++ compiler** (e.g., `g++`)
- **CMake** (for building the project)

### Installing

1. **Clone the repository**:
   ```bash
   git clone https://github.com/yourusername/xylonet.git
   cd xylonet
