#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;

    // Hacer un fork
    pid = fork();
    if (pid == -1) {
        perror("Error en fork");
        exit(1);
    }

    if (pid == 0) {
        // Proceso hijo: Ejecuta ipc con "b" como el valor para x
        execl("./Ejercicio5", "Ejercicio5", "2", "b", (char *)NULL);
        perror("Error al ejecutar ipc en el proceso hijo");
        exit(1);
    } else {
        // Proceso padre espera a que el hijo termine
        int status;
        waitpid(pid, &status, 0);
        
        // Ahora ejecuta ipc con "a" como el valor para x
        execl("./Ejercicio5", "Ejercicio5", "3", "a", (char *)NULL);
        perror("Error al ejecutar ipc en el proceso padre");
        exit(1);
    }

    return 0;
}