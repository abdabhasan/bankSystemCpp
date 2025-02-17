#pragma once
#include "../../../bankClient/clsBankClient.h"
#include "../../../utils/clsMyInputValidateLib.h"
#include "../../screen/clsScreen.h"
#include <iomanip>
#include <iostream>
using namespace std;

class clsDepositScreen : protected clsScreen {

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
    cout << "\nPlease enter Account Number? ";
    cin >> accountNumber;
    return accountNumber;
  }

public:
  static void showDepositScreen() {
    _drawScreenHeader("\t   Deposit Screen");

    string accountNumber = _readAccountNumber();

    while (!clsBankClient::isClientExist(accountNumber)) {
      cout << "\nClient with [" << accountNumber << "] does not exist.\n";
      accountNumber = _readAccountNumber();
    }

    clsBankClient client =
        clsBankClient::findClientByAccountNumber(accountNumber);
    _printClient(client);

    double amount = 0;
    cout << "\nPlease enter deposit amount? ";
    amount = clsMyInputValidateLib::readDblNumber();

    cout << "\nAre you sure you want to perform this transaction? y/n ? ";
    char answer = 'n';
    cin >> answer;

    if (answer == 'Y' || answer == 'y') {
      client.deposit(amount);
      cout << "\namount Deposited Successfully.\n";
      cout << "\nNew Balance Is: " << client.getAccountBalance();

    } else {
      cout << "\nOperation was cancelled.\n";
    }
  }
};
