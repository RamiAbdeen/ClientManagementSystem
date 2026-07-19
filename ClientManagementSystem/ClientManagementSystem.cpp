#include <iostream>
#include <vector>
#include <string>
#include <fstream>

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
};

bool CheckIfFileIsEmpty()
{
    fstream MyFile;

    string Line;

    MyFile.open("Clients.txt", ios::in);

    if (MyFile.is_open())
    {
        if (Line == "")
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

    cout << "Account Number: ";
    cin >> Client.AccountNumber;
    
    for (stClientInfo& C : vClient)
    {
        if (C.AccountNumber == Client.AccountNumber)
        {
            cout << "This number is not valid!\n";
            cout << "Enter another one: ";
            cin >> Client.AccountNumber;
        }
    }

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

void PrintClientsInfo()
{
    if(CheckIfFileIsEmpty())
        cout << "The file is empty :-)\n";

}

void DisplayClientsTable()
{
    cout << "-----------------------------------------------------------------------------------------------------------\n";
    cout << "|AccNo.|FName       |LName        |Phone          |Email               |Address   |Country      |Balance  |\n";
    cout << "-----------------------------------------------------------------------------------------------------------\n";
    PrintClientsInfo();
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

int main()
{


    return 0;
}