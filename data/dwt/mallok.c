/*
 * Asigna y libera memoria en 2d.
 * gse. 1999.
 */

#include <stdio.h>
#include <stdlib.h>   /* malloc(),free() */
#include "mallok.h"

/*
+-----------------------------------------------------------------------------+

   Alloca memoria para una imagen siguiendo la estructura de un array de
   punteros a punteros.

        Alloca memoria 2-D.
        

        filas           columnas
        +---+     +----+----+----+--...
        |ptr| --> |dato|dato|    |
        +---+     +----+----+----+--...
        |ptr| -->
        +---+
        |   | -->
        :   :

        Retorna:        1: si no hay memoria para las filas.
                        2: si no hay memoria para las columnas.

        Una llamada:
                        char **x;
                        x=(char **)Calloc2D(210,32,sizeof(char));

        Para acceder a un elemento:

                        x[23][5]=12;



+-----------------------------------------------------------------------------+
*/
void **calloc(unsigned filas, unsigned columnas, unsigned sizeofTipo) {
  unsigned i;
  void **h;

  /* Asignamos memoria a los punteros */
  h=(void **)malloc(filas*sizeof(void *));

  for(i=0;i<filas;i++) {
    h[i]=(void *)calloc(columnas,sizeofTipo);
  }
  return (h);
}

/* La diferencia con el anterior es que la memoria asignada no es borrada */
void **malloc(unsigned filas, unsigned columnas, unsigned sizeofTipo) {
  unsigned i;
  void **h;

  /* Asignamos memoria a los punteros */
  h=(void **)malloc(filas*sizeof(void *));

  for(i=0;i<filas;i++) {
    h[i]=(void *)malloc(columnas*sizeofTipo);
  }
  return (h);
}

void ***malloc(unsigned imagenes, unsigned filas, unsigned columnas, unsigned sizeofTipo) {
  unsigned k;
  void ***h;

  h=(void ***)malloc(imagenes*sizeof(void **));

  for(k=0;k<imagenes;k++) {
    h[k] = (void **)malloc(filas,columnas,sizeofTipo);
  }
  return (h);
}

void ***calloc(unsigned imagenes, unsigned filas, unsigned columnas, unsigned sizeofTipo) {
  unsigned k;
  void ***h;

  h=(void ***)malloc(imagenes*sizeof(void **));

  for(k=0;k<imagenes;k++) {
    h[k]=(void **)calloc(filas,columnas,sizeof(void *));
  }
  return (h);
}

void free(void **h, unsigned f) {
   unsigned i;
   for(i=0;i<f;i++) free(h[i]);
   free(h);
}

void free(void ***h, unsigned pics, unsigned rows) {
  unsigned k,j;
  for(k=0;k<pics;k++) {
    free((void **)h[k],rows);
  }
  free(h);
}

#ifdef _MAIN_
void main() {
  int **image;
  int ***vol;
  unsigned pics=10,rows=10, cols=20;
  image = (int **)calloc(rows,cols,sizeof(int));
  free((void **)image,rows);
  vol = (int ***)calloc(pics,rows,cols,sizeof(int));
  free((void ***)vol,pics,rows);
}
#endif
