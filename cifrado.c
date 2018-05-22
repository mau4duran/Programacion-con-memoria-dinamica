#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int main(void) {
    char* texto;
    int lon;

    printf("Escriba Cadena\n");
    gets(texto);

    printf("Longitud: ");
    scanf("%d", &lon);

    int x;

    for (int i = 0; i < strlen(texto); i++) {

        if (texto[i]==' ' || texto[i]=='.' || texto[i]==',') {
            continue;
        }else{
            if (texto[i]>=65 && texto[i]<=90 && texto[i]+lon>90) {
                texto[i]=65+(texto[i]+lon)-91;
            } else if (texto[i]>=97 && texto[i]<=122 && texto[i]+lon>122) {
                texto[i]=97+(texto[i]+lon)-123;
            }
            else{
                texto[i]+=lon;
            }

        }
    }

    for (int i = 0; i < strlen(texto); i++) {
        printf("%c", texto[i]);
    }
    printf("\n");
	return EXIT_SUCCESS;
}
