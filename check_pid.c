//
// Created by orian on 23/07/2020.
//
#include <errno.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    pid_t pid = atoi(argv[1]);
    if(kill(pid,0)==-1){
        if(errno==EPERM) printf("Process %d exist but we have no permission.",pid);
        else if(errno == ESRCH) printf("Process %d does not exist,", pid);
        else printf("Another error has happened.");
    }
    else{
        printf("Process %d exist.",pid);
    }

return 0;
}