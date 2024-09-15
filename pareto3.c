#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double dPrecio; //d=tipo de dato double
    double dPeso;
    } sPuntos;
// argv[0]=nombre del programa, argv[1]=nombre del archivo con los datos, argv[2]=argumento con la cantidad de puntos
int main( int argc, int argv[]) {
    FILE *pArchivo = fopen(argv[1], "r"); //C no permite interactuar directamente con un archivo por tanto se necesita un puntero a una estructura FILE
    if(pArchivo==NULL){//error al leer el archivo
        perror("No se puede leer el archivo");
        exit(1);}
    int nNoPuntos=atoi(argv[2]);//convertimos la cadena de entrada a un integer
    sPuntos *aPunto = (sPuntos *) malloc(nNoPuntos * sizeof(sPuntos));//asignamos memoria con malloc, convertimos el tipo punto a la estructura de sPuntos y lo asignamos al puntero aPunto
    if (aPunto==NULL){
        perror("Error al reservar memoria:");//imprimir error
        fclose(pArchivo);//cerrar archivo
        exit(2);}
    char arreglo[1025];//se define un arreglo de 1024 caracteres, \0 representa el final de la cadena
    for (int i = 0; fgets(arreglo, sizeof(arreglo), pArchivo); i++){
        sscanf(arreglo, "%lf,%lf", &aPunto[i].dPrecio, &aPunto[i].dPeso);}
    printf("He cargado %d puntos:\n", nNoPuntos);
    for (int i = 0; i < nNoPuntos; i++)
        printf("Punto %d: x = %lf, y = %lf\n", i, aPunto[i].dPrecio, aPunto[i].dPeso);
    free(aPunto); // Liberar la memoria asignada
    fclose(pArchivo); // Cerrar el archivo
return 0;
}


