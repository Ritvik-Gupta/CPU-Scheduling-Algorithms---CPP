#include <iostream>
using namespace std;

#include "../lib/services.hpp"
#include "../lib/Process.hpp"
#include "../lib/ProcessTable/index.hpp"
#include "../lib/GanttChart/index.hpp"
#include "../lib/PriorityQueue/index.hpp"
#include "../lib/MultiLevelQueue/index.hpp"

int main() {
   vector<PriorityQueue*> pq = { new ShortestRemainingTime(), new ShortestJobFirst(), new FirstComeFirstServe(), new RoundRobin(5) };
   vector<Process*>* P = new vector<Process*>({
         new Process("P-1", 2, 0, 5),
         new Process("P-2", 1, 4, 3),
         new Process("P-3", 4, 3, 9),
         new Process("P-4", 4, 10, 1),
         new Process("P-5", 3, 20, 2),
         new Process("P-6", 1, 20, 2),
         new Process("P-7", 1, 20, 2),
         new Process("P-8", 3, 20, 2)
      });

   MultiLevelQueue* MLQ = new MultiLevelQueue(&pq, P);
   MLQ->runAlgorithm();
   MLQ->display();
   delete MLQ;

   cout << endl << endl;
   return 1;
}
