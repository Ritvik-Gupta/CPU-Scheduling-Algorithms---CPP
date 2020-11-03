#ifndef SYMBOL_MultiLevelQueue_1601963303
#define SYMBOL_MultiLevelQueue_1601963303

#include <iostream>
#include <vector>
#include <deque>
using namespace std;

#include "../GanttChart/index.hpp"
#include "../ProcessTable/index.hpp"
#include "../PriorityQueue/index.hpp"

class MultiLevelQueue {

private:
   vector<PriorityQueue*>* priorityQueues;
   GanttChart* ganttChart;
   ProcessTable* processTable;
   deque<Process*>* arrivalQueue;

   PriorityQueue* getQueue(unsigned pos) {
      return this->priorityQueues->at(pos);
   }

   unsigned getActiveQueuePos() {
      unsigned pos = 0;
      while (pos < this->priorityQueues->size()) {
         if (this->getQueue(pos)->noRunning() == false)
            break;
         ++pos;
      }
      return pos;
   }

   void assignQueues() {
      auto itr = this->arrivalQueue->begin();
      while (itr != this->arrivalQueue->end()) {
         if ((*itr)->getAttribute(ARRIVAL) <= this->ganttChart->getRecordedTime()) {
            this->priorityQueues->at((*itr)->getAttribute(QUEUE_NUM))->add(*itr);
            itr = this->arrivalQueue->erase(itr);
         } else
            ++itr;
      }
   }

   void displayArrival();

public:
   MultiLevelQueue(vector<PriorityQueue*>* priorityQueues, vector<Process*>* P) {
      this->priorityQueues = priorityQueues;
      this->ganttChart = new GanttChart();
      this->processTable = new ProcessTable(P);
      this->arrivalQueue = new deque<Process*>;
      for (unsigned i = 0;i < P->size();++i)
         this->arrivalQueue->push_back(P->at(i));
   }

   void display() {
      this->ganttChart->displayChart();
      this->processTable->displayTable();
   }

   void runAlgorithm();

   ~MultiLevelQueue() {
      delete this->arrivalQueue;
      delete this->ganttChart;
      delete this->priorityQueues;
      delete this->processTable;
   }
};

#endif
