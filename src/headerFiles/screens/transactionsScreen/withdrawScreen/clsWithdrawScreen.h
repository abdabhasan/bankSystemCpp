#pragma once
#include "../../../bankClient/clsBankClient.h"
#include "../../../utils/clsMyInputValidateLib.h"
#include "../../screen/clsScreen.h"
#include <iomanip>
#include <iostream>
using namespace std;

class clsWithdrawScreen : protected clsScreen {
private:
  static void _printClient(clsBankClient client) {
    cout << "\nClient Card:";
    cout << "\n___________________";
    cout << "\nFirstName   : " << client.getFirstName();
    cout << "\nLastName    : " << client.getLastName();
    cout << "\nFull Name   : " << client.getFullName();
    cout << "\nEmail       : " << client.getEmail();
    cout << "\nPhone       : " << client.getPhone();
    cout << "\nAcc. Number : " << client.getAccountNumber();
    cout << "\nPassword    : " << client.getPinCode();
    cout << "\nBalance     : " << client.getAccountBalance();
    cout << "\n___________________\n";
  }

  static string _readAccountNumber() {
    string accountNumber = "";
    cout << "\nPlease enter AccountNumber? ";
    cin >> accountNumber;
    return accountNumber;
  }

public:
  static void ShowWithdrawScreen() {
    _drawScreenHeader("\t   Withdraw Screen");

    string accountNumber = _readAccountNumber();

    while (!clsBankClient::isClientExist(accountNumber)) {
      cout << "\nClient with [" << accountNumber << "] does not exist.\n";
      accountNumber = _readAccountNumber();
    }

    clsBankClient client =
        clsBankClient::findClientByAccountNumber(accountNumber);
    _printClient(client);

    double amount = 0;
    cout << "\nPlease enter Withdraw amount? ";
    amount = clsMyInputValidateLib::readDblNumber();

    cout << "\nAre you sure you want to perform this transaction? y/n? ";
    char answer = 'n';
    cin >> answer;

    if (answer == 'Y' || answer == 'y') {
      if (client.withdraw(amount)) {
        cout << "\nAmount Withdrew Successfully.\n";
        cout << "\nNew Balance Is: " << client.getAccountBalance();
      } else {
        cout << "\nCannot withdraw, Insuffecient Balance!\n";
        cout << "\nAmout to withdraw is: " << amount;
        cout << "\nYour Balance is: " << client.getAccountBalance();
      }
    } else {
      cout << "\nOperation was cancelled.\n";
    }
  }
};
