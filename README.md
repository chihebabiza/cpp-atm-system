# ATM System

A C++ console application that simulates an ATM (Automated Teller Machine) with basic banking functionality for client transactions.

## Overview

This application provides a simple interface for bank customers to perform common ATM operations such as withdrawals, deposits, and balance inquiries. The system requires user authentication via account number and PIN code before accessing the transaction features.

## Features

- **User Authentication**: Secure login using account number and PIN code
- **Quick Withdraw**: Predefined withdrawal amounts for faster transactions (20, 50, 100, 200, 400, 600, 800)
- **Normal Withdraw**: Custom withdrawal amount (must be divisible by 5)
- **Deposit**: Add funds to the account
- **Balance Inquiry**: Check current account balance
- **Logout**: Secure exit from the system

## Technical Details

- **Language**: C++
- **Data Storage**: Text file using a custom delimiter format
- **File Location**: Client data is stored in `data/clients.txt`

## Data Structure

Each client record contains:
- Account Number (unique identifier)
- PIN Code
- Full Name
- Phone Number
- Account Balance

## Program Flow

1. **Login Screen**: The program starts with a login screen where users must authenticate:
   ```
   ===========================================
                  Login Screen
   ===========================================
   
   Please enter AccountNumber?
   Please enter PIN Code?
   ```

2. **Main Menu**: After successful login, the ATM main menu is displayed:
   ```
   ===========================================
              ATM Main Menue Screen
   ===========================================
           [1] Quick WithDraw.
           [2] Normal WithDraw.
           [3] Disposit.
           [4] Check Balance.
           [5] Logout.
   ===========================================
   Choose what do you want to do? [1 to 5]?
   ```

3. **Quick Withdraw Screen**: When selecting Quick Withdraw, a sub-menu of predefined amounts is displayed:
   ```
   ===========================================
              Quick Withdraw Screen
   ===========================================
           [1] -  20            [2] -  50
           [3] - 100            [4] - 200
           [5] - 400            [6] - 600
           [7] - 800            [8] - Exit
   ===========================================
   Choose what do you want to do? [1 to 7]?
   ```

## Security Features

- PIN code verification for account access
- Confirmation prompt before completing transactions
- Automatic logout functionality
- Balance check to prevent overdrafts

## Transaction Constraints

- Withdrawals must be in multiples of 5
- Withdrawal amount cannot exceed account balance
- Confirmation required for all transactions

## File Format

Client data is stored in a text file with fields separated by the delimiter `#//#`. Example:

```
ACC123#//#1234#//#John Doe#//#555-1234#//#1000.00
ACC456#//#5678#//#Jane Smith#//#555-5678#//#2500.50
```

## Functions

### Authentication Functions
- `ReadExistClient()`: Reads and validates client credentials
- `PerformLogin()`: Handles the login process

### Transaction Functions
- `ShowDepositScreen()`: Interface for depositing funds
- `ShowWithDrawScreen()`: Interface for normal withdrawals
- `ShowQuickWithDrawScreen()`: Interface for quick withdrawals
- `ShowBalanceScreen()`: Displays current account balance
- `DepositBalanceToClientByAccountNumber()`: Updates account balance after transactions

### Utility Functions
- `LoadCleintsDataFromFile()`: Loads client data from the file
- `SaveCleintsDataToFile()`: Saves updated client data to the file
- `ConvertLinetoRecord()`: Converts file data to client structure
- `ConvertRecordToLine()`: Converts client structure to file format
- `SplitString()`: Splits a string by a delimiter

## Usage Example

1. User enters account number and PIN
2. Upon successful authentication, the main menu appears
3. User selects a transaction type
4. System processes the transaction and updates the account balance
5. User can perform multiple transactions before logging out


## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Contact

For inquiries or further information, you can contact the project maintainer:

Email: [chihababiza9@gmail.com](mailto:chihababiza9@gmail.com)
