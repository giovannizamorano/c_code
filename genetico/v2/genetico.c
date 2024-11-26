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
//torneo
Individuo* seleccionTorneo(Individuo *poblacion, double *errores, int m){
    Individuo *mejor = NULL;
    double mejor_error = (m==1) ? INFINITY : -INFINITY;
    for (int i = 0; i < torneoSize; i++)
    {
    int idx = rand() % padres;
    if (m==1){//minimizar
        if(errores[idx]<mejor_error){
            mejor_error=errores[idx];
            mejor=&poblacion[idx];
        }   } 
    else {
        if(errores[idx]>mejor_error){
            mejor_error = errores[idx];
            mejor = &poblacion[idx];
        }   }   }
        return mejor;
}
//xover
void cruzarIndividuos(Individuo *padre1, Individuo *padre2, Individuo *hijo) {
    int puntoCruce = rand() % 3;
    for (int i = 0; i < 3; i++){
        if (i <= puntoCruce) {
            hijo->a[i] = padre1->a[i];
            hijo->b[i] = padre1->b[i];
            hijo->c[i] = padre1->c[i];
        } else {
            hijo->a[i] = padre2->a[i];
            hijo->b[i] = padre2->b[i];
            hijo->c[i] = padre2->c[i];
        } }
}
//mutacion
void mutarIndividuo(Individuo *ind) {
    for (int i = 0; i < 3; i++) {
        // Mutación para a[i]
        if (((double)rand() / RAND_MAX) < mutacion) {
            ind->a[i] = numeroAleatorio(genMin, genMax);
        }
        // Mutación para b[i]
        if (((double)rand() / RAND_MAX) < mutacion) {
            ind->b[i] = numeroAleatorio(genMin, genMax);
        }
        // Mutación para c[i]
        if (((double)rand() / RAND_MAX) < mutacion) {
            ind->c[i] = numeroAleatorio(genMin, genMax);
        } }
}
int main() {
    int i, j;
    Individuo poblacion[popSize];
    double errores[popSize];
    int m = 1; //Minimizar el error
    //con srand se generan numeros aleatorios
    srand((unsigned int)time(NULL));
    //genes aleatorios para cada individuo
    for (i = 0; i < padres; i++) {
        for (j = 0; j < 3; j++) {
            poblacion[i].a[j] = numeroAleatorio(genMin, genMax);
            poblacion[i].b[j] = numeroAleatorio(genMin, genMax);
            poblacion[i].c[j] = numeroAleatorio(genMin, genMax);
        }}

    //rror promedio de cada individuo
    double dx = (xMax - xMin) / (ptos - 1);
    for (i = 0; i < padres; i++) {
        double suma_errores = 0.0;
        for (j = 0; j < ptos; j++) {
            double x = xMin + j * dx;
            double y_individuo = funcionIndividuo(&poblacion[i], x);
            double y_objetivo = funcionObjetivo(x);
            suma_errores += fabs(y_individuo - y_objetivo);
        } errores[i] = suma_errores / ptos;}
   // Generar hijos mediante selección por torneo, cruce y mutación       
    for (i = padres; i < popSize; i++) {
            // Seleccionar dos padres mediante torneo
            Individuo *padre1 = seleccionTorneo(poblacion, errores, m);
            Individuo *padre2 = seleccionTorneo(poblacion, errores, m);
            // Crear hijo mediante cruce
            cruzarIndividuos(padre1, padre2, &poblacion[i]);
            // Aplicar mutación al hijo
            mutarIndividuo(&poblacion[i]);
            // Calcular el error para el hijo
            double suma_errores = 0.0;
            for (j = 0; j < ptos; j++) {
                double x = xMin + j * dx;
                double y_individuo = funcionIndividuo(&poblacion[i], x);
                double y_objetivo = funcionObjetivo(x);
                suma_errores += fabs(y_individuo - y_objetivo);
            }
            errores[i] = suma_errores / ptos;
        }
    // Imprimir los resultados de los padres
    for (i = 0; i < padres; i++) {
        printf("Padre Num %d:\n", i + 1);
        printf("Genes:\n");
        for (j = 0; j < 3; j++) {
            printf("  a%d = %f, b%d = %f, c%d = %f\n",
                   j + 1, poblacion[i].a[j],
                   j + 1, poblacion[i].b[j],
                   j + 1, poblacion[i].c[j]);
        }
        printf("Error Promedio Absoluto: %f\n\n", errores[i]);
    }
    //imprimir por pantalla genes y el error promedio de cada individuo
    for (i = padres; i < popSize; i++) {
        printf("Hijo Num %d:\n", i + 1 - padres);
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