#ifndef SYMBOL_PriorityQueue_1601875871
#define SYMBOL_PriorityQueue_1601875871

#include <deque>
using namespace std;

#include "../Process.hpp"
#include "../GanttChart/index.hpp"

enum QueueTypes { RR, FCFS, SJF, SRT };

class PriorityQueue {

protected:
   deque<Process*>* waitingQueue;
   Process* running;

   void loadProcess() {
      if (this->noWaiting())
         this->running = NULL;
      else {
         this->running = this->waitingQueue->front();
         this->waitingQueue->pop_front();
      }
   }

   bool noWaiting() {
      return this->waitingQueue->empty();
   }

public:
   PriorityQueue() {
      this->waitingQueue = new deque<Process*>;
      this->running = NULL;
   }

   bool noRunning() {
      return this->running == NULL;
   }

   virtual unsigned getNextBurst() {
      if (this->noRunning()) return 0;
      return this->running->runtime;
   }

   virtual void add(Process* P) {
      this->waitingQueue->push_back(P);
      if (this->noRunning())
         this->loadProcess();
   }

   virtual GanttSnapshot* runProcess(unsigned maxRuntime) {
      unsigned timeRequired = min(this->running->runtime, maxRuntime);
      GanttSnapshot* gs = new GanttSnapshot{ this->running, timeRequired };
      this->running->runtime -= timeRequired;
      if (this->running->runtime == 0)
         this->loadProcess();
      return gs;
   }

   void displayQueue();

   virtual bool isPreemptive() = 0;
};

#endif
