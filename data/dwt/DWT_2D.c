#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "args.h"
#include "mallok.h"
#ifdef _COLOR_
#include "color.h"
typedef struct RGB TYPE;
#else
typedef int TYPE;
#endif
#include "DWT.h"
//#include "idwt.h"

#define ROWS 512
#define COLS 512
#define LEVELS 7

extern char transform_name[40];

int main(int argc, char *argv[]) {
  if(exist_arg((char *)"-help",argc,argv)) {
    fprintf(stderr,"Compute the 2D-DWT\n");
    fprintf(stderr,"%s\n",transform_name);
    fprintf(stderr," [-inverse] (inverse transform)\n");
    fprintf(stderr," [-input <int image file>] (default stdin)\n");
    fprintf(stderr," [-output <int image file>] (default stdout)\n");
    fprintf(stderr," [-rows <number of rows>] (defaults %d)\n",ROWS);
    fprintf(stderr," [-cols <number of columns>] (default %d)\n",COLS);
    fprintf(stderr," [-levels <number of levels>] (default %d)\n",LEVELS);
    //fprintf(stderr," [-mean <mean>]\n");
    //fprintf(stderr," Input File Format in the Forward Transform:\n");
    //fprintf(stderr,"  rows*cols*int32 -> The Image Data\n");
    //fprintf(stderr," Output File Format in the Forward Transform:\n");
    //fprintf(stderr,"  rows*cols*int32 -> The Transform Data\n");
    //fprintf(stderr,"  int32 -> A Mean Value\n");
  } else {
    clock_t time;

    FILE *input_file, *output_file;
    int rows = ROWS;
    int cols = COLS;
    int levels = LEVELS;
    TYPE **data;
    int i,j;
    TYPE *in_line, *out_line;
    int size;
    //int mean;
   
    if(EXIST_ARG((char *)"-v")) {
      fprintf(stderr,"%s: %s\n",argv[0],transform_name);
    }

    input_file = stdin;
    if(EXIST_ARG((char *)"-input")) {
      if(EXIST_ARG((char *)"-v")) {
	fprintf(stderr,"%s: input file = %s\n",argv[0],GET_ARG((char *)"-input"));
      }
      input_file = fopen(GET_ARG((char *)"-input"),"rb");
      if(!input_file) {
        fprintf(stderr,"%s: unable to open input file: %s\n",argv[0],GET_ARG((char *)"-input"));
        return 1;
      }
    } else {
      if(EXIST_ARG((char *)"-v")) {
	fprintf(stderr,"%s: input file = stdin\n",argv[0]);
      }
    }

    output_file= stdout;
    if(EXIST_ARG((char *)"-output")) {
      if(EXIST_ARG((char *)"-v")) {
	fprintf(stderr,"%s: output file = %s\n",argv[0],GET_ARG((char *)"-output"));
      }
      output_file = fopen(GET_ARG((char *)"-output"),"wb");
      if(!output_file) {
        fprintf(stderr,"%s: unable to open output file: %s\n",argv[0],GET_ARG((char *)"-output"));
        return 1;
      }
    } else {
      if(EXIST_ARG((char *)"-v")) {
	fprintf(stderr,"%s: output file = stdout\n",argv[0]);
      }
    }

    if(EXIST_ARG((char *)"-rows")) rows = atoi(GET_ARG((char *)"-rows"));
    if(EXIST_ARG((char *)"-cols")) cols = atoi(GET_ARG((char *)"-cols"));
    if(EXIST_ARG((char *)"-levels")) levels = atoi(GET_ARG((char *)"-levels"));
    if(EXIST_ARG((char *)"-v")) {
      fprintf(stderr,"%s: rows = %d\n",argv[0],rows);
      fprintf(stderr,"%s: cols = %d\n",argv[0],cols);
      fprintf(stderr,"%s: levels = %d\n",argv[0],levels);
    }

    size = rows>cols ? rows:cols;

    in_line = (TYPE *)malloc(size*sizeof(TYPE));
    out_line = (TYPE *)malloc(size*sizeof(TYPE));

    data = (TYPE **)malloc(rows,cols,sizeof(TYPE));

    time = clock();
    for(j=0;j<rows;j++) {
      fread(data[j],sizeof(TYPE),cols,input_file);
    }
    time = clock() - time;
    if(EXIST_ARG((char *)"-v")) {
      fprintf(stderr,"%s: input data time = %.2f seconds\n",argv[0],(float)time/CLOCKS_PER_SEC);
    }

    if(!EXIST_ARG((char *)"-inverse")) {
      time = clock();
      dwt_2d(data,in_line,out_line,rows,cols/*,&mean*/,levels);
      time = clock() - time;
      if(EXIST_ARG((char *)"-v")) {
	fprintf(stderr,"%s: transforming time = %.2f seconds\n",argv[0],(float)time/CLOCKS_PER_SEC);
      }
      //fwrite(&mean,sizeof(int),1,output_file);
    } else {
      time = clock();
      inverse_dwt_2d(data,in_line,out_line,rows,cols/*,mean*/,levels);
      time = clock() - time;
      if(EXIST_ARG((char *)"-v")) {
	fprintf(stderr,"%s: inverse transforming = %.2f seconds\n",argv[0],(float)time/CLOCKS_PER_SEC);
      }
    }

    time = clock();
    for(j=0;j<rows;j++) {
      fwrite(data[j],sizeof(TYPE),cols,output_file);
    }
    time = clock() - time;
    if(EXIST_ARG((char *)"-v")) {
      fprintf(stderr,"%s: output data = %.2f seconds\n",argv[0],(float)time/CLOCKS_PER_SEC);
    }
  }
}
