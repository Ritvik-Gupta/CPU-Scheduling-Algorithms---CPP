#ifndef SYMBOL_displayGanttChart_1602035553
#define SYMBOL_displayGanttChart_1602035553

#include <vector>
using namespace std;

#include "./Display.hpp"
#include "../services.hpp"

void Display::table(vector<GanttSnapshot*>* ganttChart) {
   vector<GanttSnapshot*>* GC;
   if (ganttChart->size() > 5) {
      table(new vector<GanttSnapshot*>(ganttChart->begin(), next(ganttChart->begin(), 5)));
      GC = new vector<GanttSnapshot*>(next(ganttChart->begin(), 5), ganttChart->end());
   } else
      GC = ganttChart;

   cout << endl << endl;
   ColorPalette::add(LIGHT_YELLOW);

   vertiDiv(DELIMETER);
   partition(2, DELIMETER, false);
   partition(GC->size(), DELIMETER);
   vertiDiv(EMPTY);
   cout << endl;

   vertiDiv(EMPTY);
   ColorPalette::add(GRAY);
   cout << setw(horizWidth * 2) << "Gantt Chart";
   ColorPalette::remove();
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
   ColorPalette::add(GRAY);
   cout << setw(horizWidth * 2) << "Start Time = 0";
   ColorPalette::remove();
   for (unsigned i = 0;i < GC->size();++i) {
      vertiDiv(EMPTY);
      ColorPalette::add(WHITE);
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
