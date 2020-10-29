#ifndef SYMBOL_runAlgorithm_1601875766
#define SYMBOL_runAlgorithm_1601875766

#include "./MultiLevelQueue.hpp"
#include "../PriorityQueue/index.hpp"
#include "../services.hpp"

void MultiLevelQueue::runAlgorithm() {

   while (true) {
      this->assignQueues();
      int queuePos = this->getActiveQueuePos();

      this->displayArrival();
      PriorityQueue::displayQueues(this->priorityQueues);
      system("pause");

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
   }

   this->processTable->compute();
}

#endif
