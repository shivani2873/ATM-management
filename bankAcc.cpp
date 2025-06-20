#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<ctime>
#include<stdlib.h>
using namespace std;

void Red()      { cout<<"\033[31m"; } 
void Green()    { cout<<"\033[32m"; }
void Yellow()   { cout<<"\033[33m"; }
void Blue()     { cout<<"\033[34m"; }
void Magenta()  { cout<<"\033[35m"; }
void Cyan()     { cout<<"\033[36m"; }
void White()    { cout<<"\033[37m"; }
void Reset()    { cout<<"\033[0m"; }   

string generateCardNo(){
    string cardNo;
    srand(time(0));
    for(int i=0;i<16;i++){
        cardNo += to_string(rand()%10);
    }
    return cardNo;
}
string generateExpDate(){
    string expD;
    srand(time(0));
    //curr date
    time_t t=time(0);
    tm *now=localtime(&t);
    int currMonth=now->tm_mon+1;  //tm_mon is 0-11
    int currYr=now->tm_year+1990;  //tm_year is yrs since 1900
    currYr += 5; //5 yrs from now

    expD += (currMonth > 9 ? to_string(currMonth) : "0"+to_string(currMonth) ) + "/"+to_string(currYr);
    return expD;
}
string generateCVV(){
    string cvv;
    srand(time(0));
    for(int i=0;i<3;i++){
        cvv+=to_string(rand()%10);
    }
    return cvv;
}
string generatePin(){
    string pin;
    srand(time(0));
    for(int i=0;i<4;i++){
        pin+=to_string(rand()%10);
    }
    return pin;
}

