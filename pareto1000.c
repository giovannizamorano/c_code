#include <stdio.h>

#include <stdlib.h>


typedef struct {

double dPrecio;

double dPeso;

} SPunto;


//leer datos del archivo

int leerPuntos(FILE *pArchivo, SPunto *aPuntos, int nMaxPuntos) {

int nPuntosLeidos = 0;

char s[1025];

while (nPuntosLeidos < nMaxPuntos && fgets(s, sizeof(s), pArchivo)) {

if (sscanf(s, "%lf,%lf", &aPuntos[nPuntosLeidos].dPrecio, &aPuntos[nPuntosLeidos].dPeso) == 2) {

nPuntosLeidos++; } }

return nPuntosLeidos; }

// calcular si un punto es parte del frente

int esPareto(SPunto *aPuntos, int i, int nPuntosRes) {

for (int j = 0; j < nPuntosRes; j++) {

if (i != j && (aPuntos[j].dPrecio <= aPuntos[i].dPrecio && aPuntos[j].dPeso <= aPuntos[i].dPeso) &&(aPuntos[j].dPrecio < aPuntos[i].dPrecio || aPuntos[j].dPeso < aPuntos[i].dPeso)) {

return 0; } } //punto dominado

return 1; } // punto no dominado

//eliminar puntos dominados: si se detecto un frente de pareto, sacar los puntos del total de puntos disponibles y

// vovler a iterar en funcion a los puntos restantes para obtener un nuevo frente de pareto que corresponde al siguiente ranking

int eliminarDominados(SPunto *aPuntos, SPunto *aPareto, int nPuntosRes, int nFrente) {

int nNuevosPuntos = 0;

for (int i = 0; i < nPuntosRes; i++) {//se revisan los puntos y se eliminan los que pertenecen al actual frente

int esDominado = 0;

for (int j = 0; j < nFrente; j++) {

if (aPuntos[i].dPrecio == aPareto[j].dPrecio && aPuntos[i].dPeso == aPareto[j].dPeso) {

esDominado = 1;//si el punto es parte del frente actral

break;

} }

if (!esDominado) {

aPuntos[nNuevosPuntos++] = aPuntos[i]; }

}

return nNuevosPuntos;

}

int main(int argc, char *argv[]) {

//abrir archivos que pasaran como argumento a la funcion

FILE *pArchivo = fopen(argv[1], "r");

if (!pArchivo) return 1;

int nNoPuntos = atoi(argv[2]);

SPunto *aPuntos = (SPunto *) malloc(nNoPuntos * sizeof(SPunto));

if (!aPuntos) {

fclose(pArchivo);

return 1;

}

int nPuntosLeidos = leerPuntos(pArchivo, aPuntos, nNoPuntos);

fclose(pArchivo);

if (nPuntosLeidos != nNoPuntos) {

nNoPuntos = nPuntosLeidos;

}

SPunto *aPareto = (SPunto *) malloc(nNoPuntos * sizeof(SPunto));

if (!aPareto) {

free(aPuntos);

return 1;

}

int nPuntosRes = nNoPuntos;

int ranking = 1;

// iterar frentes de Pareto

while (nPuntosRes > 0) {

int nFrente = 0;

for (int i = 0; i < nPuntosRes; i++) {

if (esPareto(aPuntos, i, nPuntosRes)) {

aPareto[nFrente++] = aPuntos[i];

} }

if (nFrente > 0) {

printf("Ranking frente de pareto numero: %d:\n", ranking++);

for (int i = 0; i < nFrente; i++) {

printf("%lf, %lf\n", aPareto[i].dPrecio, aPareto[i].dPeso);

}

nPuntosRes = eliminarDominados(aPuntos, aPareto, nPuntosRes, nFrente);// eliminar los puntos dominados y reducir el conjunto de puntos restantes

} else {

break;

}

}

free(aPuntos);

free(aPareto);

return 0;

} //el codigo cada vez que encuentra un frente de pareto lo extrae del total de datos

//y vuelve a iterar ya sin estos datos sumando un nuevo ranking al contador