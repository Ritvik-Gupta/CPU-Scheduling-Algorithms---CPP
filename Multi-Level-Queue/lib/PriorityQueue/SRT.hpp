#ifndef SYMBOL_SRT_1602021713
#define SYMBOL_SRT_1602021713

#include "./PriorityQueue.hpp"

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

#endif
