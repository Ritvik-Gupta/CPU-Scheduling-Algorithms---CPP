#ifndef SYMBOL_readTable_1604227870
#define SYMBOL_readTable_1604227870

#include <fstream>
#include <regex>
using namespace std;

#include "../services.hpp"
#include "../Process.hpp"
#include "./MultiLevelQueue.hpp"
#include "../PriorityQueue/index.hpp"

MultiLevelQueue* MultiLevelQueue::readTable(ifstream file) {
   vector<Process*>* processes = new vector<Process*>;
   vector<PriorityQueue*>* priorityQueues = new vector<PriorityQueue*>;
   regex RR("^RR-[0-9]+$");
   vector<string>* temp;
   string line;

   while (true) {
      getline(file, line);
      if (line == "") break;
      temp = split(&line, " ");
      cout << endl << line << endl;
      processes->push_back(new Process(
         temp->at(0), (unsigned)stoi(temp->at(1)),
         (unsigned)stoi(temp->at(2)), (unsigned)stoi(temp->at(3))
      ));
   }

   getline(file, line);
   temp = split(&line, " ");
   cout << endl << line << endl;
   for (string queueName : *temp) {
      if (queueName == "FCFS")
         priorityQueues->push_back(new FirstComeFirstServe());
      else if (queueName == "SJF")
         priorityQueues->push_back(new ShortestJobFirst());
      else if (queueName == "SRT")
         priorityQueues->push_back(new ShortestRemainingTime());
      else if (regex_match(queueName, RR))
         priorityQueues->push_back(new RoundRobin((unsigned)stoi(queueName.substr(queueName.find('-') + 1))));
      else
         priorityQueues->push_back(new RoundRobin());
   }

   file.close();
   return new MultiLevelQueue(priorityQueues, processes);
}

#endif
