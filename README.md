# 💰 Debt Simplification Tool

A powerful C++ application that minimizes the number of transactions needed to settle debts within a group. Perfect for splitting bills, group expenses, or any scenario where multiple people owe money to each other.

## 🚀 Features

- **Smart Debt Minimization**: Uses an optimized greedy algorithm to reduce the number of transactions
- **Interactive UI**: User-friendly command-line interface with menu-driven options
- **Batch Processing**: Enter multiple transactions at once
- **File Operations**: Load transactions from files and save results
- **Real-time Analysis**: View original transactions, net balances, and minimized results
- **Data Validation**: Robust input validation and error handling
- **Cross-platform**: Works on Windows, macOS, and Linux

## 📊 How It Works

The tool calculates net balances for each person and then uses a greedy algorithm to minimize transactions:

**Example:**
- Original: 5 transactions between Alice, Bob, Charlie, and David
- After minimization: Only 2-3 transactions needed
- Typical reduction: 40-70% fewer transactions

## 🔧 Installation & Usage

### Option 1: Download Pre-compiled Executable (Recommended)

1. **Download the executable** from the [Releases](../../releases) section
2. **Run the program**:
   ```bash
   # Windows
   debt_minimizer.exe
   
   # Linux/macOS
   chmod +x debt_minimizer
   ./debt_minimizer
   ```

### Option 2: Compile from Source

#### Prerequisites
- C++17 compatible compiler (GCC 7+, Clang 5+, MSVC 2017+)
- Make (optional, for easier building)

#### Quick Start
1. **Clone or download** this repository:
   ```bash
   git clone https://github.com/lk-gambhir/debt-simplification-tool.git
   cd debt-simplification-tool
   ```

2. **Compile using Make** (recommended):
   ```bash
   make
   ./debt_minimizer
   ```

3. **Or compile manually**:
   ```bash
   g++ -std=c++17 -Wall -Wextra -O2 -o debt_minimizer main.cpp debt_minimizer.cpp
   ./debt_minimizer
   ```

#### Additional Make Commands
```bash
make clean      # Clean build files
make run        # Build and run
make debug      # Build with debug info
make sample     # Create sample input file
make help       # Show all available commands
```

## 📖 Usage Guide

### Interactive Mode
1. Run the program and select "Interactive Mode"
2. Choose from the menu options:
   - **Add Transaction**: Enter individual debts
   - **Batch Entry**: Enter multiple transactions quickly
   - **Process & Minimize**: Calculate optimized transactions
   - **View Results**: See original vs minimized transactions
   - **File Operations**: Load/save data

### Demo Mode
Run the built-in demo to see how the tool works with sample data.

### File Input Format
Create a text file with transactions (one per line):
```
alice bob 100
bob charlie 50
charlie alice 30
david alice 20
bob david 10
```

## 💡 Example

**Input Transactions:**
```
Alice owes Bob ₹100
Bob owes Charlie ₹50
Charlie owes Alice ₹30
David owes Alice ₹20
Bob owes David ₹10
```

**Minimized Result:**
```
Alice pays Bob ₹70
David pays Alice ₹20
Bob pays Charlie ₹40
```

**Reduction:** From 5 transactions to 3 transactions (40% reduction)

## 🏗️ Project Structure

```
debt-simplification-tool/
├── src/
│   ├── main.cpp              # Main UI and program entry
│   ├── debt_minimizer.cpp    # Core algorithm implementation
│   └── debt_minimizer.h      # Header file with class definitions
├── Makefile                  # Build configuration
├── README.md                 # This file
└── releases/                 # Pre-compiled executables
```

## 🔧 Technical Details

- **Language**: C++17
- **Algorithm**: Greedy debt minimization
- **Time Complexity**: O(n²) where n is the number of people
- **Space Complexity**: O(n)
- **Dependencies**: Standard C++ library only

## 🤝 Contributing

Contributions are welcome! Here's how you can help:

1. **Fork** the repository
2. **Create** a feature branch (`git checkout -b feature/amazing-feature`)
3. **Commit** your changes (`git commit -m 'Add amazing feature'`)
4. **Push** to the branch (`git push origin feature/amazing-feature`)
5. **Open** a Pull Request

### Development Setup
```bash
git clone https://github.com/lk-gambhir/debt-simplification-tool.git
cd debt-simplification-tool
make debug  # Build with debug symbols
```

## 📝 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 🐛 Bug Reports & Feature Requests

Found a bug or have a feature idea? Please [open an issue](../../issues) with:
- Clear description of the problem/feature
- Steps to reproduce (for bugs)
- Expected vs actual behaviour
- Your system information (OS, compiler version)

## 📈 Roadmap

- [ ] Web-based interface
- [ ] Support for different currencies
- [ ] Transaction categories
- [ ] Export to Excel/PDF
- [ ] Mobile app
- [ ] API for integration

## 🙏 Acknowledgments

- Thanks to all contributors who help improve this tool
- Inspired by the need to simplify group expense management
- Built with ❤️ for the open-source community

## 📧 Contact

- **Author**: Lakshay Gambhir
- **Email**: lakshaygambhir96@gmail.com
- **GitHub**: [@lk-gambhir](https://github.com/lk-gambhir)

---

⭐ **Star this repository** if you find it helpful!

