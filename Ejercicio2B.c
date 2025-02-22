#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid_hijo, pid_nieto, pid_bisnieto;
    clock_t start, end;
    double elapsed_time;

    start = clock();

    pid_hijo = fork(); //proceso hijo

    if (pid_hijo == 0) { // Código hijo
        pid_nieto = fork(); // proceso nieto

        if (pid_nieto == 0) { //nieto
            pid_bisnieto = fork(); // proceso bisnieto (?

            if (pid_bisnieto == 0) { 
                for (int i = 0; i < 1000000; i++);
            } else { 
                wait(NULL); //espera a que termine
                for (int i = 0; i < 1000000; i++); 
            }
        } else {
            wait(NULL);
            for (int i = 0; i < 1000000; i++); 
        }
    } else {
        wait(NULL);
        end = clock();

        elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;
        printf("Tiempo transcurrido: %f segundos\n", elapsed_time);
    }
    return 0;
}
