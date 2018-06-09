#include <stdio.h>
#include <stdlib.h> // esta permite trabajar con memoria dinámica
#include <math.h>
#include <string.h>
#include <time.h>

double pi();

int main(void){

    clock_t start = clock();

    printf("Pi:\t%.10lf\n",pi() );

    clock_t stop = clock();

    long ms = 1000 * (stop - start)/CLOCKS_PER_SEC;

    printf("Tiempo:\t%ldms\n", ms);
    return EXIT_SUCCESS;


}

double pi(){
    double suma = 0;
    int w = 1;
    for (long long i = 1; i <= 50000000000; i++) {
        suma += (( i + 1 ) & 1 ? -1.0 :1.0)/(2*i-1);
    }

    suma *= 4;

    return suma;
}
