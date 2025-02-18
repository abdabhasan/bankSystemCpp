#pragma once

#include "../../global.h"
#include "../../user/clsUser.h"
#include "../mainScreen/clsMainScreen.h"
#include "../screen/clsScreen.h"
#include <iomanip>
#include <iostream>

class clsLoginScreen : protected clsScreen {

private:
  static void _login() {
    bool loginFaild = false;

    string username, password;
    do {

      if (loginFaild) {
        cout << "\nInvlaid Username/Password!\n\n";
      }

      cout << "Enter Username? ";
      cin >> username;

      cout << "Enter Password? ";
      cin >> password;

      currentUser = clsUser::findUserByUserNameAndPassword(username, password);

      loginFaild = currentUser.isEmpty();

    } while (loginFaild);

    clsMainScreen::showMainMenu();
  }

public:
  static void showLoginScreen() {
    system("clear");
    _drawScreenHeader("\t  Login Screen");
    _login();
  }
};
