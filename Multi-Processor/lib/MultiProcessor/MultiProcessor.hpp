#ifndef SYMBOL_MultiProcessor_1603945286
#define SYMBOL_MultiProcessor_1603945286

#include <deque>
#include <vector>
using namespace std;

#include "../services.hpp"
#include "../Process.hpp"
#include "../Processor/index.hpp"
#include "../GanttChart/index.hpp"

class MultiProcessor {

private:
   deque<Process*>* arrivalQueue;
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
      return processor->noRunning() && processor->getTime() >= process->getAttribute(ARRIVAL);
   }

public:
   MultiProcessor(deque<Process*>* processes, unsigned numProcessors) {
      this->stopProcessors = false;
      this->arrivalQueue = processes;
      this->processors = new vector<Processor*>;
      this->processorThreads = new vector<pthread_t*>;
      for (unsigned i = 0;i < numProcessors;++i) {
         this->processors->push_back(new Processor("Processor " + to_string(i + 1)));
         this->processorThreads->push_back(new pthread_t);
      }
   }
   ~MultiProcessor() {
      delete processors;
      delete processorThreads;
   }

   void startProcessors();
};

#endif
