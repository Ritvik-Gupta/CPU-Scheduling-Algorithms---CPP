#include <iostream>
using namespace std;

#include "../lib/services.hpp"
#include "../lib/Process.hpp"
#include "../lib/Processor/index.hpp"
#include "../lib/MultiProcessor/index.hpp"

int main() {
   initGlobalVariables();

   deque<Process*>* processes = new deque<Process*>({
      new Process("P1", 0, 10),
      new Process("P2", 2, 5),
      new Process("P3", 4, 1),
      new Process("P4", 12, 8),
      new Process("P5", 12, 8),
      new Process("P6", 12, 8),
      new Process("P7", 12, 8),
      new Process("P8", 12, 8),
      });
   unsigned int numProcessors = 5;

   MultiProcessor* MP = new MultiProcessor(processes, numProcessors);
   MP->startProcessors();

   delete MP;
   destroyGlobalVariables();

   cout << endl << endl;
   return 1;
}