#ifndef SYMBOL_Process_1603945484
#define SYMBOL_Process_1603945484

#include <string>
using namespace std;

enum ProcessAttributes { ARRIVAL, BURST, COMPLETION, TURNAROUND, WAITING };
string getAttributeName(ProcessAttributes attr) {
   switch (attr) {
      case ARRIVAL:return "Arrival";
      case BURST:return "Burst";
      case COMPLETION:return "Completion";
      case TURNAROUND:return  "Turnaround";
      case WAITING:return "Waiting";
      default: return "";
   }
}

class Process {

private:
   string id;
   unsigned arrival;
   unsigned burst;
   unsigned completion;
   unsigned turnaroud;
   unsigned waiting;

public:
   Process(string id, unsigned arrival, unsigned burst) {
      this->id = id;
      this->arrival = arrival;
      this->burst = burst;
      this->completion = 0;
      this->turnaroud = 0;
      this->waiting = 0;
   }

   string getId() {
      return this->id;
   }

   unsigned getAttribute(ProcessAttributes attr) {
      switch (attr) {
         case ARRIVAL:return this->arrival;
         case BURST:return this->burst;
         case COMPLETION:return this->completion;
         case TURNAROUND:return this->turnaroud;
         case WAITING:return this->waiting;
         default: return 0;
      }
   }

   friend class GanttChart;
};

string NONE_SYMBOL = "*";
Process* unitProcess = new Process(NONE_SYMBOL, 0, 1);

#endif
