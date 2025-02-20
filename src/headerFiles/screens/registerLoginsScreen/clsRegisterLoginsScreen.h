
#include "../../user/clsUser.h"
#include "../mainScreen/clsMainScreen.h"
#include "../screen/clsScreen.h"
#include <iomanip>
#include <iostream>

class clsLoginRegisterScreen : protected clsScreen {

private:
  static void _printLoginRegisterRecordLine(
      clsUser::stLoginRegisterRecord loginRegisterRecord) {

    cout << setw(8) << left << "" << "| " << setw(35) << left
         << loginRegisterRecord.dateTime;
    cout << "| " << setw(20) << left << loginRegisterRecord.userName;
    cout << "| " << setw(20) << left << loginRegisterRecord.password;
    cout << "| " << setw(10) << left << loginRegisterRecord.permissions;
  }

public:
  static void showLoginRegisterScreen() {

    if (!checkAccessRights(clsUser::enPermissions::pShowLoginRegister)) {
      return;
    }

    vector<clsUser::stLoginRegisterRecord> vLoginRegisterRecord =
        clsUser::getLoginRegisterList();

    string Title = "\tLogin Register List Screen";
    string SubTitle =
        "\t\t(" + to_string(vLoginRegisterRecord.size()) + ") Record(s).";

    _drawScreenHeader(Title, SubTitle);

    cout << setw(8) << left << ""
         << "\n\t_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    cout << setw(8) << left << "" << "| " << left << setw(35) << "Date/Time";
    cout << "| " << left << setw(20) << "UserName";
    cout << "| " << left << setw(20) << "Password";
    cout << "| " << left << setw(10) << "Permissions";
    cout << setw(8) << left << ""
         << "\n\t_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    if (vLoginRegisterRecord.size() == 0)
      cout << "\t\t\t\tNo Logins Available In the System!";
    else

      for (clsUser::stLoginRegisterRecord Record : vLoginRegisterRecord) {

        _printLoginRegisterRecordLine(Record);
        cout << endl;
      }

    cout << setw(8) << left << ""
         << "\n\t_______________________________________________________";
    cout << "_________________________________________\n" << endl;
  }
};
