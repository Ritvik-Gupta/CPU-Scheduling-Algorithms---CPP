#ifndef SYMBOL_services_1601875909
#define SYMBOL_services_1601875909

#include <vector>
#include <random>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <windows.h>
#include <pthread.h>
using namespace std;

string NONE_SYMBOL = "*";
pthread_mutex_t* consoleLock = new pthread_mutex_t;

void initGlobalVariables() {
   pthread_mutex_init(consoleLock, NULL);
}

void destroyGlobalVariables() {
   pthread_mutex_destroy(consoleLock);
}

vector<string>* split(string* line, const char* spl) {
   vector<string>* vec = new vector<string>;
   char* token;
   char str[line->size()];
   strcpy(str, line->c_str());
   token = strtok(str, spl);
   while (token != NULL) {
      vec->push_back(token);
      token = strtok(NULL, spl);
   }
   return vec;
}

minstd_rand0 generator(chrono::system_clock::now().time_since_epoch().count());

enum constants { DELIMETER = '~', EMPTY = ' ' };
const unsigned horizWidth = 14;
const unsigned vertiWidth = 7;

const void horizDiv(char fill) {
   cout << left << setw(horizWidth) << setfill(fill) << "";
   cout << setfill(' ');
}

const void vertiDiv(char fill) {
   cout << left << setw(vertiWidth) << setfill(fill) << "|";
   cout << setfill(' ');
}

const void partition(unsigned size, char ch, bool hasVerti = true) {
   for (unsigned i = 0; i < size; ++i) {
      if (hasVerti) vertiDiv(ch);
      horizDiv(ch);
   }
}

enum possibleColors {
   BLACK, BLUE, GREEN, AQUA, RED, PURPLE, YELLOW, WHITE, GRAY, LIGHT_BLUE,
   LIGHT_GREEN, LIGHT_AQUA, LIGHT_RED, LIGHT_PURPLE, LIGHT_YELLOW, BRIGHT_WHITE
};
class ColorPalette {

private:
   static vector<possibleColors>* colorStack;
   static HANDLE colorHandle;

public:
   static void add(possibleColors col) {
      colorStack->push_back(col);
      SetConsoleTextAttribute(colorHandle, col);
   }

   static void remove() {
      colorStack->pop_back();
      SetConsoleTextAttribute(colorHandle, (colorStack->size() == 0) ? WHITE : colorStack->back());
   }

   static void clear() {
      colorStack->clear();
      SetConsoleTextAttribute(colorHandle, WHITE);
   }

};
vector<possibleColors>* ColorPalette::colorStack = new vector<possibleColors>;
HANDLE ColorPalette::colorHandle = GetStdHandle(STD_OUTPUT_HANDLE);

#endif
