#pragma once
#include "../../../user/clsUser.h"
#include "../../../utils/clsMyInputValidateLib.h"
#include "../../screen/clsScreen.h"
#include <iomanip>
#include <iostream>
using namespace std;

class clsDeleteUserScreen : protected clsScreen {

private:
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

public:
  static void showDeleteUserScreen() {

    _drawScreenHeader("\tDelete User Screen");

    string userName = "";

    cout << "\nPlease Enter Username: ";
    userName = clsMyInputValidateLib::readString();
    while (!clsUser::isUserExist(userName)) {
      cout << "\nUser is not found, choose another one: ";
      userName = clsMyInputValidateLib::readString();
    }

    clsUser user = clsUser::findUserByUserName(userName);
    _printUser(user);

    cout << "\nAre you sure you want to delete this User y/n? ";

    char answer = 'n';
    cin >> answer;

    if (answer == 'y' || answer == 'Y') {

      if (user.deleteUser()) {
        cout << "\nUser Deleted Successfully :-)\n";
        _printUser(user);
      } else {
        cout << "\nError User Was not Deleted\n";
      }
    }
  }
};
