//
// Created by orian on 26/07/2020.
//
#include <stdio.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>

int counter =0;
void sigusr1Handler(int sig){
    printf("Server got %d SIGINT signals\n",counter);

}
void sigintHandler(int sig){
    counter++;
}


int main(){
    signal(SIGUSR1,sigusr1Handler);
    signal(SIGINT,sigintHandler);
    printf("Server pid is: %d\n",getpid());

    getchar();
    return 0;
}
