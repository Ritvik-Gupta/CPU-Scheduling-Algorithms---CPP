#ifndef SYMBOL_RR_1601875887
#define SYMBOL_RR_1601875887

#include "./PriorityQueue.hpp"

class RoundRobin : public PriorityQueue {
private:
   unsigned quantum;
public:
   RoundRobin(unsigned quantum = 2) {
      this->quantum = quantum;
   }

   unsigned getNextBurst() {
      if (this->noRunning()) return 0;
      if (this->running->runtime > this->quantum) return this->quantum;
      return this->running->runtime;
   }

   GanttSnapshot* runProcess(unsigned maxRuntime) {
      unsigned timeRequired = min(this->running->runtime, min(maxRuntime, this->quantum));
      GanttSnapshot* gs = new GanttSnapshot{ this->running, timeRequired };
      this->running->runtime -= timeRequired;
      if (this->running->runtime != 0)
         this->waitingQueue->push_back(this->running);
      this->loadProcess();
      return gs;
   }

   bool isPreemptive() {
      return true;
   }
};

#endif
