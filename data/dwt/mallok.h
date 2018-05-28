void **calloc(unsigned filas, unsigned columnas, unsigned sizeofTipo);
void **malloc(unsigned filas, unsigned columnas, unsigned sizeofTipo);
void ***malloc(unsigned imagenes, unsigned filas, unsigned columnas, unsigned sizeofTipo);
void ***calloc(unsigned imagenes, unsigned filas, unsigned columnas, unsigned sizeofTipo);
void free(void **h, unsigned f);
void free(void ***h, unsigned pics, unsigned rows);
