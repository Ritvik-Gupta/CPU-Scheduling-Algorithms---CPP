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
   string name;
   Process* runningProcess;
   GanttChart* ganttChart;
   vector<Process*>* cache;
   pthread_mutex_t* processorLock;

   void* beginLoop(void* ctx) {
      bool* stopProcessor = (bool*)ctx;

      while (*stopProcessor == false) {

         if (this->noRunning())
            continue;
         this->lock(true);

         if (this->runningProcess != unitProcess) {
            pthread_mutex_lock(consoleLock);
            this->displayProcessor();
            pthread_mutex_unlock(consoleLock);
         }

         float burst = (float)this->runningProcess->getAttribute(BURST);
         if (this->isCached(this->runningProcess))
            burst /= 2;
         else if (this->runningProcess != unitProcess)
            this->cache->push_back(this->runningProcess);

         this->lock(false);
         Sleep(burst * 500);

         this->ganttChart->addSnapshot(new GanttSnapshot{ this->runningProcess, (unsigned)ceil(burst) });
         this->loadProcess(NULL);
      }

      this->ganttChart->reduce();
      pthread_exit((void*)this->ganttChart);
      return NULL;
   }

   void displayProcessor();

public:
   Processor(string name) {
      this->name = name;
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

   bool noRunning() {
      return this->runningProcess == NULL;
   }

   bool isCached(Process* process) {
      for (Process* cachedProcess : *this->cache) {
         if (cachedProcess->getId() == process->getId())
            return true;
      }
      return false;
   }

   void loadProcess(Process* process) {
      this->runningProcess = process;
   }


   static void* begin(void* ctx) {
      ctxProcessor* context = (ctxProcessor*)ctx;
      return context->processor->beginLoop((void*)context->stopProcessor);
   }
};

#endif
