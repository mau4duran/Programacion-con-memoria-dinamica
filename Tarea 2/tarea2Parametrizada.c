#include <stdio.h>
#include <stdlib.h> // esta permite trabajar con memoria dinámica
#include <math.h>
#include <string.h>
#include <time.h>
#include <pthread.h>

double pi();

int main(void){

    clock_t start = clock();


    printf("%.10lf\n",pi(0,50000000000));

    clock_t stop = clock();

    int ms = 1000 * (stop - start)/CLOCKS_PER_SEC;
    return EXIT_SUCCESS;
}

double pi(long n, long m){
    double suma = 0;
    for (long i = n; i <= m; i++) {
        suma += (( i + 1 ) & 1 ? -1.0 :1.0)/(2*i-1);
    }

    suma *= 4;

    return suma;
}
