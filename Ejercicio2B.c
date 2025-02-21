#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid_hijo, pid_nieto, pid_bisnieto;
    clock_t start, end;
    double elapsed_time;

    // Captura el tiempo antes del primer fork()
    start = clock();

    pid_hijo = fork(); // Primer fork: crea el proceso hijo

    if (pid_hijo == 0) { // Código del hijo
        pid_nieto = fork(); // Segundo fork: crea el proceso nieto

        if (pid_nieto == 0) { // Código del nieto
            pid_bisnieto = fork(); // Tercer fork: crea el proceso bisnieto

            if (pid_bisnieto == 0) { // Código del bisnieto
                for (int i = 0; i < 1000000; i++); // Ciclo del bisnieto
            } else { // Código del nieto
                wait(NULL); // Espera a que termine el bisnieto
                for (int i = 0; i < 1000000; i++); // Ciclo del nieto
            }
        } else { // Código del hijo
            wait(NULL); // Espera a que termine el nieto
            for (int i = 0; i < 1000000; i++); // Ciclo del hijo
        }
    } else { // Código del proceso padre
        wait(NULL); // Espera a que termine el hijo
        end = clock(); // Captura el tiempo después de que termine el hijo

        // Cálculo del tiempo transcurrido en segundos
        elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;
        printf("Tiempo transcurrido: %f segundos\n", elapsed_time);
    }

    return 0;
}