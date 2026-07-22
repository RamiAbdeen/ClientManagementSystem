#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

struct stClientInfo
{
    string AccountNumber;
    string FirstName;
    string LastName;
    string Phone;
    string Email;
    string Address;
    string Country;
    double Balance;
    bool MarkForDelete = false;
};

enum enOperation { ShowClients = 1, AddNewClient = 2, DeleteClient = 3, UpdateClient = 4, FindClient = 5, Transaction = 6, Exit = 7};

enum enTransaction { Deposit = 1, Withdraw = 2, TotalBalances = 3, MainMenu = 4 };

bool CheckIfFileIsEmpty()
{
    fstream MyFile;

    string Line;

    MyFile.open("Clients.txt", ios::in);

    if (MyFile.is_open())
    {
        if (!getline(MyFile, Line))
        {
            MyFile.close();
            return true;
        }

        MyFile.close();
        return false;
    }
}

void DeleteTxtFileContent()
{
    fstream MyFile;

    string Line;

    MyFile.open("Clients.txt", ios::out);

    if (MyFile.is_open())
    {
        Line = "";

        MyFile.close();
    }
}

stClientInfo ReadClientInfo(vector <stClientInfo> vClient)
{
    stClientInfo Client;

    bool IsAccountExist = false;
    do
    {
        IsAccountExist = false;

        cout << "Account Number: ";
        cin >> Client.AccountNumber;

        for (stClientInfo& C : vClient)
        {
            if (C.AccountNumber == Client.AccountNumber)
            {
                IsAccountExist = true;
                cout << "This number is not valid!\n";
                break;
            }
        }
    } while (IsAccountExist);

    cout << "First Name    : ";
    cin >> Client.FirstName;

    cout << "Last Name     : ";
    cin >> Client.LastName;

    cout << "Phone         : ";
    cin >> Client.Phone;

    cout << "Email         : ";
    cin >> Client.Email;

    cout << "Address       : ";
    cin >> Client.Address;

    cout << "Country       : ";
    cin >> Client.Country;
    
    cout << "Balance       : ";
    cin >> Client.Balance;

    return Client;
}

vector <stClientInfo> FillVectorWithClientsFromTxtFile();

void AddASingleClientToTheTxtFile(stClientInfo Client, string Separator = "#//#")
{
    fstream MyFile;

    MyFile.open("Clients.txt", ios::out | ios::app);

    if (MyFile.is_open())
    {
        MyFile << Client.AccountNumber << Separator;
        MyFile << Client.FirstName << Separator;
        MyFile << Client.LastName << Separator;
        MyFile << Client.Phone << Separator;
        MyFile << Client.Email << Separator;
        MyFile << Client.Address << Separator;
        MyFile << Client.Country << Separator;
        MyFile << Client.Balance << endl;

        MyFile.close();
    }
}

vector <stClientInfo> FillVectorWithClients()
{
    vector <stClientInfo> vClient = FillVectorWithClientsFromTxtFile();
    char AddMore = 'Y';
    
    do
    {
        vClient.push_back(ReadClientInfo(vClient));
        AddASingleClientToTheTxtFile(vClient.back());
        cout << "\nDo you want to add more? Y/N\n";
        cin >> AddMore;

    } while (AddMore == 'Y' || AddMore == 'y');

    return vClient;
}

stClientInfo ReadClientInfoFromTxtFile(vector <string> vClient)
{
    stClientInfo Client;

    Client.AccountNumber = vClient.at(0);
    Client.FirstName = vClient.at(1);
    Client.LastName = vClient.at(2);
    Client.Phone = vClient.at(3);
    Client.Email = vClient.at(4);
    Client.Address = vClient.at(5);
    Client.Country = vClient.at(6);
    Client.Balance = stod(vClient.at(7));

    return Client;
}

