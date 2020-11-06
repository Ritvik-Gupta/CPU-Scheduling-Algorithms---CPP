#ifndef SYMBOL_ProcessTable_1602126428
#define SYMBOL_ProcessTable_1602126428

#include <vector>
using namespace std;

#include "../Process.hpp"

class ProcessTable {

private:
   vector<Process*>* table;

public:
   ProcessTable(vector<Process*>* P) {
      this->table = P;
   }

   void compute() {
      for (auto itr = this->table->begin();itr != this->table->end();++itr) {
         (*itr)->turnaroud = (*itr)->completion - (*itr)->arrival;
         (*itr)->waiting = (*itr)->turnaroud - (*itr)->burst;
      }
   }

   float getAvg(ProcessAttributes attr) {
      unsigned avg = 0;
      for (auto itr = this->table->begin();itr != this->table->end();++itr)
         avg += (*itr)->getAttribute(attr);
      return (float)(avg) / (float)(this->table->size());
   }

   void displayTable();
   void displayAvgVals();
};

#endif
