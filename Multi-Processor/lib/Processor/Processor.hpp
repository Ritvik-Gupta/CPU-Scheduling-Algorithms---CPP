#ifndef SYMBOL_Processor_1604030876
#define SYMBOL_Processor_1604030876

#include <vector>
#include <pthread.h>
using namespace std;

#include "../services.hpp"
#include "../Process.hpp"
#include "../GanttChart/index.hpp"

class Processor;
struct ctxProcessor {
   Processor* processor;
   bool* stopProcessor;
};

class Processor {

private:
   string id;
   unsigned cacheFactor;
   Process* runningProcess;
   GanttChart* ganttChart;
   vector<Process*>* cache;
   pthread_mutex_t* processorLock;

   void* startProcessorLoop(void*);
   void displayProcessor();

public:
   Processor(string processorId, unsigned cacheFactor) {
      this->id = processorId;
      this->cacheFactor = cacheFactor;
      this->runningProcess = NULL;
      this->ganttChart = new GanttChart();
      this->cache = new vector<Process*>;
      this->processorLock = new pthread_mutex_t;
      pthread_mutex_init(this->processorLock, NULL);
   }

   ~Processor() {
      pthread_mutex_destroy(this->processorLock);
   }

   void lock(bool toLock) {
      if (toLock)
         pthread_mutex_lock(this->processorLock);
      else
         pthread_mutex_unlock(this->processorLock);
   }

   unsigned getTime() {
      return this->ganttChart->getRecordedTime();
   }

   bool isIdle() {
      return this->runningProcess == NULL;
   }

   bool isCached(Process* process) {
      for (Process* cachedProcess : *this->cache) {
         if (Process::hasSameShell(cachedProcess, process))
            return true;
      }
      return false;
   }

   void loadProcess(Process* process) {
      if (process != NULL)
         process->assignProcessor(this->id);
      this->runningProcess = process;
   }


   static void* begin(void* ctx) {
      ctxProcessor* context = (ctxProcessor*)ctx;
      return context->processor->startProcessorLoop((void*)context->stopProcessor);
   }
};

#endif
