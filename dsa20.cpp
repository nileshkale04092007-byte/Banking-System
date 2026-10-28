#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <ctime>
using namespace std;

class Customer {
protected:
    string custName;
    string address;
    double annualIncome;
    string mobileNo;

public:
    void setCustomerDetails(string name, string addr, double income, string mobile) {
        custName = name;
        address = addr;
        annualIncome = income;
        mobileNo = mobile;
    }
};

class Bank : public Customer {
private:
    string accountNumber;
    string ifscCode;
    string branchName;
    double balance;
    vector<string> transactionHistory;
    static const double MIN_BALANCE;

    string getCurrentTime() {
        time_t now = time(0);
        char* dt = ctime(&now);
        string s(dt);
        if (!s.empty() && s.back() == '\n') s.pop_back();
        return s;
    }

    void addTransaction(string type, double amount) {
        
        string record = getCurrentTime() + " | " + type + " Rs." + to_string((int)amount) + " | Bal: Rs." + to_string((int)balance);
        transactionHistory.push_back(record);
    }

public:
    Bank(string accNo, string ifsc, string branch, double initialBal,
         string name, string addr, double income, string mobile) {

        if (initialBal < MIN_BALANCE) {
            throw invalid_argument("Initial balance must be at least Rs. 500");
        }

        accountNumber = accNo;
        ifscCode = ifsc;
        branchName = branch;
        balance = initialBal;
        
        setCustomerDetails(name, addr, income, mobile);
        addTransaction("Account Opened +", initialBal);
    }

    void deposit(double amount) {
        cout << "\n>> Deposit: Rs." << amount << endl;
        if (amount <= 0) {
            cout << "[ FAILED ] Invalid Amount!" << endl; return;
        }
        balance += amount;
        addTransaction("Deposited +", amount);
        cout << "[ SUCCESS ] New Balance: Rs." << balance << endl;
    }

    void withdraw(double amount) {
        cout << "\n>> Withdraw: Rs." << amount << endl;
        if (amount <= 0) {
            cout << "[ FAILED ] Invalid Amount!" << endl; return;
        }
        if (amount > balance) {
            cout << "[ FAILED ] Out of Balance! Available: Rs." << balance << endl; return;
        }
        if ((balance - amount) < MIN_BALANCE) {
            cout << "[ FAILED ] Min Balance Rs.500 maintain karna hai!" << endl; return;
        }
        balance -= amount;
        addTransaction("Withdrawn -", amount);
        cout << "[ SUCCESS ] Remaining Balance: Rs." << balance << endl;
    }

    void checkBalance() const {
        cout << "\nBalance: Rs." << fixed << setprecision(2) << balance << endl;
    }

    void printReceipt() const {
        cout << "\n=========================================" << endl;
        cout << "         BANK TRANSACTION RECEIPT        " << endl;
        cout << "=========================================" << endl;
        cout << "Branch    : " << branchName << endl;
        cout << "IFSC      : " << ifscCode << endl;
        cout << "Acc No    : " << accountNumber << endl;
        cout << "Name      : " << custName << endl;
        cout << "Balance   : Rs." << balance << endl;
        cout << "Time      : " << ctime(nullptr);
        cout << "=========================================" << endl;
    }

    void showAllTransactions() const {
        cout << "\n--- TRANSACTION HISTORY ---" << endl;
        for (auto &t : transactionHistory) cout << t << endl;
    }
};

const double Bank::MIN_BALANCE = 500.0;

int main() {
    Bank acc1("SBIN000123456", "SBIN0000456", "Aurangabad Main Branch",
              5000.0, "Asha Sharma", "Cidco, Aurangabad", 600000, "9876543210");

    acc1.deposit(2000);
    acc1.withdraw(1000);
    acc1.withdraw(10000); // Out of balance check
    acc1.deposit(-500);   // Invalid amount check
    acc1.withdraw(6000);  // Min balance check

    acc1.checkBalance();
    acc1.showAllTransactions();
    acc1.printReceipt();
    return 0;
}