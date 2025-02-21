# include <stdio.h>
#include <time.h>

int main (){
    clock_t start_time, end_time;
    double total_time;

    start_time = clock(); //inicia timer

    for(int i = 0; i<1000000; i++);
    for(int i = 0; i<1000000; i++);
    for(int i = 0; i<1000000; i++);

    end_time = clock(); //termina timer
    //tiempo total segundos
    total_time = (double)(end_time-start_time)/CLOCKS_PER_SEC;
    printf("TIEMPO TOTAL: %f segundos\n", total_time);
    return 0;
}