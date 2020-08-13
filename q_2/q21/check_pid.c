//
// Created by orian on 23/07/2020.
//
#include <errno.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    if(argc!=2){
    	printf("Wrong parameter to main");
    	return -1;
    }
    pid_t pid = atoi(argv[1]);
    if(kill(pid,0)==-1){
        if(errno==EPERM) printf("Process %d exist but we have no permission.\n",pid);
        else if(errno == ESRCH) printf("Process %d does not exist.\n", pid);
        else printf("Another error has happened\n.");
    }
    else{
        printf("Process %d exist.\n",pid);
    }

return 0;
}
