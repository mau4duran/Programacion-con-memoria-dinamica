#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int main(void) {
    char texto[30];
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
            texto[i]+=lon;
        }
    }

    for (int i = 0; i < strlen(texto); i++) {
        printf("%c", texto[i]);
    }
	return EXIT_SUCCESS;
}
