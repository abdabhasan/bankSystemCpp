#include "src/headerFiles/bankClient/clsBankClient.h"
#include <iostream>

using namespace std;

int main() {

  clsBankClient client1 = clsBankClient::findClientByAccountNumber("A101");
  client1.printClient();

  clsBankClient client2 =
      clsBankClient::findClientByAccountNumberAndPinCode("A101", 4151);
  client2.printClient();

  return 0;
}