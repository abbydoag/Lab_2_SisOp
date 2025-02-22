#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>

int main(){
    pid_t pid = fork();
    
    if (pid < 0){
        perror("Error fork");
        exit(1);
    }
    if (pid == 0){
        printf("Proceso hijo desplegado");
    } else{
        while(1){
            //ciclo infinito para proceso padre
        }
    }
    return 0;
}