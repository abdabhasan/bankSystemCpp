#pragma once

#include "../person/clsPerson.h"
#include "../utils/clsMyInputValidateLib.h"
#include "../utils/clsMyStringLib.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class clsBankClient : public clsPerson {

private:
  enum enMode { emptyMode = 0, updateMode = 1, addNewMode = 2 };
  enMode _mode;

  string _accountNumber;
  short _pinCode;
  float _accountBalance;
  bool _markedForDelete = false;

  bool _isEmpty() { return (_mode == enMode::emptyMode); }
  static clsBankClient _convertLineToClientObject(string line,
                                                  string seperator = "#//#") {
    vector<string> vClientData;
    vClientData = clsMyStringLib::split(line, seperator);

    return clsBankClient(enMode::updateMode, vClientData[0], vClientData[1],
                         vClientData[2], vClientData[3], vClientData[4],
                         stoi(vClientData[5]), stod(vClientData[6]));
  }

  static clsBankClient _getEmptyClientObject() {
    return clsBankClient(enMode::emptyMode, "", "", "", "", "", 0, 0);
  }

  static string _convertClientObjectToLine(clsBankClient client,
                                           string seperator = "#//#") {

    string stClientRecord = "";

    stClientRecord += client.getFirstName() + seperator;
    stClientRecord += client.getLastName() + seperator;
    stClientRecord += client.getEmail() + seperator;
    stClientRecord += client.getPhone() + seperator;
    stClientRecord += client.getAccountNumber() + seperator;
    stClientRecord += to_string(client.getPinCode()) + seperator;
    stClientRecord += to_string(client.getAccountBalance()) + seperator;

    return stClientRecord;
  }

  static void _saveClientsDataToFile(vector<clsBankClient> vClients) {

    fstream myFile;
    myFile.open("clients.txt", ios::out); // overwrite mode

    string dataLine;

    if (myFile.is_open()) {

      for (clsBankClient c : vClients) {

        if (c.getMarkedForDelete() == false) {

          dataLine = _convertClientObjectToLine(c);
          myFile << dataLine << endl;
        }
      }
    }
  }

  static vector<clsBankClient> _loadClientsDataFromFile() {
    vector<clsBankClient> vClients;

    fstream myFile;
    myFile.open("clients.txt", ios::in); // read mode

    if (myFile.is_open()) {
      string line;

      while (getline(myFile, line)) {
        clsBankClient client = _convertLineToClientObject(line);
        vClients.push_back(client);
      }
      myFile.close();
    }
    return vClients;
  }

  void _updateClient() {
    vector<clsBankClient> vClients;
    vClients = _loadClientsDataFromFile();

    for (clsBankClient &c : vClients) {
      if (c.getAccountNumber() == getAccountNumber()) {
        c = *this;
        break;
      }
    }
    _saveClientsDataToFile(vClients);
  }

  void _addNewClient() {
    _addDataLineToFile(_convertClientObjectToLine(*this));
  }

  void _addDataLineToFile(string stDataLine) {

    fstream myFile;
    myFile.open("clients.txt", ios::out | ios::app);

    if (myFile.is_open()) {

      myFile << stDataLine << endl;

      myFile.close();
    }
  }

public:
  clsBankClient(enMode mode, string firstName, string lastName, string email,
                string phone, string accountNumber, short pinCode,
                float accountBalance)
      : clsPerson(firstName, lastName, email, phone) {
    _mode = mode;
    _accountNumber = accountNumber;
    _pinCode = pinCode;
    _accountBalance = accountBalance;
  }

  string getAccountNumber() { return _accountNumber; }
  void setPinCode(short pinCode) { _pinCode = pinCode; }

  short getPinCode() { return _pinCode; }

  void setAccountBalance(float accountBalance) {
    _accountBalance = accountBalance;
  }

  float getAccountBalance() { return _accountBalance; }

  bool getMarkedForDelete() { return _markedForDelete; }

  void printClient() {

    cout << "\nClient:";
    cout << "\n----------------------";
    cout << "\nAccount Number   : " << getAccountNumber();
    cout << "\nFull Name        : " << getFullName();
    cout << "\nEmail            : " << getEmail();
    cout << "\nPin              : " << getPinCode();
    cout << "\nBalance          : " << getAccountBalance();
    cout << "\n----------------------" << endl;
  }

  static clsBankClient findClientByAccountNumber(string accountNumber) {
    vector<clsBankClient> vClients;
    fstream myFile;

    myFile.open("clients.txt", ios::in); // read mode

    if (myFile.is_open()) {

      string line;

      while (getline(myFile, line)) {

        clsBankClient client = _convertLineToClientObject(line);
        if (client.getAccountNumber() == accountNumber) {
          myFile.close();
          return client;
        }
        vClients.push_back(client);
      }
      myFile.close();
    }
    return _getEmptyClientObject();
  }

  static clsBankClient findClientByAccountNumberAndPinCode(string accountNumber,
                                                           short pinCode) {
    vector<clsBankClient> vClients;
    fstream myFile;

    myFile.open("clients.txt", ios::in); // read mode

    if (myFile.is_open()) {

      string line;

      while (getline(myFile, line)) {

        clsBankClient client = _convertLineToClientObject(line);
        if (client.getAccountNumber() == accountNumber &&
            client.getPinCode() == pinCode) {
          myFile.close();
          return client;
        }
        vClients.push_back(client);
      }
      myFile.close();
    }
    return _getEmptyClientObject();
  }

  static bool isClientExist(string accountNumber) {
    clsBankClient client =
        clsBankClient::findClientByAccountNumber(accountNumber);
    return (!client._isEmpty());
  }

  enum enSaveResults {
    svFaildEmptyObject = 0,
    svSucceeded = 1,
    svFaildAccountExists = 2
  };

  enSaveResults saveClient() {

    switch (_mode) {
    case enMode::emptyMode:
      return enSaveResults::svFaildEmptyObject;

    case enMode::updateMode: {
      _updateClient();
      return enSaveResults::svSucceeded;
    }
    case enMode::addNewMode: {

      if (clsBankClient::isClientExist(getAccountNumber())) {
        return enSaveResults::svFaildAccountExists;
      } else {
        _addNewClient();

        _mode = enMode::updateMode;
        return enSaveResults::svSucceeded;
      }
    }

    default:
      break;
    }
  }

  static clsBankClient getAddNewClientObject(string accountNumber) {
    return clsBankClient(enMode::addNewMode, "", "", "", "", accountNumber,
                         0000, 0);
  }

  bool deleteClient() {
    vector<clsBankClient> vClients;
    vClients = _loadClientsDataFromFile();
    for (clsBankClient &c : vClients) {
      if (c.getAccountNumber() == _accountNumber) {
        c._markedForDelete = true;
        break;
      }
    }

    _saveClientsDataToFile(vClients);

    *this = _getEmptyClientObject();
    return true;
  }

  static vector<clsBankClient> getClientsList() {
    return _loadClientsDataFromFile();
  }

  void deposit(double amount) {
    setAccountBalance(getAccountBalance() + amount);

    saveClient();
  }

  void withdraw(double amount) {
    setAccountBalance(getAccountBalance() - amount);

    saveClient();
  }
};