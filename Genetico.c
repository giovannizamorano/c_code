#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NUM_INDIVIDUOS 100
#define NUM_PUNTOS 1000

// Estructura para los genes de cada individuo
typedef struct {
    double a, b, c, d, f, g, h, i, j;
    double error_promedio;
} Individuo;

// Función objetivo
double funcionObjetivo(double x) {
    return sin(x) + 2 * sin(1.5 * x - 5) + 3 * sin(x / 2 + 1);
}

// Función generada por genes de un individuo
double funcionGenerada(Individuo ind, double x) {
    return ind.a * sin(ind.b * x + ind.c) + 
           ind.d * sin(ind.f * x + ind.g) + 
           ind.h * sin(ind.i * x + ind.j);
}

// Inicializa los individuos con genes aleatorios
void inicializarIndividuos(Individuo individuos[]) {
    for (int i = 0; i < NUM_INDIVIDUOS; i++) {
        individuos[i].a = ((double)rand() / RAND_MAX) * 2 - 1; // Valores entre -1 y 1
        individuos[i].b = ((double)rand() / RAND_MAX) * 2 - 1;
        individuos[i].c = ((double)rand() / RAND_MAX) * 2 - 1;
        individuos[i].d = ((double)rand() / RAND_MAX) * 2 - 1;
        individuos[i].f = ((double)rand() / RAND_MAX) * 2 - 1;
        individuos[i].g = ((double)rand() / RAND_MAX) * 2 - 1;
        individuos[i].h = ((double)rand() / RAND_MAX) * 2 - 1;
        individuos[i].i = ((double)rand() / RAND_MAX) * 2 - 1;
        individuos[i].j = ((double)rand() / RAND_MAX) * 2 - 1;
        individuos[i].error_promedio = 0;
    }
}

// Calcula el error promedio de un individuo
void calcularError(Individuo *ind, double puntos_x[], double valores_objetivo[]) {
    double error_total = 0;
    for (int i = 0; i < NUM_PUNTOS; i++) {
        double f_gen = funcionGenerada(*ind, puntos_x[i]);
        error_total += fabs(valores_objetivo[i] - f_gen); // Error absoluto
    }
    ind->error_promedio = error_total / NUM_PUNTOS;
}

// Imprime los genes y el error de cada individuo
void imprimirResultados(Individuo individuos[]) {
    for (int i = 0; i < NUM_INDIVIDUOS; i++) {
        printf("Individuo %d: Genes: a=%.3f, b=%.3f, c=%.3f, d=%.3f, f=%.3f, g=%.3f, h=%.3f, i=%.3f, j=%.3f | Error Promedio: %.5f\n",
            i + 1, 
            individuos[i].a, individuos[i].b, individuos[i].c,
            individuos[i].d, individuos[i].f, individuos[i].g,
            individuos[i].h, individuos[i].i, individuos[i].j,
            individuos[i].error_promedio);
    }
}

int main() {
    // Generar puntos_x y valores objetivo
    double puntos_x[NUM_PUNTOS];
    double valores_objetivo[NUM_PUNTOS];
    double x = -500;
    for (int i = 0; i < NUM_PUNTOS; i++) {
        puntos_x[i] = x;
        valores_objetivo[i] = funcionObjetivo(x);
        x += 1; // Incremento en 1 para ir de -500 a 500
    }

    // Inicializar población de individuos
    Individuo individuos[NUM_INDIVIDUOS];
    inicializarIndividuos(individuos);
    
    // Calcular error de cada individuo
    for (int i = 0; i < NUM_INDIVIDUOS; i++) {
        calcularError(&individuos[i], puntos_x, valores_objetivo);
    }

    // Imprimir los resultados
    imprimirResultados(individuos);

    // Código para guardar los resultados en un CSV (comentar esta sección)
    /*
    FILE *file = fopen("resultados.csv", "w");
    if (file) {
        fprintf(file, "Individuo,a,b,c,d,f,g,h,i,j,Error Promedio\n");
        for (int i = 0; i < NUM_INDIVIDUOS; i++) {
            fprintf(file, "%d,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.5f\n",
                    i + 1,
                    individuos[i].a, individuos[i].b, individuos[i].c,
                    individuos[i].d, individuos[i].f, individuos[i].g,
                    individuos[i].h, individuos[i].i, individuos[i].j,
                    individuos[i].error_promedio);
        }
        fclose(file);
    }
    */

    return 0;
}
