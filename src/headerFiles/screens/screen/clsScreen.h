#pragma once

#include "../../utils/clsMyDateLib.h"
#include <iostream>
using namespace std;

class clsScreen {

protected:
  static void _drawScreenHeader(string title, string subTitle = "") {
    cout << "\t\t\t\t\t______________________________________";
    cout << "\n\n\t\t\t\t\t  " << title;
    if (subTitle != "") {
      cout << "\n\t\t\t\t\t  " << subTitle;
    }
    cout << "\n\t\t\t\t\t______________________________________\n";
    cout << "\n\t\t\t\t\tUsername: " << currentUser.getUserName() << "\n";
    cout << "\t\t\t\t\tDate: " << clsMyDateLib::dateToString(clsMyDateLib())
         << "\n\n";
  }

  static bool checkAccessRights(clsUser::enPermissions permission) {

    if (!currentUser.checkAccessPermission(permission)) {
      cout << "\t\t\t\t\t______________________________________";
      cout << "\n\n\t\t\t\t\t  Access Denied! Contact your Admin.";
      cout << "\n\t\t\t\t\t______________________________________\n\n";
      return false;
    } else {
      return true;
    }
  }
};
