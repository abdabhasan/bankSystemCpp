#pragma once
#include "../person/clsPerson.h"
#include "../utils/clsMyStringLib.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
class clsUser : public clsPerson {
private:
  enum enMode { emptyMode = 0, updateMode = 1, addNewMode = 2 };
  enMode _mode;
  string _userName;
  string _password;
  int _permissions;

  bool _markedForDelete = false;

  string _prepareLogInRecord(string seperator = "#//#") {
    string loginRecord = "";
    loginRecord += clsMyDateLib::getSystemDateTimeString() + seperator;
    loginRecord += getUserName() + seperator;
    loginRecord += getPassword() + seperator;
    loginRecord += to_string(getPermissions());
    return loginRecord;
  }

  static clsUser _convertLinetoUserObject(string line,
                                          string seperator = "#//#") {
    vector<string> vUserData;
    vUserData = clsMyStringLib::split(line, seperator);

    return clsUser(enMode::updateMode, vUserData[0], vUserData[1], vUserData[2],
                   vUserData[3], vUserData[4], vUserData[5],
                   stoi(vUserData[6]));
  }

  static string _converUserObjectToLine(clsUser user,
                                        string seperator = "#//#") {

    string userRecord = "";
    userRecord += user.getFirstName() + seperator;
    userRecord += user.getLastName() + seperator;
    userRecord += user.getEmail() + seperator;
    userRecord += user.getPhone() + seperator;
    userRecord += user.getUserName() + seperator;
    userRecord += user.getPassword() + seperator;
    userRecord += to_string(user.getPermissions());

    return userRecord;
  }

  static vector<clsUser> _loadUsersDataFromFile() {

    vector<clsUser> vUsers;

    fstream myFile;
    myFile.open("users.txt", ios::in); // read Mode

    if (myFile.is_open()) {

      string line;

      while (getline(myFile, line)) {

        clsUser user = _convertLinetoUserObject(line);

        vUsers.push_back(user);
      }

      myFile.close();
    }

    return vUsers;
  }

  static void _saveUsersDataToFile(vector<clsUser> vUsers) {

    fstream myFile;
    myFile.open("users.txt", ios::out); // overwrite

    string dataLine;

    if (myFile.is_open()) {

      for (clsUser u : vUsers) {
        if (u.markedForDeleted() == false) {
          // we only write records that are not marked for delete.
          dataLine = _converUserObjectToLine(u);
          myFile << dataLine << endl;
        }
      }

      myFile.close();
    }
  }

  void _updateUser() {
    vector<clsUser> _vUsers;
    _vUsers = _loadUsersDataFromFile();

    for (clsUser &u : _vUsers) {
      if (u.getUserName() == getUserName()) {
        u = *this;
        break;
      }
    }

    _saveUsersDataToFile(_vUsers);
  }

  void _addNewUser() { _addDataLineToFile(_converUserObjectToLine(*this)); }

  void _addDataLineToFile(string stDataLine) {
    fstream myFile;
    myFile.open("users.txt", ios::out | ios::app);

    if (myFile.is_open()) {

      myFile << stDataLine << endl;

      myFile.close();
    }
  }

  static clsUser _getEmptyUserObject() {
    return clsUser(enMode::emptyMode, "", "", "", "", "", "", 0);
  }

public:
  enum enPermissions {
    eAll = -1,
    pListClients = 1,
    pAddNewClient = 2,
    pDeleteClient = 4,
    pUpdateClients = 8,
    pFindClient = 16,
    pTranactions = 32,
    pManageUsers = 64
  };

  clsUser(enMode mode, string firstName, string lastName, string email,
          string phone, string userName, string password, int permissions)
      : clsPerson(firstName, lastName, email, phone)

  {
    _mode = mode;
    _userName = userName;
    _password = password;
    _permissions = permissions;
  }

  bool isEmpty() { return (_mode == enMode::emptyMode); }

  bool markedForDeleted() { return _markedForDelete; }

  string getUserName() { return _userName; }

  void setUserName(string userName) { _userName = userName; }

  void setPassword(string password) { _password = password; }

  string getPassword() { return _password; }

  void setPermissions(int permissions) { _permissions = permissions; }

  int getPermissions() { return _permissions; }

  static clsUser findUserByUserName(string userName) {
    fstream myFile;
    myFile.open("users.txt", ios::in); // read Mode

    if (myFile.is_open()) {
      string line;
      while (getline(myFile, line)) {
        clsUser user = _convertLinetoUserObject(line);
        if (user.getUserName() == userName) {
          myFile.close();
          return user;
        }
      }

      myFile.close();
    }

    return _getEmptyUserObject();
  }

  static clsUser findUserByUserNameAndPassword(string userName,
                                               string password) {

    fstream myFile;
    myFile.open("users.txt", ios::in); // read Mode

    if (myFile.is_open()) {
      string line;
      while (getline(myFile, line)) {
        clsUser user = _convertLinetoUserObject(line);
        if (user.getUserName() == userName && user.getPassword() == password) {
          myFile.close();
          return user;
        }
      }

      myFile.close();
    }

    return _getEmptyUserObject();
  }

  enum enSaveResults {
    svFaildEmptyObject = 0,
    svSucceeded = 1,
    svFaildUserExists = 2
  };

  enSaveResults saveUser() {

    switch (_mode) {
    case enMode::emptyMode: {
      if (isEmpty()) {
        return enSaveResults::svFaildEmptyObject;
      }
    }

    case enMode::updateMode: {
      _updateUser();
      return enSaveResults::svSucceeded;

      break;
    }

    case enMode::addNewMode: {
      // This will add new record to file or database
      if (clsUser::isUserExist(_userName)) {
        return enSaveResults::svFaildUserExists;
      } else {
        _addNewUser();
        // We need to set the mode to update after add new
        _mode = enMode::updateMode;
        return enSaveResults::svSucceeded;
      }

      break;
    }
    }
  }

  static bool isUserExist(string userName) {

    clsUser User = clsUser::findUserByUserName(userName);
    return (!User.isEmpty());
  }

  bool deleteUser() {
    vector<clsUser> _vUsers;
    _vUsers = _loadUsersDataFromFile();

    for (clsUser &u : _vUsers) {
      if (u.getUserName() == _userName) {
        u._markedForDelete = true;
        break;
      }
    }

    _saveUsersDataToFile(_vUsers);

    *this = _getEmptyUserObject();

    return true;
  }

  static clsUser getAddNewUserObject(string userName) {
    return clsUser(enMode::addNewMode, "", "", "", "", userName, "", 0);
  }

  static vector<clsUser> getUsersList() { return _loadUsersDataFromFile(); }

  bool checkAccessPermission(enPermissions permission) {
    if (this->getPermissions() == enPermissions::eAll)
      return true;

    if ((permission & this->getPermissions()) == permission)
      return true;

    else
      return false;
  }

  void registerLogin() {

    string stDataLine = _prepareLogInRecord();

    fstream myFile;
    myFile.open("loginRegister.txt", ios::out | ios::app);

    if (myFile.is_open()) {

      myFile << stDataLine << endl;

      myFile.close();
    }
  }
};
