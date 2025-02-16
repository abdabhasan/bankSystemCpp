#include "./src/headerFiles/bankClient/clsBankClient.h"
#include "./src/headerFiles/mainScreen/clsMainScreen.h"
#include <iomanip>
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

void deleteClient() {
  string accountNumber = "";
  cout << "\nPlease enter account number : ";
  accountNumber = clsMyInputValidateLib::readString();
  while (!clsBankClient::isClientExist(accountNumber)) {
    cout << "\nAccount not found, try again: ";
    accountNumber = clsMyInputValidateLib::readString();
  }
  clsBankClient client =
      clsBankClient::findClientByAccountNumber(accountNumber);
  client.printClient();

  cout << "\nAre you sure? y/n?  ";

  char answer = 'n';
  cin >> answer;

  if (answer == 'y' || answer == 'Y') {
    if (client.deleteClient()) {
      cout << "\nClient deleted successfully! ";

      client.printClient();
    } else {
      cout << "\nError, Client was not deleted!" << endl;
    }
  }
}

void printClientRecordLine(clsBankClient client) {

  cout << "| " << setw(15) << left << client.getAccountNumber();
  cout << "| " << setw(20) << left << client.getFullName();
  cout << "| " << setw(12) << left << client.getPhone();
  cout << "| " << setw(20) << left << client.getEmail();
  cout << "| " << setw(10) << left << client.getPinCode();
  cout << "| " << setw(12) << left << client.getAccountBalance();
}

void showClientsList() {
  vector<clsBankClient> vClients = clsBankClient::getClientsList();

  cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
  cout << "\n_______________________________________________________";
  cout << "_________________________________________\n" << endl;

  cout << "| " << left << setw(15) << "Accout Number";
  cout << "| " << left << setw(20) << "Client Name";
  cout << "| " << left << setw(12) << "Phone";
  cout << "| " << left << setw(20) << "Email";
  cout << "| " << left << setw(10) << "Pin Code";
  cout << "| " << left << setw(12) << "Balance";
  cout << "\n_______________________________________________________";
  cout << "_________________________________________\n" << endl;

  if (vClients.size() == 0)
    cout << "\t\t\t\tNo Clients Available In the System!";
  else

    for (clsBankClient client : vClients) {

      printClientRecordLine(client);
      cout << endl;
    }

  cout << "\n_______________________________________________________";
  cout << "_________________________________________\n" << endl;
}

int main() {

  clsMainScreen::showMainMenu();
  return 0;
}