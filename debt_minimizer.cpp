#include "debt_minimizer.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cctype>

// Normalize string by converting to lowercase and trimming spaces
std::string DebtMinimizer::normalizeString(const std::string& str) {
    std::string result = str;
    
    // Remove leading and trailing spaces
    result.erase(0, result.find_first_not_of(" \t"));
    result.erase(result.find_last_not_of(" \t") + 1);
    
    // Convert to lowercase for case-insensitive comparison
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    
    return result;
}

// Add a new transaction to the system
void DebtMinimizer::addTransaction(const std::string& from, const std::string& to, int amount) {
    // Validate input
    if (amount <= 0) {
        std::cout << "Error: Amount must be positive!" << std::endl;
        return;
    }
    
    std::string normalizedFrom = normalizeString(from);
    std::string normalizedTo = normalizeString(to);
    
    if (normalizedFrom == normalizedTo) {
        std::cout << "Error: Cannot create transaction where sender and receiver are the same!" << std::endl;
        return;
    }
    
    if (normalizedFrom.empty() || normalizedTo.empty()) {
        std::cout << "Error: Names cannot be empty!" << std::endl;
        return;
    }
    
    transactions.emplace_back(normalizedFrom, normalizedTo, amount);
    std::cout << "Transaction added successfully!" << std::endl;
}

// Calculate net balance for each person
void DebtMinimizer::calculateNetBalances() {
    netBalances.clear();
    
    // Process all transactions to calculate net balances
    for (const auto& transaction : transactions) {
        // Debtor (from) has negative balance
        netBalances[transaction.from] -= transaction.amount;
        // Creditor (to) has positive balance
        netBalances[transaction.to] += transaction.amount;
    }
}

// Filter out zero balances and store non-zero balances
void DebtMinimizer::filterNonZeroBalances() {
    nonZeroBalances.clear();
    
    for (const auto& pair : netBalances) {
        if (pair.second != 0) {
            nonZeroBalances.emplace_back(pair.first, pair.second);
        }
    }
}

// Find the person with maximum credit (positive balance)
int DebtMinimizer::findMaxCreditor(const std::vector<NetBalance>& balances) {
    int maxIndex = -1;
    int maxAmount = 0;
    
    for (int i = 0; i < balances.size(); i++) {
        if (balances[i].balance > maxAmount) {
            maxAmount = balances[i].balance;
            maxIndex = i;
        }
    }
    
    return maxIndex;
}

// Find the person with maximum debit (most negative balance)
int DebtMinimizer::findMaxDebtor(const std::vector<NetBalance>& balances) {
    int maxIndex = -1;
    int maxDebt = 0;
    
    for (int i = 0; i < balances.size(); i++) {
        if (balances[i].balance < maxDebt) {
            maxDebt = balances[i].balance;
            maxIndex = i;
        }
    }
    
    return maxIndex;
}

// Recursive greedy algorithm to minimize debt transactions
void DebtMinimizer::minimizeDebt(std::vector<NetBalance>& balances) {
    // Base case: if all balances are zero, we're done
    bool allZero = true;
    for (const auto& balance : balances) {
        if (balance.balance != 0) {
            allZero = false;
            break;
        }
    }
    
    if (allZero) {
        return;
    }
    
    // Find maximum creditor and maximum debtor
    int creditorIndex = findMaxCreditor(balances);
    int debtorIndex = findMaxDebtor(balances);
    
    if (creditorIndex == -1 || debtorIndex == -1) {
        return;
    }
    
    // Calculate the minimum amount that can be settled
    int minAmount = std::min(balances[creditorIndex].balance, 
                            -balances[debtorIndex].balance);
    
    // Create a new minimized transaction
    minimizedTransactions.emplace_back(
        balances[debtorIndex].name,
        balances[creditorIndex].name,
        minAmount
    );
    
    // Update balances
    balances[creditorIndex].balance -= minAmount;
    balances[debtorIndex].balance += minAmount;
    
    // Recursive call to continue minimization
    minimizeDebt(balances);
}

// Main processing function that orchestrates the debt minimization
void DebtMinimizer::processTransactions() {
    if (transactions.empty()) {
        std::cout << "No transactions to process!" << std::endl;
        return;
    }
    
    minimizedTransactions.clear();
    
    // Step 1: Calculate net balances
    calculateNetBalances();
    
    // Step 2: Filter out zero balances
    filterNonZeroBalances();
    
    // Step 3: Apply debt minimization algorithm
    if (!nonZeroBalances.empty()) {
        minimizeDebt(nonZeroBalances);
    }
    
    std::cout << "Debt minimization completed!" << std::endl;
}

