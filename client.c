//
// Created by orian on 26/07/2020.
//
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc , char* argv[]){
    if(argc !=4 && (atoi(argv[2])!=2 || atoi(argv[2])!=10)){
        printf("Wrong parameters, exit from program");
        exit(-1);
    }
    pid_t  pid = atoi(argv[1]);
    int sig = atoi(argv[2]);
    int times = atoi(argv[3]);
    printf("sig:%d , times:%d , pid:%d , argc:%d\n",sig,times,pid, argc);
    int n = 0;
    while(n<times){
        kill(pid,sig);
        n++;
    }
    return 0;
}
