#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <math.h>

using namespace std;

const string ClientsFileName = "data/clients.txt";

void ShowMainMenue();
void ShowQuickWithDrawScreen();

struct sClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
};

sClient CurrentClient;

vector<string> SplitString(string S1, string Delim)
{
    vector<string> vString;
    short pos = 0;
    string sWord;
    while ((pos = S1.find(Delim)) != std::string::npos)
    {
        sWord = S1.substr(0, pos);
        if (sWord != "")
        {
            vString.push_back(sWord);
        }
        S1.erase(0, pos + Delim.length());
    }
    if (S1 != "")
    {
        vString.push_back(S1);
    }
    return vString;
}

sClient ConvertLinetoRecord(string Line, string Seperator = "#//#")
{
    sClient Client;
    vector<string> vClientData;
    vClientData = SplitString(Line, Seperator);
    Client.AccountNumber = vClientData[0];
    Client.PinCode = vClientData[1];
    Client.Name = vClientData[2];
    Client.Phone = vClientData[3];
    Client.AccountBalance = stod(vClientData[4]); // cast string to
    return Client;
}

string ConvertRecordToLine(sClient Client, string Seperator = "#//#")
{
    string stClientRecord = "";
    stClientRecord += Client.AccountNumber + Seperator;
    stClientRecord += Client.PinCode + Seperator;
    stClientRecord += Client.Name + Seperator;
    stClientRecord += Client.Phone + Seperator;
    stClientRecord += to_string(Client.AccountBalance);
    return stClientRecord;
}

vector<sClient> SaveCleintsDataToFile(string FileName, vector<sClient> vClients)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out);
    string DataLine;
    if (MyFile.is_open())
    {
        for (sClient C : vClients)
        {

            DataLine = ConvertRecordToLine(C);
            MyFile << DataLine << endl;
        }
        MyFile.close();
    }
    return vClients;
}

bool ClientExist(string AccountNumber, string PINCode, string FileName, sClient &Client)
{
    fstream MyFile;
    MyFile.open(FileName, ios::in);
    if (MyFile.is_open())
    {
        string Line;
        while (getline(MyFile, Line))
        {
            Client = ConvertLinetoRecord(Line);
            if (Client.AccountNumber == AccountNumber && Client.PinCode == PINCode)
            {
                MyFile.close();
                return true;
            }
        }
        MyFile.close();
    }
    return false;
}

bool DepositBalanceToClientByAccountNumber(string AccountNumber, double Amount, vector<sClient> &vClients)
{
    char Answer = 'n';
    cout << "\n\nAre you sure you want perfrom this transaction?y /n? ";
    cin >>
        Answer;
    if (Answer == 'y' || Answer == 'Y')
    {
        for (sClient &C : vClients)
        {
            if (C.AccountNumber == AccountNumber)
            {
                C.AccountBalance += Amount;
                SaveCleintsDataToFile(ClientsFileName, vClients);
                cout << "\n\nDone Successfully. New balance is: " << C.AccountBalance;
                return true;
            }
        }
        return false;
    }
}

string ReadClientAccountNumber()
{
    string AccountNumber = "";
    cout << "\nPlease enter AccountNumber? ";
    cin >> AccountNumber;
    return AccountNumber;
}

vector<sClient> LoadCleintsDataFromFile(string FileName)
{
    vector<sClient> vClients;
    fstream MyFile;
    MyFile.open(FileName, ios::in);
    if (MyFile.is_open())
    {
        string Line;
        sClient Client;
        while (getline(MyFile, Line))
        {
            Client = ConvertLinetoRecord(Line);
            vClients.push_back(Client);
        }
        MyFile.close();
    }
    return vClients;
}

void ShowDepositScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tDeposit Screen";
    cout << "\n-----------------------------------\n";
    sClient Client;
    vector<sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    double Amount = 0;
    cout << "\nPlease enter deposit amount? ";
    cin >> Amount;
    DepositBalanceToClientByAccountNumber(CurrentClient.AccountNumber, Amount, vClients);
}

void ShowWithDrawScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tWithdraw Screen";
    cout << "\n-----------------------------------\n";
    vector<sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);

    double Amount = 0;
    do
    {
        cout << "\nPlease enter withdraw amount? (devide by 5)";
        cin >> Amount;
    } while (fmod(Amount, 5) != 0);
    while (Amount > CurrentClient.AccountBalance)
    {
        cout << "\nAmount Exceeds the balance, you can withdraw up to : " << CurrentClient.AccountBalance << endl;
        cout
            << "Please enter another amount? ";
        cin >> Amount;
    }
    DepositBalanceToClientByAccountNumber(CurrentClient.AccountNumber, Amount * -1, vClients);
}

void ShowBalanceScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tYour Balance is : " << CurrentClient.AccountBalance;
    cout << "\n-----------------------------------\n";
}

enum enTransactionsMenueOptions
{
    eQuickWithDraw = 1,
    eNormalWithDraw = 2,
    eDisposit = 3,
    eCheckBalace = 4,
    eLogOut = 5
};

enum enQuickWithDrawOptions
{
    e20 = 1,
    e50 = 2,
    e100 = 3,
    e200 = 4,
    e400 = 5,
    e600 = 6,
    e800 = 7,
    eExit = 8
};

