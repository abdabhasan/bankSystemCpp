#pragma once
#include "../../../user/clsUser.h"
#include "../../../utils/clsMyInputValidateLib.h"
#include "../../screen/clsScreen.h"
#include <iomanip>
#include <iostream>
using namespace std;

class clsListUsersScreen : protected clsScreen {

private:
  static void _printUserRecordLine(clsUser user) {

    cout << setw(8) << left << "" << "| " << setw(12) << left
         << user.getUserName();
    cout << "| " << setw(25) << left << user.getFullName();
    cout << "| " << setw(12) << left << user.getPhone();
    cout << "| " << setw(20) << left << user.getEmail();
    cout << "| " << setw(10) << left << user.getPassword();
    cout << "| " << setw(12) << left << user.getPermissions();
  }

public:
  static void showUsersList() {
    vector<clsUser> vUsers = clsUser::getUsersList();

    string title = "\t  User List Screen";
    string subtitle = "\t    (" + to_string(vUsers.size()) + ") User(s).";

    _drawScreenHeader(title, subtitle);

    cout << setw(8) << left << ""
         << "\n\t_______________________________________________________";
    cout << "______________________________________________\n" << endl;

    cout << setw(8) << left << "" << "| " << left << setw(12) << "UserName";
    cout << "| " << left << setw(25) << "Full Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(20) << "Email";
    cout << "| " << left << setw(10) << "Password";
    cout << "| " << left << setw(12) << "Permissions";
    cout << setw(8) << left << ""
         << "\n\t_______________________________________________________";
    cout << "______________________________________________\n" << endl;

    if (vUsers.size() == 0)
      cout << "\t\t\t\tNo Users Available In the System!";
    else

      for (clsUser user : vUsers) {

        _printUserRecordLine(user);
        cout << endl;
      }

    cout << setw(8) << left << ""
         << "\n\t_______________________________________________________";
    cout << "______________________________________________\n" << endl;
  }
};