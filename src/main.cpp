#include <iostream>
using namespace std;

#include "../lib/services.hpp"
#include "../lib/Process.hpp"
#include "../lib/PriorityQueue/index.hpp"
#include "../lib/MultiLevelQueue/index.hpp"

int main() {
   cout << endl << endl;

   vector<PriorityQueue*> pq = { new ShortestRemainingTime(), new ShortestJobFirst() };
   vector<Process*>* P = new vector<Process*>;
   P->push_back(new Process("P-1", 0, 0, 5));
   P->push_back(new Process("P-2", 0, 4, 3));
   P->push_back(new Process("P-3", 1, 3, 9));
   P->push_back(new Process("P-4", 1, 10, 1));
   P->push_back(new Process("P-5", 0, 20, 2));

   MLQ* ml = new MLQ(&pq, P);

   delete ml;

   cout << endl << endl;
   return 1;
}
