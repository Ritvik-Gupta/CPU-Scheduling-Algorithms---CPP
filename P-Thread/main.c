#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>

int first[5], second[5], third[5];
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
bool string1 = false;
FILE* file;
pthread_cond_t cond;

struct process {
   int pid;
   int burst;
   int priority;
   int working;
   int waiting;
   struct process* next;
};

void* read_for_pthread() {
   while (true) {
      while (string1);
      pthread_mutex_lock(&lock);
      printf("Input data\n");
      printf("PID Brust time Priority\n");
      for (unsigned i = 0; i < 5; ++i) {
         fscanf(stdin, "%d %d %d", &first[i], &second[i], &third[i]);
         printf("\n");
         fprintf(file, "%d %d %d\n", first[i], second[i], third[i]);
      }
      fclose(file);
      string1 = true;
      pthread_mutex_unlock(&lock);
      pthread_cond_signal(&cond);
      pthread_exit(NULL);
   }
}

void* write_for_pthread() {
   while (true) {
      pthread_mutex_lock(&lock);
      while (!string1)
         pthread_cond_wait(&cond, &lock);
      fprintf(stdout, "\n\n");
      printf("PID Brust time Priority\n");
      for (unsigned i = 0; i < 5; ++i) {
         fscanf(file, "%d %d %d", &first[i], &second[i], &third[i]);
         printf("Process:");
         fprintf(stdout, "%d %d %d \n", first[i], second[i], third[i]);
      }
      fclose(file);
      string1 = false;
      pthread_mutex_unlock(&lock);
      pthread_exit(NULL);
   }
}

struct process* init_process(int pid, int burst, int priority) {
   struct process* proc = (struct process*)malloc(sizeof(struct process));
   if (proc == NULL) {
      printf("Fatal error: memory allocation failure.\nTerminating.\n");
      exit(1);
   }
   proc->pid = pid;
   proc->burst = burst;
   proc->priority = priority;
   proc->working = 0;
   proc->waiting = 0;
   proc->next = NULL;
   return(proc);
};

void display(struct process* first) {
   printf("Please Enter your Choice:\n");
   printf("\n1 for List of Processes\n");
   printf("2 for First Come First Serve Scheduling Algorithm\n");
   printf("3 for Round Robin Scheduling Algorithm\n");
   printf("4 for Shortest job first Scheduling Algorithm\n");
   printf("5 to Display All Scheduling Algorithms\n");
   printf("6 To Exit Terminal\n");
   printf("-->\t");
   int aa;
   scanf("%d", &aa);
   switch (aa) {
      case 1:
         listprocs(first);
         display(first);
         break;
      case 2:
         fcfs(first);
         display(first);
         break;
      case 3:
         rr(first, 1);
         display(first);
         break;
      case 4:
         sjf(first);
         display(first);
         break;
      case 5:
         listprocs(first);
         fcfs(first);
         rr(first, 1);
         sjf(first);
         display(first);
         break;
      case 6:
         break;
      default:
         display(first);
         break;
   }
}

void fcfs(struct process* proc) {
   int time = 0, start, completion, avgfcfs = 0, avgfcfs1 = 0;
   struct process* tmp = proc;
   printf("BEGIN:\tFCFS Scheduling Algorithm\n");
   while (tmp != NULL) {
      start = time;
      time += tmp->burst;
      completion = time;
      printf("Process: %d\tCompletion Time: %d\tWaiting: %d\tTurnaround: %d\n",
         tmp->pid, time, start, completion);
      avgfcfs = avgfcfs + completion;
      avgfcfs1 = avgfcfs1 + start;
      tmp = tmp->next;
   }
   printf("Average Turn Around Time:%f\n", (float)avgfcfs / 5);
   printf("Average Waiting Time:%f\n", (float)avgfcfs1 / 5);
   printf("Therefore Average Burst Time:%f\n", (float)(avgfcfs - avgfcfs1) / 5);
   printf("END:\tFCFS Scheduling Algorithm\n\n");
}

void listprocs(struct process* proc) {
   struct process* tmp = proc;
   printf("BEGIN:\tProcess Listing\n");
   while (tmp != NULL) {
      printf("PID: %d\t\tPriority: %d\tBurst: %d\n", tmp->pid, tmp->priority, tmp->burst);
      tmp = tmp->next;
   }
   printf("END:\tProcess Listing\n\n");
}

