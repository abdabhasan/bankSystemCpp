#pragma once
#include "../../utils/clsMyInputValidateLib.h"
#include "../screen/clsScreen.h"
#include "./listUsersScreen/clsListUsersScreen.h"
#include <iomanip>
#include <iostream>
using namespace std;

class clsManageUsersScreen : protected clsScreen {

private:
  enum enManageUsersMenuOptions {
    eListUsers = 1,
    eAddNewUser = 2,
    eDeleteUser = 3,
    eUpdateUser = 4,
    eFindUser = 5,
    eMainMenu = 6
  };

  static short _readManageUsersMenuOption() {
    cout << setw(37) << left << ""
         << "Choose what do you want to do? [1 to 6]? ";
    short choice = clsMyInputValidateLib::readShortNumberBetween(
        1, 6, "Enter Number between 1 to 6? ");
    return choice;
  }

  static void _goBackToManageUsersMenu() {
    cout << "\n\nPress any key to go back to Manage Users Menu...";
    cin.ignore(); // Clear any previous input
    getchar();    // Wait for a key press
    showManageUsersMenu();
  }

  static void _showListUsersScreen() { clsListUsersScreen::showUsersList(); }

  static void _showAddNewUserScreen() {
    cout << "\nAdd New User Screen Will Be Here.\n";
  }

  static void _showDeleteUserScreen() {
    cout << "\nDelete User Screen Will Be Here.\n";
  }

  static void _showUpdateUserScreen() {
    cout << "\nUpdate User Screen Will Be Here.\n";
  }

  static void _showFindUserScreen() {
    cout << "\nFind User Screen Will Be Here.\n";
  }

  static void _performManageUsersMenuOption(
      enManageUsersMenuOptions manageUsersMenuOption) {

    switch (manageUsersMenuOption) {
    case enManageUsersMenuOptions::eListUsers: {
      system("clear");
      _showListUsersScreen();
      _goBackToManageUsersMenu();
      break;
    }

    case enManageUsersMenuOptions::eAddNewUser: {
      system("clear");
      _showAddNewUserScreen();
      _goBackToManageUsersMenu();
      break;
    }

    case enManageUsersMenuOptions::eDeleteUser: {
      system("clear");
      _showDeleteUserScreen();
      _goBackToManageUsersMenu();
      break;
    }

    case enManageUsersMenuOptions::eUpdateUser: {
      system("clear");
      _showUpdateUserScreen();
      _goBackToManageUsersMenu();
      break;
    }

    case enManageUsersMenuOptions::eFindUser: {
      system("clear");

      _showFindUserScreen();
      _goBackToManageUsersMenu();
      break;
    }

    case enManageUsersMenuOptions::eMainMenu: {
      // do nothing here the main screen will handle it :-) ;
    }
    }
  }

public:
  static void showManageUsersMenu() {

    system("clear");
    _drawScreenHeader("\t Manage Users Screen");

    cout << setw(37) << left << ""
         << "===========================================\n";
    cout << setw(37) << left << "" << "\t\t  Manage Users Menu\n";
    cout << setw(37) << left << ""
         << "===========================================\n";
    cout << setw(37) << left << "" << "\t[1] List Users.\n";
    cout << setw(37) << left << "" << "\t[2] Add New User.\n";
    cout << setw(37) << left << "" << "\t[3] Delete User.\n";
    cout << setw(37) << left << "" << "\t[4] Update User.\n";
    cout << setw(37) << left << "" << "\t[5] Find User.\n";
    cout << setw(37) << left << "" << "\t[6] Main Menu.\n";
    cout << setw(37) << left << ""
         << "===========================================\n";

    _performManageUsersMenuOption(
        (enManageUsersMenuOptions)_readManageUsersMenuOption());
  }
};
