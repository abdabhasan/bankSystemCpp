#pragma once
#include "../../bankClient/clsBankClient.h"
#include "../../utils/clsMyInputValidateLib.h"
#include "../screen/clsScreen.h"
#include "./depositScreen/clsDepositScreen.h"
#include "./withdrawScreen/clsWithdrawScreen.h"
#include <iomanip>
#include <iostream>
using namespace std;

class clsTransactionsScreen : protected clsScreen {

private:
  enum enTransactionsMenuOptions {
    eDeposit = 1,
    eWithdraw = 2,
    eShowTotalBalance = 3,
    eShowMainMenu = 4
  };

  static short _readTransactionsMenuOption() {
    cout << setw(37) << left << ""
         << "Choose what do you want to do? [1 to 4]? ";
    short choice = clsMyInputValidateLib::readShortNumberBetween(
        1, 4, "Enter Number between 1 to 4? ");
    return choice;
  }

  static void _showDepositScreen() { clsDepositScreen::showDepositScreen(); }

  static void _showWithdrawScreen() { clsWithdrawScreen::ShowWithdrawScreen(); }

  static void _showTotalBalancesScreen() {
    cout << "\n Balances Screen will be here.\n";
  }

  static void _goBackToTransactionsMenu() {
    cout << "\n\nPress any key to go back to Transactions Menu...";
    cin.ignore(); // Clear any previous input
    getchar();    // Wait for a key press
    showTransactionsMenu();
  }

  static void _performTransactionsMenuOption(
      enTransactionsMenuOptions transactionsMenuOption) {
    switch (transactionsMenuOption) {
    case enTransactionsMenuOptions::eDeposit: {
      system("clear");
      _showDepositScreen();
      _goBackToTransactionsMenu();
      break;
    }

    case enTransactionsMenuOptions::eWithdraw: {
      system("clear");
      _showWithdrawScreen();
      _goBackToTransactionsMenu();
      break;
    }

    case enTransactionsMenuOptions::eShowTotalBalance: {
      system("clear");
      _showTotalBalancesScreen();
      _goBackToTransactionsMenu();
      break;
    }

    case enTransactionsMenuOptions::eShowMainMenu: {
      // do nothing here the main screen will handle it;
    }
    }
  }

public:
  static void showTransactionsMenu() {

    system("clear");
    _drawScreenHeader("\t  Transactions Screen");

    cout << setw(37) << left << ""
         << "===========================================\n";
    cout << setw(37) << left << "" << "\t\t  Transactions Menu\n";
    cout << setw(37) << left << ""
         << "===========================================\n";
    cout << setw(37) << left << "" << "\t[1] Deposit.\n";
    cout << setw(37) << left << "" << "\t[2] Withdraw.\n";
    cout << setw(37) << left << "" << "\t[3] Total Balances.\n";
    cout << setw(37) << left << "" << "\t[4] Main Menu.\n";
    cout << setw(37) << left << ""
         << "===========================================\n";

    _performTransactionsMenuOption(
        (enTransactionsMenuOptions)_readTransactionsMenuOption());
  }
};
