#ifndef SYMBOL_displayQueues_1602686063
#define SYMBOL_displayQueues_1602686063

#include <iostream>
#include <iomanip>
using namespace std;

#include "./PriorityQueue.hpp"
#include "../services.hpp"

void PriorityQueue::displayQueues(vector<PriorityQueue*>* priorityQueues) {
   unsigned maxWaitingQueueSize = 1;
   for (auto itr = priorityQueues->begin();itr != priorityQueues->end();++itr) {
      if ((*itr)->waitingQueue->size() > maxWaitingQueueSize)
         maxWaitingQueueSize = (*itr)->waitingQueue->size();
   }

   cout << endl << endl;
   ColorPalette::add(YELLOW);

   vertiDiv(DELIMETER);
   partition(2, DELIMETER, false);
   vertiDiv(DELIMETER);
   partition(priorityQueues->size(), DELIMETER);
   vertiDiv(EMPTY);
   cout << endl;

   vertiDiv(EMPTY);
   partition(2, EMPTY, false);
   vertiDiv(EMPTY);
   for (unsigned i = 0;i < priorityQueues->size();++i) {
      vertiDiv(EMPTY);
      ColorPalette::add(GRAY);
      cout << setw(horizWidth) << (i + 1);
      ColorPalette::remove();
   }
   vertiDiv(EMPTY);
   cout << endl;

   vertiDiv(DELIMETER);
   partition(2, DELIMETER, false);
   vertiDiv(DELIMETER);
   partition(priorityQueues->size(), DELIMETER);
   vertiDiv(EMPTY);
   cout << endl;

   vertiDiv(DELIMETER);
   partition(2, DELIMETER, false);
   vertiDiv(EMPTY);
   ColorPalette::add(WHITE);
   partition(priorityQueues->size(), DELIMETER);
   vertiDiv(EMPTY);
   ColorPalette::remove();
   cout << endl;

   vertiDiv(EMPTY);
   ColorPalette::add(LIGHT_YELLOW);
   cout << setw(2 * horizWidth) << "Running Process";
   ColorPalette::remove();
   vertiDiv(EMPTY);
   ColorPalette::add(WHITE);
   for (auto itr = priorityQueues->begin();itr != priorityQueues->end();++itr) {
      vertiDiv(EMPTY);
      ColorPalette::add((*itr)->running != NULL ? AQUA : GRAY);
      cout << setw(horizWidth) << ((*itr)->running != NULL ? (*itr)->running->getId() : "-");
      ColorPalette::remove();
   }
   vertiDiv(EMPTY);
   ColorPalette::remove();
   cout << endl;

   vertiDiv(DELIMETER);
   partition(2, DELIMETER, false);
   vertiDiv(EMPTY);
   ColorPalette::add(WHITE);
   partition(priorityQueues->size(), DELIMETER);
   vertiDiv(EMPTY);
   ColorPalette::remove();
   cout << endl;

   vertiDiv(DELIMETER);
   partition(2, DELIMETER, false);
   vertiDiv(EMPTY);
   ColorPalette::add(WHITE);
   partition(priorityQueues->size(), DELIMETER);
   vertiDiv(EMPTY);
   ColorPalette::remove();
   cout << endl;

   for (unsigned i = 0;i < maxWaitingQueueSize;++i) {
      vertiDiv(EMPTY);
      ColorPalette::add(LIGHT_YELLOW);
      cout << setw(2 * horizWidth) << (i == 0 ? "Waiting Queue" : "*");
      ColorPalette::remove();
      vertiDiv(EMPTY);
      ColorPalette::add(WHITE);
      for (auto itr = priorityQueues->begin();itr != priorityQueues->end();++itr) {
         vertiDiv(EMPTY);
         if (i < (*itr)->waitingQueue->size()) {
            ColorPalette::add(AQUA);
            cout << setw(horizWidth) << (*itr)->waitingQueue->at(i)->getId();
         } else {
            ColorPalette::add(GRAY);
            cout << setw(horizWidth) << "-";
         }
         ColorPalette::remove();
      }
      vertiDiv(EMPTY);
      ColorPalette::remove();
      cout << endl;

      vertiDiv(DELIMETER);
      partition(2, DELIMETER, false);
      vertiDiv(DELIMETER);
      ColorPalette::add(WHITE);
      partition(priorityQueues->size(), DELIMETER);
      vertiDiv(EMPTY);
      ColorPalette::remove();
      cout << endl;
   }

   ColorPalette::clear();
}

#endif
