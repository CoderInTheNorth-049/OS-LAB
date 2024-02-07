#include<stdio.h>
#include<unistd.h>
#include <iostream>
using namespace std;

int main() {
    int pipefd1[2], pipefd2[2];
    char readmsg1[80], readmsg2[80];
    
    if (pipe(pipefd1) == -1){
      cout<<"Pipe 1 creation error";
      return 1;
    }
    if (pipe(pipefd2) == -1){
      cout<<"Pipe 2 creation error";
      return 1;
    }

    int pid = fork();
    cout<<"forked\n";

    if (pid < 0){
      cout<<"Fork error";
      return 1;
    }

    if (pid == 0)
    { //child
      close(pipefd2[0]);
      write(pipefd2[1], "Child writes to pipe 2. Parent reads and outputs from pipe 2.", 80);
      cout<<"written in pipe 2\n";
      close(pipefd2[1]);

      close(pipefd1[1]);
      read(pipefd1[0], readmsg1, 80);
      cout<<readmsg1<<endl;
      close(pipefd1[0]);
    }
    else
    { //parent
      close(pipefd2[1]);
      read(pipefd2[0], readmsg2, 80);
      cout<<readmsg2<<endl;
      close(pipefd2[0]);

      close(pipefd1[0]);
      write(pipefd1[1], "Parent writes to pipe 1. Child reads and outputs from pipe 1.", 80);
      cout<<"written in pipe 1\n";
      close(pipefd1[1]);
    }

  return 0;
}

//output:
/*
forked
forked
written in pipe 2
Child writes to pipe 2. Parent reads and outputs from pipe 2.
written in pipe 1
Parent writes to pipe 1. Child reads and outputs from pipe 1.
*/