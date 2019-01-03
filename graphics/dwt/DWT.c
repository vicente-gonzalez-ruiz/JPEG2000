#ifdef _DEBUG_
#include <stdio.h>
#endif

#include <string.h>

#include "color.h"
#ifdef _COLOR_

typedef struct RGB TYPE;
#else
typedef int TYPE;
#endif
#include "DWT.h"
#include "filters.h"

/* Transformada Wavelet 1D */
#ifndef _COLOR_
void dwt_1d(int data[],
	    int in_line[],
	    int cols,
	    int levels) {
#else
void dwt_1d_rgb(struct RGB data[],
		struct RGB in_line[],
		int cols,
		int levels) {
#endif /* _COLOR_ */

/* {{{  */
  int lv;
  for(lv=0; lv<levels; lv++) {
    int nx;

    nx = cols; cols >>= 1;

    if(nx & 1) {
      memcpy(in_line,data,nx*sizeof(TYPE));
      TransformStep_Odd(nx,in_line,data,data+cols+1);
    } else {
      memcpy(in_line,data,nx*sizeof(TYPE));
      TransformStep_Even(nx,in_line,data,data+cols);
    }
  }
}
/* }}} */

/* Transformada Wavelet Inversa 1D */
#ifndef _COLOR_
void inverse_dwt_1d(int data[],
		    int in_line[],
		    int cols,
		    int levels) {
#else
void inverse_dwt_1d_rgb(struct RGB data[],
			struct RGB in_line[],
			int cols,
			int levels) {
#endif /* _COLOR_ */
/* {{{  */

  int nx, lv;

  nx = cols >> levels;

  for (lv=levels-1; lv>=0; lv--) {
    int mx;
    mx = nx; nx = cols >> lv;

    if(nx & 1) {
      memcpy(in_line,data,nx*sizeof(TYPE));
      i_TransformStep_Odd(nx,data,in_line,in_line+mx+1);
    } else {
      memcpy(in_line,data,nx*sizeof(TYPE));
      i_TransformStep_Even(nx,data,in_line,in_line+mx);
    }
  }
}
/* }}} */

/* Transformada Wavelet 2D */
#ifndef _COLOR_
void dwt_2d(int **data, 
	    int *in_line,
	    int *out_line,
	    int rows,
	    int cols,
	    int levels){
#else
void dwt_2d_rgb(struct RGB **data,
		struct RGB *in_line,
		struct RGB *out_line,
		int rows,
		int cols,
		int levels){
#endif /* _COLOR_ */

/* {{{  */

  int lv;
  int i,j;

  for(lv=0;lv<levels;lv++) {
    int nx, ny;
    
#ifdef _DEBUG_
    fprintf(stderr,"dwt 2D: rows=%d cols=%d\n",rows,cols);
#endif

    nx = cols; cols >>= 1;
    ny = rows; rows >>= 1;
    if(rows == 0) rows = 1; /* Nuevo */
    if(cols == 0) cols = 1; /* Nuevo */

    /* Transformamos las filas */
    if(nx & 1) { /* N'umero impar de columnas */
      for(j=0;j<ny;j++) {
        memcpy(in_line,data[j],nx*sizeof(TYPE));
        TransformStep_Odd(nx,in_line,data[j],data[j]+cols+1);
      }
    } else { /* N'umero par de columnas */
      for(j=0;j<ny;j++) {
        memcpy(in_line,data[j],nx*sizeof(TYPE));
        TransformStep_Even(nx,in_line,data[j],data[j]+cols);
      }
    }

    /* Transformamos las columnas */
    if(ny & 1) { /* N'umero impar de filas */
      for(i=0;i<nx;i++) {
        for(j=0;j<ny;j++) in_line[j]=data[j][i];
        TransformStep_Odd(ny,in_line,out_line,out_line+rows+1);
        for(j=0;j<ny;j++) data[j][i]=out_line[j];
      }
    } else { /* N'umero par de filas */
      for(i=0;i<nx;i++) {
        for(j=0;j<ny;j++) in_line[j]=data[j][i];
        TransformStep_Even(ny,in_line,out_line,out_line+rows);
        for(j=0;j<ny;j++) data[j][i]=out_line[j];
      }
    }
  }
}
/* }}} */

/* Transformada Wavelet Inversa 2D */
#ifndef _COLOR_
void inverse_dwt_2d(int **data,
		    int *in_line,
		    int *out_line,
		    int rows,
		    int cols,
		    int levels) {
#else
void inverse_dwt_2d_rgb(struct RGB **data,
			struct RGB *in_line,
			struct RGB *out_line,
			int rows,
			int cols,
			int levels) {
#endif /* _COLOR_ */
/* {{{  */

  int nx, ny, lv;
  int i,j;

  nx = cols>>levels;
  ny = rows>>levels;

  for (lv = levels-1; lv>=0; lv--) {
    int mx, my;
    mx = nx; nx=cols>>lv;
    my = ny; ny=rows>>lv;
    if(nx==0) nx=1; /* Nuevo */
    if(ny==0) ny=1; /* Nuevo */

    /* Transformamos las filas */
    if(ny & 1) { /* N'umero de filas impar */
      for(i=0;i<nx;i++) {
        for(j=0;j<ny;j++) in_line[j]=data[j][i];
        i_TransformStep_Odd(ny,out_line,in_line,in_line+my+1);
        for(j=0;j<ny;j++) data[j][i]=out_line[j];
      }
    } else { /* N'umero de filas par */
      for(i=0;i<nx;i++) {
        for(j=0;j<ny;j++) in_line[j]=data[j][i];
        i_TransformStep_Even(ny,out_line,in_line,in_line+my);
        for(j=0;j<ny;j++) data[j][i]=out_line[j];
      }
    }

    /* Transformamos las columnas (i) */
    if(nx & 1) { /* N'umero impar de columnas */
      for(j=0;j<ny;j++) {
        memcpy(in_line,data[j],nx*sizeof(TYPE));
        i_TransformStep_Odd(nx,data[j],in_line,in_line+mx+1);
      }
    } else { /* N'umero par de columas */
      for(j=0;j<ny;j++) {
        memcpy(in_line,data[j],nx*sizeof(TYPE));
        i_TransformStep_Even(nx,data[j],in_line,in_line+mx);
      }
    }
  }
}

/* }}} */
#ifdef _1_
/* Transformada Wavelet 3D */
#ifndef _COLOR_
void dwt_3d(int ***data,
	    int *in_line,
	    int *out_line,
	    int pics,
	    int rows,
	    int cols,
	    int levels){
#else
void dwt_3d_rgb(struct RGB ***data,
		struct RGB *in_line,
		struct RGB *out_line,
		int pics,
		int rows,
		int cols,
		int levels){
#endif /* _COLOR_ */
/* {{{  */

  int lv;
  int k,j,i;

  for(lv=0;lv<levels;lv++) {
    int nx, ny, nz;

#ifdef _DEBUG_
    fprintf(stderr,"dwt 3D: pics=%d rows=%d cols=%d\n",pics,rows,cols);
#endif

    nx = cols; cols >>= 1;
    ny = rows; rows >>= 1;
    nz = pics; pics >>= 1;
    //if(pics == 0) pics = 1; if(rows == 0) rows = 1; if(cols == 0) cols = 1; /* Nuevo */

    /* Transformamos las columnas */
    if(nx & 1) { /* N'umero impar de columnas */
      for(k=0;k<nz;k++) {
	for(j=0;j<ny;j++) {
	  memcpy(in_line,data[k][j],nx*sizeof(TYPE));
	  TransformStep_Odd(nx,in_line,data[k][j],data[k][j]+cols+1);
	}
      }
    } else { /* N'umero par de columnas */
      for(k=0;k<nz;k++) {
	for(j=0;j<ny;j++) {
	  memcpy(in_line,data[k][j],nx*sizeof(TYPE));
	  TransformStep_Even(nx,in_line,data[k][j],data[k][j]+cols);
	}
      }
    }

    /* Transformamos las filas */
    if(ny & 1) { /* N'umero impar de filas */
      for(k=0;k<nz;k++) {
	for(i=0;i<nx;i++) {
	  for(j=0;j<ny;j++) in_line[j]=data[k][j][i];
	  TransformStep_Odd(ny,in_line,out_line,out_line+rows+1);
	  for(j=0;j<ny;j++) data[k][j][i]=out_line[j];
	}
      }
    } else { /* N'umero par de filas */
      for(k=0;k<nz;k++) {
	for(i=0;i<nx;i++) {
	  for(j=0;j<ny;j++) in_line[j]=data[k][j][i];
	  TransformStep_Even(ny,in_line,out_line,out_line+rows);
	  for(j=0;j<ny;j++) data[k][j][i]=out_line[j];
	}
      }
    }

    /* Transformamos los planos */
    if(nz & 1) { /* N'umero impar de planos */
      for(i=0;i<nx;i++) {
	for(j=0;j<ny;j++) {
	  for(k=0;k<nz;k++) in_line[k]=data[k][j][i];
	  TransformStep_Odd(nz,in_line,out_line,out_line+pics+1);
	  for(k=0;k<nz;k++) data[k][j][i]=out_line[k];
	}
      }
    } else { /* N'umero par de planos */
      for(i=0;i<nx;i++) {
	for(j=0;j<ny;j++) {
	  for(k=0;k<nz;k++) in_line[k]=data[k][j][i];
	  TransformStep_Even(nz,in_line,out_line,out_line+pics);
	  for(k=0;k<nz;k++) data[k][j][i]=out_line[k];
	}
      }
    }
  }
}

/* }}} */

/* Transformada Wavelet Inversa 3D */
#ifndef _COLOR_
void inverse_dwt_3d(int ***data,
		    int *in_line,
		    int *out_line,
		    int pics,
		    int rows,
		    int cols,
		    int levels) {
#else
void inverse_dwt_3d_rgb(struct RGB ***data,
			struct RGB *in_line,
			struct RGB *out_line,
			int pics,
			int rows,
			int cols,
			int levels) {
#endif /* _COLOR_ */
/* {{{  */

  int nx, ny, nz, lv;
  int k,j,i;

  //int **data = _data[0];

  nx = cols>>levels;
  ny = rows>>levels;
  nz = pics>>levels;

  for (lv = levels-1; lv>=0; lv--) {
    int mx, my, mz;
    mx = nx; nx = cols>>lv;
    my = ny; ny = rows>>lv;
    mz = nz; nz = pics>>lv;

    //if(nx==0) nx=1; if(ny==0) ny=1; if(nz==0) nz=1; /* Nuevo */

    /* Transformamos las planos */
    if(nz & 1) { /* N'umero de planos impar */
      for(i=0;i<nx;i++) {
	for(j=0;j<ny;j++) {
	  for(k=0;k<nz;k++) in_line[k]=data[k][j][i];
	  i_TransformStep_Odd(nz,out_line,in_line,in_line+mz+1);
	  for(k=0;k<nz;k++) data[k][j][i]=out_line[k];
	}
      }
    } else { /* N'umero de planos par */
      for(i=0;i<nx;i++) {
	for(j=0;j<ny;j++) {
	  for(k=0;k<nz;k++) in_line[k]=data[k][j][i];
	  i_TransformStep_Even(nz,out_line,in_line,in_line+mz);
	  for(k=0;k<nz;k++) data[k][j][i]=out_line[k];
	}
      }
    }

    /* Transformamos las filas */
    if(ny & 1) { /* N'umero de filas impar */
      for(k=0;k<nz;k++) {
	for(i=0;i<nx;i++) {
	  for(j=0;j<ny;j++) in_line[j]=data[k][j][i];
	  i_TransformStep_Odd(ny,out_line,in_line,in_line+my+1);
	  for(j=0;j<ny;j++) data[k][j][i]=out_line[j];
	}
      }
    } else { /* N'umero de filas par */
      for(k=0;k<nz;k++) {
	for(i=0;i<nx;i++) {
	  for(j=0;j<ny;j++) in_line[j]=data[k][j][i];
	  i_TransformStep_Even(ny,out_line,in_line,in_line+my);
	  for(j=0;j<ny;j++) data[k][j][i]=out_line[j];
	}
      }
    }

    /* Transformamos las columnas */
    if(nx & 1) { /* N'umero impar de columnas */
      for(k=0;k<nz;k++) {
	for(j=0;j<ny;j++) {
	  memcpy(in_line,data[k][j],nx*sizeof(TYPE));
	  i_TransformStep_Odd(nx,data[k][j],in_line,in_line+mx+1);
	}
      }
    } else { /* N'umero par de columas */
      for(k=0;k<nz;k++) {
	for(j=0;j<ny;j++) {
	  memcpy(in_line,data[k][j],nx*sizeof(TYPE));
	  i_TransformStep_Even(nx,data[k][j],in_line,in_line+mx);
	}
      }
    }
  }
}

/* }}} */
#endif /* _1_ */
