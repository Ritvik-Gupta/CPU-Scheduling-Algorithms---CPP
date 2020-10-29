#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <deque>
#include <vector>

using namespace std;

#define NUM_THREADS 5
pthread_mutex_t lock;
pthread_mutex_t* consoleLock = new pthread_mutex_t;

class X;
struct A {
   X* obj;
   unsigned param;
};

class X {

private:
   vector<unsigned>* vars;

public:
   X() {
      this->vars = new vector<unsigned>{ 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20 };
   }

   void* x(void* context) {
      unsigned sleep_time;
      unsigned tid = (unsigned)context;
      while (this->vars->size() > 0) {
         pthread_mutex_lock(&lock);
         sleep_time = this->vars->back();
         this->vars->pop_back();
         pthread_mutex_unlock(&lock);
         pthread_mutex_lock(consoleLock);
         cout << "Sleeping in thread with id :\t" << tid << "\t for\t" << sleep_time << " sec" << endl;
         pthread_mutex_unlock(consoleLock);
         sleep(sleep_time / 5);
      }
      pthread_mutex_lock(consoleLock);
      cout << "Thread with id : " << tid;
      sleep(2);
      cout << "\t...exiting " << endl;
      pthread_mutex_unlock(consoleLock);
      pthread_exit((void*)(2 * tid));
      return NULL;
   }

   static void* create(void* context) {
      A* a = (A*)context;
      return a->obj->x((void*)a->param);
   }
};

int main() {
   vector<pthread_t*>* threads = new vector<pthread_t*>;
   void* status;
   pthread_mutex_init(&lock, NULL);
   X* obj = new X();

   for (unsigned i = 0; i < NUM_THREADS; ++i) {
      // cout << "main() : creating thread, " << i << endl;
      threads->push_back(new pthread_t);
      pthread_create(threads->back(), NULL, X::create, (void*)new A{ obj, i });
   }

   pthread_exit(NULL);
   pthread_mutex_destroy(&lock);
   return 1;
}
