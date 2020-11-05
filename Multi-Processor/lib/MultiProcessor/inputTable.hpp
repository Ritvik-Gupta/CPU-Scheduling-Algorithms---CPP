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
   vector<string>* temp;
   string line;

   while (true) {
      getline(file, line);
      if (line == "") break;
      temp = split(&line, ",");
      processShells->push_back(new ProcessShell{ temp->front(), (unsigned)stoi(temp->back()) });
   }

   while (true) {
      getline(file, line);
      if (line == "") break;
      temp = split(&line, ",");
      ProcessShell* referencedShell = NULL;
      for (ProcessShell* shell : *processShells) {
         if (shell->id == temp->front())
            referencedShell = shell;
      }
      processes->push_back(new Process(referencedShell, (unsigned)stoi(temp->back())));
   }

   while (true) {
      getline(file, line);
      if (line == "") break;
      temp = split(&line, ",");
      processors->push_back(new Processor(temp->front(), (unsigned)stoi(temp->back())));
   }

   file.close();
   return new MultiProcessor(processes, processors);
}

#endif
