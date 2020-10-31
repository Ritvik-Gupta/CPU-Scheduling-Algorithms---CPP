#ifndef SYMBOL_startProcessors_1604058512
#define SYMBOL_startProcessors_1604058512

#include <vector>
#include <pthread.h>
using namespace std;

#include "../GanttChart/index.hpp"
#include "../ProcessTable/index.hpp"
#include "./MultiProcessor.hpp"

void MultiProcessor::startProcessors() {

   for (unsigned i = 0;i < this->processors->size();++i) {
      pthread_create(
         this->processorThreads->at(i),
         NULL, Processor::begin,
         (void*)new ctxProcessor{ this->processors->at(i), &stopProcessors }
      );
   }

   while (this->arrivalQueue->size() > 0) {

      for (Processor* processor : *this->processors)
         processor->lock(true);

      auto itr = this->arrivalQueue->begin();
      while (itr != this->arrivalQueue->end()) {
         Processor* optimalProcessor = this->isCachedIn(*itr);
         if (optimalProcessor != NULL && this->canBeLoaded(optimalProcessor, *itr)) {
            optimalProcessor->loadProcess(*itr);
            itr = this->arrivalQueue->erase(itr);
         } else
            ++itr;
      }

      for (Processor* processor : *this->processors) {
         auto itr = this->arrivalQueue->begin();
         while (itr != this->arrivalQueue->end()) {
            if (this->canBeLoaded(processor, *itr)) {
               processor->loadProcess(*itr);
               itr = this->arrivalQueue->erase(itr);
               break;
            } else
               ++itr;
         }

         if (processor->notIdle())
            processor->loadProcess(unitProcess);
      }

      for (Processor* processor : *this->processors)
         processor->lock(false);
   }

   this->stopProcessors = true;
   void* status;
   vector<GanttChart*>* collectedCharts = new vector<GanttChart*>;

   for (pthread_t* thread : *this->processorThreads) {
      pthread_join(*thread, &status);
      collectedCharts->push_back((GanttChart*)status);
   }

   for (GanttChart* ganttChart : *collectedCharts)
      ganttChart->displayChart();

   this->processTable->compute();
   this->processTable->displayTable();
}

#endif
