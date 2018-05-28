/*
 * Filtros utilizados en la transformada wavelet.
 * gse. 2002.
 */

#ifdef __cplusplus
extern "C" {
#endif

void TransformStep_Even(int n, int s[], int l[], int h[]);
void TransformStep_Odd(int n, int s[], int l[], int h[]);
void i_TransformStep_Even(int n, int s[], int l[], int h[]);
void i_TransformStep_Odd(int n, int s[], int l[], int h[]);

void trans_step_even_rgb(int n, struct RGB s[], struct RGB l[], struct RGB h[]);
void trans_step_odd_rgb(int n, struct RGB s[], struct RGB l[], struct RGB h[]);
void itrans_step_even_rgb(int n, struct RGB s[], struct RGB l[], struct RGB h[]);
void itrans_step_odd_rgb(int n, struct RGB s[], struct RGB l[], struct RGB h[]);

#ifdef __cplusplus
}
#endif
