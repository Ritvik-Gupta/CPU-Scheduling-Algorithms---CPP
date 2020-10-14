#ifndef SYMBOL_defineQueues_1602669206
#define SYMBOL_defineQueues_1602669206

#include "./PriorityQueue.hpp"
#include "../Process.hpp"
#include "../GanttChart/index.hpp"

class FirstComeFirstServe : public PriorityQueue {

public:
   FirstComeFirstServe() {}

   bool isPreemptive() {
      return false;
   }
};

class ShortestJobFirst : public PriorityQueue {

public:
   ShortestJobFirst() {}

   void add(Process* P) {
      unsigned pos = this->waitingQueue->size();
      while (pos > 0) {
         if (this->waitingQueue->at(pos - 1)->runtime < P->runtime)
            break;
         --pos;
      }
      auto itr = this->waitingQueue->begin();
      this->waitingQueue->emplace(next(itr, pos), P);
      if (this->noRunning())
         this->loadProcess();
   }

   bool isPreemptive() {
      return false;
   }
};

class ShortestRemainingTime : public PriorityQueue {

public:
   ShortestRemainingTime() {}

   void add(Process* P) {
      if (this->noRunning())
         this->running = P;
      else {
         if (this->running->runtime < P->runtime)
            swap(this->running, P);
         unsigned pos = this->waitingQueue->size();
         while (pos > 0) {
            if (this->waitingQueue->at(pos - 1)->runtime < P->runtime)
               break;
            --pos;
         }
         auto itr = this->waitingQueue->begin();
         this->waitingQueue->emplace(next(itr, pos), P);
      }
   }

   bool isPreemptive() {
      return true;
   }
};

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