vector <string> SplitLineRecord(string LineRecord, string Separator = "#//#")
{
    vector <string> vClient;

    short pos = 0;
    string sWord;

    while ((pos = LineRecord.find(Separator)) != string::npos)
    {
        sWord = LineRecord.substr(0, pos);
        if (sWord != "")
        {
            vClient.push_back(sWord);
        }
        LineRecord.erase(0, pos + Separator.length());
    }
    if (LineRecord != "")
    {
        vClient.push_back(LineRecord);
    }

    return vClient;
}

vector <stClientInfo> FillVectorWithClientsFromTxtFile()
{
    vector <stClientInfo> vClient;

    fstream MyFile;

    MyFile.open("Clients.txt", ios::in);

    stClientInfo Client;

    string Line;

    if (MyFile.is_open())
    {
        while (getline(MyFile, Line))
        {
            vClient.push_back(ReadClientInfoFromTxtFile(SplitLineRecord(Line)));
        }
        MyFile.close();
    }

    return vClient;
}

void FillTxtFileWithClients(vector <stClientInfo> vClient, string Separator = "#//#")
{
    fstream MyFile;

    MyFile.open("Clients.txt", ios::out);

    if (MyFile.is_open())
    {
        for (stClientInfo& C : vClient)
        {
            MyFile << C.AccountNumber << Separator;
            MyFile << C.FirstName << Separator;
            MyFile << C.LastName << Separator;
            MyFile << C.Phone << Separator;
            MyFile << C.Email << Separator;
            MyFile << C.Address << Separator;
            MyFile << C.Country << Separator;
            MyFile << C.Balance << endl;
        }
        MyFile.close();
    }
}

void PrintClientsInfo(vector <stClientInfo> vClient)
{
    if (CheckIfFileIsEmpty())
        cout << "The file is empty :-)\n";

    for (stClientInfo& C : vClient)
    {
        cout << "|" << setw(6) << left << C.AccountNumber;
        cout << "|" << setw(12) << left << C.FirstName;
        cout << "|" << setw(13) << left << C.LastName;
        cout << "|" << setw(15) << left << C.Phone;
        cout << "|" << setw(20) << left << C.Email;
        cout << "|" << setw(10) << left << C.Address;
        cout << "|" << setw(13) << left << C.Country;
        cout << "|" << setw(9) << left << C.Balance;
        cout << "|" << endl;
    }
}

void DisplayClientsTable()
{
    cout << "-----------------------------------------------------------------------------------------------------------\n";
    cout << "|AccNo.|FName       |LName        |Phone          |Email               |Address   |Country      |Balance  |\n";
    cout << "-----------------------------------------------------------------------------------------------------------\n";
    PrintClientsInfo(FillVectorWithClientsFromTxtFile());
    cout << "-----------------------------------------------------------------------------------------------------------\n";
}

void CreateTxtFile()
{
    fstream MyFile;

    MyFile.open("Clients.txt", ios::out);

    if (MyFile.is_open())
    {
        MyFile << "";

        MyFile.close();
    }
}

void RemoveClient()
{
    vector <stClientInfo> vClient = FillVectorWithClientsFromTxtFile();
    vector <stClientInfo> vMClient;
    string AccNo;
    bool Found = false;

    cout << "Enter Account Number: ";
    cin >> AccNo;

    for (stClientInfo& C : vClient)
    {
        if (AccNo == C.AccountNumber)
        {
            Found = true;
            C.MarkForDelete = true;
            break;
        }
    }
    if (Found == false)
    {
        cout << "This Account does not exist! :=>)\n";
        return;
    }

    for (stClientInfo& MC : vClient)
    {
        if (MC.MarkForDelete == false)
        {
            vMClient.push_back(MC);
        }
    }

    FillTxtFileWithClients(vMClient);
}

