#ifndef SYMBOL_GanttChart_1602127075
#define SYMBOL_GanttChart_1602127075

#include <deque>
using namespace std;

#include "../Process.hpp"

struct GanttSnapshot {
   Process* process;
   unsigned recordedTime;
};

class GanttChart {
private:
   deque<GanttSnapshot*>* chart;
   unsigned recordedTime;

public:
   GanttChart() {
      this->chart = new deque<GanttSnapshot*>;
      this->recordedTime = 0;
   }

   void addSnapshot(GanttSnapshot* gs) {
      gs->recordedTime = this->recordedTime = gs->recordedTime + this->recordedTime;
      if (gs->process != NULL)
         gs->process->completion = gs->recordedTime;
      this->chart->push_back(gs);
   }

   void addSnapshot(Process* process) {
      this->recordedTime += process->burst;
      GanttSnapshot* gs = new GanttSnapshot{ process, this->recordedTime };
      if (gs->process != NULL)
         gs->process->completion = gs->recordedTime;
      this->chart->push_back(gs);
   }

   unsigned getRecordedTime() {
      return this->recordedTime;
   }

   void reduce() {
      auto itr = this->chart->begin();
      while ((itr + 1) != this->chart->end()) {
         if ((*itr)->process == unitProcess && (*(itr + 1))->process == unitProcess)
            itr = this->chart->erase(itr);
         else
            ++itr;
      }
   }

   void displayChart();
};

#endif
