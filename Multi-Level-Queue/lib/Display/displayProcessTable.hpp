#ifndef SYMBOL_displayProcessTable_1602040533
#define SYMBOL_displayProcessTable_1602040533

#include <vector>
using namespace std;

#include "./Display.hpp"
#include "../services.hpp"

void Display::table(vector<Process*>* PT) {
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

   for (unsigned i = 0;i < PT->size();++i) {
      vertiDiv(EMPTY);
      ColorPalette::add(LIGHT_AQUA);
      cout << setw(horizWidth) << PT->at(i)->getId();
      ColorPalette::remove();
      for (unsigned j = 0;j < keys->size();++j) {
         vertiDiv(EMPTY);
         ColorPalette::add(LIGHT_GREEN);
         cout << setw(horizWidth) << PT->at(i)->getAttribute(keys->at(j));
         ColorPalette::remove();
      }
      vertiDiv(EMPTY);
      cout << endl;
   }

   partition(keys->size() + 1, DELIMETER);
   vertiDiv(EMPTY);
   cout << endl;

   ColorPalette::remove();

   partition(keys->size() + 1, DELIMETER);
   vertiDiv(EMPTY);
   cout << endl;

   ColorPalette::clear();
}

#endif
