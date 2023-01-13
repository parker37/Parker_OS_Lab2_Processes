#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define  MAXSIZE  100

void childProc(int);

int main() {
  pid_t pid, *status;
  int i, iterations, children = 0;
  char buf[MAXSIZE];

  const int FORKS = 5;

  srandom(time(NULL));
  

  for(i = 0; i < FORKS; i++) {
    iterations = random() % 10 + 1;
    printf("%d\n", iterations);

    pid = fork();
    children++;

    if(pid > 0) {
      continue;

    } else if(pid == 0) {
      childProc(iterations);

      // should not get here
      exit(0); 

    } else {
      printf("An error has occured: fork()\n");
    }
  }
  
  do {
    pid = wait(&status);
    sprintf(buf, "Child Pid: %d has completed\n\n", pid);
    write(1, buf, strlen(buf));
    children--;

  } while(children > 0);


  return(0);
}

void childProc(int iter) {
  char buf[MAXSIZE];

  while(iter > 0){
    //print "Child Pid: %d is going to sleep!"
    sprintf(buf, "Child Pid: %d is going to sleep!\n\n", getpid());
    write(1, buf, strlen(buf));

    int secs = random() % 10 + 1;
    sleep(secs);

    //print "Child Pid: %d is awake!\nWhere is my Parent: %d?"
    sprintf(buf, "Child Pid: %d is awake!\nWhere is my Parent: %d?\n\n", getpid(), getppid());
    write(1, buf, strlen(buf));
    
    iter--;
  }

  exit(0);
}