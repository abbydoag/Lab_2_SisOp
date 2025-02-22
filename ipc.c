#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/mman.h>

#define SHM_SIZE 1024 // Tamaño de la memoria compartida
#define SHM_NAME "/lab_shm" // Nombre del objeto de memoria compartida

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Uso: %s <n> <x>\n", argv[0]);
        exit(1);
    }

    int n = atoi(argv[1]);  // Número 'n'
    char x = argv[2][0];    // Carácter 'x'

    int shm_fd;
    char *shm_ptr;

    // Intentar abrir la memoria compartida existente
    shm_fd = shm_open(SHM_NAME, O_RDWR, 0666);
    int first_time = 0;

    if (shm_fd == -1) {
        if (errno == ENOENT) {
            // Si no existe, crearla
            shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
            if (shm_fd == -1) {
                perror("Error en shm_open");
                exit(1);
            }

            // Ajustar tamaño
            if (ftruncate(shm_fd, SHM_SIZE) == -1) {
                perror("Error en ftruncate");
                exit(1);
            }

            first_time = 1; // Indicar que somos la primera ejecución
        } else {
            perror("Error en shm_open");
            exit(1);
        }
    }

    // Mapear la memoria compartida
    shm_ptr = mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (shm_ptr == MAP_FAILED) {
        perror("Error en mmap");
        exit(1);
    }

    // Cerrar el descriptor de archivo (ya no es necesario)
    close(shm_fd);

    // Si es la primera vez que se ejecuta, inicializar la memoria con '-'
    if (first_time) {
        memset(shm_ptr, '-', SHM_SIZE);
    }

    // Crear un pipe para la comunicación padre-hijo
    int pipefds[2];
    if (pipe(pipefds) == -1) {
        perror("Error en pipe");
        exit(1);
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("Error en fork");
        exit(1);
    }

    if (pid == 0) {  
        // ---- Proceso hijo ----
        close(pipefds[1]); // Cerrar escritura del pipe

        int index;
        while (read(pipefds[0], &index, sizeof(index)) > 0) {
            if (index >= 0 && index < SHM_SIZE) {
                shm_ptr[index] = x; // Escribir solo en las posiciones correspondientes
            }
        }

        close(pipefds[0]); // Cerrar lectura del pipe
        exit(0);

    } else {  
        // ---- Proceso padre ----
        close(pipefds[0]); // Cerrar lectura del pipe

        for (int i = 0; i < SHM_SIZE; i++) {
            if (i % n == 0) {
                write(pipefds[1], &i, sizeof(i)); // Notificar al hijo
            }
        }

        close(pipefds[1]); // Cerrar escritura del pipe
        wait(NULL); // Esperar al hijo

        // Imprimir la memoria compartida
        printf("Contenido de la memoria compartida:\n");
        write(STDOUT_FILENO, shm_ptr, SHM_SIZE);
        printf("\n");

        // Liberar recursos
        munmap(shm_ptr, SHM_SIZE);
    }

    return 0;
}