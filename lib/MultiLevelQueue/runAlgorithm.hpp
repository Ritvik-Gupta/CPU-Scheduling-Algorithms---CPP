#ifndef SYMBOL_runAlgorithm_1601875766
#define SYMBOL_runAlgorithm_1601875766

#include "./MLQ.hpp"

void MLQ::runAlgorithm() {

   while (true) {
      this->assignQueues();
      int queuePos = this->getActiveQueuePos();

      if (queuePos != this->priorityQueues->size()) {

         unsigned nextEstimate = this->recordedTime + this->getQueue(queuePos)->getNextBurst();
         for (auto itr = this->arrivalQueue->begin();itr != this->arrivalQueue->end();++itr) {
            if (
               (*itr)->getArrival() < nextEstimate && (
                  (*itr)->getQueueNum() < queuePos ||
                  (this->getQueue(queuePos)->isPreemptive() && (*itr)->getQueueNum() == queuePos)
                  )
               )
               nextEstimate = (*itr)->getArrival();
         }
         GanttSnapshot* snapshot = this->getQueue(queuePos)->runProcess(nextEstimate - this->recordedTime);
         this->addSnapshot(snapshot);

      } else if (this->arrivalQueue->size() != 0) {

         unsigned nextEstimate = this->arrivalQueue->front()->getArrival();
         for (auto itr = this->arrivalQueue->begin();itr != this->arrivalQueue->end();++itr) {
            if ((*itr)->getArrival() < nextEstimate)
               nextEstimate = (*itr)->getArrival();
         }
         this->addSnapshot(new GanttSnapshot{ NULL, nextEstimate - this->recordedTime });

      } else break;
   }
}

#endif
