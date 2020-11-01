#ifndef SYMBOL_displayProcessor_1604059340
#define SYMBOL_displayProcessor_1604059340

#include "./Processor.hpp"

void Processor::displayProcessor() {
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
   cout << setw(2 * horizWidth) << this->id;
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

   vertiDiv(DELIMETER);
   partition(2, DELIMETER, false);
   vertiDiv(DELIMETER);
   ColorPalette::add(WHITE);
   vertiDiv(DELIMETER);
   horizDiv(DELIMETER);
   vertiDiv(EMPTY);
   ColorPalette::remove();
   cout << endl;

   vertiDiv(EMPTY);
   ColorPalette::add(LIGHT_YELLOW);
   cout << setw(2 * horizWidth) << "Running Process";
   ColorPalette::remove();
   vertiDiv(EMPTY);
   ColorPalette::add(WHITE);
   vertiDiv(EMPTY);
   ColorPalette::add(AQUA);
   cout << setw(horizWidth) << this->runningProcess->getId();
   ColorPalette::remove();
   vertiDiv(EMPTY);
   ColorPalette::remove();
   cout << endl;

   vertiDiv(DELIMETER);
   partition(2, DELIMETER, false);
   vertiDiv(DELIMETER);
   ColorPalette::add(WHITE);
   vertiDiv(DELIMETER);
   horizDiv(DELIMETER);
   vertiDiv(EMPTY);
   ColorPalette::remove();
   cout << endl;

   if (this->cache->size() > 0) {
      for (unsigned i = 0;i < this->cache->size();++i) {
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
         cout << setw(2 * horizWidth) << (i == 0 ? "Cached Processes" : NONE_SYMBOL);
         ColorPalette::remove();
         vertiDiv(EMPTY);
         ColorPalette::add(WHITE);
         vertiDiv(EMPTY);
         ColorPalette::add(AQUA);
         cout << setw(horizWidth) << this->cache->at(i)->getId();
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
