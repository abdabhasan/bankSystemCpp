#pragma once

#include "../../bankClient/clsBankClient.h"
#include "../../utils/clsMyInputValidateLib.h"
#include "../screen/clsScreen.h"
#include <iostream>

class clsUpdateClientScreen : protected clsScreen

{
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

  static void _readClientInfo(clsBankClient &client) {
    cout << "\nEnter First Name: ";
    client.setFirstName(clsMyInputValidateLib::readString());

    cout << "\nEnter LastName: ";
    client.setLastName(clsMyInputValidateLib::readString());

    cout << "\nEnter Email: ";
    client.setEmail(clsMyInputValidateLib::readString());

    cout << "\nEnter Phone: ";
    client.setPhone(clsMyInputValidateLib::readString());

    cout << "\nEnter PinCode: ";
    client.setPinCode(clsMyInputValidateLib::readShortNumber());

    cout << "\nEnter Account Balance: ";
    client.setAccountBalance(clsMyInputValidateLib::readDblNumber());
  }

public:
  static void showUpdateClientScreen() {

    _drawScreenHeader("\tUpdate Client Screen");

    string accountNumber = "";

    cout << "\nPlease Enter client Account Number: ";
    accountNumber = clsMyInputValidateLib::readString();

    while (!clsBankClient::isClientExist(accountNumber)) {
      cout << "\nAccount number is not found, choose another one: ";
      accountNumber = clsMyInputValidateLib::readString();
    }

    clsBankClient client =
        clsBankClient::findClientByAccountNumber(accountNumber);

    _printClient(client);

    cout << "\nAre you sure you want to update this client y/n? ";

    char answer = 'n';
    cin >> answer;

    if (answer == 'y' || answer == 'Y') {

      cout << "\n\nUpdate Client Info:";
      cout << "\n____________________\n";

      _readClientInfo(client);

      clsBankClient::enSaveResults saveResult;

      saveResult = client.saveClient();

      switch (saveResult) {
      case clsBankClient::enSaveResults::svSucceeded: {
        cout << "\nAccount Updated Successfully :-)\n";

        _printClient(client);
        break;
      }
      case clsBankClient::enSaveResults::svFaildEmptyObject: {
        cout << "\nError account was not saved because it's Empty";
        break;
      }
      }
    }
  }
};