// Display original transactions
void DebtMinimizer::displayOriginalTransactions() const {
    if (transactions.empty()) {
        std::cout << "No transactions to display!" << std::endl;
        return;
    }
    
    std::cout << "\n=== ORIGINAL TRANSACTIONS ===" << std::endl;
    std::cout << std::setw(15) << "From" << std::setw(15) << "To" << std::setw(10) << "Amount" << std::endl;
    std::cout << std::string(40, '-') << std::endl;
    
    for (const auto& transaction : transactions) {
        std::cout << std::setw(15) << transaction.from 
                  << std::setw(15) << transaction.to 
                  << std::setw(10) << "₹" + std::to_string(transaction.amount) << std::endl;
    }
    std::cout << "Total original transactions: " << transactions.size() << std::endl;
}

// Display net balances
void DebtMinimizer::displayNetBalances() const {
    if (netBalances.empty()) {
        std::cout << "No net balances to display!" << std::endl;
        return;
    }
    
    std::cout << "\n=== NET BALANCES ===" << std::endl;
    std::cout << std::setw(15) << "Person" << std::setw(15) << "Net Balance" << std::setw(10) << "Status" << std::endl;
    std::cout << std::string(40, '-') << std::endl;
    
    for (const auto& pair : netBalances) {
        std::string status = (pair.second > 0) ? "Creditor" : 
                            (pair.second < 0) ? "Debtor" : "Settled";
        std::cout << std::setw(15) << pair.first 
                  << std::setw(15) << "" + std::to_string(pair.second)
                  << std::setw(10) << status << std::endl;
    }
}

// Display minimized transactions
void DebtMinimizer::displayMinimizedTransactions() const {
    std::cout << "\n=== MINIMIZED TRANSACTIONS ===" << std::endl;
    
    if (minimizedTransactions.empty()) {
        std::cout << "All debts are already settled! No transactions needed." << std::endl;
        return;
    }
    
    std::cout << std::setw(15) << "From" << std::setw(15) << "To" << std::setw(10) << "Amount" << std::endl;
    std::cout << std::string(40, '-') << std::endl;
    
    for (const auto& transaction : minimizedTransactions) {
        std::cout << transaction.from << " pays " << transaction.to 
                  << " ₹" << transaction.amount << std::endl;
    }
    
    std::cout << "\nTotal minimized transactions: " << minimizedTransactions.size() << std::endl;
    
    // Calculate reduction percentage
    if (!transactions.empty()) {
        double reductionPercent = ((double)(transactions.size() - minimizedTransactions.size()) / transactions.size()) * 100;
        std::cout << "Reduction achieved: " << std::fixed << std::setprecision(1) 
                  << reductionPercent << "%" << std::endl;
    }
}

// Get the count of minimized transactions
int DebtMinimizer::getMinimizedTransactionCount() const {
    return minimizedTransactions.size();
}

// Clear all data
void DebtMinimizer::clearData() {
    transactions.clear();
    netBalances.clear();
    nonZeroBalances.clear();
    minimizedTransactions.clear();
    std::cout << "All data cleared successfully!" << std::endl;
}

// Load transactions from file
bool DebtMinimizer::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error: Could not open file " << filename << std::endl;
        return false;
    }
    
    clearData();
    std::string line;
    int count = 0;
    
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string from, to;
        int amount;
        
        if (iss >> from >> to >> amount) {
            addTransaction(from, to, amount);
            count++;
        }
    }
    
    file.close();
    std::cout << "Loaded " << count << " transactions from " << filename << std::endl;
    return true;
}

// Save minimized transactions to file
bool DebtMinimizer::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error: Could not create file " << filename << std::endl;
        return false;
    }
    
    file << "=== MINIMIZED DEBT TRANSACTIONS ===" << std::endl;
    file << "Generated by Debt Minimizer Tool" << std::endl;
    file << std::string(40, '=') << std::endl;
    
    if (minimizedTransactions.empty()) {
        file << "All debts are settled! No transactions needed." << std::endl;
    } else {
        for (const auto& transaction : minimizedTransactions) {
            file << transaction.from << " pays " << transaction.to 
                 << transaction.amount << std::endl;
        }
        file << std::endl << "Total transactions: " << minimizedTransactions.size() << std::endl;
    }
    
    file.close();
    std::cout << "Results saved to " << filename << std::endl;
    return true;
}