void rr(struct process* proc, int quantum) {
   int jobsremain, passes, avgrr = 0, avgrr1 = 0;
   struct process* copy, * tmpsource, * tmp, * slot;
   printf("BEGIN:\tRR Scheduling Algorithm (Quantum: %d)\n", quantum);
   tmpsource = proc;
   copy = tmp = NULL;
   while (tmpsource != NULL) {
      if (copy == NULL) {
         copy = init_process(tmpsource->pid, tmpsource->burst, tmpsource->priority);
         tmp = copy;
      } else {
         tmp->next = init_process(tmpsource->pid, tmpsource->burst, tmpsource->priority);
         tmp = tmp->next;
      }
      tmpsource = tmpsource->next;
   }
   jobsremain = 1;
   slot = NULL;
   while (jobsremain) {
      jobsremain = 0;
      if (slot == NULL) {
         slot = copy;
         jobsremain = 1;
      } else {
         passes = 0;
         do {
            if (slot->next == NULL) {
               passes++;
               slot = copy;
            } else
               slot = slot->next;

         } while (passes <= 2 && slot->burst == slot->working);
         if (passes <= 2) {
            jobsremain = 1;
         }
      }
      tmp = copy;
      while (tmp != NULL) {
         if (tmp->burst > tmp->working) {
            if (tmp == slot)
               tmp->working += quantum;
            else
               tmp->waiting += quantum;
         }
         tmp = tmp->next;
      }
   }
   tmp = copy;
   while (tmp != NULL) {
      printf("Process: %d\tWorking: %d\tWaiting: %d\tTurnaround: %d\n",
         tmp->pid, tmp->working, tmp->waiting, tmp->working + tmp->waiting);
      avgrr = avgrr + tmp->working + tmp->waiting;
      avgrr1 = avgrr1 + (tmp->waiting);
      tmpsource = tmp;
      tmp = tmp->next;
      free(tmpsource);
   }
   printf("Average TAT:%f\n", (float)avgrr / 5);
   printf("Average WT:%f\n", (float)avgrr1 / 5);
   printf("Therefore Average Burst Time:%f\n", (float)(avgrr - avgrr1) / 5);
   printf("END:\tRR Scheduling Algorithm\n\n");
}

void sjf(struct process* proc) {
   int time, start, completion, shortest, avgsjf = 0, avgsjf1 = 0;
   struct process* copy, * tmpsource, * tmp, * beforeshortest;
   printf("BEGIN:\tSJF Scheduling Algorithm\n");
   tmpsource = proc;
   copy = tmp = NULL;
   while (tmpsource != NULL) {
      if (copy == NULL) {
         copy = init_process(tmpsource->pid, tmpsource->burst, tmpsource->priority);
         tmp = copy;
      } else {
         tmp->next = init_process(tmpsource->pid, tmpsource->burst, tmpsource->priority);
         tmp = tmp->next;
      }
      tmpsource = tmpsource->next;
   }
   time = 0;
   while (copy != NULL) {
      beforeshortest = NULL;
      shortest = copy->burst;
      tmp = copy->next;
      tmpsource = copy;
      while (tmp != NULL) {
         if (tmp->burst < shortest) {
            shortest = tmp->burst;
            beforeshortest = tmpsource;
         }
         tmpsource = tmp;
         tmp = tmp->next;
      }
      if (beforeshortest == NULL) {
         start = time;
         time += copy->burst;
         completion = time;
         printf("Process: %d\t Burst Time: %d\t Completion Time: %d\tWaiting: %d\tTurnaround: %d\n",
            copy->pid, completion - start, time, start, completion);
         avgsjf = avgsjf + completion;
         avgsjf1 = avgsjf1 + start;
         tmpsource = copy;
         copy = copy->next;
         free(tmpsource);
      } else {
         tmp = beforeshortest->next;
         start = time;
         time += tmp->burst;
         completion = time;
         printf("Process: %d\t Burst Time: %d\t Completion Time: %d\tWaiting: %d\tTurnaround: %d\n",
            tmp->pid, completion - start, time, start, completion);
         avgsjf = avgsjf + completion;
         avgsjf1 = avgsjf1 + start;
         beforeshortest->next = tmp->next;
         free(tmp);
      }
   }
   printf("Average Turn Around Time:%f\n", (float)avgsjf / 5);
   printf("Average Waiting Time:%f\n", (float)avgsjf1 / 5);
   printf("Therefore Average Burst Time:%f\n", (float)(avgsjf - avgsjf1) / 5);
   printf("END:\tSJF Scheduling Algorithm\n\n");
}

void main() {
   struct process* plist, * ptmp;
   pthread_t tr, tw;
   pthread_create(&tr, NULL, read_for_pthread, NULL);
   pthread_create(&tw, NULL, write_for_pthread, NULL);
   pthread_join(tr, NULL);
   pthread_join(tw, NULL);

   plist = init_process(first[0], second[0], third[0]);
   plist->next = init_process(first[1], second[1], third[1]); ptmp = plist->next;

   ptmp->next = init_process(first[2], second[2], third[2]); ptmp = ptmp->next;
   ptmp->next = init_process(first[3], second[3], third[3]); ptmp = ptmp->next;
   ptmp->next = init_process(first[4], second[4], third[4]);

   display(plist);
   while (plist != NULL) {
      ptmp = plist;
      plist = plist->next;
      free(ptmp);
   }
}
