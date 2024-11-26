#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
// Constantes
#define popSize 200
#define Npadres 100
#define ptos 1000
#define xMin -500.0
#define xMax 500.0
#define genMin -10.0
#define genMax 10.0
#define torneoSize 4
#define mutacion 0.1
#define generaciones 100
// Estructura del individuo
typedef struct {
    double a, b, c, d, e, f, g, h, i;
} Individuo;
// Genera un número aleatorio entre min y max
double numeroAleatorio(double min, double max) {
    return min + ((double)rand() / RAND_MAX) * (max - min);
}
// Función objetivo
double funcionObjetivo(double x) {
    return sin(x) + 2 * sin(1.5 * x - 5) + 3 * sin(x / 2 + 1);
}
// Función del individuo
double funcionIndividuo(Individuo *ind, double x) {
    return ind->a * sin(ind->b * x + ind->c) +
           ind->d * sin(ind->e * x + ind->f) +
           ind->g * sin(ind->h * x + ind->i);
}
// Selección por torneo
Individuo* seleccionTorneo(Individuo *poblacion, double *errores, int m) {
    Individuo *mejor = NULL;
    double mejor_error = (m == 1) ? INFINITY : -INFINITY;
    for (int i = 0; i < torneoSize; i++) {
        int idx = rand() % Npadres;
        if ((m == 1 && errores[idx] < mejor_error) ||
            (m != 1 && errores[idx] > mejor_error)) {
            mejor_error = errores[idx];
            mejor = &poblacion[idx];
        }
    }
    return mejor;
}
// cruce
void cruzarIndividuos(Individuo *padre1, Individuo *padre2, Individuo *hijo) {
    int puntoCruce = rand() % 9;
    double *genesPadre1 = (double *)padre1;
    double *genesPadre2 = (double *)padre2;
    double *genesHijo = (double *)hijo;

    for (int i = 0; i < 9; i++) {
        genesHijo[i] = (i <= puntoCruce) ? genesPadre1[i] : genesPadre2[i];
    }
}
// mutacion
void mutarIndividuo(Individuo *ind) {
    double *genes = (double *)ind;
    for (int i = 0; i < 9; i++) {
        if (((double)rand() / RAND_MAX) < mutacion) {
            genes[i] = numeroAleatorio(genMin, genMax);
        }
    }
}
int main() {
    srand(127); //semilla
    Individuo poblacion1[Npadres];
    Individuo poblacion2[Npadres];
    Individuo *padres = poblacion1;
    Individuo *hijos = poblacion2;
    double erroresPadres[Npadres];
    double erroresHijos[Npadres];
    double dx = (xMax - xMin) / (ptos - 1);
    //padres
    for (int i = 0; i < Npadres; i++) {
        double *genes = (double *)&padres[i];
        for (int j = 0; j < 9; j++) {
            genes[j] = numeroAleatorio(genMin, genMax);
        }   }
    int mejorIdx = 0;
    // inici el algoritmo genético
    for (int gen = 0; gen < generaciones; gen++) {
        // Evaluacion padres
        double sumaErroresGeneracion = 0.0;
        for (int i = 0; i < Npadres; i++) {
            double sumaErrores = 0.0;
            for (int j = 0; j < ptos; j++) {
                double x = xMin + j * dx;
                double yIndividuo = funcionIndividuo(&padres[i], x);
                double yObjetivo = funcionObjetivo(x);
                sumaErrores += fabs(yIndividuo - yObjetivo);
            }
            erroresPadres[i] = sumaErrores / ptos;
            sumaErroresGeneracion += erroresPadres[i];
            // Actualizacion índice del mejor individuo
            if (erroresPadres[i] < erroresPadres[mejorIdx]) {
                mejorIdx = i;
            }   }
        //error promedio de cada generacion
        double errorPromedio = sumaErroresGeneracion / Npadres;
        printf("Generacion %d: Error promedio absoluto = %f\n", gen + 1, errorPromedio);

        //generaicon de hijos
        for (int i = 0; i < Npadres; i++) {
            Individuo *padre1 = seleccionTorneo(padres, erroresPadres, 1);
            Individuo *padre2 = seleccionTorneo(padres, erroresPadres, 1);
            cruzarIndividuos(padre1, padre2, &hijos[i]);
            mutarIndividuo(&hijos[i]);
        }

        // intercambio de poblaciones para la proxima generacion
        Individuo *tempPoblacion = padres;
        padres = hijos;
        hijos = tempPoblacion;
    }

    // Imprimir el mejor individuo al final
    printf("\nMejor Individuo:\n");
    printf("Genes: a=%f, b=%f, c=%f, d=%f, e=%f, f=%f, g=%f, h=%f, i=%f\n",
           padres[mejorIdx].a, padres[mejorIdx].b, padres[mejorIdx].c,
           padres[mejorIdx].d, padres[mejorIdx].e, padres[mejorIdx].f,
           padres[mejorIdx].g, padres[mejorIdx].h, padres[mejorIdx].i);
    printf("Error: %f\n", erroresPadres[mejorIdx]);

    return 0;
}
