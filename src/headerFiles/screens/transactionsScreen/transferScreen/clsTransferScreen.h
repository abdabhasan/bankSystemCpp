#pragma once
#include "../../../bankClient/clsBankClient.h"
#include "../../../utils/clsMyInputValidateLib.h"
#include "../../screen/clsScreen.h"
#include <iomanip>
#include <iostream>
using namespace std;

class clsTransferScreen : protected clsScreen {

private:
  static void _printClient(clsBankClient client) {
    cout << "\nClient Card:";
    cout << "\n___________________\n";
    cout << "\nFull Name   : " << client.getFullName();
    cout << "\nAcc. Number : " << client.getAccountNumber();
    cout << "\nBalance     : " << client.getAccountBalance();
    cout << "\n___________________\n";
  }

  static string _readAccountNumber() {
    string accountNumber;
    cout << "\nPlease Enter Account Number to Transfer From: ";
    accountNumber = clsMyInputValidateLib::readString();
    while (!clsBankClient::isClientExist(accountNumber)) {
      cout << "\nAccount number is not found, choose another one: ";
      accountNumber = clsMyInputValidateLib::readString();
    }
    return accountNumber;
  }

  static float _readAmount(clsBankClient sourceClient) {
    float amount;

    cout << "\nEnter Transfer Amount? ";

    amount = clsMyInputValidateLib::readDblNumber();

    while (amount > sourceClient.getAccountBalance()) {
      cout << "\nAmount Exceeds the available Balance, Enter another Amount ? ";
      amount = clsMyInputValidateLib::readDblNumber();
    }
    return amount;
  }

public:
  static void showTransferScreen() {

    _drawScreenHeader("\tTransfer Screen");

    clsBankClient sourceClient =
        clsBankClient::findClientByAccountNumber(_readAccountNumber());

    _printClient(sourceClient);

    clsBankClient destinationClient =
        clsBankClient::findClientByAccountNumber(_readAccountNumber());

    _printClient(destinationClient);

    float amount = _readAmount(sourceClient);

    cout << "\nAre you sure you want to perform this operation? y/n? ";
    char answer = 'n';
    cin >> answer;
    if (answer == 'Y' || answer == 'y') {
      if (sourceClient.transfer(amount, destinationClient)) {
        cout << "\nTransfer done successfully\n";
      } else {
        cout << "\nTransfer Faild \n";
      }
    }

    _printClient(sourceClient);
    _printClient(destinationClient);
  }
};
