#ifndef SYMBOL_displayChart_1602667933
#define SYMBOL_displayChart_1602667933

#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

#include "./GanttChart.hpp"
#include "../services.hpp"

void GanttChart::displayChart() {
   vector<vector<GanttSnapshot*>*>* ganttChartRows = new vector<vector<GanttSnapshot*>*>;
   for (unsigned i = 0;i < this->chart->size();++i) {
      if (i % 5 == 0)
         ganttChartRows->push_back(new vector<GanttSnapshot*>);
      ganttChartRows->back()->push_back(this->chart->at(i));
   }

   for (auto itr = ganttChartRows->begin();itr != ganttChartRows->end();++itr) {
      cout << endl << endl;
      ColorPalette::add(YELLOW);

      vertiDiv(DELIMETER);
      partition(2, DELIMETER, false);
      ColorPalette::add(LIGHT_YELLOW);
      partition((*itr)->size(), DELIMETER);
      vertiDiv(EMPTY);
      ColorPalette::remove();
      cout << endl;

      vertiDiv(EMPTY);
      cout << setw(horizWidth * 2) << "Gantt Chart";
      ColorPalette::add(LIGHT_YELLOW);
      for (unsigned i = 0;i < (*itr)->size();++i) {
         vertiDiv(EMPTY);
         if ((*itr)->at(i)->process != NULL && (*itr)->at(i)->process != unitProcess) {
            ColorPalette::add(LIGHT_AQUA);
            cout << setw(horizWidth) << (*itr)->at(i)->process->getId();
         } else {
            ColorPalette::add(GRAY);
            cout << setw(horizWidth) << nullProcessId;
         }
         ColorPalette::remove();
      }
      vertiDiv(EMPTY);
      ColorPalette::remove();
      cout << endl;

      vertiDiv(DELIMETER);
      partition(2, DELIMETER, false);
      ColorPalette::add(LIGHT_YELLOW);
      partition((*itr)->size(), DELIMETER);
      vertiDiv(EMPTY);
      ColorPalette::remove();
      cout << endl;

      vertiDiv(EMPTY);
      cout << setw(horizWidth * 2) <<
         (itr == ganttChartRows->begin() ? "Record (Start = 0)" : "Continued");
      ColorPalette::add(LIGHT_YELLOW);
      for (unsigned i = 0;i < (*itr)->size();++i) {
         vertiDiv(EMPTY);
         ColorPalette::add(WHITE);
         cout << setw(horizWidth) << (*itr)->at(i)->recordedTime;
         ColorPalette::remove();
      }
      vertiDiv(EMPTY);
      ColorPalette::remove();
      cout << endl;

      vertiDiv(DELIMETER);
      partition(2, DELIMETER, false);
      ColorPalette::add(LIGHT_YELLOW);
      partition((*itr)->size(), DELIMETER);
      vertiDiv(EMPTY);
      ColorPalette::remove();
      cout << endl;

      ColorPalette::clear();
   }
}

#endif
