#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>

int status=0;

void ChildProcess(){
  srand(time(0));
  int num = (rand() % 30)+ 1;
  int i; 
  for(i=0;i<num;i++){
    printf("Child Pid: %d is going to sleep!\n",getpid());
    sleep(rand()%10+1);
    printf("Child Pid: %d is awake!\nWhere is my Parent: %d?\n",getpid(),getppid());
  }
  exit(0);
}

int main(){
  
  pid_t pid = fork();
  if(pid != 0){
    pid_t pid_2 = fork();
    if(pid_2 == 0){
      ChildProcess();
    }
  }
  else{
    ChildProcess();
  }
  
  int i;
  for(i=0;i<2;i++){
    int childpid = wait(&status);
    printf("Child Pid: %d has completed\n",childpid);
  }

  return 0;
}