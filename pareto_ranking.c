#include <stdio.h>
#include <stdlib.h>
#include <math.h>
typedef struct {
    double dPrecio;
    double dPeso;
    double perimetro; // Nuevo: Almacena el perímetro del punto
} SPunto;
int leerPuntos(FILE *pArchivo, SPunto *aPuntos, int nMaxPuntos) {
    int nPuntosLeidos = 0;
    char s[1025];
    while (nPuntosLeidos < nMaxPuntos && fgets(s, sizeof(s), pArchivo)) {
        if (sscanf(s, "%lf,%lf", &aPuntos[nPuntosLeidos].dPrecio, &aPuntos[nPuntosLeidos].dPeso) == 2) {
            aPuntos[nPuntosLeidos].perimetro = 0.0; // Inicializamos el perímetro en 0
            nPuntosLeidos++;
        }   }
    return nPuntosLeidos;
}
double calcularDistancia(SPunto p1, SPunto p2) {
    return sqrt(pow(p2.dPrecio - p1.dPrecio, 2) + pow(p2.dPeso - p1.dPeso, 2));
}
void calcularPerimetros(SPunto *aPareto, int nFrente) {
    for (int i = 0; i < nFrente; i++) {
        double perimetro = 0.0;
        for (int j = 0; j < nFrente; j++) {
            if (i != j) {
                perimetro += calcularDistancia(aPareto[i], aPareto[j]);
            }   }
        aPareto[i].perimetro = perimetro;
    }   }
double calcularCalidad(SPunto *aPareto, int nFrente) {
    double sumaPerimetros = 0.0;
    for (int i = 0; i < nFrente; i++) {
        sumaPerimetros += aPareto[i].perimetro;}
    return sumaPerimetros / nFrente;
}
int esPareto(SPunto *aPuntos, int i, int nPuntosRes) {
    for (int j = 0; j < nPuntosRes; j++) {
        if (i != j &&
            (aPuntos[j].dPrecio <= aPuntos[i].dPrecio &&
             aPuntos[j].dPeso <= aPuntos[i].dPeso) &&
            (aPuntos[j].dPrecio < aPuntos[i].dPrecio ||
             aPuntos[j].dPeso < aPuntos[i].dPeso)) {
            return 0;
        }   }
    return 1; 
}
int eliminarDominados(SPunto *aPuntos, SPunto *aPareto, int nPuntosRes, int nFrente) {
    int nNuevosPuntos = 0;
    for (int i = 0; i < nPuntosRes; i++) {
        int esDominado = 0;
        for (int j = 0; j < nFrente; j++) {
            if (aPuntos[i].dPrecio == aPareto[j].dPrecio &&
                aPuntos[i].dPeso == aPareto[j].dPeso) {
                esDominado = 1;
                break;
            }       }
        if (!esDominado) {
            aPuntos[nNuevosPuntos++] = aPuntos[i];
        }   }
    return nNuevosPuntos;
}
int main(int argc, char *argv[]) {
    FILE *pArchivo = fopen(argv[1], "r");
    if (!pArchivo) return 1;
    int nNoPuntos = atoi(argv[2]);
    SPunto *aPuntos = (SPunto *)malloc(nNoPuntos * sizeof(SPunto));
    if (!aPuntos) {
        fclose(pArchivo);
        return 1;
    }
    int nPuntosLeidos = leerPuntos(pArchivo, aPuntos, nNoPuntos);
    fclose(pArchivo);
    if (nPuntosLeidos != nNoPuntos) {
        nNoPuntos = nPuntosLeidos;
    }
    SPunto *aPareto = (SPunto *)malloc(nNoPuntos * sizeof(SPunto));
    if (!aPareto) {
        free(aPuntos);
        return 1;
    }
    int nPuntosRes = nNoPuntos;
    int ranking = 1;
    while (nPuntosRes > 0) {
        int nFrente = 0;
        for (int i = 0; i < nPuntosRes; i++) {
            if (esPareto(aPuntos, i, nPuntosRes)) {
                aPareto[nFrente++] = aPuntos[i];
            }   }
        if (nFrente > 0) {
            calcularPerimetros(aPareto, nFrente); 
            double calidad = calcularCalidad(aPareto, nFrente); 
            printf("Ranking frente de Pareto numero: %d:\n", ranking++);
            for (int i = 0; i < nFrente; i++) {
                printf("Punto: %lf, %lf | Perimetro: %lf\n",
                       aPareto[i].dPrecio, aPareto[i].dPeso, aPareto[i].perimetro); 
                       }
            printf("Largo del frente: %d\n", nFrente);
            printf("Calidad del frente: %lf\n\n", calidad);
            nPuntosRes = eliminarDominados(aPuntos, aPareto, nPuntosRes, nFrente);
        } else {
            break;
        }   }
    free(aPuntos);
    free(aPareto);
    return 0;
}