#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "DWT.h"

int main(int argc, char *argv[]) {
  int no_of_samples; /* N'umero de muestras/longitud de las funciones base */
  int no_of_basis;
  int *samples;   /* vector de muestras */
  int *in_line;
  int levels;

  if(argc<3) {
    fprintf(stderr,"<nombre kernel> <n'umero de muestras>\n");
    return 1;
  }

  no_of_samples = atoi(argv[2]);
  /*fprintf(stderr,"n'umero de muestras (longitud de las funciones base) = %d\n",no_of_samples);*/

  in_line = (int *)malloc(no_of_samples*sizeof(int));
  levels = (int)(log((double)no_of_samples)/log(2.0));

  {
    int b;
    no_of_basis = no_of_samples;
    samples = (int *)malloc(no_of_samples*sizeof(int));
    
    for(b=no_of_basis; b>=0; --b) {
      int n;
      for(n=0;n<no_of_samples;n++) {
	samples[n] = 0;
      }
      samples[b] = no_of_samples;//1.0;
      inverse_dwt_1d(samples,in_line,no_of_samples,levels);
      {
	float L2_norm = 0;
	for(n=0; n<no_of_samples; n++) {
	  float abs_sample = abs(samples[n]);
	  L2_norm += abs_sample*abs_sample;
	}
	printf("Basis function %3d, L2_norm = %f\n", b, L2_norm);
      }
    }
  }
  return 0;
}
