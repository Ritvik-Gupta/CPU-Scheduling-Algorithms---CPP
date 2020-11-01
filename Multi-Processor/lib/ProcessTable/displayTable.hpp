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
   keys->assign({ ARRIVAL, BURST,COMPLETION, TURNAROUND, WAITING });

   cout << endl << endl;
   ColorPalette::add(YELLOW);

   vertiDiv(DELIMETER);
   horizDiv(DELIMETER);
   vertiDiv(DELIMETER);
   horizDiv(DELIMETER);
   vertiDiv(DELIMETER);
   partition(keys->size(), DELIMETER);
   vertiDiv(EMPTY);
   cout << endl;

   vertiDiv(EMPTY);
   horizDiv(EMPTY);
   vertiDiv(EMPTY);
   horizDiv(EMPTY);
   vertiDiv(EMPTY);
   partition(keys->size(), EMPTY);
   vertiDiv(EMPTY);
   cout << endl;

   vertiDiv(EMPTY);
   ColorPalette::add(LIGHT_YELLOW);
   cout << setw(horizWidth) << "Process";
   ColorPalette::remove();
   vertiDiv(EMPTY);
   ColorPalette::add(LIGHT_YELLOW);
   cout << setw(horizWidth) << "Assigned To";
   ColorPalette::remove();
   vertiDiv(EMPTY);
   for (ProcessAttributes attribute : *keys) {
      vertiDiv(EMPTY);
      cout << setw(horizWidth) << getAttributeName(attribute);
   }
   vertiDiv(EMPTY);
   cout << endl;

   vertiDiv(EMPTY);
   horizDiv(EMPTY);
   vertiDiv(EMPTY);
   horizDiv(EMPTY);
   vertiDiv(EMPTY);
   partition(keys->size(), EMPTY);
   vertiDiv(EMPTY);
   cout << endl;

   vertiDiv(DELIMETER);
   horizDiv(DELIMETER);
   vertiDiv(DELIMETER);
   horizDiv(DELIMETER);
   vertiDiv(DELIMETER);
   partition(keys->size(), DELIMETER);
   vertiDiv(EMPTY);
   cout << endl;

   vertiDiv(DELIMETER);
   horizDiv(DELIMETER);
   vertiDiv(DELIMETER);
   horizDiv(DELIMETER);
   vertiDiv(DELIMETER);
   ColorPalette::add(WHITE);
   partition(keys->size(), DELIMETER);
   vertiDiv(EMPTY);
   ColorPalette::remove();
   cout << endl;

   for (Process* process : *this->table) {
      vertiDiv(EMPTY);
      ColorPalette::add(GRAY);
      cout << setw(horizWidth) << process->getId();
      ColorPalette::remove();
      vertiDiv(EMPTY);
      ColorPalette::add(GRAY);
      cout << setw(horizWidth) << process->getProcessorId();
      ColorPalette::remove();
      vertiDiv(EMPTY);
      ColorPalette::add(WHITE);
      for (ProcessAttributes attribute : *keys) {
         vertiDiv(EMPTY);
         ColorPalette::add(LIGHT_GREEN);
         cout << setw(horizWidth) << process->getAttribute(attribute);
         ColorPalette::remove();
      }
      vertiDiv(EMPTY);
      ColorPalette::remove();
      cout << endl;

      vertiDiv(DELIMETER);
      horizDiv(DELIMETER);
      vertiDiv(DELIMETER);
      horizDiv(DELIMETER);
      vertiDiv(EMPTY);
      ColorPalette::add(WHITE);
      partition(keys->size(), DELIMETER);
      vertiDiv(EMPTY);
      ColorPalette::remove();
      cout << endl;
   }

   vertiDiv(DELIMETER);
   horizDiv(DELIMETER);
   vertiDiv(DELIMETER);
   horizDiv(DELIMETER);
   vertiDiv(DELIMETER);
   partition(keys->size(), DELIMETER);
   vertiDiv(EMPTY);
   cout << endl;

   ColorPalette::clear();
}

#endif
