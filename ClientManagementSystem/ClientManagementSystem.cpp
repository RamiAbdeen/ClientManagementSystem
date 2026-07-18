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

stClientInfo ReadClientInfo()
{
    stClientInfo Client;


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
    DisplayClientsTable();

    return 0;
}