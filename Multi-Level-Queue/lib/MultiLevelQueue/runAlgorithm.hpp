#ifndef SYMBOL_runAlgorithm_1601875766
#define SYMBOL_runAlgorithm_1601875766

#include "./MultiLevelQueue.hpp"

void MultiLevelQueue::runAlgorithm() {

   while (true) {
      this->assignQueues();
      int queuePos = this->getActiveQueuePos();

      if (queuePos != this->priorityQueues->size()) {

         unsigned nextEstimate = this->recordedTime + this->getQueue(queuePos)->getNextBurst();
         for (auto itr = this->arrivalQueue->begin();itr != this->arrivalQueue->end();++itr) {
            if (
               (*itr)->arrival < nextEstimate && (
                  (*itr)->queueNum < queuePos ||
                  (this->getQueue(queuePos)->isPreemptive() && (*itr)->queueNum == queuePos)
                  )
               )
               nextEstimate = (*itr)->arrival;
         }
         GanttSnapshot* snapshot = this->getQueue(queuePos)->runProcess(nextEstimate - this->recordedTime);
         this->addSnapshot(snapshot);

      } else if (this->arrivalQueue->size() != 0) {

         unsigned nextEstimate = this->arrivalQueue->front()->arrival;
         for (auto itr = this->arrivalQueue->begin();itr != this->arrivalQueue->end();++itr) {
            if ((*itr)->arrival < nextEstimate)
               nextEstimate = (*itr)->arrival;
         }
         this->addSnapshot(new GanttSnapshot{ NULL, nextEstimate - this->recordedTime });

      } else break;
   }

   for (unsigned i = 0;i < this->processTable->size();++i) {
      this->processTable->at(i)->turnaroud =
         this->processTable->at(i)->completion - this->processTable->at(i)->arrival;
      this->processTable->at(i)->waiting =
         this->processTable->at(i)->turnaroud - this->processTable->at(i)->burst;
   }
}

#endif
