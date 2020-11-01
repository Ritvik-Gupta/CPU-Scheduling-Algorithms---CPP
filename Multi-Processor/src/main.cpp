#include <iostream>
using namespace std;

#include "../lib/services.hpp"
#include "../lib/Process.hpp"
#include "../lib/Processor/index.hpp"
#include "../lib/GanttChart/index.hpp"
#include "../lib/ProcessTable/index.hpp"
#include "../lib/MultiProcessor/index.hpp"

int main() {
   initGlobalVariables();

   vector<ProcessShell*>* processShells = new vector<ProcessShell*>({
      new ProcessShell{"P1", 10},
      new ProcessShell{"P2", 5},
      new ProcessShell{"P3", 1},
      new ProcessShell{"P4", 8},
      new ProcessShell{"P5", 8},
      });

   vector<Process*>* processes = new vector<Process*>({
      new Process(processShells->at(0), 0),
      new Process(processShells->at(0), 0),
      new Process(processShells->at(0), 0),
      new Process(processShells->at(0), 0),
      new Process(processShells->at(1), 5),
      new Process(processShells->at(2), 4),
      new Process(processShells->at(3), 12),
      new Process(processShells->at(3), 12),
      new Process(processShells->at(3), 12),
      new Process(processShells->at(3), 12),
      new Process(processShells->at(4), 22),
      new Process(processShells->at(4), 40),
      new Process(processShells->at(4), 40),
      });

   vector<Processor*>* processors = new vector<Processor*>({
      new Processor("Prs. A", 2),
      new Processor("Prs. B", 3),
      new Processor("Prs. Z", 4),
      new Processor("Prs. X", 5),
      });

   MultiProcessor* MP = MultiProcessor::readTable(ifstream("../table/T1.txt"));
   MP->startProcessors();

   delete MP;
   destroyGlobalVariables();

   cout << endl << endl;
   return 1;
}
