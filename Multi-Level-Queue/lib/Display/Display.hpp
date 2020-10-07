#ifndef SYMBOL_Display_1602035119
#define SYMBOL_Display_1602035119

#include <iomanip>
using namespace std;

#include "../services.hpp"
#include "../Process.hpp"
#include "../MultiLevelQueue/index.hpp"

class Display {

private:
   static const unsigned horizWidth = 10;
   static const unsigned vertiWidth = 7;

   static void horizDiv(char fill) {
      cout << left << setw(horizWidth) << setfill(fill) << "";
      cout << setfill(' ');
   }

   static void vertiDiv(char fill) {
      cout << left << setw(vertiWidth) << setfill(fill) << "|";
      cout << setfill(' ');
   }

   static void partition(unsigned size, char ch, bool hasVerti = true) {
      for (unsigned i = 0; i < size; ++i) {
         if (hasVerti) vertiDiv(ch);
         horizDiv(ch);
      }
   }

public:
   static void table(MultiLevelQueue* MLQ) {
      table(MLQ->ganttChart);
   }

   static void table(vector<GanttSnapshot*>*);
   static void table(vector<Process*>*);

};

#endif
