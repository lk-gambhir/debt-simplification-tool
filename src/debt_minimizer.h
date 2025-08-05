#ifndef DEBT_MINIMIZER_H
#define DEBT_MINIMIZER_H

#include <string>
#include <vector>
#include <map>
#include <iostream>

// Structure to represent a transaction
struct Transaction {
    std::string from;
    std::string to;
    int amount;
    
    Transaction(const std::string& f, const std::string& t, int amt) 
        : from(f), to(t), amount(amt) {}
};

// Structure to represent a person's net balance
struct NetBalance {
    std::string name;
    int balance;  // Positive = creditor, Negative = debtor
    
    NetBalance(const std::string& n, int b) : name(n), balance(b) {}
};

class DebtMinimizer {
private:
    std::vector<Transaction> transactions;
    std::map<std::string, int> netBalances;
    std::vector<NetBalance> nonZeroBalances;
    std::vector<Transaction> minimizedTransactions;
    
    // Helper functions
    std::string normalizeString(const std::string& str);
    void calculateNetBalances();
    void filterNonZeroBalances();
    void minimizeDebt(std::vector<NetBalance>& balances);
    int findMaxCreditor(const std::vector<NetBalance>& balances);
    int findMaxDebtor(const std::vector<NetBalance>& balances);
    
public:
    // Public interface functions
    void addTransaction(const std::string& from, const std::string& to, int amount);
    void processTransactions();
    void displayOriginalTransactions() const;
    void displayNetBalances() const;
    void displayMinimizedTransactions() const;
    void clearData();
    int getMinimizedTransactionCount() const;
    
    // File operations
    bool loadFromFile(const std::string& filename);
    bool saveToFile(const std::string& filename) const;
};

#endif // DEBT_MINIMIZER_H