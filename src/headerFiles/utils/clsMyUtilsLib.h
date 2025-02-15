#pragma once
#include "clsMyDateLib.h"
#include <iostream>
#include <string>

using namespace std;

class clsMyUtilsLib {

public:
  enum encharType {
    samallLetter = 1,
    capitalLetter = 2,
    digit = 3,
    mixChars = 4,
    specialCharacter = 5
  };

  static void seedSrand() {
    // Seeds the random number generator in C++, called only once
    srand((unsigned)time(NULL));
  }

  static int randomNumber(int from, int to) {
    // Function to generate a random number
    int randNum = rand() % (to - from + 1) + from;
    return randNum;
  }

  static char getRandomCharacter(encharType charType) {

    // updated this method to accept mixchars
    if (charType == mixChars) {
      // Capital/Samll/digits only
      charType = (encharType)randomNumber(1, 3);
    }

    switch (charType) {

    case encharType::samallLetter: {
      return char(randomNumber(97, 122));
      break;
    }
    case encharType::capitalLetter: {
      return char(randomNumber(65, 90));
      break;
    }
    case encharType::specialCharacter: {
      return char(randomNumber(33, 47));
      break;
    }
    case encharType::digit: {
      return char(randomNumber(48, 57));
      break;
    }
    defualt: {
      return char(randomNumber(65, 90));
      break;
    }
    }
  }

  static string generateWord(encharType charType, short length)

  {
    string word;

    for (int i = 1; i <= length; i++)

    {

      word = word + getRandomCharacter(charType);
    }
    return word;
  }

  static string generateKey(encharType charType = capitalLetter) {

    string key = "";

    key = generateWord(charType, 4) + "-";
    key = key + generateWord(charType, 4) + "-";
    key = key + generateWord(charType, 4) + "-";
    key = key + generateWord(charType, 4);

    return key;
  }

  static void generateKeys(short numberOfKeys, encharType charType) {

    for (int i = 1; i <= numberOfKeys; i++)

    {
      cout << "Key [" << i << "] : ";
      cout << generateKey(charType) << endl;
    }
  }

  static void fillArrayWithrandomNumbers(int arr[100], int arrLength, int from,
                                         int to) {
    for (int i = 0; i < arrLength; i++)
      arr[i] = randomNumber(from, to);
  }

  static void fillArrayWithRandomWords(string arr[100], int arrLength,
                                       encharType charType, short wordlength) {
    for (int i = 0; i < arrLength; i++)
      arr[i] = generateWord(charType, wordlength);
  }

  static void fillArrayWithRandomKeys(string arr[100], int arrLength,
                                      encharType charType) {
    for (int i = 0; i < arrLength; i++)
      arr[i] = generateKey(charType);
  }

  static void swap(int &a, int &b) {
    int temp;

    temp = a;
    a = b;
    b = temp;
  }

  static void swap(double &a, double &b) {
    double temp;

    temp = a;
    a = b;
    b = temp;
  }

  static void swap(bool &a, bool &b) {
    bool temp;

    temp = a;
    a = b;
    b = temp;
  }

  static void swap(char &a, char &b) {
    char temp;

    temp = a;
    a = b;
    b = temp;
  }

  static void swap(string &a, string &b) {
    string temp;

    temp = a;
    a = b;
    b = temp;
  }

  static void swap(clsMyDateLib &a, clsMyDateLib &b) {
    clsMyDateLib::swapDates(a, b);
  }

  static void shuffleArray(int arr[100], int arrLength) {

    for (int i = 0; i < arrLength; i++) {
      swap(arr[randomNumber(1, arrLength) - 1],
           arr[randomNumber(1, arrLength) - 1]);
    }
  }

  static void shuffleArray(string arr[100], int arrLength) {

    for (int i = 0; i < arrLength; i++) {
      swap(arr[randomNumber(1, arrLength) - 1],
           arr[randomNumber(1, arrLength) - 1]);
    }
  }

  static string tabs(short numberOfTabs) {
    string t = "";

    for (int i = 1; i < numberOfTabs; i++) {
      t = t + "\t";
      cout << t;
    }
    return t;
  }

  static string encryptText(string text, short encryptionKey) {

    for (int i = 0; i <= text.length(); i++) {

      text[i] = char((int)text[i] + encryptionKey);
    }

    return text;
  }

  static string decryptText(string text, short encryptionKey) {

    for (int i = 0; i <= text.length(); i++) {

      text[i] = char((int)text[i] - encryptionKey);
    }
    return text;
  }
};
