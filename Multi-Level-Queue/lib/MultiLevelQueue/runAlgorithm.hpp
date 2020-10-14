#ifndef SYMBOL_runAlgorithm_1601875766
#define SYMBOL_runAlgorithm_1601875766

#include "./MultiLevelQueue.hpp"

void MultiLevelQueue::runAlgorithm() {

   while (true) {
      this->assignQueues();
      int queuePos = this->getActiveQueuePos();

      if (queuePos != this->priorityQueues->size()) {

         unsigned nextEstimate = this->ganttChart->getRecordedTime() + this->getQueue(queuePos)->getNextBurst();
         for (auto itr = this->arrivalQueue->begin();itr != this->arrivalQueue->end();++itr) {
            if (
               (*itr)->getAttribute(ARRIVAL) < nextEstimate && (
                  (*itr)->getAttribute(QUEUE_NUM) < queuePos ||
                  (this->getQueue(queuePos)->isPreemptive() && (*itr)->getAttribute(QUEUE_NUM) == queuePos)
                  )
               )
               nextEstimate = (*itr)->getAttribute(ARRIVAL);
         }
         GanttSnapshot* snapshot = this->getQueue(queuePos)->runProcess(nextEstimate - this->ganttChart->getRecordedTime());
         this->ganttChart->addSnapshot(snapshot);

      } else if (this->arrivalQueue->size() != 0) {

         unsigned nextEstimate = this->arrivalQueue->front()->getAttribute(ARRIVAL);
         for (auto itr = this->arrivalQueue->begin();itr != this->arrivalQueue->end();++itr) {
            if ((*itr)->getAttribute(ARRIVAL) < nextEstimate)
               nextEstimate = (*itr)->getAttribute(ARRIVAL);
         }
         this->ganttChart->addSnapshot(new GanttSnapshot{ NULL, nextEstimate - this->ganttChart->getRecordedTime() });

      } else break;
      if (this->queueDisplay) {
         for (unsigned i = 0;i < this->priorityQueues->size();++i)
            this->priorityQueues->at(i)->displayQueue();
      }
   }

   this->processTable->compute();
}

#endif
