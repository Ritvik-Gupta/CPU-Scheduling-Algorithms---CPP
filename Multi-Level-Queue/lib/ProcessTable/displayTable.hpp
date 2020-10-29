#ifndef SYMBOL_displayTable_1602668414
#define SYMBOL_displayTable_1602668414

#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

#include "./ProcessTable.hpp"
#include "../services.hpp"

void ProcessTable::displayTable() {
   vector<ProcessAttributes>* keys = new vector<ProcessAttributes>;
   keys->assign({ QUEUE_NUM, ARRIVAL, BURST,COMPLETION, TURNAROUND, WAITING });

   cout << endl << endl;
   ColorPalette::add(YELLOW);

   partition(keys->size() + 1, DELIMETER);
   vertiDiv(EMPTY);
   cout << endl;

   partition(keys->size() + 1, EMPTY);
   vertiDiv(EMPTY);
   cout << endl;

   vertiDiv(EMPTY);
   ColorPalette::add(LIGHT_YELLOW);
   cout << setw(horizWidth) << "Process";
   ColorPalette::remove();
   for (unsigned i = 0;i < keys->size();++i) {
      vertiDiv(EMPTY);
      cout << setw(horizWidth) << getAttributeName(keys->at(i));
   }
   vertiDiv(EMPTY);
   cout << endl;

   partition(keys->size() + 1, EMPTY);
   vertiDiv(EMPTY);
   cout << endl;

   partition(keys->size() + 1, DELIMETER);
   vertiDiv(EMPTY);
   cout << endl;

   ColorPalette::add(WHITE);

   partition(keys->size() + 1, DELIMETER);
   vertiDiv(EMPTY);
   cout << endl;

   for (unsigned i = 0;i < this->table->size();++i) {
      vertiDiv(EMPTY);
      ColorPalette::add(LIGHT_YELLOW);
      cout << setw(horizWidth) << this->table->at(i)->getId();
      ColorPalette::remove();
      for (unsigned j = 0;j < keys->size();++j) {
         vertiDiv(EMPTY);
         ColorPalette::add(LIGHT_GREEN);
         cout << setw(horizWidth) << this->table->at(i)->getAttribute(keys->at(j));
         ColorPalette::remove();
      }
      vertiDiv(EMPTY);
      cout << endl;

      partition(keys->size() + 1, DELIMETER);
      vertiDiv(EMPTY);
      cout << endl;
   }

   ColorPalette::remove();

   partition(keys->size() + 1, DELIMETER);
   vertiDiv(EMPTY);
   cout << endl;

   ColorPalette::clear();
}

#endif
