#ifndef SYMBOL_SJF_1601875898
#define SYMBOL_SJF_1601875898

#include "./PriorityQueue.hpp"

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

#endif
