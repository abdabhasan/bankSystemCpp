#pragma once
#include "clsMyDateLib.h"
#include "clsMyStringLib.h"
#include <iostream>
#include <limits>
#include <string>

class clsMyInputValidateLib {

public:
  static bool isNumberBetween(short number, short from, short to) {
    if (number >= from && number <= to)
      return true;
    else
      return false;
  }

  static bool isNumberBetween(int number, int from, int to) {
    if (number >= from && number <= to)
      return true;
    else
      return false;
  }

  static bool isNumberBetween(float number, float from, float to) {
    if (number >= from && number <= to)
      return true;
    else
      return false;
  }

  static bool isNumberBetween(double number, double from, double to) {
    if (number >= from && number <= to)
      return true;
    else
      return false;
  }

  static bool isDateBetween(clsMyDateLib date, clsMyDateLib from,
                            clsMyDateLib to) {
    // Date>=from && Date<=to
    if ((clsMyDateLib::isDate1AfterDate2(date, from) ||
         clsMyDateLib::isDate1EqualDate2(date, from)) &&
        (clsMyDateLib::isDate1BeforeDate2(date, to) ||
         clsMyDateLib::isDate1EqualDate2(date, to))) {
      return true;
    }

    // Date>=to && Date<=from
    if ((clsMyDateLib::isDate1AfterDate2(date, to) ||
         clsMyDateLib::isDate1EqualDate2(date, to)) &&
        (clsMyDateLib::isDate1BeforeDate2(date, from) ||
         clsMyDateLib::isDate1EqualDate2(date, from))) {
      return true;
    }

    return false;
  }

  static int
  readIntNumber(string errorMessage = "Invalid number, Enter again\n") {
    int number;
    while (!(cin >> number)) {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << errorMessage;
    }
    return number;
  }

  static int readIntNumberBetween(
      int from, int to,
      string errorMessage = "Number is not within range, Enter again:\n") {
    int number = readIntNumber();

    while (!isNumberBetween(number, from, to)) {
      cout << errorMessage;
      number = readIntNumber();
    }
    return number;
  }

  static short
  readShortNumber(string errorMessage = "Invalid number, Enter again\n") {
    short number;
    while (!(cin >> number)) {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << errorMessage;
    }
    return number;
  }

  static short readShortNumberBetween(
      short from, short to,
      string errorMessage = "Number isn't in range, try again:\n") {

    short number = readShortNumber();

    while (!isNumberBetween(number, from, to)) {
      cout << errorMessage;
      number = readShortNumber();
    }
    return number;
  }

  static double
  readDblNumber(string errorMessage = "Invalid number, Enter again\n") {
    double number;
    while (!(cin >> number)) {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << errorMessage;
    }
    return number;
  }

  static double readDblNumberBetween(
      double from, double to,
      string errorMessage = "Number is not within range, Enter again:\n") {
    double number = readDblNumber();

    while (!isNumberBetween(number, from, to)) {
      cout << errorMessage;
      number = readDblNumber();
    }
    return number;
  }

  static bool isValideDate(clsMyDateLib Date) {
    return clsMyDateLib::isValidDate(Date);
  }

  static string readString() {
    string s1 = "";
    // Usage of std::ws will extract all the whitespace character
    getline(cin >> ws, s1);
    return s1;
  }
};
