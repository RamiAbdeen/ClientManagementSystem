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

vector <stClientInfo> FillVectorWithClients()
{
    vector <stClientInfo> vClient;
    char AddMore = 'Y';
    
    do
    {
        vClient.push_back(ReadClientInfo(vClient));
        cout << "\nDo you want to add more? Y/N\n";
        cin >> AddMore;

    } while (AddMore == 'Y' || AddMore == 'y');

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
    FillTxtFileWithClients(FillVectorWithClients());

    return 0;
}