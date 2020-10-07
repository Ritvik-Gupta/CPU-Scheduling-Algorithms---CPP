#ifndef SYMBOL_FCFS_1601875859
#define SYMBOL_FCFS_1601875859

#include "./PriorityQueue.hpp"

class FirstComeFirstServe : public PriorityQueue {

public:
   FirstComeFirstServe() {}

   bool isPreemptive() {
      return false;
   }
};

#endif
