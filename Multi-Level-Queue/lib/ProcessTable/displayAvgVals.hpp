#ifndef SYMBOL_displayAvgVals_1604226466
#define SYMBOL_displayAvgVals_1604226466

#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

#include "./ProcessTable.hpp"
#include "../services.hpp"

void ProcessTable::displayAvgVals() {
   vector<ProcessAttributes>* keys = new vector<ProcessAttributes>;
   keys->assign({ BURST, COMPLETION, TURNAROUND, WAITING });

   cout << endl << endl;
   ColorPalette::add(YELLOW);

   partition(keys->size(), DELIMETER);
   vertiDiv(EMPTY);
   cout << endl;

   partition(keys->size(), EMPTY);
   vertiDiv(EMPTY);
   cout << endl;

   for (ProcessAttributes attr : *keys) {
      vertiDiv(EMPTY);
      ColorPalette::add(AQUA);
      cout << setw(horizWidth) << getAttributeName(attr);
      ColorPalette::remove();
   }
   vertiDiv(EMPTY);
   cout << endl;


   partition(keys->size(), EMPTY);
   vertiDiv(EMPTY);
   cout << endl;

   partition(keys->size(), DELIMETER);
   vertiDiv(EMPTY);
   cout << endl;

   for (ProcessAttributes attr : *keys) {
      vertiDiv(EMPTY);
      ColorPalette::add(GREEN);
      cout << setw(horizWidth) << this->getAvg(attr);
      ColorPalette::remove();
   }
   vertiDiv(EMPTY);
   cout << endl;

   partition(keys->size(), DELIMETER);
   vertiDiv(EMPTY);
   cout << endl;

   ColorPalette::clear();
}

#endif
