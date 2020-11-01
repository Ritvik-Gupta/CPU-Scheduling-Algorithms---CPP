#ifndef SYMBOL_readTable_1604227870
#define SYMBOL_readTable_1604227870

#include <fstream>
using namespace std;

#include "../services.hpp"
#include "./MultiProcessor.hpp"

MultiProcessor* MultiProcessor::readTable(ifstream file) {
   vector<ProcessShell*>* processShells = new vector<ProcessShell*>;
   vector<Process*>* processes = new vector<Process*>;
   vector<Processor*>* processors = new vector<Processor*>;
   vector<vector<string>*>* splitPoints = new vector<vector<string>*>;
   string line;

   while (true) {
      getline(file, line);
      if (line == "")
         break;
      splitPoints->push_back(split(&line, ","));
   }

   for (vector<string>* point : *splitPoints)
      processShells->push_back(new ProcessShell{ point->front(), (unsigned)stoi(point->back()) });
   splitPoints->clear();

   while (true) {
      getline(file, line);
      if (line == "")
         break;
      splitPoints->push_back(split(&line, ","));
   }

   for (vector<string>* point : *splitPoints) {
      ProcessShell* referencedShell = NULL;
      for (ProcessShell* shell : *processShells) {
         if (shell->id == point->front())
            referencedShell = shell;
      }
      processes->push_back(new Process(referencedShell, (unsigned)stoi(point->back())));
   }
   splitPoints->clear();

   while (true) {
      getline(file, line);
      if (line == "")
         break;
      splitPoints->push_back(split(&line, ","));
   }

   for (vector<string>* point : *splitPoints)
      processors->push_back(new Processor(point->front(), (unsigned)stoi(point->back())));
   splitPoints->clear();

   file.close();
   return new MultiProcessor(processes, processors);
}

#endif
