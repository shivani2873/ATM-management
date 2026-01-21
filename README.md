
---

## 🔄 Project Flow

### 1️⃣ Bank Account Module
1. User creates a bank account
2. Account details are saved in a separate file
3. User logs in using Account Number & Password
4. User can:
   - Deposit money
   - Withdraw money
   - Check balance
   - View account details
   - View transaction history
   - Apply for a debit card

---

### 2️⃣ ATM Module
1. User enters ATM Card Number
2. User enters ATM PIN
3. System verifies details from ATM card file
4. If valid:
   - Linked bank account is loaded automatically
   - ATM menu is displayed
5. User can:
   - Check balance
   - Withdraw money
   - Deposit money
   - View mini statement
   - Logout safely

---

## ✨ Features

### ✅ Bank Account Features
- Create bank account with minimum balance
- Secure login authentication
- Deposit & withdraw money
- Persistent data storage using files
- Complete transaction history
- Apply for debit card

### ✅ ATM Features
- ATM card authentication
- PIN-based secure access
- ATM withdrawal & deposit
- Mini statement
- Auto-sync with bank account data

---

## 💾 File Handling Logic

### 📄 Bank Account File (`<AccountNumber>.txt`)
Stores:
- Account holder name
- Account number
- Password
- Aadhar number
- Email
- Phone number
- Balance
- Transaction history

### 💳 ATM Card File (`<CardNumber>.txt`)
Stores:
- ATM card number
- Linked account number
- Expiry date
- CVV
- ATM PIN

Each user has **separate files**, ensuring data persistence and isolation.

---

## 🔐 OOP Design

### `bankAcc` Class
- Handles all bank-related operations
- Manages balance, transactions, and account details
- Uses `vector<string>` for transaction history
- Implements file save & load functionality

### `ATM` Class
- Inherits from `bankAcc`
- Implements ATM card authentication
- Provides ATM-specific menu
- Demonstrates inheritance and code reusability

---

## 🚀 How to Run the Project

### Compile & Run Bank Module
```bash
g++ -std=c++17 -o bankAcc bankAcc.cpp
./bankAcc
