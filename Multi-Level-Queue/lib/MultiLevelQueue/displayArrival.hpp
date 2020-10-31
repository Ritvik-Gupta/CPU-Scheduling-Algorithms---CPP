#ifndef SYMBOL_displayArrival_1603781778
#define SYMBOL_displayArrival_1603781778

#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

#include "./MultiLevelQueue.hpp"
#include "../services.hpp"

void MultiLevelQueue::displayArrival() {
   cout << endl << endl;
   ColorPalette::add(YELLOW);

   vertiDiv(DELIMETER);
   partition(2, DELIMETER, false);
   vertiDiv(DELIMETER);
   vertiDiv(DELIMETER);
   horizDiv(DELIMETER);
   vertiDiv(EMPTY);
   cout << endl;

   vertiDiv(EMPTY);
   ColorPalette::add(LIGHT_YELLOW);
   cout << setw(horizWidth * 2) << "Current Time";
   ColorPalette::remove();
   vertiDiv(EMPTY);
   vertiDiv(EMPTY);
   ColorPalette::add(GREEN);
   cout << setw(horizWidth) << this->ganttChart->getRecordedTime();
   ColorPalette::remove();
   vertiDiv(EMPTY);
   cout << endl;

   vertiDiv(DELIMETER);
   partition(2, DELIMETER, false);
   vertiDiv(DELIMETER);
   vertiDiv(DELIMETER);
   horizDiv(DELIMETER);
   vertiDiv(EMPTY);
   cout << endl;

   if (this->arrivalQueue->size() > 0) {
      for (unsigned i = 0;i < this->arrivalQueue->size();++i) {
         vertiDiv(DELIMETER);
         partition(2, DELIMETER, false);
         vertiDiv(EMPTY);
         ColorPalette::add(WHITE);
         vertiDiv(DELIMETER);
         horizDiv(DELIMETER);
         vertiDiv(EMPTY);
         ColorPalette::remove();
         cout << endl;

         vertiDiv(EMPTY);
         ColorPalette::add(LIGHT_YELLOW);
         cout << setw(horizWidth * 2) << (i == 0 ? "Arrival Queue" : "*");
         ColorPalette::remove();
         vertiDiv(EMPTY);
         ColorPalette::add(WHITE);
         vertiDiv(EMPTY);
         ColorPalette::add(AQUA);
         cout << setw(horizWidth) << this->arrivalQueue->at(i)->getId();
         ColorPalette::remove();
         vertiDiv(EMPTY);
         ColorPalette::remove();
         cout << endl;
      }

      vertiDiv(DELIMETER);
      partition(2, DELIMETER, false);
      vertiDiv(DELIMETER);
      ColorPalette::add(WHITE);
      vertiDiv(DELIMETER);
      horizDiv(DELIMETER);
      vertiDiv(EMPTY);
      ColorPalette::remove();
      cout << endl;
   }

   ColorPalette::clear();
}

#endif
