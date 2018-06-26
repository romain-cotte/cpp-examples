#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <thread>

using namespace std;

void *print_message_function(void *ptr );

void *print_message_function(void *ptr) {
  char *message;
  message = (char *) ptr;
  printf("%s \n", message);
}

int main(int argc, const char **argv) {
  pthread_t thread1, thread2;
  char *message1 = "Thread 1";
  char *message2 = "Thread 2";
  int  iret1, iret2;

  /* Create independent threads each of which will execute function */

  iret1 = pthread_create(&thread1, NULL, print_message_function, (void*) message1);
  iret2 = pthread_create(&thread2, NULL, print_message_function, (void*) message2);

  /* Wait till threads are complete before main continues. Unless we  */
  /* wait we run the risk of executing an exit which will terminate   */
  /* the process and all threads before the threads have completed.   */

  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);

  printf("Thread 1 returns: %d\n", iret1);
  printf("Thread 2 returns: %d\n", iret2);

  unsigned int n = std::thread::hardware_concurrency();
  std::cout << n << " concurrent threads are supported.\n";

  exit(0);
}
