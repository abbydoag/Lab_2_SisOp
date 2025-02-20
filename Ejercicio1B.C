//ciclo for con 4 iteraciones
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
    for(int i=0; i<4; i++){
        pid_t pid = fork();
        if (pid<0){
            perror("Error fork");
            exit(1);
        } else if (pid ==0){
            printf("Child %d: PID= %d, ParentPID= %d \n", i, getpid(), getppid());
            exit(0); //child no crea procesos
        }
    }
    sleep(2);
    printf("Parent completado\nPID= %d\n", getpid());
    return 0;
}