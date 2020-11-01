#ifndef SYMBOL_MultiProcessor_1603945286
#define SYMBOL_MultiProcessor_1603945286

#include <deque>
#include <vector>
using namespace std;

#include "../services.hpp"
#include "../Process.hpp"
#include "../Processor/index.hpp"
#include "../ProcessTable/index.hpp"

class MultiProcessor {

private:
   deque<Process*>* arrivalQueue;
   ProcessTable* processTable;
   vector<Processor*>* processors;
   vector<pthread_t*>* processorThreads;
   bool stopProcessors;

   Processor* isCachedIn(Process* process) {
      for (Processor* processor : *this->processors) {
         if (processor->isCached(process))
            return processor;
      }
      return NULL;
   }

   bool canBeLoaded(Processor* processor, Process* process) {
      return processor->isIdle() && processor->getTime() >= process->getAttribute(ARRIVAL);
   }

public:
   MultiProcessor(vector<Process*>* processes, vector<Processor*>* processors) {
      this->stopProcessors = false;
      this->processors = processors;
      this->processTable = new ProcessTable(processes);
      this->arrivalQueue = new deque<Process*>;
      this->processorThreads = new vector<pthread_t*>;
      for (Process* process : *processes)
         this->arrivalQueue->push_back(process);
      for (unsigned i = 0;i < this->processors->size();++i)
         this->processorThreads->push_back(new pthread_t);
   }
   ~MultiProcessor() {
      delete processors;
      delete processorThreads;
   }

   void startProcessors();
};

#endif
