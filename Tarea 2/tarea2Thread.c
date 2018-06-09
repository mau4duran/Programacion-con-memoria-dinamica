#include <stdio.h>
#include <stdlib.h> // esta permite trabajar con memoria dinámica
#include <math.h>
#include <string.h>
#include <time.h>
#include <pthread.h>

typedef struct{
    long low;
    long high;
}limit;

double valorPi = 0;

void * pi(void * arg);

int main(void){
    struct timespec start, finish; //
    int elapsed;//

    limit lim[16];
    pthread_t h[16];

    int n;
    printf("Hilos?\t" );
    scanf("%d", &n);

    clock_gettime(CLOCK_MONOTONIC, &start);

    long r = 50000000000/n;
    for (int i = 0; i < n; i++) {
        lim[i].low= r*i+1;
        lim[i].high =r*(i+1);

        pthread_create(&h[i], NULL, pi, (void *) &lim[i]);

    }
    double resp;

    for (int k = 0; k < n; k++) {
        pthread_join(h[k] , NULL);
    }

    printf("Pi:\t%.10lf\n", valorPi);


    //clock_t stop = clock();
    clock_gettime(CLOCK_MONOTONIC, &finish);

    //long ms = (stop - start)/CLOCKS_PER_SEC;

    elapsed = (finish.tv_sec - start.tv_sec)*1000;
    elapsed += (finish.tv_nsec - start.tv_nsec)*1000 / 1000000000.0;

    printf("Tiempo:\t%d ms\n", elapsed);

    return EXIT_SUCCESS;
}

void * pi(void * arg){
    limit *lim = (limit*) arg;
    double suma = 0;
    for (long long i = lim->low; i <= lim->high; i++) {
        //suma += (pow(-1,i+1)/(2*i-1));
        suma += (( i + 1 ) & 1 ? -1.0 :1.0)/(2*i-1);
    }

    suma *= 4;

    valorPi += suma;


    return NULL;

}
