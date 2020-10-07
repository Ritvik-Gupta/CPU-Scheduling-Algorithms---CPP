#ifndef SYMBOL_Process_1601909114
#define SYMBOL_Process_1601909114

#include <string>
using namespace std;

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

   unsigned getArrival() {
      return this->arrival;
   }

   unsigned getQueueNum() {
      return this->queueNum;
   }

   friend class MLQ;
};

#endif
