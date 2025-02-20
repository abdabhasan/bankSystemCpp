#pragma once
#include "../../../user/clsUser.h"
#include "../../../utils/clsMyInputValidateLib.h"
#include "../../screen/clsScreen.h"
#include <iomanip>
#include <iostream>
using namespace std;

class clsAddNewUserScreen : protected clsScreen {
private:
  static void _readUserInfo(clsUser &user) {
    cout << "\nEnter FirstName: ";
    user.setFirstName(clsMyInputValidateLib::readString());

    cout << "\nEnter LastName: ";
    user.setLastName(clsMyInputValidateLib::readString());

    cout << "\nEnter Email: ";
    user.setEmail(clsMyInputValidateLib::readString());

    cout << "\nEnter Phone: ";
    user.setPhone(clsMyInputValidateLib::readString());

    cout << "\nEnter Password: ";
    user.setPassword(clsMyInputValidateLib::readString());

    cout << "\nEnter Permission: ";
    user.setPermissions(_readPermissionsToSet());
  }

  static void _printUser(clsUser user) {
    cout << "\nUser Card:";
    cout << "\n___________________";
    cout << "\nFull Name   : " << user.getFullName();
    cout << "\nEmail       : " << user.getEmail();
    cout << "\nPhone       : " << user.getPhone();
    cout << "\nuser Name   : " << user.getUserName();
    cout << "\nPassword    : " << user.getPassword();
    cout << "\nPermissions : " << user.getPermissions();
    cout << "\n___________________\n";
  }

  static int _readPermissionsToSet() {

    int permissions = 0;
    char answer = 'n';

    cout << "\nDo you want to give full access? y/n? ";
    cin >> answer;
    if (answer == 'y' || answer == 'Y') {
      return -1;
    }

    cout << "\nDo you want to give access to : \n ";

    cout << "\nShow Client List? y/n? ";
    cin >> answer;
    if (answer == 'y' || answer == 'Y') {

      permissions += clsUser::enPermissions::pListClients;
    }

    cout << "\nAdd New Client? y/n? ";
    cin >> answer;
    if (answer == 'y' || answer == 'Y') {
      permissions += clsUser::enPermissions::pAddNewClient;
    }

    cout << "\nDelete Client? y/n? ";
    cin >> answer;
    if (answer == 'y' || answer == 'Y') {
      permissions += clsUser::enPermissions::pDeleteClient;
    }

    cout << "\nUpdate Client? y/n? ";
    cin >> answer;
    if (answer == 'y' || answer == 'Y') {
      permissions += clsUser::enPermissions::pUpdateClients;
    }

    cout << "\nFind Client? y/n? ";
    cin >> answer;
    if (answer == 'y' || answer == 'Y') {
      permissions += clsUser::enPermissions::pFindClient;
    }

    cout << "\nTransactions? y/n? ";
    cin >> answer;
    if (answer == 'y' || answer == 'Y') {
      permissions += clsUser::enPermissions::pTranactions;
    }

    cout << "\nManage Users? y/n? ";
    cin >> answer;
    if (answer == 'y' || answer == 'Y') {
      permissions += clsUser::enPermissions::pManageUsers;
    }

    cout << "\nShow Login Register? y/n? ";
    cin >> answer;
    if (answer == 'y' || answer == 'Y') {
      permissions += clsUser::enPermissions::pShowLoginRegister;
    }

    return permissions;
  }

public:
  static void showAddNewUserScreen() {

    _drawScreenHeader("\t  Add New User Screen");

    string userName = "";

    cout << "\nPlease Enter User Name: ";
    userName = clsMyInputValidateLib::readString();
    while (clsUser::isUserExist(userName)) {
      cout << "\nUserName Is Already Used, Choose another one: ";
      userName = clsMyInputValidateLib::readString();
    }

    clsUser newUser = clsUser::getAddNewUserObject(userName);

    _readUserInfo(newUser);

    clsUser::enSaveResults saveResult;

    saveResult = newUser.saveUser();

    switch (saveResult) {
    case clsUser::enSaveResults::svSucceeded: {
      cout << "\nUser Addeded Successfully :-)\n";
      _printUser(newUser);
      break;
    }
    case clsUser::enSaveResults::svFaildEmptyObject: {
      cout << "\nError User was not saved because it's Empty";
      break;
    }
    case clsUser::enSaveResults::svFaildUserExists: {
      cout << "\nError User was not saved because UserName is used!\n";
      break;
    }
    }
  }
};
