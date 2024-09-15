#include <stdio.h>

#define NUM_PUNTOS 10 // Número de puntos en la lista

// Función para determinar si un punto es dominado por otro
int esDominado(int x1, int y1, int x2, int y2) {
    return (x2 >= x1 && y2 >= y1 && (x2 > x1 || y2 > y1));
}

int main() {
    // Lista de puntos (x, y)
    int puntos[NUM_PUNTOS][2] = {
        {1, 8},
        {2, 7},
        {4, 7},
        {8, 7},
        {5, 5},
        {7, 4},
        {6, 3},
        {7, 2},
        {8, 1},
        {10, 1}
    };
    
    // Array para marcar si un punto es parte del frente de Pareto
    int esPareto[NUM_PUNTOS] = {1}; // Inicializamos todos a 1, asumimos que todos son Pareto al principio

    // Algoritmo para determinar el frente de Pareto
    for (int i = 0; i < NUM_PUNTOS; i++) {
        for (int j = 0; j < NUM_PUNTOS; j++) {
            if (i != j && esDominado(puntos[i][0], puntos[i][1], puntos[j][0], puntos[j][1])) {
                esPareto[i] = 0; // El punto i está dominado, no es Pareto
                break; // No necesitamos seguir buscando, este punto ya está dominado
            }
        }
    }

    // Imprimir los puntos del frente de Pareto
    printf("Puntos en el frente de Pareto:\n");
    for (int i = 0; i < NUM_PUNTOS; i++) {
        if (esPareto[i]) {
            printf("(%d, %d)\n", puntos[i][0], puntos[i][1]);
        }
    }

    return 0;
}