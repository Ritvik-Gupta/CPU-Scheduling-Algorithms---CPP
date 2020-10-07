#ifndef SYMBOL_services_1601875909
#define SYMBOL_services_1601875909

#include <vector>
#include <random>
#include <chrono>
#include <windows.h>
using namespace std;

#include "./Process.hpp"

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

unsigned seed = chrono::system_clock::now().time_since_epoch().count();
minstd_rand0 generator(seed);

enum constants { DELIMETER = '~', EMPTY = ' ' };

enum QueueTypes { RR, FCFS, SJF, SRT };

struct GanttSnapshot {
   Process* process;
   unsigned recordedTime;
};

#endif
