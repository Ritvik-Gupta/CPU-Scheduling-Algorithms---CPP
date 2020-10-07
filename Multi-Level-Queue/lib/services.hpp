#ifndef SYMBOL_services_1601875909
#define SYMBOL_services_1601875909

#include "./Process.hpp"

enum QueueTypes { RR, FCFS, SJF, SRT };

struct GanttSnapshot {
   Process* process;
   unsigned recordedTime;
};

#endif