void ModifyClient()
{
    vector <stClientInfo> vClient = FillVectorWithClientsFromTxtFile();

    string AccNo;
    bool Found = false;

    cout << "Enter Account Number: ";
    cin >> AccNo;

    for (stClientInfo& C : vClient)
    {
        if (AccNo == C.AccountNumber)
        {
            Found = true;

            cout << "Account Number: " << C.AccountNumber << endl;

            cout << "First Name: ";
            cin >> C.FirstName;

            cout << "Last Name: ";
            cin >> C.LastName;

            cout << "Phone: ";
            cin >> C.Phone;

            cout << "Email: ";
            cin >> C.Email;

            cout << "Address: ";
            cin >> C.Address;

            cout << "Country: ";
            cin >> C.Country;

            cout << "Balance: ";
            cin >> C.Balance;

            break;
        }
    }
    if (Found == false)
    {
        cout << "This Account does not exist! :=>)\n";
        return;
    }

    FillTxtFileWithClients(vClient);
}

void DisplayClientCard()
{
    vector <stClientInfo> vClient = FillVectorWithClientsFromTxtFile();

    string AccNo;
    bool Found = false;

    cout << "Enter Account Number: ";
    cin >> AccNo;

    for (stClientInfo& C : vClient)
    {
        if (AccNo == C.AccountNumber)
        {
            Found = true;

            cout << "-------------------------------------\n";
            cout << "Account Number: " << C.AccountNumber << endl;
            cout << "Full Name: " << C.FirstName << " " << C.LastName << endl;
            cout << "Phone: " << C.Phone << endl;
            cout << "Email: " << C.Email << endl;
            cout << "Address: " << C.Address << endl;
            cout << "Country: " << C.Country << endl;
            cout << "Balance: " << C.Balance << endl;
            cout << "-------------------------------------\n";

            break;
        }
    }
    if (Found == false)
    {
        cout << "This Account does not exist! :=>)\n";
    }
}

void DisplayExitScreen()
{
    cout << "-------------------------------------\n";
    cout << "\tProgram Ends Here...\n";
    cout << "-------------------------------------\n";
}

void DepositAmount()
{
    vector <stClientInfo> vClient = FillVectorWithClientsFromTxtFile();

    string AccNo;
    bool Found = false;
    int Amount;

    cout << "Enter Account Number: ";
    cin >> AccNo;

    for (stClientInfo& C : vClient)
    {
        if (AccNo == C.AccountNumber)
        {
            Found = true;

            do
            {
                cout << "Enter Amount: ";
                cin >> Amount;
            } while (Amount < 0);
            C.Balance += Amount;

            break;
        }
    }
    if (Found == false)
    {
        cout << "This Account does not exist! :=>)\n";
        return;
    }

    FillTxtFileWithClients(vClient);
}

void WithdrawAmount()
{
    vector <stClientInfo> vClient = FillVectorWithClientsFromTxtFile();

    string AccNo;
    bool Found = false;
    int Amount;

    cout << "Enter Account Number: ";
    cin >> AccNo;

    for (stClientInfo& C : vClient)
    {
        if (AccNo == C.AccountNumber)
        {
            Found = true;

            do
            {
                cout << "Enter Amount: ";
                cin >> Amount;
            } while (Amount < 0 || Amount > C.Balance);
            C.Balance -= Amount;

            break;
        }
    }
    if (Found == false)
    {
        cout << "This Account does not exist! :=>)\n";
        return;
    }

    FillTxtFileWithClients(vClient);
}

double CalculateTotalBalances()
{
    double TotalBalances = 0;

    vector <stClientInfo> vClient = FillVectorWithClientsFromTxtFile();

    for (stClientInfo C : vClient)
    {
        TotalBalances += C.Balance;
    }

    return TotalBalances;
}

void DisplayBalncesTabel(vector <stClientInfo> vClient)
{
    if (CheckIfFileIsEmpty())
        cout << "The file is empty :-)\n";

    for (stClientInfo& C : vClient)
    {
        cout << "|" << left << setw(15) << left << C.AccountNumber;
        cout << "|" << left << setw(22) << left << C.FirstName + " " + C.LastName;
        cout << "|" << left << setw(14) << left << C.Balance;
        cout << "|" << endl;
    }
}

