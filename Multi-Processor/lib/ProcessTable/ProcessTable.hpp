#ifndef SYMBOL_ProcessTable_1602126428
#define SYMBOL_ProcessTable_1602126428

#include <vector>
using namespace std;

#include "../Process.hpp"

class ProcessTable {

private:
   vector<Process*>* table;

public:
   ProcessTable(vector<Process*>* processes) {
      this->table = processes;
   }

   void compute() {
      for (Process* process : *this->table) {
         process->turnaroud = process->completion - process->arrival;
         process->waiting = process->turnaroud - process->burst;
      }
   }

   float getAvg(ProcessAttributes attr) {
      unsigned avg = 0;
      for (Process* process : *this->table)
         avg += process->getAttribute(attr);
      return (float)(avg) / (float)(this->table->size());
   }

   void displayTable();
};

#endif
