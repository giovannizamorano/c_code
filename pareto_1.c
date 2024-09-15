#include <stdio.h>
int main() {
    int datos[10][2] = {1, 8, 2, 7, 4, 7, 8, 7, 5, 5, 7, 4, 6, 3, 7, 2, 8, 1, 10, 1}; //coordenadas
    int pareto[10];
    for (int i = 0; i < 10; i++) {pareto[i] = 1;}
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (i != j) {
                if ((datos[j][0] <= datos[i][0] && datos[j][1] <= datos[i][1]) && (datos[j][0] < datos[i][0] || datos[j][1] < datos[i][1])) 
                {pareto[i] = 0; 
                break;
                }       }            }  }
    for (int i = 0; i < 10; i++) {
        if (pareto[i]) {
            printf("punto de pareto: (%d,%d)\n", datos[i][0], datos[i][1]);
                        }        } 
    return 0;
}