#include <iostream>
using namespace std;

#include "../lib/services.hpp"
#include "../lib/Process.hpp"
#include "../lib/Processor/index.hpp"
#include "../lib/MultiProcessor/index.hpp"

int main() {
   initGlobalVariables();

   vector<Process*>* processes = new vector<Process*>({
      new Process("P1", 0, 10),
      new Process("P1", 0, 10),
      new Process("P1", 0, 10),
      new Process("P1", 0, 10),
      new Process("P2", 2, 5),
      new Process("P3", 4, 1),
      new Process("P4", 12, 8),
      new Process("P4", 12, 8),
      new Process("P4", 12, 8),
      new Process("P4", 12, 8),
      new Process("P10", 22, 8),
      new Process("P10", 40, 8),
      });

   vector<Processor*>* processors = new vector<Processor*>({
      new Processor("Processor 1", 2),
      new Processor("Processor 2", 3),
      new Processor("Processor 3", 5),
      });

   MultiProcessor* MP = new MultiProcessor(processes, processors);
   MP->startProcessors();

   delete MP;
   destroyGlobalVariables();

   cout << endl << endl;
   return 1;
}
