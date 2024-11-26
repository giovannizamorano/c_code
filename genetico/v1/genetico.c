//Librerias
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
//constantes
#define popSize 200 //100 padres + 100 hijos
#define padres 100
#define ptos 1000
#define xMin -500.0
#define xMax 500.0
#define genMin -10.0
#define genMax 10.0
#define torneoSize 4
#define mutacion 0.1

//estructura del individuo
typedef struct {
    double a[3];
    double b[3];
    double c[3];
} Individuo;
// funcion pra generar un numero aleatorio entre min y max
double numeroAleatorio(double min, double max) {
    return min + ((double)rand() / RAND_MAX) * (max - min);
}
//funcion objetivo
double funcionObjetivo(double x) {
    return sin(x) + 2 * sin(1.5 * x - 5) + 3 * sin(x / 2 + 1);
}
// funcion del individuo
double funcionIndividuo(Individuo *ind, double x) {
    double suma = 0;
    for (int k = 0; k < 3; k++) {
        suma += ind->a[k] * sin(ind->b[k] * x + ind->c[k]);
    }
    return suma; 
}

int main() {
    int i, j;
    Individuo poblacion[popSize];
    double errores[popSize];
    //con srand se generan numeros aleatorios
    srand((unsigned int)time(NULL));
    //genes aleatorios para cada individuo
    for (i = 0; i < popSize; i++) {
        for (j = 0; j < 3; j++) {
            poblacion[i].a[j] = numeroAleatorio(genMin, genMax);
            poblacion[i].b[j] = numeroAleatorio(genMin, genMax);
            poblacion[i].c[j] = numeroAleatorio(genMin, genMax);
        }}
    //rror promedio de cada individuo
    double dx = (xMax - xMin) / (ptos - 1);
    for (i = 0; i < popSize; i++) {
        double suma_errores = 0.0;
        for (j = 0; j < ptos; j++) {
            double x = xMin + j * dx;
            double y_individuo = funcionIndividuo(&poblacion[i], x);
            double y_objetivo = funcionObjetivo(x);
            double error = fabs(y_individuo - y_objetivo);
            suma_errores += error;
        } errores[i] = suma_errores / ptos;}
    //imprimir por pantalla genes y el error promedio de cada individuo
    for (i = 0; i < popSize; i++) {
        printf("Individuo Num %d:\n", i + 1);
        printf("Genes:\n");
        for (j = 0; j < 3; j++) {
            printf("  a%d = %f, b%d = %f, c%d = %f\n",
                   j + 1, poblacion[i].a[j],
                   j + 1, poblacion[i].b[j],
                   j + 1, poblacion[i].c[j]);
        }
        printf("Error Promedio Absoluto: %f\n\n", errores[i]); }
    return 0;
}