void GoBackToATMMainMenue()
{
    cout << "\n\nPress any key to go back to ATM Main Menue...";
    system("pause>0");
    ShowMainMenue();
}

string ReadPINCode()
{
    string PIN = "";
    cout << "\nPlease enter PIN Code? ";
    cin >> PIN;
    return PIN;
}

sClient ReadExistClient()
{
    sClient Client;
    bool isExist;
    do
    {
        Client.AccountNumber = ReadClientAccountNumber();
        Client.PinCode = ReadPINCode();

        isExist = ClientExist(Client.AccountNumber, Client.PinCode, ClientsFileName, Client);

        if (!isExist)
            cout << "\nInvalid Account Number or PIN Code";
    } while (!isExist);

    return Client;
}

void PerformLogin()
{
    CurrentClient = ReadExistClient();
    ShowMainMenue();
    system("pause>0");
}

void ShowLoginScreen()
{
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tLogin Screen\n";
    cout << "===========================================\n";
    PerformLogin();
}

void PerfromMainMenueOption(enTransactionsMenueOptions TransactionMenueOption)
{
    switch (TransactionMenueOption)
    {
    case enTransactionsMenueOptions::eDisposit:
    {
        system("cls");
        ShowDepositScreen();
        GoBackToATMMainMenue();
        break;
    }

    case enTransactionsMenueOptions::eNormalWithDraw:
    {
        system("cls");
        ShowWithDrawScreen();
        GoBackToATMMainMenue();
        break;
    }

    case enTransactionsMenueOptions::eCheckBalace:
    {
        system("cls");
        ShowBalanceScreen();
        GoBackToATMMainMenue();
        break;
    }

    case enTransactionsMenueOptions::eQuickWithDraw:
    {
        system("cls");
        ShowQuickWithDrawScreen();
        GoBackToATMMainMenue();
        break;
    }

    case enTransactionsMenueOptions::eLogOut:
    {
        ShowLoginScreen();
    }
    }
}

void PerfromQuickWithDrawMenueOption(enQuickWithDrawOptions QuickWithDrawMenuOption)
{
    vector<sClient> vClient = LoadCleintsDataFromFile(ClientsFileName);
    switch (QuickWithDrawMenuOption)
    {
    case enQuickWithDrawOptions::e20:
    {
        system("cls");
        DepositBalanceToClientByAccountNumber(CurrentClient.AccountNumber, -20, vClient);
        GoBackToATMMainMenue();
        break;
    }
    case enQuickWithDrawOptions::e50:
    {
        system("cls");
        DepositBalanceToClientByAccountNumber(CurrentClient.AccountNumber, -50, vClient);
        GoBackToATMMainMenue();
        break;
    }
    case enQuickWithDrawOptions::e100:
    {
        system("cls");
        DepositBalanceToClientByAccountNumber(CurrentClient.AccountNumber, -100, vClient);
        GoBackToATMMainMenue();
        break;
    }
    case enQuickWithDrawOptions::e200:
    {
        system("cls");
        DepositBalanceToClientByAccountNumber(CurrentClient.AccountNumber, -200, vClient);
        GoBackToATMMainMenue();
        break;
    }
    case enQuickWithDrawOptions::e400:
    {
        system("cls");
        DepositBalanceToClientByAccountNumber(CurrentClient.AccountNumber, -400, vClient);
        GoBackToATMMainMenue();
        break;
    }
    case enQuickWithDrawOptions::e800:
    {
        system("cls");
        DepositBalanceToClientByAccountNumber(CurrentClient.AccountNumber, -800, vClient);
        GoBackToATMMainMenue();
        break;
    }
    case enQuickWithDrawOptions::eExit:
    {
        system("cls");
        ShowMainMenue();
        break;
    }
    }
}

short ReadQuickWithDrawMenueOption()
{
    cout << "Choose what do you want to do? [1 to 7]? ";
    short Choice = 0;
    cin >> Choice;
    return Choice;
}

short ReadMainMenueOption()
{
    cout << "Choose what do you want to do? [1 to 5]? ";
    short Choice = 0;
    cin >> Choice;
    return Choice;
}

void ShowMainMenue()
{
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tATM Main Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Quick WithDraw.\n";
    cout << "\t[2] Normal WithDraw.\n";
    cout << "\t[3] Disposit.\n";
    cout << "\t[4] Check Balance.\n";
    cout << "\t[5] Logout.\n";
    cout << "===========================================\n";
    PerfromMainMenueOption((enTransactionsMenueOptions)ReadMainMenueOption());
}

void ShowQuickWithDrawScreen()
{
    system("cls");
    cout << "\n===========================================\n";
    cout << "\t\tQuick Withdraw Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] -  20\t\t[2] -  50\n";
    cout << "\t[3] - 100\t\t[4] - 200\n";
    cout << "\t[5] - 400\t\t[6] - 600\n";
    cout << "\t[7] - 800\t\t[8] - Exit\n";
    cout << "===========================================\n";
    PerfromQuickWithDrawMenueOption((enQuickWithDrawOptions)ReadQuickWithDrawMenueOption());
}

int main()
{
    ShowLoginScreen();
    system("pause");
    return 0;
}