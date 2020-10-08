#ifndef SYMBOL_displayGanttChart_1602035553
#define SYMBOL_displayGanttChart_1602035553

#include <vector>
using namespace std;

#include "./Display.hpp"
#include "../services.hpp"

void Display::table(vector<GanttSnapshot*>* ganttChart, unsigned beginTime = 0) {
   vector<GanttSnapshot*>* GC = ganttChart;
   vector<GanttSnapshot*>* nextGC = NULL;
   if (ganttChart->size() > 5) {
      GC = new vector<GanttSnapshot*>(ganttChart->begin(), next(ganttChart->begin(), 5));
      nextGC = new vector<GanttSnapshot*>(next(ganttChart->begin(), 5), ganttChart->end());
   }

   cout << endl << endl;
   ColorPalette::add(YELLOW);

   vertiDiv(DELIMETER);
   partition(2, DELIMETER, false);
   ColorPalette::add(LIGHT_YELLOW);
   partition(GC->size(), DELIMETER);
   vertiDiv(EMPTY);
   ColorPalette::remove();
   cout << endl;

   vertiDiv(EMPTY);
   cout << setw(horizWidth * 2) << "Gantt Chart";
   ColorPalette::add(LIGHT_YELLOW);
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
   ColorPalette::remove();
   cout << endl;

   vertiDiv(DELIMETER);
   partition(2, DELIMETER, false);
   ColorPalette::add(LIGHT_YELLOW);
   partition(GC->size(), DELIMETER);
   vertiDiv(EMPTY);
   ColorPalette::remove();
   cout << endl;

   vertiDiv(EMPTY);
   cout << setw(horizWidth * 2) <<
      (beginTime == 0 ? "Record (Start = 0)" : "Continued Time = " + to_string(beginTime));
   ColorPalette::add(LIGHT_YELLOW);
   for (unsigned i = 0;i < GC->size();++i) {
      vertiDiv(EMPTY);
      ColorPalette::add(WHITE);
      cout << setw(horizWidth) << GC->at(i)->recordedTime;
      ColorPalette::remove();
   }
   vertiDiv(EMPTY);
   ColorPalette::remove();
   cout << endl;

   vertiDiv(DELIMETER);
   partition(2, DELIMETER, false);
   ColorPalette::add(LIGHT_YELLOW);
   partition(GC->size(), DELIMETER);
   vertiDiv(EMPTY);
   ColorPalette::remove();
   cout << endl;

   ColorPalette::clear();

   if (nextGC != NULL)
      table(nextGC, GC->back()->recordedTime);
}

#endif
