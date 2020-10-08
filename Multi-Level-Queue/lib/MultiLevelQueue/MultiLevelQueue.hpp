#ifndef SYMBOL_MultiLevelQueue_1601963303
#define SYMBOL_MultiLevelQueue_1601963303

#include <iostream>
#include <vector>
#include <deque>
using namespace std;

#include "../GanttChart.hpp"
#include "../ProcessTable.hpp"
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

public:
   MultiLevelQueue(vector<PriorityQueue*>* priorityQueues, vector<Process*>* P) {
      this->priorityQueues = priorityQueues;
      this->ganttChart = new GanttChart();
      this->processTable = new ProcessTable(P);
      this->arrivalQueue = new deque<Process*>;
      for (unsigned i = 0;i < P->size();++i)
         this->arrivalQueue->push_back(P->at(i));
   }

   MultiLevelQueue(vector<QueueTypes>* queueTypes, vector<Process*>* P) {
      this->priorityQueues = new vector<PriorityQueue*>;
      this->ganttChart = new GanttChart();
      this->processTable = new ProcessTable(P);
      this->arrivalQueue = new deque<Process*>;
      for (unsigned i = 0;i < P->size();++i)
         this->arrivalQueue->push_back(P->at(i));

      for (unsigned i = 0;i < queueTypes->size();++i) {
         switch (queueTypes->at(i)) {
            case RR:
               this->priorityQueues->push_back(new RoundRobin());
               break;
            case FCFS:
               this->priorityQueues->push_back(new FirstComeFirstServe());
               break;
            case SJF:
               this->priorityQueues->push_back(new ShortestJobFirst());
               break;
            case SRT:
               this->priorityQueues->push_back(new ShortestRemainingTime());
               break;
            default:
               this->priorityQueues->push_back(new FirstComeFirstServe());
               break;
         }
      }
   }

   void runAlgorithm();

   ~MultiLevelQueue() {
      delete this->arrivalQueue;
      delete this->ganttChart;
      delete this->priorityQueues;
      delete this->processTable;
   }

   friend class Display;
};

#endif
