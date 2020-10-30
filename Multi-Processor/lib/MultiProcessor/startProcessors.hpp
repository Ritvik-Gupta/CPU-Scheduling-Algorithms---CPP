#ifndef SYMBOL_startProcessors_1604058512
#define SYMBOL_startProcessors_1604058512

#include <vector>
#include <pthread.h>
using namespace std;

#include "../GanttChart/index.hpp"
#include "./MultiProcessor.hpp"

void MultiProcessor::startProcessors() {
   for (unsigned i = 0;i < this->processors->size();++i) {
      pthread_create(
         this->processorThreads->at(i),
         NULL, Processor::begin,
         (void*)new ctxProcessor{ this->processors->at(i), &stopProcessors }
      );
   }
   // while (this->arrivalQueue->size() > 0) {
   //    for (Processor* processor : *this->processors) {
   //       if (!processor->noRunning())
   //          continue;
   //       auto itr = this->arrivalQueue->begin();
   //       while (itr != this->arrivalQueue->end()) {
   //          if (processor->getTime() >= (*itr)->getAttribute(ARRIVAL)) {
   //             processor->setProcess(*itr);
   //             itr = this->arrivalQueue->erase(itr);
   //             break;
   //          } else
   //             ++itr;
   //       }
   //       if (processor->noRunning())
   //          processor->setProcess(unitProcess);
   //    }
   // }
   while (this->arrivalQueue->size() > 0) {
      for (Processor* processor : *this->processors) {
         if (!processor->noRunning())
            continue;
         auto optimalProcess = this->arrivalQueue->end();
         for (auto itr = this->arrivalQueue->begin();itr != this->arrivalQueue->end();++itr) {
            if (processor->getTime() >= (*itr)->getAttribute(ARRIVAL)) {
               optimalProcess = itr;
               if (processor->isCached(*itr))
                  break;
            }
         }
         if (optimalProcess != this->arrivalQueue->end()) {
            processor->setProcess(*optimalProcess);
            this->arrivalQueue->erase(optimalProcess);
         } else
            processor->setProcess(unitProcess);
      }
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
}

#endif
