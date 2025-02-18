#pragma once

#include "../../bankClient/clsBankClient.h"
#include "../../utils/clsMyInputValidateLib.h"
#include "../screen/clsScreen.h"

#include <iomanip>
#include <iostream>

class clsAddNewClientScreen : protected clsScreen {
private:
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
  static void showAddNewClientScreen() {

    if (!checkAccessRights(clsUser::enPermissions::pAddNewClient)) {
      return;
    }

    _drawScreenHeader("\t  Add New Client Screen");

    string accountNumber = "";

    cout << "\nPlease Enter Account Number: ";
    accountNumber = clsMyInputValidateLib::readString();
    while (clsBankClient::isClientExist(accountNumber)) {
      cout << "\nAlready Used, try again! : ";
      accountNumber = clsMyInputValidateLib::readString();
    }

    clsBankClient newClient =
        clsBankClient::getAddNewClientObject(accountNumber);

    _readClientInfo(newClient);

    clsBankClient::enSaveResults SaveResult;

    SaveResult = newClient.saveClient();

    switch (SaveResult) {
    case clsBankClient::enSaveResults::svSucceeded: {
      cout << "\nAccount Addeded Successfully :-)\n";
      _printClient(newClient);
      break;
    }
    case clsBankClient::enSaveResults::svFaildEmptyObject: {
      cout << "\nError account was not saved because it's Empty";
      break;
    }
    case clsBankClient::enSaveResults::svFaildAccountExists: {
      cout << "\nError account was not saved because account number is used!\n";
      break;
    }
    }
  }
};
