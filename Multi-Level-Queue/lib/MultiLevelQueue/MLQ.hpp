#ifndef SYMBOL_MLQ_1601963303
#define SYMBOL_MLQ_1601963303

#include <iostream>
#include <vector>
#include <deque>
using namespace std;

#include "../services.hpp"
#include "../PriorityQueue/index.hpp"

class MLQ {
private:
   vector<GanttSnapshot*>* ganttChart;
   vector<PriorityQueue*>* priorityQueues;
   vector<Process*>* processTable;
   deque<Process*>* arrivalQueue;
   unsigned recordedTime;

   PriorityQueue* getQueue(unsigned pos) {
      return this->priorityQueues->at(pos);
   }

   void addSnapshot(GanttSnapshot* gs) {
      gs->recordedTime = this->recordedTime = gs->recordedTime + this->recordedTime;
      if (gs->process != NULL) gs->process->completion = gs->recordedTime;
      this->ganttChart->push_back(gs);
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
         if ((*itr)->getArrival() <= this->recordedTime) {
            this->priorityQueues->at((*itr)->getQueueNum())->add(*itr);
            itr = this->arrivalQueue->erase(itr);
         } else
            ++itr;
      }
   }

   void runAlgorithm();

public:
   MLQ(vector<PriorityQueue*>* priorityQueues, vector<Process*>* P) {
      this->priorityQueues = priorityQueues;
      this->ganttChart = new vector<GanttSnapshot*>;
      this->processTable = P;
      this->arrivalQueue = new deque<Process*>;
      for (unsigned i = 0;i < P->size();++i)
         this->arrivalQueue->push_back(P->at(i));
      this->recordedTime = 0;

      this->runAlgorithm();
      for (auto itr = this->ganttChart->begin();itr != this->ganttChart->end();++itr) {
         cout << ((*itr)->process != NULL ? (*itr)->process->getId() : "");
         cout << "\t:\t" << (*itr)->recordedTime << endl;
      }
   }

   MLQ(vector<QueueTypes>* queueTypes, vector<Process*>* P) {
      this->priorityQueues = new vector<PriorityQueue*>;
      this->ganttChart = new vector<GanttSnapshot*>;
      this->processTable = P;
      this->arrivalQueue = new deque<Process*>;
      for (unsigned i = 0;i < P->size();++i)
         this->arrivalQueue->push_back(P->at(i));
      this->recordedTime = 0;

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
      this->runAlgorithm();
      for (auto itr = this->ganttChart->begin();itr != this->ganttChart->end();++itr) {
         cout << ((*itr)->process != NULL ? (*itr)->process->getId() : "");
         cout << "\t:\t" << (*itr)->recordedTime << endl;
      }
   }

   ~MLQ() {
      delete this->arrivalQueue;
      delete this->ganttChart;
      delete this->priorityQueues;
      delete this->processTable;
   }
};

#endif
