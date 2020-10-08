#ifndef SYMBOL_Process_1601909114
#define SYMBOL_Process_1601909114

#include <string>
using namespace std;

enum ProcessAttributes { QUEUE_NUM, ARRIVAL, BURST, COMPLETION, TURNAROUND, WAITING };
string getAttributeName(ProcessAttributes attr) {
   switch (attr) {
      case QUEUE_NUM: return "Queue Num";
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
   unsigned queueNum;
   unsigned arrival;
   unsigned burst;
   unsigned completion;
   unsigned turnaroud;
   unsigned waiting;

public:
   unsigned runtime;

   Process(string id, unsigned queueNum, unsigned arrival, unsigned burst) {
      this->id = id;
      this->queueNum = queueNum;
      this->arrival = arrival;
      this->burst = burst;
      this->runtime = burst;
      this->completion = 0;
      this->turnaroud = 0;
      this->waiting = 0;
   }

   string getId() {
      return this->id;
   }

   unsigned getAttribute(ProcessAttributes attr) {
      switch (attr) {
         case QUEUE_NUM: return this->queueNum;
         case ARRIVAL:return this->arrival;
         case BURST:return this->burst;
         case COMPLETION:return this->completion;
         case TURNAROUND:return this->turnaroud;
         case WAITING:return this->waiting;
         default: return 0;
      }
   }

   friend class ProcessTable;
   friend class GanttChart;
};

#endif