class bankAcc{
// private:
protected:
//best way to use is getter/setter and inheriting it
    //CAN-canara bank
    string bankName="CAN";
    int bankCode;
    string accHolderName;
    string accNumber;
    string accPassword;
    string aadharNo;
    string email;
    string phoneNo;
    double balance;  
    //container to store transaction history
    vector<string> transactionHis; 
public:
    void savetoFile();
    void loadFromFile();
    void mainMenu();
    void createAcc();
    void loginBankAcc();
    void depositMoney();
    void withdrawMoney();
    void checkBalance();
    void accDetails();
    void allTransactionHistory();
    void applyDebitCard();
};
void bankAcc::savetoFile(){
    ofstream file(accNumber + ".txt");
    if(file.is_open()){
        file<<accHolderName<<endl;
        file<<accNumber<<endl;
        file<<accPassword<<endl;
        file<<aadharNo<<endl;
        file<<email<<endl;
        file<<phoneNo<<endl;
        file<<balance<<endl;
        for(auto transaction:transactionHis){
            file<<transaction<<endl;
        }
        file.close();
    }else{
        cout<<"Error opening file!"<<endl;
    }
}
void bankAcc::loadFromFile(){
    ifstream file(accNumber+".txt");
    if(file.is_open()){
        getline(file, accHolderName);
        getline(file, accNumber);
        getline(file, accPassword);
        getline(file, aadharNo);
        getline(file, email);
        getline(file, phoneNo);
        file >> balance;
        file.ignore();   //khali krne ke liye
        string transaction;
        while (getline(file, transaction)) {
            transactionHis.push_back(transaction);
        }
        file.close();
    }else{
        cout<<"Error opening file!"<<endl;
    }
}
void bankAcc::mainMenu(){
    int choice;
    do{
        cout<<"----------------------------------"<<endl;
        cout<<" Enter 1 for Deposit Money "<<endl;
        cout<<" Enter 2 for Withdraw Money "<<endl;
        cout<<" Enter 3 for Check Balance "<<endl;
        cout<<" Enter 4 for Account Details "<<endl;
        cout<<" Enter 5 for All Transaction History "<<endl;
        cout<<" Enter 6 for Apply Debit Card "<<endl;
        cout<<" Enter 7 for Logout "<<endl;
        cout<<"----------------------------------"<<endl;
        cout<<" Enter your choice: ";
        cin >> choice;
        cin.ignore();
        system("clear");
        switch (choice)  {
            case 1:
                depositMoney();
                break;
            case 2:
                withdrawMoney();
                break;
            case 3:
                checkBalance();
                break;
            case 4:
                accDetails();
                break;
            case 5:
                allTransactionHistory();
                break;
            case 6:
                applyDebitCard();
                break;
            case 7:
                cout << "Logging out...!" << endl;
                savetoFile();
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }

    }while(choice != 7);
}
void bankAcc::createAcc(){
    Green();
    cout<<"     Create Account    "<<endl;
    cout<<"-----------------------"<<endl;
    cout<<"Enter Your Full Name   : ";
    getline(cin, accHolderName);
    cout<<"Enter Email Id         : ";
    getline(cin, email);
    cout<<"Enter Phone Number     : ";
    getline(cin, phoneNo);
    cout<<"Enter Addhar Number    : ";
    getline(cin, aadharNo);
    cout<<"Enter Account Password : ";
    getline(cin, accPassword);
    cout<<"-----------------------"<<endl;
    Reset();   //colour reset kiya
    //minimum balance is 500/-
    balance = 500.0;
    //ifstream->file se data
    ifstream file("Canara-Bank-Of-India.txt");
    if(file.is_open())  {
        file>>bankCode;
        file.close();
        //ofstream-> file ko open kr rhe h
        ofstream output("Canara-Bank-Of-India.txt");
        if(output.is_open())    {
            output<<bankCode+1;
            output.close();
        }
        else {
            cout << "Error opening file!" << endl;
        }
    } else {
        cout << "Error opening file!" << endl;
    }
    //save into acc no.
    accNumber = bankName+ to_string(bankCode);
    transactionHis.push_back("Deposit :- " + to_string(balance));
    Yellow();
    cout << "Account Created Successfully!" << endl;
    cout << "Account Number   : " << accNumber << endl;
    cout << "Account Password : " << accPassword << endl;
    cout << "Minimum Balance  : 500.0" << endl;
    cout<<"-----------------------"<<endl;
    Reset();
    savetoFile();
}
void bankAcc::loginBankAcc(){
    string enteredAccNumber;
    string enteredPassword;
    Blue();
    cout << "     Login Account     " << endl;
    cout << "-----------------------" << endl;
    cout << "Enter Account Number   : ";
    getline(cin, enteredAccNumber);
    accNumber = enteredAccNumber;    //important
    ifstream file(enteredAccNumber + ".txt");
    if (file.is_open()) {
        loadFromFile();
        cout << "Enter Account Password : ";
        getline(cin, enteredPassword);
        if (accPassword == enteredPassword) {
            cout << "Login Successful!" << endl;
            mainMenu();
        } else {
            cout << "Invalid Password!" << endl;
        }
        file.close();
    } else {
        cout << "Account not found!" << endl;
    }
}
void bankAcc::depositMoney(){
    double amnt;
    cout << "Enter Amount to Deposit : ";
    cin >> amnt;
    cin.ignore();
    if (amnt > 0) {
        balance += amnt;
        transactionHis.push_back("Deposit  :- " + to_string(amnt));
        ofstream file(accNumber + ".txt",ios::app);
        if(file.is_open()) {
            cout << "Deposit Successful!" << endl;
            cout << "New Balance: " << balance << endl;
            file<<"Deposit  :- " + to_string(amnt) + "\n";
            file.close();
        } else {
            cout << "Deposit Not Successful!" << endl;
        }
    } else {
        cout << "Invalid Amount!" << endl;
    }
}
void bankAcc::withdrawMoney(){
    double amnt;
    cout << "Enter Amount to Withdraw : ";
    cin >> amnt;
    cin.ignore();
    if (amnt > 0 && amnt <= balance) {
        balance -= amnt;
        transactionHis.push_back("Withdraw :- " + to_string(amnt));
        ofstream file(accNumber + ".txt", ios::app);
        if(file.is_open()) {
            cout << "Withdraw Successful!" << endl;
            cout << "New Balance: " << balance << endl;
            file<<"Withdraw :- " + to_string(amnt) + "\n";
            file.close();
        } else {
            cout << "Withdraw Not Successful!" << endl;
        }
    } else {
        cout << "Invalid Amount!" << endl;
    }
}
void bankAcc::checkBalance()   {
    cout << "Current Balance : " << balance << endl;
    cout<<"-----------------------"<<endl;
}
void bankAcc::accDetails() {
    Magenta();
    cout<<"|------------------------------|"<<endl;
    cout<<"|    Canara Bank Of India      |"<<endl;
    cout<<"|------------------------------|"<<endl;
    Blue();
    cout << "Account Holder Name : " << accHolderName << endl;
    cout << "Account Number      : " << accNumber << endl;
    cout << "Addhar Number       : " << aadharNo << endl;
    cout << "Email Id            : " << email << endl;
    cout << "Phone Number        : " << phoneNo << endl;
    cout << "Current Balance     : " << balance << endl;
    cout<<"-------------------------------"<<endl;
    Reset();
}
void bankAcc::allTransactionHistory() { 
    cout << " Transaction History :- " << endl;
    Yellow();
    cout<<"-------------------------------"<<endl;
    cout << "Account Holder Name : " << accHolderName << endl;
    cout << "Account Number      : " << accNumber << endl;
    for (const auto& transaction : transactionHis) {
        cout << transaction << endl;
    }
    cout<<"-------------------------------"<<endl;
    Reset();
}
void bankAcc::applyDebitCard(){
    string cardNo;
    string expDate;;
    string pin;
    string cvv;
    string aadharNum;
    string accNo;

    cout<<"Apply for Debit Card"<<endl;
    cout<<"--------------------------------"<<endl;
    cout<<"Enter Account Number      :";
    getline(cin,accNo);
    cout<<"Enter Aadhar Number       :";
    getline(cin,aadharNum);
    cout<<"--------------------------------"<<endl;
    if(aadharNum==aadharNo && accNo==accNumber){
        cardNo=generateCardNo();
        expDate=generateExpDate();
        cvv=generateCVV();
        pin=generatePin();
        //credit create hone ke baad uski alag file banana
        ofstream file(cardNo+".txt");
        if(file.is_open()){
            file<<cardNo<<endl;
            file<<accNumber<<endl;
            file<<expDate<<endl;
            file<<cvv<<endl;
            file<<pin<<endl;
            file.close();
            cout<<"--------------------------------"<<endl;
            cout<<"Debit Card Applied Successfully!"<<endl;
            cout<<"--------------------------------"<<endl;
            cout<<"Debit Card Holder Name :"<<accHolderName<<endl;
            cout<<"Debit Card Number      :"<<cardNo<<endl;
            cout<<"Expiry Date            :"<<expDate<<endl;
            cout<<"CVV                    :"<<cvv<<endl;
            cout<<"Pin                    :"<<pin<<endl;
            cout<<"--------------------------------"<<endl;
        }else{
            cout<<"Debit Card Not Apply!"<<endl;
        }
    }else{
        cout<<"Invalid Account Number or Aadhar Number"<<endl;
    }
}

// int main() {
//     bankAcc account;
//     int choice;
//     do {
//         cout<<" Welcome to Canara Bank Of India" << endl;
//         cout<<"--------------------------------------"<<endl;
//         cout << "1. Create Account" << endl;
//         cout << "2. Login" << endl;
//         cout << "3. Exit" << endl;
//         cout << "Enter your choice: ";
//         cin >> choice;
//         cin.ignore();
//         system("clear");
//         switch (choice) {
//             case 1:
//                 account.createAcc();
//                 break;
//             case 2:
//                 account.loginBankAcc();
//                 break;
//             case 3:
//                 cout << "Exiting..." << endl;
//                 break;
//             default:
//                 cout << "Invalid choice. Please try again." << endl;
//         }
//     } while (choice != 3);
//     return 0;
// }

// to run this use, 
// g++ -std=c++17 -o bankAcc bankAcc.cpp
// ./bankAcc