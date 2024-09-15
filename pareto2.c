#include <stdio.h>
#include <stdlib.h>

// Crear una estructura para almacenar un punto
typedef struct {
    double dPrecio;
    double dPeso;
} SPunto;

int main(int argc, char *argv[]) {
  // argc es el número de argumentos en la línea de comandos
  // (el nombre del programa cuenta como argumento)
  // *argv[] es un puntero hacia un conjunto de cadenas que contienen todos
  // los argumentos (incluido el nombre del programa expresado como argv[0])
  // Sugiero «$ pareto nombre_del_archivo numero_de_puntos»

  printf("arg0=%s, arg1=%s, arg2=%s\n", argv[0],argv[1],argv[2]);

  FILE *pArchivo = fopen(argv[1], "r"); // abrir un archivo en modo lectura
  if (pArchivo == NULL) {               // Si no ha podido abrirlo
    perror("\n*** No pude abrir el archivo ***\n");
    exit(1); // Se muestra un mensaje de error en la salida de «error estándar»
  }          //  y se devuelve un código de error distinto de 0.
          
  int nNoPuntos=atoi(argv[2]); // atoi = ascii to integer, convierte la cadena de caracteres a un numero entero, esto se guarda en nNoPuntos el numero de puntos ingresados por consola(n=tipo de datos, No=Numero)
  
  SPunto *aPunto = (SPunto *) malloc(nNoPuntos * sizeof(SPunto));//sizeof devuelve el tamaño en bytes de un solo elemento, por tanto al multiplicar por numero de puntos obtenemos el equivalente a la suma del tamaño de todos los bytes, en este caso es de 1000 puntos x sizeof(sPunto), ej: si sPunto = 4 y numero de puntos(nNoPuntos)=1000 ==> multiplicamos 1000x4 = 4000
  // malloc = asignación dinámica en el heap
  // Si malloc funciona, devuelve la dirección donde se asignó la memoria
  //SPuntos *apunto = aPunto es un puntero que contiene la direccion de los datos de SPunto
  //SPunto * = convierte el puntero devuelto por malloc, el cual es generico y puede apuntar a cualquier tipo de dato a un puntero especifico para el tipo de dato que se va a usar
  //malloc(nNoPuntos * sizeof(SPunto))
  
  
  
  
  if (aPunto == NULL) { // si no funciona
    perror("\n*** Imposible reservar memoria ***\n");
    fclose(pArchivo); // cerrar el archivo
    exit(2); // y se devuelve un código de error distinto de 0 y 1 
  } // los códigos de error son preciosas indicaciones sobre lo que salió mal
    
  char s[1025]; // Creación de una cadena de 1024 caracteres (+ \0) para recuperar una palabra del archivo
  for (int i = 0; fgets(s, sizeof(s), pArchivo); i++) // Mientras nos devuelvan palabras
    sscanf(s, "%lf,%lf", &aPunto[i].dPrecio, &aPunto[i].dPeso); // escribir el punto en el array

  // Imprimir los puntos cargados
  printf("He cargado %d puntos:\n", nNoPuntos);
  for (int i = 0; i < nNoPuntos; i++)
    printf("Punto %d: x = %lf, y = %lf\n", i, aPunto[i].dPrecio, aPunto[i].dPeso);

  free(aPunto); // Liberar la memoria asignada
  fclose(pArchivo); // Cerrar el archivo

  return 0;
}
