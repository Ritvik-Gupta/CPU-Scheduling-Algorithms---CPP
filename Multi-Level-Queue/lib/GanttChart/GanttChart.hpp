#ifndef SYMBOL_GanttChart_1602127075
#define SYMBOL_GanttChart_1602127075

#include <vector>
using namespace std;

#include "../Process.hpp"

struct GanttSnapshot {
   Process* process;
   unsigned recordedTime;
};

class GanttChart {
private:
   vector<GanttSnapshot*>* chart;
   unsigned recordedTime;

public:
   GanttChart() {
      this->chart = new vector<GanttSnapshot*>;
      this->recordedTime = 0;
   }

   void addSnapshot(GanttSnapshot* gs) {
      gs->recordedTime = this->recordedTime = gs->recordedTime + this->recordedTime;
      if (gs->process != NULL)
         gs->process->completion = gs->recordedTime;
      this->chart->push_back(gs);
   }

   unsigned getRecordedTime() {
      return this->recordedTime;
   }

   void displayChart();
};

#endif
