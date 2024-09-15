#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double dPrecio;
    double dPeso;
} SPunto;

int main(int argc, char *argv[]) {
    // Lectura de argumentos y archivo
    if (argc != 3) {
        printf("Uso: %s <archivo_datos> <numero_de_puntos>\n", argv[0]);
        return 1;
    }

    FILE *pArchivo = fopen(argv[1], "r");
    if (pArchivo == NULL) {
        return 1;
    }

    int nNoPuntos = atoi(argv[2]);
    
    // Reserva de memoria para los puntos
    SPunto *aPunto = (SPunto *) malloc(nNoPuntos * sizeof(SPunto));
    if (aPunto == NULL) {
        fclose(pArchivo);
        return 1;
    }

    // Lectura de los puntos del archivo (Código proviene de "pareto22.c")
    int puntosLeidos = 0;
    char s[1025];
    while (puntosLeidos < nNoPuntos && fgets(s, sizeof(s), pArchivo)) {
        if (sscanf(s, "%lf,%lf", &aPunto[puntosLeidos].dPrecio, &aPunto[puntosLeidos].dPeso) == 2) {
            puntosLeidos++;
        }
    }

    fclose(pArchivo);

    // Ajustar el número de puntos si se leyeron menos de los esperados
    if (puntosLeidos != nNoPuntos) {
        nNoPuntos = puntosLeidos;
    }

    // Preparación para el cálculo del frente de Pareto
    // Array para almacenar los puntos restantes
    SPunto *aPuntoRestante = (SPunto *) malloc(nNoPuntos * sizeof(SPunto));
    // Array para almacenar el frente de Pareto actual
    SPunto *aPuntoPareto = (SPunto *) malloc(nNoPuntos * sizeof(SPunto));

    if (aPuntoRestante == NULL || aPuntoPareto == NULL) {
        free(aPunto);
        return 1;
    }

    // Copiamos los puntos originales al array de puntos restantes
    for (int i = 0; i < nNoPuntos; i++) {
        aPuntoRestante[i] = aPunto[i];
    }

    int ranking = 1;
    int puntosRestantes = nNoPuntos;

    // Cálculo iterativo de los frentes de Pareto (Este bloque es nuevo, lo agregué yo)
    while (puntosRestantes > 0) {
        int nFrente = 0;  // Número de puntos en el frente de Pareto actual

        // Calcular el frente de Pareto actual
        for (int i = 0; i < puntosRestantes; i++) {
            int esPareto = 1;
            for (int j = 0; j < puntosRestantes; j++) {
                if (i != j) {
                    // Comparación para verificar si el punto i es dominado por el punto j (Código adaptado de "pareto_1.c")
                    if ((aPuntoRestante[j].dPrecio <= aPuntoRestante[i].dPrecio && aPuntoRestante[j].dPeso <= aPuntoRestante[i].dPeso) &&
                        (aPuntoRestante[j].dPrecio < aPuntoRestante[i].dPrecio || aPuntoRestante[j].dPeso < aPuntoRestante[i].dPeso)) {
                        esPareto = 0;
                        break;
                    }
                }
            }
            if (esPareto) {
                // Guardamos los puntos del frente de Pareto en el array aPuntoPareto (nuevo)
                aPuntoPareto[nFrente] = aPuntoRestante[i];
                nFrente++;
            }
        }

        // Imprimimos el frente de Pareto actual (Este bloque también es nuevo)
        if (nFrente > 0) {
            printf("Frente de Pareto ranking %d:\n", ranking);
            for (int i = 0; i < nFrente; i++) {
                printf("%lf, %lf\n", aPuntoPareto[i].dPrecio, aPuntoPareto[i].dPeso);
            }

            // Eliminamos los puntos del frente de Pareto del array de puntos restantes
            int nuevosPuntos = 0;
            for (int i = 0; i < puntosRestantes; i++) {
                int esPareto = 0;
                for (int j = 0; j < nFrente; j++) {
                    if (aPuntoRestante[i].dPrecio == aPuntoPareto[j].dPrecio && aPuntoRestante[i].dPeso == aPuntoPareto[j].dPeso) {
                        esPareto = 1;
                        break;
                    }
                }
                if (!esPareto) {
                    // Guardamos los puntos no dominados de nuevo en aPuntoRestante (nuevo)
                    aPuntoRestante[nuevosPuntos] = aPuntoRestante[i];
                    nuevosPuntos++;
                }
            }

            puntosRestantes = nuevosPuntos;  // Actualizamos la cantidad de puntos restantes
            ranking++;  // Incrementamos el ranking del frente de Pareto
        } else {
            break;  // Si no encontramos más puntos en el frente de Pareto, terminamos
        }
    }

    // Liberamos la memoria usada
    free(aPunto);
    free(aPuntoRestante);
    free(aPuntoPareto);

    return 0;
}
