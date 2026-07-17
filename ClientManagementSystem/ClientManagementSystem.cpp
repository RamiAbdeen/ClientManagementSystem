#include <iostream>
#include <vector>
#include <string>

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

void DisplayClientsTable()
{
    cout << "-----------------------------------------------------------------------------------------------------------\n";
    cout << "|AccNo.|FName       |LName        |Phone          |Email               |Address   |Country      |Balance  |\n";
    cout << "-----------------------------------------------------------------------------------------------------------\n";
    PrintClientsInfo();
    cout << "-----------------------------------------------------------------------------------------------------------\n";
}

int main()
{
    return 0;
}