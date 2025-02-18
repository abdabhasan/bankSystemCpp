#include "./src/headerFiles/screens/loginScreen/clsLoginScreen.h"
#include <iomanip>
#include <iostream>

using namespace std;

int main() {

  while (true) {

    if (!clsLoginScreen::showLoginScreen()) {
      break;
    }
  }

  return 0;
}