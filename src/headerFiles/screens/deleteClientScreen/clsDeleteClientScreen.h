#pragma once
#include "../../bankClient/clsBankClient.h"
#include "../../utils/clsMyInputValidateLib.h"
#include "../screen/clsScreen.h"
#include <iostream>

class clsDeleteClientScreen : protected clsScreen {

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

public:
  static void showDeleteClientScreen() {

    _drawScreenHeader("\tDelete Client Screen");

    string accountNumber = "";

    cout << "\nPlease Enter Account Number: ";
    accountNumber = clsMyInputValidateLib::readString();
    while (!clsBankClient::isClientExist(accountNumber)) {
      cout << "\nAccount number is not found, choose another one: ";
      accountNumber = clsMyInputValidateLib::readString();
    }

    clsBankClient client =
        clsBankClient::findClientByAccountNumber(accountNumber);
    _printClient(client);

    cout << "\nAre you sure you want to delete this client y/n? ";

    char answer = 'n';
    cin >> answer;

    if (answer == 'y' || answer == 'Y') {

      if (client.deleteClient()) {
        cout << "\nClient Deleted Successfully :-)\n";
        _printClient(client);
      } else {
        cout << "\nError Client Was not Deleted\n";
      }
    }
  }
};
