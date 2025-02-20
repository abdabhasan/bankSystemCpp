#pragma once
#include "../../../user/clsUser.h"
#include "../../../utils/clsMyInputValidateLib.h"
#include "../../screen/clsScreen.h"
#include <iomanip>
#include <iostream>
using namespace std;

class clsUpdateUserScreen : protected clsScreen

{
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
  static void showUpdateUserScreen() {

    _drawScreenHeader("\tUpdate User Screen");

    string userName = "";

    cout << "\nPlease Enter User UserName: ";
    userName = clsMyInputValidateLib::readString();

    while (!clsUser::isUserExist(userName)) {
      cout << "\nAccount number is not found, choose another one: ";
      userName = clsMyInputValidateLib::readString();
    }

    clsUser user = clsUser::findUserByUserName(userName);

    _printUser(user);

    cout << "\nAre you sure you want to update this User y/n? ";

    char answer = 'n';
    cin >> answer;

    if (answer == 'y' || answer == 'Y') {

      cout << "\n\nUpdate User Info:";
      cout << "\n____________________\n";

      _readUserInfo(user);

      clsUser::enSaveResults saveResult;

      saveResult = user.saveUser();

      switch (saveResult) {
      case clsUser::enSaveResults::svSucceeded: {
        cout << "\nUser Updated Successfully :-)\n";

        _printUser(user);
        break;
      }
      case clsUser::enSaveResults::svFaildEmptyObject: {
        cout << "\nError User was not saved because it's Empty";
        break;
      }
      }
    }
  }
};
