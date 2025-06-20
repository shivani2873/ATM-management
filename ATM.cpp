#include<iostream>
#include<string>
#include<fstream>
#include"bankAcc.cpp"

class ATM: public bankAcc{
private:
    string atmCardNo;
    string atmPin;
    double atmBalance;
    string atmExpDate;
    string atmCVV;
    string accNo;
public:
    void mainMenuATM();
    void checkATMCard();
};
void ATM::mainMenuATM(){
    int choice;
    loadFromFile();
    do {
        cout << "----------------------------------" << endl;
        cout << " Enter 1 for Check Balance " << endl;
        cout << " Enter 2 for Withdraw Money from ATM " << endl;
        cout << " Enter 3 for Deposit Money to ATM " << endl;
        cout << " Enter 4 for Mini statment " << endl;
        cout << " Enter 5 for Logout " << endl;
        cout << "----------------------------------" << endl;
        cout << " Enter your choice : ";
        cin >> choice;
        cin.ignore();
        system("clear");

        switch (choice) {
            case 1:
                checkBalance();
                break;
            case 2:
                withdrawMoney();
                break;
            case 3:
                depositMoney();
                break;
            case 4:
                allTransactionHistory();
                break;
            case 5:
                cout << "Logging out...!" << endl;
                savetoFile();
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 5);
}
void ATM::checkATMCard(){
    string cardNum;
    string pin;
    cout<<"Enter ATM Card Number: ";
    getline(cin, cardNum);
    cout<<"Enter ATM Card Pin: ";
    getline(cin, pin);

    ifstream file(cardNum + ".txt");
    if (file.is_open()) {
        getline(file, atmCardNo);
        getline(file, accNo);
        getline(file, atmExpDate);
        getline(file, atmCVV);
        getline(file, atmPin);
        file.close();

        if(atmCardNo == cardNum && atmPin == pin) {
            accNumber = accNo;
            mainMenuATM();
        } else {
            cout << "Invalid ATM Card Number or Pin!" << endl;
        }
    } else {
        cout << "File Invalid ATM Card Number or Pin!" << endl;
    }
}

int main() {
    ATM atm;
    atm.checkATMCard();    
    return 0;
}