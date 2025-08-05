#include "debt_minimizer.h"
#include <iostream>
#include <string>
#include <limits>
#include <sstream>

class DebtMinimizerUI {
private:
    DebtMinimizer minimizer;
    
    void displayHeader() {
        std::cout << "\n" << std::string(60, '=') << std::endl;
        std::cout << "           DEBT SIMPLIFICATION TOOL" << std::endl;
        std::cout << "         Minimize Your Group Expenses" << std::endl;
        std::cout << std::string(60, '=') << std::endl;
    }
    
    void displayMenu() {
        std::cout << "\n=== MAIN MENU ===" << std::endl;
        std::cout << "1. Add Transaction" << std::endl;
        std::cout << "2. Process & Minimize Debts" << std::endl;
        std::cout << "3. View Original Transactions" << std::endl;
        std::cout << "4. View Net Balances" << std::endl;
        std::cout << "5. View Minimized Transactions" << std::endl;
        std::cout << "6. Load from File" << std::endl;
        std::cout << "7. Save Results to File" << std::endl;
        std::cout << "8. Clear All Data" << std::endl;
        std::cout << "9. Batch Entry Mode" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << std::string(30, '-') << std::endl;
        std::cout << "Enter your choice: ";
    }
    
    void addSingleTransaction() {
        std::cout << "\n=== ADD TRANSACTION ===" << std::endl;
        
        std::string from, to;
        int amount;
        
        std::cout << "Enter debtor's name: ";
        std::cin.ignore();
        std::getline(std::cin, from);
        
        std::cout << "Enter creditor's name: ";
        std::getline(std::cin, to);
        
        std::cout << "Enter amount: ";
        while (!(std::cin >> amount) || amount <= 0) {
            std::cout << "Please enter a valid positive amount: ₹";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        
        minimizer.addTransaction(from, to, amount);
    }
    
    void batchEntryMode() {
        std::cout << "\n=== BATCH ENTRY MODE ===" << std::endl;
        std::cout << "Enter transactions (type 'done' to finish)" << std::endl;
        std::cout << "Format: From To Amount" << std::endl;
        std::cout << "Example: Alice Bob 100" << std::endl;
        std::cout << std::string(40, '-') << std::endl;
        
        std::cin.ignore();
        std::string line;
        int count = 0;
        
        while (true) {
            std::cout << "Transaction " << (count + 1) << ": ";
            std::getline(std::cin, line);
            
            if (line == "done" || line == "DONE") {
                break;
            }
            
            std::istringstream iss(line);
            std::string from, to;
            int amount;
            
            if (iss >> from >> to >> amount) {
                minimizer.addTransaction(from, to, amount);
                count++;
            } else {
                std::cout << "Invalid format! Please use: From To Amount" << std::endl;
            }
        }
        
        std::cout << "Batch entry completed! Added " << count << " transactions." << std::endl;
    }
    
    void loadFromFile() {
        std::cout << "\n=== LOAD FROM FILE ===" << std::endl;
        std::cout << "Enter filename (format: from to amount per line): ";
        
        std::string filename;
        std::cin.ignore();
        std::getline(std::cin, filename);
        
        minimizer.loadFromFile(filename);
    }
    
    void saveToFile() {
        std::cout << "\n=== SAVE TO FILE ===" << std::endl;
        std::cout << "Enter filename to save results: ";
        
        std::string filename;
        std::cin.ignore();
        std::getline(std::cin, filename);
        
        minimizer.saveToFile(filename);
    }
    
    void waitForUser() {
        std::cout << "\nPress Enter to continue...";
        std::cin.ignore();
        std::cin.get();
    }
    
public:
    void run() {
        displayHeader();
        
        int choice;
        bool running = true;
        
        while (running) {
            displayMenu();
            
            while (!(std::cin >> choice)) {
                std::cout << "Please enter a valid number: ";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            
            switch (choice) {
                case 1:
                    addSingleTransaction();
                    waitForUser();
                    break;
                    
                case 2:
                    std::cout << "\n=== PROCESSING DEBTS ===" << std::endl;
                    minimizer.processTransactions();
                    minimizer.displayMinimizedTransactions();
                    waitForUser();
                    break;
                    
                case 3:
                    minimizer.displayOriginalTransactions();
                    waitForUser();
                    break;
                    
                case 4:
                    minimizer.displayNetBalances();
                    waitForUser();
                    break;
                    
                case 5:
                    minimizer.displayMinimizedTransactions();
                    waitForUser();
                    break;
                    
                case 6:
                    loadFromFile();
                    waitForUser();
                    break;
                    
                case 7:
                    saveToFile();
                    waitForUser();
                    break;
                    
                case 8:
                    std::cout << "\n=== CLEAR DATA ===" << std::endl;
                    minimizer.clearData();
                    waitForUser();
                    break;
                    
                case 9:
                    batchEntryMode();
                    waitForUser();
                    break;
                    
                case 0:
                    std::cout << "\nThank you for using Debt Simplification Tool!" << std::endl;
                    std::cout << "Goodbye!" << std::endl;
                    running = false;
                    break;
                    
                default:
                    std::cout << "Invalid choice! Please select a valid option." << std::endl;
                    waitForUser();
                    break;
            }
        }
    }
};

// Demo function to show sample usage
void runDemo() {
    std::cout << "\n=== RUNNING DEMO ===" << std::endl;
    
    DebtMinimizer demo;
    
    // Add sample transactions
    std::cout << "Adding sample transactions..." << std::endl;
    demo.addTransaction("Alice", "Bob", 100);
    demo.addTransaction("Bob", "Charlie", 50);
    demo.addTransaction("Charlie", "Alice", 30);
    demo.addTransaction("David", "Alice", 20);
    demo.addTransaction("Bob", "David", 10);
    
    // Display original transactions
    demo.displayOriginalTransactions();
    
    // Process and minimize
    std::cout << "\nProcessing transactions..." << std::endl;
    demo.processTransactions();
    
    // Display results
    demo.displayNetBalances();
    demo.displayMinimizedTransactions();
    
    std::cout << "\nDemo completed!" << std::endl;
}

int main() {
    std::cout << "Welcome to Debt Simplification Tool!" << std::endl;
    std::cout << "1. Run Interactive Mode" << std::endl;
    std::cout << "2. Run Demo" << std::endl;
    std::cout << "Enter choice (1/2): ";
    
    int choice;
    while (!(std::cin >> choice) || (choice != 1 && choice != 2)) {
        std::cout << "Please enter 1 or 2: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    
    if (choice == 1) {
        DebtMinimizerUI ui;
        ui.run();
    } else {
        runDemo();
        
        std::cout << "\nWould you like to try interactive mode? (y/n): ";
        char response;
        std::cin >> response;
        
        if (response == 'y' || response == 'Y') {
            DebtMinimizerUI ui;
            ui.run();
        }
    }
    
    return 0;
}