#pragma once

#include "../person/clsPerson.h"
#include "../utils/clsMyStringLib.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class clsBankClient : public clsPerson {

private:
  enum enMode { emptyMode = 0, updateMode = 1 };
  enMode _mode;

  string _accountNumber;
  short _pinCode;
  float _accountBalance;

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
};