void DisplayTotalBalancesTable()
{
    cout << "-------------------------------------------------------\n";
    cout << "|Account Number |Full Name             |Balance       |\n";
    cout << "-------------------------------------------------------\n";
    DisplayBalncesTabel(FillVectorWithClientsFromTxtFile());
    cout << "-------------------------------------------------------\n";
    cout << "|" << setw(38) << left << "Total Balances";
    cout << "|" << setw(14) << left << CalculateTotalBalances() << "|\n";
    cout << "-------------------------------------------------------\n";
}

short ReadOption();
void SelectOperationFromMainMenu();

void PerformTransaction(enTransaction Option)
{
    switch (Option)
    {
    case enTransaction::Deposit:
    {
        system("cls");
        DepositAmount();
        system("pause");
        break;
    }
    case enTransaction::Withdraw:
    {
        system("cls");
        WithdrawAmount();
        system("pause");
        break;
    }
    case enTransaction::TotalBalances:
    {
        system("cls");
        DisplayTotalBalancesTable();
        system("pause");
        break;
    }
    case enTransaction::MainMenu:
    {
        system("cls");
        return;
    }
    default:
    {
        cout << "Select a valid option :-)\n";
    }
    }
}

void DisplayTransactions()
{
    short YourChoice;
    do
    {
        system("cls");
        cout << "---------------------------------------------\n";
        cout << "\t\tTransactions\n";
        cout << "---------------------------------------------\n";
        cout << "[1] Deposit.\n";
        cout << "[2] Withdraw.\n";
        cout << "[3] Total Balances.\n";
        cout << "[4] Main Menu.\n";
        cout << "---------------------------------------------\n";
        YourChoice = ReadOption();
        PerformTransaction((enTransaction)YourChoice);
    } while (YourChoice != 4);
}

void ApplyOperation(enOperation Op)
{
    switch (Op)
    {
    case enOperation::ShowClients:
    {
        system("cls");
        DisplayClientsTable();
        system("pause");
        break;
    }
    case enOperation::AddNewClient:
    {
        system("cls");
        FillVectorWithClients();
        system("pause");
        break;
    }
    case enOperation::DeleteClient:
    {
        system("cls");
        RemoveClient();
        system("pause");
        break;
    }
    case enOperation::UpdateClient:
    {
        system("cls");
        ModifyClient();
        system("pause");
        break;
    }
    case enOperation::FindClient:
    {
        system("cls");
        DisplayClientCard();
        system("pause");
        break;
    }
    case enOperation::Transaction:
    {
        system("cls");
        DisplayTransactions();
        system("pause");
        break;
    }
    case enOperation::Exit:
    {
        system("cls");
        DisplayExitScreen();
        system("pause");
        break;
    }
    default:
    {
        cout << "Select a valid option :-v||\n";
    }
    }
}

short ReadOption()
{
    short Number;
    cout << "Please enter a Number? ";
    cin >> Number;

    while (cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Invalid Number, Enter a valid one:" << endl;
        cin >> Number;
    }

    return Number;
}

void SelectOperationFromMainMenu()
{
    short YourSelection;
    do
    {
        system("cls");
        cout << "---------------------------------------------\n";
        cout << "\t\tMain Menu\n";
        cout << "---------------------------------------------\n";
        cout << "[1] Display Clients Table.\n";
        cout << "[2] Add New Client.\n";
        cout << "[3] Delete Client.\n";
        cout << "[4] Update Client.\n";
        cout << "[5] Find Client.\n";
        cout << "[6] Transaction.\n";
        cout << "[7] Exit.\n";
        cout << "---------------------------------------------\n";
        YourSelection = ReadOption();
        ApplyOperation((enOperation)YourSelection);
    } while (YourSelection != 7);
}

int main()
{
    SelectOperationFromMainMenu();

    return 0;
}