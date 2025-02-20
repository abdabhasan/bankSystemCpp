#pragma once

#include "../../utils/clsMyInputValidateLib.h"
#include "../addNewClientScreen/clsAddNewClientScreen.h"
#include "../clientListScreen/clsClientListScreen.h"
#include "../deleteClientScreen/clsDeleteClientScreen.h"
#include "../manageUsersScreen/clsManageUsersScreen.h"
#include "../registerLoginsScreen/clsRegisterLoginsScreen.h"
#include "../screen/clsScreen.h"
#include "../transactionsScreen/clsTransactionsScreen.h"
#include "../updateClientScreen/clsUpdateClientScreen.h"

#include <iomanip>
#include <iostream>

using namespace std;

class clsMainScreen : protected clsScreen {

private:
  enum enMainMenuOptions {
    eListClients = 1,
    eAddNewClient = 2,
    eDeleteClient = 3,
    eUpdateClient = 4,
    eFindClient = 5,
    eShowTransactionsMenu = 6,
    eManageUsers = 7,
    eLoginRegister = 8,
    eExit = 9
  };

  static short _readMainMenuOption() {
    cout << setw(37) << left << ""
         << "Choose what do you want to do? [1 to 9]? ";
    short choice = clsMyInputValidateLib::readShortNumberBetween(
        1, 9, "Enter Number between 1 to 8? ");
    return choice;
  }

  static void _goBackToMainMenu() {
    cout << setw(37) << left << ""
         << "\n\tPress any key to go back to Main Menu...\n";

    cin.ignore(); // Clear any previous input
    getchar();    // Wait for a key press
    showMainMenu();
  }

  static void _showAllClientsScreen() {
    clsClientListScreen::showClientsList();
  }

  static void _showAddNewClientsScreen() {
    clsAddNewClientScreen::showAddNewClientScreen();
  }

  static void _showDeleteClientScreen() {
    clsDeleteClientScreen::showDeleteClientScreen();
  }

  static void _showUpdateClientScreen() {
    clsUpdateClientScreen::showUpdateClientScreen();
  }

  static void _showFindClientScreen() {
    cout << "\nFind Client Screen Will be here...\n";
  }

  static void _showTransactionsMenu() {
    clsTransactionsScreen::showTransactionsMenu();
  }

  static void _showManageUsersMenu() {
    clsManageUsersScreen::showManageUsersMenu();
  }

  static void _showRegisterLoginsMenu() {
    clsLoginRegisterScreen::showLoginRegisterScreen();
  }

  static void _logout() {

    currentUser = clsUser::findUserByUserNameAndPassword("", "");
  }

  static void _perfromMainMenuOption(enMainMenuOptions mainMenuOption) {
    switch (mainMenuOption) {
    case enMainMenuOptions::eListClients: {
      system("clear");
      _showAllClientsScreen();
      _goBackToMainMenu();
      break;
    }
    case enMainMenuOptions::eAddNewClient:
      system("clear");
      _showAddNewClientsScreen();
      _goBackToMainMenu();
      break;

    case enMainMenuOptions::eDeleteClient:
      system("clear");
      _showDeleteClientScreen();
      _goBackToMainMenu();
      break;

    case enMainMenuOptions::eUpdateClient:
      system("clear");
      _showUpdateClientScreen();
      _goBackToMainMenu();
      break;

    case enMainMenuOptions::eFindClient:
      system("clear");
      _showFindClientScreen();
      _goBackToMainMenu();
      break;

    case enMainMenuOptions::eShowTransactionsMenu:
      system("clear");
      _showTransactionsMenu();
      _goBackToMainMenu();
      break;

    case enMainMenuOptions::eManageUsers:
      system("clear");
      _showManageUsersMenu();
      _goBackToMainMenu();
      break;

    case enMainMenuOptions::eLoginRegister:
      system("clear");
      _showRegisterLoginsMenu();
      _goBackToMainMenu();
      break;

    case enMainMenuOptions::eExit:
      system("clear");
      _logout();
      break;
    }
  }

public:
  static void showMainMenu() {

    system("clear");
    _drawScreenHeader("\t\tMain Screen");

    cout << setw(37) << left << ""
         << "===========================================\n";
    cout << setw(37) << left << "" << "\t\t\tMain Menu\n";
    cout << setw(37) << left << ""
         << "===========================================\n";
    cout << setw(37) << left << "" << "\t[1] Show Client List.\n";
    cout << setw(37) << left << "" << "\t[2] Add New Client.\n";
    cout << setw(37) << left << "" << "\t[3] Delete Client.\n";
    cout << setw(37) << left << "" << "\t[4] Update Client Info.\n";
    cout << setw(37) << left << "" << "\t[5] Find Client.\n";
    cout << setw(37) << left << "" << "\t[6] Transactions.\n";
    cout << setw(37) << left << "" << "\t[7] Manage Users.\n";
    cout << setw(37) << left << "" << "\t[8] Logins Registers.\n";
    cout << setw(37) << left << "" << "\t[9] Logout.\n";
    cout << setw(37) << left << ""
         << "===========================================\n";

    _perfromMainMenuOption((enMainMenuOptions)_readMainMenuOption());
  }
};
