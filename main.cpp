#include "src/headerFiles/bankClient/clsBankClient.h"
#include <iostream>

using namespace std;

void readClientInfo(clsBankClient &client) {

  cout << "\nEnter First Name: ";
  client.setFirstName(clsMyInputValidateLib::readString());

  cout << "\nEnter Last Name: ";
  client.setLastName(clsMyInputValidateLib::readString());

  cout << "\nEnter Email  : ";
  client.setEmail(clsMyInputValidateLib::readString());

  cout << "\nEnter phone : ";
  client.setPhone(clsMyInputValidateLib::readString());

  cout << "\nEnter pin code : ";
  client.setPinCode(clsMyInputValidateLib::readIntNumber());

  cout << "\nEnter account balance : ";
  client.setAccountBalance(clsMyInputValidateLib::readDblNumber());
}

void updateClient() {
  string accountNumber = "";

  cout << "\nPlease enter client Account Number :  ";
  accountNumber = clsMyInputValidateLib::readString();

  while (!clsBankClient::isClientExist(accountNumber)) {
    cout << "\nAccount not found, try again! ";
    accountNumber = clsMyInputValidateLib::readString();
  }

  clsBankClient client =
      clsBankClient::findClientByAccountNumber(accountNumber);
  client.printClient();

  cout << "\n\nUpdate Client info : ";
  cout << "\n-----------------------------\n";

  readClientInfo(client);

  client.saveClient();
}

void addNewClient() {
  string accountNumber = "";

  cout << "\nPlease enter Account Number: ";
  accountNumber = clsMyInputValidateLib::readString();

  while (clsBankClient::isClientExist(accountNumber)) {
    cout << "\nAccount already exists, try again! ";
    accountNumber = clsMyInputValidateLib::readString();
  }

  clsBankClient newClient = clsBankClient::getAddNewClientObject(accountNumber);

  readClientInfo(newClient);

  clsBankClient::enSaveResults saveResult;

  saveResult = newClient.saveClient();

  switch (saveResult) {
  case clsBankClient::enSaveResults::svSucceeded: {
    cout << "\nAccount created successfully :) " << endl;
    newClient.printClient();
    break;
  }
  case clsBankClient::enSaveResults::svFaildEmptyObject: {
    cout << "\nError...";
    break;
  }

  default:
    break;
  }
}

int main() {

  addNewClient();
  return 0;
}