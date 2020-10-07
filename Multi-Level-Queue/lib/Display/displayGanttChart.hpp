#ifndef SYMBOL_displayGanttChart_1602035553
#define SYMBOL_displayGanttChart_1602035553

#include <vector>
using namespace std;

#include "./Display.hpp"
#include "../services.hpp"

void Display::table(vector<GanttSnapshot*>* GC) {
   ColorPalette::add(LIGHT_YELLOW);

   vertiDiv(DELIMETER);
   partition(2, DELIMETER, false);
   partition(GC->size(), DELIMETER);
   vertiDiv(EMPTY);
   cout << endl;

   vertiDiv(EMPTY);
   cout << setw(horizWidth * 2) << "Gantt Chart";
   for (unsigned i = 0;i < GC->size();++i) {
      vertiDiv(EMPTY);
      if (GC->at(i)->process != NULL) {
         ColorPalette::add(LIGHT_AQUA);
         cout << setw(horizWidth) << GC->at(i)->process->getId();
      } else {
         ColorPalette::add(LIGHT_RED);
         cout << setw(horizWidth) << "*";
      }
      ColorPalette::remove();
   }
   vertiDiv(EMPTY);
   cout << endl;

   vertiDiv(DELIMETER);
   partition(2, DELIMETER, false);
   partition(GC->size(), DELIMETER);
   vertiDiv(EMPTY);
   cout << endl;

   vertiDiv(EMPTY);
   cout << setw(horizWidth * 2) << "Record (Str = 0)";
   for (unsigned i = 0;i < GC->size();++i) {
      vertiDiv(EMPTY);
      ColorPalette::add(BRIGHT_WHITE);
      cout << setw(horizWidth) << GC->at(i)->recordedTime;
      ColorPalette::remove();
   }
   vertiDiv(EMPTY);
   cout << endl;

   vertiDiv(DELIMETER);
   partition(2, DELIMETER, false);
   partition(GC->size(), DELIMETER);
   vertiDiv(EMPTY);
   cout << endl;

   ColorPalette::clear();
}

#endif
