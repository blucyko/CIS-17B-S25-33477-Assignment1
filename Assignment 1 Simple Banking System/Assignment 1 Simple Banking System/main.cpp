// Ash Nguyen
// CIS-17B-S25-33477
// 2/24/25
// Assignment 1 Simple Banking System

#include <iostream>
#include <string>
#include <limits>

using namespace std;

// Maximum number of accounts
const int MAX_ACCOUNTS = 100;

class BankAccount
{
private:
    string accountHolderName;
    int accountNumber;
    double balance;

public:
    BankAccount() : accountHolderName(""), accountNumber(0), balance(0.0) {} // Default constructor

    BankAccount(string name, double initialBalance) : accountHolderName(name), balance(initialBalance)
    {
        accountNumber = generateAccountNumber();
    }

    // Generate a unique 6-digit account number
    static int generateAccountNumber()
    {
        return 100000 + rand() % 950000;
    }

    // Public member function for deposit money
    void deposit(double amount)
    {
        if (amount < 0)
        {
            throw invalid_argument("Deposit amount cannot be negative.");
        }
        balance += amount;
        cout << "Deposit successful! New balance: $" << balance << endl;
    }

    // Public member function for withdraw money
    void withdraw(double amount)
    {
        if (amount < 0)
        {
            throw invalid_argument("Withdrawal amount cannot be negative.");
        }
        if (amount > balance)
        {
            cout << "Insufficient funds!" << endl;
            return;
        }
        balance -= amount;
        cout << "Withdrawal successful! New balance: $" << balance << endl;
    }

    // Public member function for getting account balance
    double getBalance() const
    {
        return balance;
    }

    // Public member function for getting account number
    int getAccountNumber() const
    {
        return accountNumber;
    }

    // Public member function for displaying account details
    void displayAccount() const
    {
        cout << "\nAccount Holder: " << accountHolderName
            << "\nAccount Number: " << accountNumber
            << "\nBalance: $" << balance << "\n";
    }
};

// Global variables
BankAccount accounts[MAX_ACCOUNTS]; // Fixed-size array of bank accounts
int accountCount = 0;               // Track the number of accounts

// Function prototypes
void createAccount();
void depositMoney();
void withdrawMoney();
void checkBalance();

int main()
{
    // Seed random number generator for account numbers
    srand(time(0));

    // Constants for menu choices
    const int CREATE_ACCOUNT_CHOICE = 1;
    const int DEPOSIT_MONEY_CHOICE = 2;
    const int WITHDRAW_MONEY_CHOICE = 3;
    const int CHECK_BALANCE_CHOICE = 4;
    const int QUIT_CHOICE = 5;

    // Variable
    int choice;

    // Menu for the Simple Bank System
    do {
        cout << "\nWelcome to Simple Bank System" << endl;
        cout << "=================================" << endl;
        cout << "1. Create Account" << endl;
        cout << "2. Deposit Money" << endl;
        cout << "3. Withdraw Money" << endl;
        cout << "4. Check Balance" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case CREATE_ACCOUNT_CHOICE:
            createAccount();
            break;
        case DEPOSIT_MONEY_CHOICE:
            depositMoney();
            break;
        case WITHDRAW_MONEY_CHOICE:
            withdrawMoney();
            break;
        case CHECK_BALANCE_CHOICE:
            checkBalance();
            break;
        case QUIT_CHOICE:
            cout << "Thank you for using Simple Bank System!" << endl;
            break;
        default:
            cout << "Invalid option. Please choose a valid option." << endl;
        }
    } while (choice != 5);

    return 0;
}


//******************************************//
//				   Functions				//
//******************************************//


// ============================= //
// Function to create an account //
// ============================= //
void createAccount()
{
    if (accountCount >= MAX_ACCOUNTS)
    {
        cout << "Account limit reached. Cannot create more accounts." << endl;
        return;
    }

    // Variables
    string name;
    double initialDeposit;

    cout << "Enter account holder name: ";
    cin.ignore(100, '\n');
    getline(cin, name);

    cout << "Enter initial deposit: ";
    while (!(cin >> initialDeposit) || initialDeposit < 0)
    {
        cout << "Invalid input. Please enter a positive number: ";
        cin.clear();
        cin.ignore(100, '\n');
    }

    // Create new account in the fixed array
    accounts[accountCount] = BankAccount(name, initialDeposit);

    cout << "Account created successfully! Your account number is: " << accounts[accountCount].getAccountNumber() << "\n";
    accountCount++; 
}
// ************************************************************* //

// ========================= //
// Function to deposit money //
// ========================= //
void depositMoney()
{
    // Variables
    int accNum;
    double amount;

    cout << "Enter account number: ";
    cin >> accNum;

    // Find the account
    for (int i = 0; i < accountCount; i++)
    {
        if (accounts[i].getAccountNumber() == accNum)
        {
            // Try Catch Block 
            cout << "Enter amount to deposit: ";
            while (true)
            {
                if (!(cin >> amount))
                {
                    cout << "Invalid input. Please enter a valid number: ";
                    cin.clear(); 
                    cin.ignore(100, '\n');
                    continue;
                }
                try
                {
                    accounts[i].deposit(amount);
                    break; 
                }
                catch (const exception& e)
                {
                    cout << e.what() << "\nTry again: ";
                }
            }
            return;
        }
    }
    cout << "Account not found." << endl;
}
// ************************************************************* //

// ========================== //
// Function to withdraw money //
// ========================== //
void withdrawMoney()
{
    int accNum;
    double amount;

    cout << "Enter account number: ";
    cin >> accNum;

    // Find the account
    for (int i = 0; i < accountCount; i++)
    {
        if (accounts[i].getAccountNumber() == accNum)
        {
            // Try Catch Block
            cout << "Enter amount to withdraw: ";
            while (true)
            {
                if (!(cin >> amount))
                {
                    cout << "Invalid input. Please enter a valid number: ";
                    cin.clear();
                    cin.ignore(100, '\n');
                    continue;
                }
                try
                {
                    accounts[i].withdraw(amount);
                    break; 
                }
                catch (const exception& e)
                {
                    cout << e.what() << "\nTry again: ";
                }
            }
            return;
        }
    }
    cout << "Account not found." << endl;
}
// ************************************************************* //


// ================================= //
// Function to check account balance //
// ================================= //
void checkBalance()
{
    int accNum;
    cout << "Enter account number: ";
    cin >> accNum;

    for (int i = 0; i < accountCount; i++)
    {
        if (accounts[i].getAccountNumber() == accNum)
        {
            accounts[i].displayAccount();
            return;
        }
    }
    cout << "Account not found." << endl;
}
// ************************************************************* //
