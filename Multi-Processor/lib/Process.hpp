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

struct ProcessShell {
   string id;
   unsigned burst;
};

class Process {

private:
   ProcessShell* shell;
   string processorId;
   unsigned arrival;
   unsigned burst;
   unsigned completion;
   unsigned turnaroud;
   unsigned waiting;

public:
   Process(ProcessShell* shell, unsigned arrival) {
      this->shell = shell;
      this->processorId = NONE_SYMBOL;
      this->arrival = arrival;
      this->burst = shell->burst;
      this->completion = 0;
      this->turnaroud = 0;
      this->waiting = 0;
   }

   void assignProcessor(string processorId) {
      this->processorId = processorId;
   }

   string getProcessorId() {
      return this->processorId;
   }

   string getId() {
      return this->shell->id;
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

   static bool hasSameShell(Process* processA, Process* processB) {
      return processA->shell == processB->shell;
   }

   friend class GanttChart;
   friend class ProcessTable;
};

Process* unitProcess = new Process(new ProcessShell{ NONE_SYMBOL, 1 }, 0);

#endif
