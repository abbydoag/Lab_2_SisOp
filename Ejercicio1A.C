//4 forks consecutivos
# include  <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
    fork();
    fork();
    fork();
    fork();    //4 forks
    printf("PID: %d, ParentPID: %d\n", getpid(), getppid());
    sleep(1); //visualizacion salida
    return 0;
}