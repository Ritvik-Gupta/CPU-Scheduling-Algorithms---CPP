#include <iostream>
using namespace std;

#include "../lib/services.hpp"
#include "../lib/Process.hpp"
#include "../lib/PriorityQueue/index.hpp"
#include "../lib/MultiLevelQueue/index.hpp"
#include "../lib/Display/index.hpp"

int main() {

   vector<PriorityQueue*> pq = { new ShortestRemainingTime(), new ShortestJobFirst() };
   vector<Process*>* P = new vector<Process*>;
   P->push_back(new Process("P-1", 0, 0, 5));
   P->push_back(new Process("P-2", 0, 4, 3));
   P->push_back(new Process("P-3", 1, 3, 9));
   P->push_back(new Process("P-4", 1, 10, 1));
   P->push_back(new Process("P-5", 0, 20, 2));
   P->push_back(new Process("P-6", 0, 20, 2));
   P->push_back(new Process("P-7", 0, 20, 2));
   P->push_back(new Process("P-8", 0, 20, 2));

   MultiLevelQueue* MLQ = new MultiLevelQueue(&pq, P);
   MLQ->runAlgorithm();
   Display::table(MLQ);
   delete MLQ;

   cout << endl << endl;
   return 1;
}
