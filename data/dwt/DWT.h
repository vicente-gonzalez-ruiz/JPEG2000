/*
 * data = matriz de coeficientes 
 * in_line, out_line = buffer de memoria de apoyo
 * pics, rows, cols = dimensiones de la transformada
 * levels = nùmero de niveles de la descomposiciòn
 */

#ifdef __cplusplus
extern "C" {
#endif

/* Transformada Wavelet 1D */
void dwt_1d(int *data,
	    int *in_line,
	    int cols,
	    int levels);

void dwt_1d_rgb(struct RGB *data,
		struct RGB *in_line,
		int cols,
		int levels);

void inverse_dwt_1d(int *data,
		    int *in_line,
		    int cols,
		    int levels);

void inverse_dwt_1d_rgb(struct RGB *data,
			struct RGB *in_line,
			int cols,
			int levels);

/* Transformada Wavelet 2D */
void dwt_2d(int **data,
	    int *in_line,
	    int *out_line,
	    int rows,
	    int cols,
	    int levels);

void dwt_2d_rgb(struct RGB **data,
		struct RGB *in_line,
		struct RGB *out_line,
		int rows,
		int cols,
		int levels);

void inverse_dwt_2d(int **data,
		    int *in_line,
		    int *out_line,
		    int rows,
		    int cols,
		    int levels);

void inverse_dwt_2d_rgb(struct RGB **data,
			struct RGB *in_line,
			struct RGB *out_line,
			int rows,
			int cols,
			int levels);

/* Transformada Wavelet 3D */
void dwt_3d(int ***data,
	    int *in_line,
	    int *out_line,
	    int pics,
	    int rows,
	    int cols,
	    int levels);

void dwt_3d_rgb(struct RGB ***data,
		struct RGB *in_line,
		struct RGB *out_line,
		int pics,
		int rows,
		int cols,
		int levels);

void inverse_dwt_3d(int ***data,
		    int *in_line,
		    int *out_line,
		    int pics,
		    int rows,
		    int cols,
		    int levels);

void inverse_dwt_3d_rgb(struct RGB ***data,
			struct RGB *in_line,
			struct RGB *out_line,
			int pics,
			int rows,
			int cols,
			int levels);

#ifdef __cplusplus
}
#endif
