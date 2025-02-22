#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main(){
    pid_t pid = fork();
    
    if (pid < 0){
        perror("Error fork");
        exit(1);
    }
    if (pid == 0){
        int count = 0;
        clock_t start_time = clock();
        clock_t time_passed; 
        for (int i =0; i < 4000000; i++){
            count++;
            time_passed = clock()-start_time;
            double time = ((double)time_passed)/CLOCKS_PER_SEC;
            if (time >= 5 && time<=15){
                break; //duracion de entre 5 y 15 segundos
            }
        }
        printf("Proceso hijo, conteo total: %d en %.2f s \n", count, ((double)time_passed)/CLOCKS_PER_SEC);
    } else{
        while(1){
            //ciclo infinito para proceso padre
        }
    }
    return 0;
}