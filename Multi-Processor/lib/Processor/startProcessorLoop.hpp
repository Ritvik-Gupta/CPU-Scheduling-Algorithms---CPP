#ifndef SYMBOL_startProcessorLoop_1604196682
#define SYMBOL_startProcessorLoop_1604196682

#include "./Processor.hpp"

void* Processor::startProcessorLoop(void* ctx) {
   bool* stopProcessor = (bool*)ctx;

   while (*stopProcessor == false) {

      if (this->isIdle())
         continue;
      this->lock(true);

      if (this->runningProcess != unitProcess) {
         pthread_mutex_lock(consoleLock);
         this->displayProcessor();
         pthread_mutex_unlock(consoleLock);
      }

      float burst = (float)this->runningProcess->getAttribute(BURST);
      if (this->isCached(this->runningProcess))
         burst /= cacheFactor;
      else if (this->runningProcess != unitProcess)
         this->cache->push_back(this->runningProcess);

      this->lock(false);
      Sleep((unsigned)ceil(burst * 500));
      this->lock(true);

      this->ganttChart->addSnapshot(new GanttSnapshot{ this->runningProcess, (unsigned)ceil(burst) });
      this->loadProcess(NULL);
      this->lock(false);
   }

   this->ganttChart->reduce();
   pthread_exit((void*)this->ganttChart);
   return NULL;
}

#endif
