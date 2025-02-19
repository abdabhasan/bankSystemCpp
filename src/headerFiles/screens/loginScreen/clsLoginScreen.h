#pragma once

#include "../../global.h"
#include "../../user/clsUser.h"
#include "../mainScreen/clsMainScreen.h"
#include "../screen/clsScreen.h"
#include <iomanip>
#include <iostream>

class clsLoginScreen : protected clsScreen {

private:
  static bool _login() {

    bool loginFaild = false;
    short faildLoginCount = 0;

    string username, password;
    do {

      if (loginFaild) {

        faildLoginCount++;

        cout << "\nInvlaid Username/Password!";
        cout << "\nYou have " << (3 - faildLoginCount)
             << " Trial(s) to login.\n\n";
      }

      if (faildLoginCount == 3) {
        cout << "\nYour are Locked after 3 faild trails \n\n";
        return false;
      }

      cout << "Enter Username? ";
      cin >> username;

      cout << "Enter Password? ";
      cin >> password;

      currentUser = clsUser::findUserByUserNameAndPassword(username, password);

      loginFaild = currentUser.isEmpty();

    } while (loginFaild);

    currentUser.registerLogin();
    clsMainScreen::showMainMenu();
    return true;
  }

public:
  static bool showLoginScreen() {
    system("clear");
    _drawScreenHeader("\t  Login Screen");
    return _login();
  }
};
