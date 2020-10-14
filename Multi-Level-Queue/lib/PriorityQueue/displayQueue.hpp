#ifndef SYMBOL_displayQueue_1602669738
#define SYMBOL_displayQueue_1602669738

#include <iostream>
#include <iomanip>
using namespace std;

#include "./PriorityQueue.hpp"
#include "../services.hpp"

void PriorityQueue::displayQueue() {
   cout << this->waitingQueue->size() << endl;
}

#endif
