#include<iostream>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<string.h>

using namespace std;

int main(int argc, char* argv[]){

    int pid=fork();

    if(pid<0){
        exit(0);
    }
    else if(pid==0){
        if (strcmp(argv[1], "ls") == 0){
            execlp("/bin/ls", "ls", NULL);
        }
        else if (strcmp(argv[1], "cp") == 0){
            execlp("/bin/cp", "cp", argv[2], argv[3], NULL);
        }
        else if (strcmp(argv[1], "grep") == 0){
            execlp("/bin/grep", "grep", argv[2], argv[3], argv[4], NULL);
        }
        else{
            printf("Invalid command\n");
            exit(1);
        }
    }
    else{
        int status;
        waitpid(pid, &status, 0);

        if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
        {
            printf("Child process executed successfully\n");
        }
        else
        {
            printf("Child process failed to execute\n");
        }
    }
    return 0;
}

/* 
commands :
    ./a.out ls
    ./a.out cp f1.txt f2.txt
    ./a.out grep -i arif f1.txt
 */

/* 
outputs:
1)  ./a.out ls
    a.out  copy.cpp  os_ass1.cpp
    Child process executed successfully

2) ./a.out cp f1.txt f2.txt
    Child process executed successfully

3) ./a.out grep -i arif f1.txt
    arif mulani
    Child process executed successfully
 */

/* 
(base) pccoe@pccoe-V50t-Gen-2-13IOB:~/TYCOC157-OS$ ./a.out ls
a.out  copy.cpp  f1.txt  f2.txt  os_ass1.cpp
Child process executed successfully
(base) pccoe@pccoe-V50t-Gen-2-13IOB:~/TYCOC157-OS$ ./a.out cp f1.txt f2.txt
Child process executed successfully
(base) pccoe@pccoe-V50t-Gen-2-13IOB:~/TYCOC157-OS$ ./a.out grep -i arif f1.txt
arif mulani
Child process executed successfully
(base) pccoe@pccoe-V50t-Gen-2-13IOB:~/TYCOC157-OS$ 
 */