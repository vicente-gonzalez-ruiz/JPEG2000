#include <iostream>

#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;

#include "args.hh"

#ifndef DIM_Y
#define DIM_Y 288
#endif

#ifndef DIM_X
#define DIM_X 352
#endif

inline void rgb2yuv(int r, int g, int b,
		    int *y, int *u, int *v) {
  *y = ( ( g << 1 ) + r + b ) >> 2;
  *u = b - g;
  *v = r - g;
}

inline void yuv2rgb(int y, int u, int v,
		    int *r, int *g, int *b) {
  *g = y - ( ( u + v ) >> 2 );
  *b = u + *g;
  *r = v + *g;
}

int main(int argc, char *argv[]) {
  args args(argc, argv);
  if(args.exist_arg((char *)"-help")) {
    cerr << "Converts between int raw rgb and a int raw yuv sequences\n";
    cerr << " < input_file > output_file\n";
  } else {
    
    FILE *input_file = stdin;
    FILE *output_file = stdout;

    int r, g, b;
    int y, u, v;
    if(!strcmp(argv[0],"rgb2yuv")) {
      for(;;) {
	fread(&r, sizeof(int), 1, input_file);
	fread(&g, sizeof(int), 1, input_file);
    	fread(&b, sizeof(int), 1, input_file);
	if(feof(input_file)) break;
	rgb2yuv(r,g,b,&y,&u,&v);
	fwrite(&y, sizeof(int), 1, output_file);
 	fwrite(&u, sizeof(int), 1, output_file);
 	fwrite(&v, sizeof(int), 1, output_file);
      }
    } else {
      for(;;) {
	fread(&y, sizeof(int), 1, input_file);
	fread(&u, sizeof(int), 1, input_file);
    	fread(&v, sizeof(int), 1, input_file);
	if(feof(input_file)) break;
	yuv2rgb(y,u,v,&r,&g,&b);
	fwrite(&r, sizeof(int), 1, output_file);
 	fwrite(&g, sizeof(int), 1, output_file);
 	fwrite(&b, sizeof(int), 1, output_file);
      }
    }
  }
}
