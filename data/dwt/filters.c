#include "color.h"
#include "filters.h"

#ifdef _COLOR_
typedef struct RGB TYPE;
#else
typedef int TYPE;
#endif /* _COLOR_ */

#ifdef _Haar_

char transform_name[40]="Haar Transform";

void TransformStep_Even(int n, TYPE s[], TYPE l[], TYPE h[]) {
  int i, k;
  for (i = k = 0; k < n; i++, k += 2) {
#ifndef _COLOR_
    h[i] = s[k+1] - s[k];
    l[i] = s[k] + h[i]/2;
#else /* _COLOR_ */
    h[i].r = s[k+1].r - s[k].r;
    h[i].g = s[k+1].g - s[k].g;
    h[i].b = s[k+1].b - s[k].b;
    l[i].r = s[k].r + h[i].r/2;
    l[i].g = s[k].g + h[i].g/2;
    l[i].b = s[k].b + h[i].b/2;
#endif /* _COLOR_ */
  }
}
void i_TransformStep_Even(int n, TYPE s[], TYPE l[], TYPE h[]) {
  int i, k;
  for (i = k = 0; k < n; i++, k += 2) {
#ifndef _COLOR_
    s[k] = l[i] - h[i]/2;
    s[k+1] = s[k] + h[i];
#else /* _COLOR_ */
    s[k].r = l[i].r - h[i].r/2;
    s[k].g = l[i].g - h[i].g/2;
    s[k].b = l[i].b - h[i].b/2;
    s[k+1].r = s[k].r + h[i].r;
    s[k+1].g = s[k].g + h[i].g;
    s[k+1].b = s[k].b + h[i].b;
#endif /* _COLOR_ */
  }
}
void TransformStep_Odd(int n, TYPE s[], TYPE l[], TYPE h[]) {
  int i, k;
  for (i = k = 0; k < (n-1); i++, k += 2) {
#ifndef _COLOR_
    h[i] = s[k+1] - s[k];
    l[i] = s[k] + h[i]/2;
#else /* _COLOR_ */
    h[i].r = s[k+1].r - s[k].r;
    h[i].g = s[k+1].g - s[k].g;
    h[i].b = s[k+1].b - s[k].b;
    l[i].r = s[k].r + h[i].r/2;
    l[i].g = s[k].g + h[i].g/2;
    l[i].b = s[k].b + h[i].b/2;
#endif /* _COLOR_ */
  }
  l[i] = s[k];
}
void i_TransformStep_Odd(int n, TYPE s[], TYPE l[], TYPE h[]) {
  int i, k;
  for (i = k = 0; k < (n-1); i++, k += 2) {
#ifndef _COLOR_
    s[k] = l[i] - h[i]/2;
    s[k+1] = s[k] + h[i];
#else /* _COLOR_ */
    s[k].r = l[i].r - h[i].r/2;
    s[k].g = l[i].g - h[i].g/2;
    s[k].b = l[i].b - h[i].b/2;
    s[k+1].r = s[k].r + h[i].r;
    s[k+1].g = s[k].g + h[i].g;
    s[k+1].b = s[k].b + h[i].b;
#endif /* _COLOR_ */
  }
  s[k] = l[i];
}
#endif /* _Haar_ */

/* {{{ ST */

#ifdef _ST_
/* entropias
  lena     157778
  barb     180537
  boats    162675
  zelda    147267
  goldhill 169917
  fear     706952

  uchar2int < /home/vruiz/bin/lena | dwt_2d | histogram -lis -256 -his 255 -bps 4 | entropy -as 512
  uchar2int < $HOME/bin/fear | dwt_2d -rows 1024 -cols 1024 | histogram -lis -512 -his 511 -bps 4 | entropy -as 1024
*/

#ifndef _COLOR_
char transform_name[40]="Sequential Transform";
#else /* _COLOR_ */
char transform_name_color[40]="Sequential Transform";
#endif /* _COLOR_ */

void TransformStep_Even(int n, TYPE s[], TYPE l[], TYPE h[]) {
  int i, k;
  for (i = k = 0; k < n; i++, k += 2) {
#ifndef _COLOR_
    l[i] = (s[k] + s[k+1]) >> 1;
    h[i] =  s[k] - s[k+1];
#else /* _COLOR_ */
    l[i].r = (s[k].r + s[k+1].r) >> 1;
    l[i].g = (s[k].g + s[k+1].g) >> 1;
    l[i].b = (s[k].b + s[k+1].b) >> 1;
    h[i].r =  s[k].r - s[k+1].r;
    h[i].g =  s[k].g - s[k+1].g;
    h[i].b =  s[k].b - s[k+1].b;
#endif /* _COLOR_ */
  }
}
void i_TransformStep_Even(int n, TYPE s[], TYPE l[], TYPE h[]) {
  int i, k;
  for (i = k = 0; k < n; i++, k += 2) {
#ifndef _COLOR_
    s[k] = l[i] + ((h[i] + 1) >> 1);
    s[k+1] = s[k] - h[i];
#else /* _COLOR_ */
    s[k].r = l[i].r + ((h[i].r + 1) >> 1);
    s[k].g = l[i].g + ((h[i].g + 1) >> 1);
    s[k].b = l[i].b + ((h[i].b + 1) >> 1);
    s[k+1].r = s[k].r - h[i].r;
    s[k+1].g = s[k].g - h[i].g;
    s[k+1].b = s[k].b - h[i].b;
#endif /* _COLOR_ */
  }
}
void TransformStep_Odd(int n, TYPE s[], TYPE l[], TYPE h[]) {
  int i, k;
  for (i = k = 0; k < (n-1); i++, k += 2) {
#ifndef _COLOR_
    l[i] = (s[k] + s[k+1]) >> 1;
    h[i] =  s[k] - s[k+1];
#else /* _COLOR_ */
    l[i].r = (s[k].r + s[k+1].r) >> 1;
    l[i].g = (s[k].g + s[k+1].g) >> 1;
    l[i].b = (s[k].b + s[k+1].b) >> 1;
    h[i].r =  s[k].r - s[k+1].r;
    h[i].g =  s[k].g - s[k+1].g;
    h[i].b =  s[k].b - s[k+1].b;
#endif /* _COLOR_ */
  }
  l[i] = s[k];
}
void i_TransformStep_Odd(int n, TYPE s[], TYPE l[], TYPE h[]) {
  int i, k;
  for (i = k = 0; k < (n-1); i++, k += 2) {
#ifndef _COLOR_
    s[k] = l[i] + ((h[i] + 1) >> 1);
    s[k+1] = s[k] - h[i];
#else /* _COLOR_ */
    s[k].r = l[i].r + ((h[i].r + 1) >> 1);
    s[k].g = l[i].g + ((h[i].g + 1) >> 1);
    s[k].b = l[i].b + ((h[i].b + 1) >> 1);
    s[k+1].r = s[k].r - h[i].r;
    s[k+1].g = s[k].g - h[i].g;
    s[k+1].b = s[k].b - h[i].b;
#endif /* _COLOR_ */
  }
  s[k] = l[i];
}
#endif
/* }}} */
/* {{{ UST */

#ifdef _UST_
/* entropias
  lena     157778
  barb     180537
  boats    162675
  zelda    147267
  goldhill 169917
  fear     706952

  uchar2int < /home/vruiz/bin/lena | dwt_2d | histogram -lis -256 -his 255 -bps 4 | entropy -as 512
  uchar2int < $HOME/bin/fear | dwt_2d -rows 1024 -cols 1024 | histogram -lis -512 -his 511 -bps 4 | entropy -as 1024
*/

char transform_name[40]="Sequential Transform";

void TransformStep_Even(int n, TYPE s[], TYPE l[], TYPE h[]) {
  int i, k;
  for (i = k = 0; k < n; i++, k += 2) {
    l[i] = ((s[k] + s[k+1])>>1)<<1;
    h[i] =  s[k] - s[k+1];
  }
}
void i_TransformStep_Even(int n, TYPE s[], TYPE l[], TYPE h[]) {
  int i, k;
  for (i = k = 0; k < n; i++, k += 2) {
    s[k] = (l[i]>>1) + ((h[i] + 1) >> 1);
    s[k+1] = s[k] - h[i];
  }
}
void TransformStep_Odd(int n, TYPE s[], TYPE l[], TYPE h[]) {
  int i, k;
  for (i = k = 0; k < (n-1); i++, k += 2) {
    l[i] = ((s[k] + s[k+1]) >> 1)<<1;
    h[i] =  s[k] - s[k+1];
  }
  l[i] = s[k]<<1;
}
void i_TransformStep_Odd(int n, TYPE s[], TYPE l[], TYPE h[]) {
  int i, k;
  for (i = k = 0; k < (n-1); i++, k += 2) {
    s[k] = (l[i]>>1) + ((h[i] + 1) >> 1);
    s[k+1] = s[k] - h[i];
  }
  s[k] = l[i]>>1;
}
#endif
/* }}} */
/* {{{ SPT */
/* entropias
  lena     143896
  barb     164115
  boats    151949
  zelda    134732
  goldhill 160956
  fear     699288
*/
#ifdef _SPT_

#ifndef _COLOR_
char transform_name[40]="Sequential+Prediction Transform";
#else /* _COLOR_ */
char transform_name_color[40]="Sequential+Prediction Transform";
#endif /* _COLOR_ */

void TransformStep_Even(int n, TYPE s[], TYPE l[], TYPE h[]) {
  int i, k, mm = n/2 - 1;
  TYPE d1, d2;

  for (i = k = 0; k < n; i++, k += 2) {
#ifndef _COLOR_
    l[i] = (s[k] + s[k+1]) >> 1;
    h[i] =  s[k] - s[k+1];
#else /* _COLOR_ */
    l[i].r = (s[k].r + s[k+1].r) >> 1;
    l[i].g = (s[k].g + s[k+1].g) >> 1;
    l[i].b = (s[k].b + s[k+1].b) >> 1;
    h[i].r =  s[k].r - s[k+1].r;
    h[i].g =  s[k].g - s[k+1].g;
    h[i].b =  s[k].b - s[k+1].b;
#endif /* _COLOR_ */
  }
  if(n>2) {
#ifndef _COLOR_
    h[0] -= (d2 = l[0] - l[1]) >> 2;
#else /* _COLOR_ */
    h[0].r -= (d2.r = l[0].r - l[1].r) >> 2;
    h[0].g -= (d2.g = l[0].g - l[1].g) >> 2;
    h[0].b -= (d2.b = l[0].b - l[1].b) >> 2;
#endif /* _COLOR_ */
    for (i = 1; i < mm; i++) {
#ifndef _COLOR_
      d1 = d2;  d2 = l[i] - l[i+1];
      h[i] -= (((d1 + d2 - h[i+1]) << 1) + d2 + 3) >> 3;
#else /* _COLOR_ */
      d1 = d2;
      d2.r = l[i].r - l[i+1].r;
      d2.g = l[i].g - l[i+1].g;
      d2.b = l[i].b - l[i+1].b;
      h[i].r -= (((d1.r + d2.r - h[i+1].r) << 1) + d2.r + 3) >> 3;
      h[i].g -= (((d1.g + d2.g - h[i+1].g) << 1) + d2.g + 3) >> 3;
      h[i].b -= (((d1.b + d2.b - h[i+1].b) << 1) + d2.b + 3) >> 3;
#endif /* _COLOR_ */
    }
#ifndef _COLOR_
    h[i] -= d2 >> 2;
#else /* _COLOR_ */
    h[i].r -= d2.r >> 2;
    h[i].g -= d2.g >> 2;
    h[i].b -= d2.b >> 2;
#endif /* _COLOR_ */
  }
}
void i_TransformStep_Even(int n, TYPE s[], TYPE l[], TYPE h[]) {
  int i, k, m=n/2;
  TYPE d1, d2;
  
  if(n>2) {
#ifndef _COLOR_
    h[m-1] += (d1 = l[m-2] - l[m-1]) >> 2;
#else /* _COLOR_ */
    h[m-1].r += (d1.r = l[m-2].r - l[m-1].r) >> 2;
    h[m-1].g += (d1.g = l[m-2].g - l[m-1].g) >> 2;
    h[m-1].b += (d1.b = l[m-2].b - l[m-1].b) >> 2;
#endif /* _COLOR_ */
    for (i = m - 2; i > 0; i--) {
#ifndef _COLOR_
      d2 = d1;  d1 = l[i-1] - l[i];
      h[i] += (((d1 + d2 - h[i+1]) << 1) + d2 + 3) >> 3;
#else /* _COLOR_ */
      d2 = d1;
      d1.r = l[i-1].r - l[i].r;
      d1.g = l[i-1].g - l[i].g;
      d1.b = l[i-1].b - l[i].b;
      h[i].r += (((d1.r + d2.r - h[i+1].r) << 1) + d2.r + 3) >> 3;
      h[i].g += (((d1.g + d2.g - h[i+1].g) << 1) + d2.g + 3) >> 3;
      h[i].b += (((d1.b + d2.b - h[i+1].b) << 1) + d2.b + 3) >> 3;
#endif /* _COLOR_ */
    }
#ifndef _COLOR_
    h[0] += d1 >> 2;
#else /* _COLOR_ */
    h[0].r += d1.r >> 2;
    h[0].g += d1.g >> 2;
    h[0].b += d1.b >> 2;
#endif /* _COLOR_ */
  }
  for (i = k = 0; k < n; i++, k += 2) {
#ifndef _COLOR_
    s[k] = l[i] + ((h[i] + 1) >> 1);
    s[k+1] = s[k] - h[i];
#else /* _COLOR_ */
    s[k].r = l[i].r + ((h[i].r + 1) >> 1);
    s[k].g = l[i].g + ((h[i].g + 1) >> 1);
    s[k].b = l[i].b + ((h[i].b + 1) >> 1);
    s[k+1].r = s[k].r - h[i].r;
    s[k+1].g = s[k].g - h[i].g;
    s[k+1].b = s[k].b - h[i].b;
#endif /* _COLOR_ */
  }
}
void TransformStep_Odd(int n, TYPE s[], TYPE l[], TYPE h[]) {
  int i, k, mm = n/2 - 1;
  TYPE d1, d2;

  for (i = k = 0; k < (n-1); i++, k += 2) {
#ifndef _COLOR_
    l[i] = (s[k] + s[k+1]) >> 1;
    h[i] =  s[k] - s[k+1];
#else /* _COLOR_ */
    l[i].r = (s[k].r + s[k+1].r) >> 1;
    l[i].g = (s[k].g + s[k+1].g) >> 1;
    l[i].b = (s[k].b + s[k+1].b) >> 1;
    h[i].r =  s[k].r - s[k+1].r;
    h[i].g =  s[k].g - s[k+1].g;
    h[i].b =  s[k].b - s[k+1].b;
#endif /* _COLOR_ */
  }
  l[i] = s[n-1];
  if(n>2) {
#ifndef _COLOR_
    h[0] -= (d2 = l[0] - l[1]) >> 2;
#else /* _COLOR_ */
    h[0].r -= (d2.r = l[0].r - l[1].r) >> 2;
    h[0].g -= (d2.g = l[0].g - l[1].g) >> 2;
    h[0].b -= (d2.b = l[0].b - l[1].b) >> 2;
#endif /* _COLOR_ */
    for (i = 1; i < mm; i++) {
#ifndef _COLOR_
      d1 = d2;  d2 = l[i] - l[i+1];
      h[i] -= (((d1 + d2 - h[i+1]) << 1) + d2 + 3) >> 3;
#else /* _COLOR_ */
      d1 = d2;
      d2.r = l[i].r - l[i+1].r;
      d2.g = l[i].g - l[i+1].g;
      d2.b = l[i].b - l[i+1].b;
      h[i].r -= (((d1.r + d2.r - h[i+1].r) << 1) + d2.r + 3) >> 3;
      h[i].g -= (((d1.g + d2.g - h[i+1].g) << 1) + d2.g + 3) >> 3;
      h[i].b -= (((d1.b + d2.b - h[i+1].b) << 1) + d2.b + 3) >> 3;
#endif /* _COLOR_ */
    }
#ifndef _COLOR_
    h[i] -= d2 >> 2;
#else /* _COLOR_ */
    h[i].r -= d2.r >> 2;
    h[i].g -= d2.g >> 2;
    h[i].b -= d2.b >> 2;
#endif /* _COLOR_ */
  }
}
void i_TransformStep_Odd(int n, TYPE s[], TYPE l[], TYPE h[]) {
  int i, k, m=n/2;
  TYPE d1, d2;
  if(n>2) {
#ifndef _COLOR_
    h[m-1] += (d1 = l[m-2] - l[m-1]) >> 2;
#else /* _COLOR_ */
    h[m-1].r += (d1.r = l[m-2].r - l[m-1].r) >> 2;
    h[m-1].g += (d1.g = l[m-2].g - l[m-1].r) >> 2;
    h[m-1].b += (d1.b = l[m-2].b - l[m-1].r) >> 2;
#endif /* _COLOR_ */
    for (i = m - 2; i > 0; i--) {
#ifndef _COLOR_
      d2 = d1;  d1 = l[i-1] - l[i];
      h[i] += (((d1 + d2 - h[i+1]) << 1) + d2 + 3) >> 3;
#else /* _COLOR_ */
      d2 = d1;
      d1.r = l[i-1].r - l[i].r;
      d1.g = l[i-1].g - l[i].g;
      d1.b = l[i-1].b - l[i].b;
      h[i].r += (((d1.r + d2.r - h[i+1].r) << 1) + d2.r + 3) >> 3;
      h[i].g += (((d1.g + d2.g - h[i+1].g) << 1) + d2.g + 3) >> 3;
      h[i].b += (((d1.b + d2.b - h[i+1].b) << 1) + d2.b + 3) >> 3;
#endif /* _COLOR_ */
    }
#ifndef _COLOR_
    h[0] += d1 >> 2;
#else /* _COLOR_ */
    h[0].r += d1.r >> 2;
    h[0].g += d1.g >> 2;
    h[0].b += d1.b >> 2;
#endif /* _COLOR_ */
  }
  for (i = k = 0; k < (n-1); i++, k += 2) {
#ifndef _COLOR_
    s[k] = l[i] + ((h[i] + 1) >> 1);
    s[k+1] = s[k] - h[i];
#else /* _COLOR_ */
    s[k].r = l[i].r + ((h[i].r + 1) >> 1);
    s[k].g = l[i].g + ((h[i].g + 1) >> 1);
    s[k].b = l[i].b + ((h[i].b + 1) >> 1);
    s[k+1].r = s[k].r - h[i].r;
    s[k+1].g = s[k].g - h[i].g;
    s[k+1].b = s[k].b - h[i].b;
#endif /* _COLOR_ */
  }
  s[k] = l[i];
}
#endif

/* }}} */
/* {{{ 2/6 */

#ifdef _2_6_
/* entropias
  lena     146334
  barb     168397
  boats    155090
  zelda    134925
  goldhill 163054
  fear     695950
*/

char transform_name[40]="2/6 Transform";

void TransformStep_Even(int n, TYPE s[], TYPE l[], TYPE h[]) {
  int i, k;
  for (i = k = 0; k < n; i++, k += 2) {
    h[i] = s[k+1] - s[k];
    l[i] = s[k] + (h[i] >> 1);
  }
  for (i=1; i<n/2-1; i++) {
    h[i] += ((l[i-1]-l[i+1]+2)>>2);
  }
}
void i_TransformStep_Even(int n, TYPE s[], TYPE l[], TYPE h[]) {
  int i, k;
  for (i=1; i<n/2-1; i++) {
    h[i] -= ((l[i-1]-l[i+1]+2)>>2);
  }
  for (i = k = 0; k < n; i++, k += 2) {
    s[k] = l[i] - (h[i] >> 1);
    s[k+1] = s[k] + h[i];
  }
}
void TransformStep_Odd(int n, TYPE s[], TYPE l[], TYPE h[]) {
  int i, k;
  for (i = k = 0; k < (n-1); i++, k += 2) {
    h[i] =  s[k+1] - s[k];
    l[i] = s[k] + (h[i] >> 1);
  }
  l[i] = s[k];
  for (i=1; i<n/2-1; i++) {
    h[i] += ((l[i-1]-l[i+1]+2)>>2);
  }

}
void i_TransformStep_Odd(int n, TYPE s[], TYPE l[], TYPE h[]) {
  int i, k;
  for (i=1; i<n/2-1; i++) {
    h[i] -= ((l[i-1]-l[i+1]+2)>>2);
  }
  for (i = k = 0; k < (n-1); i++, k += 2) {
    s[k] = l[i] - (h[i] >> 1);
    s[k+1] = s[k] + h[i];
  }
  s[k] = l[i];
}
#endif

/* }}} */
/* {{{ 2/10 */

#ifdef _2_10_
/* entropias
  lena     145617
  barb     166005
  boats    154745
  zelda    134529
  goldhill 162995
  fear     697838
*/

char transform_name[40]="2/10 Transform";

void TransformStep_Even(int n, TYPE s[], TYPE l[], TYPE h[]) {
  int i, k;
  for (i = k = 0; k < n; i++, k += 2) {
    h[i] = s[k+1] - s[k];
    l[i] = s[k] + (h[i] >> 1);
  }
  for (i=2; i<n/2-2; i++) {
    h[i] += ((22*(l[i-1]-l[i+1])+3*(l[i+2]-l[i-2])+32)>>6);
  }
}
void i_TransformStep_Even(int n, TYPE s[], TYPE l[], TYPE h[]) {
  int i, k;
  for (i=2; i<n/2-2; i++) {
    h[i] -= ((22*(l[i-1]-l[i+1])+3*(l[i+2]-l[i-2])+32)>>6);
  }
  for (i = k = 0; k < n; i++, k += 2) {
    s[k] = l[i] - (h[i] >> 1);
    s[k+1] = s[k] + h[i];
  }
}
void TransformStep_Odd(int n, TYPE s[], TYPE l[], TYPE h[]) {
  int i, k;
  for (i = k = 0; k < (n-1); i++, k += 2) {
    h[i] =  s[k+1] - s[k];
    l[i] = s[k] + (h[i] >> 1);
  }
  l[i] = s[k];
  for (i=2; i<n/2-2; i++) {
    h[i] += ((22*(l[i-1]-l[i+1])+3*(l[i+2]-l[i-2])+32)>>6);
  }
}
void i_TransformStep_Odd(int n, TYPE s[], TYPE l[], TYPE h[]) {
  int i, k;
  for (i=2; i<n/2-2; i++) {
    h[i] -= ((22*(l[i-1]-l[i+1])+3*(l[i+2]-l[i-2])+32)>>6);
  }
  for (i = k = 0; k < (n-1); i++, k += 2) {
    s[k] = l[i] - (h[i] >> 1);
    s[k+1] = s[k] + h[i];
  }
  s[k] = l[i];
}
#endif

/* }}} */
/* {{{ SPB */

#ifdef _SPB_
/* entropias
  lena     143848
  barb     164189
  boats    152007
  zelda    134790
  goldhill 160962
  fear     699253
*/

char transform_name[40]="Sequential+Prediction (B) Transform";

/*
 * La Transformada S+P predictor B.
 *
 * Versi'on de:
 * Adams, M.D. and Kossentini, F.
 * "Reversible Integer-to-Integer Wavelet Transforms
 * for Image Compression: Performance Evaluation and Analysis"
 * IEEE Transactions on Image Processing, Vol 9, Num 6, pp: 1010-1024, 2000.
 *
 * Ver tambi'en:
 *
 * A. Said and W.A. Pearlman
 * "An Image Multiresolution Representation for Lossless and Lossy Compression"
 * IEEE Transactions on Image Processing, Vol 5, Num 9, pp: 1303-1310, 1996.
 *
 * porque no se trata ex'actamente de la misma transformada.
 */
void TransformStep_Even(int n, TYPE s[], TYPE l[], TYPE h[]) {
  int i, k;
  for (i = k = 0; k < n; i++, k += 2) {
    h[i] = s[k+1] - s[k];
    l[i] = s[k] + (h[i] >> 1);
  }
  for(i=1; i<(n/2-1); i++) {
    h[i] += ((2*l[i-1] + l[i] - 3*l[i+1] + 2*h[i+1] + 4)>>3);
  }
}
void i_TransformStep_Even(int n, TYPE s[], TYPE l[], TYPE h[]) {
  int i, k;
  for(i=n/2-2; i>0; i--) {
    h[i] -= ((2*l[i-1] + l[i] - 3*l[i+1] + 2*h[i+1] + 4)>>3);
  }
  for (i = k = 0; k < n; i++, k += 2) {
    s[k] = l[i] - (h[i] >> 1);
    s[k+1] = s[k] + h[i];
  }
}
void TransformStep_Odd(int n, TYPE s[], TYPE l[], TYPE h[]) {
  int i, k;
  for (i = k = 0; k < (n-1); i++, k += 2) {
    h[i] =  s[k+1] - s[k];
    l[i] = s[k] + (h[i] >> 1);
  }
  l[i] = s[k];
  for(i=1; i<(n/2-1); i++) {
    h[i] += ((2*l[i-1] + l[i] - 3*l[i+1] + 2*h[i+1] + 4)>>3);
  }
}
void i_TransformStep_Odd(int n, TYPE s[], TYPE l[], TYPE h[]) {
  int i, k;
  for(i=n/2-2; i>0; i--) {
    h[i] -= ((2*l[i-1] + l[i] - 3*l[i+1] + 2*h[i+1] + 4)>>3);
  }
  for (i = k = 0; k < (n-1); i++, k += 2) {
    s[k] = l[i] - (h[i] >> 1);
    s[k+1] = s[k] + h[i];
  }
  s[k] = l[i];
}
#endif

/* }}} */
/* {{{ SPC */

#ifdef _SPC_
/* entropias
  lena     144955
  barb     162497
  boats    152928
  zelda    136785
  goldhill 162424
  fear     710813
*/

char transform_name[40]="Sequential+Prediction (C) Transform";

/*
 * La Transformada S+P predictor C.
 *
 * Versi'on de:
 * Adams, M.D. and Kossentini, F.
 * "Reversible Integer-to-Integer Wavelet Transforms
 * for Image Compression: Performance Evaluation and Analysis"
 * IEEE Transactions on Image Processing, Vol 9, Num 6, pp: 1010-1024, 2000.
 *
 * Ver tambi'en:
 *
 * A. Said and W.A. Pearlman
 * "An Image Multiresolution Representation for Lossless and Lossy Compression"
 * IEEE Transactions on Image Processing, Vol 5, Num 9, pp: 1303-1310, 1996.
 *
 * porque no se trata ex'actamente de la misma transformada.
 */
void TransformStep_Even(int n, TYPE s[], TYPE l[], TYPE h[]) {
  int i, k;
  for (i = k = 0; k < n; i++, k += 2) {
    h[i] = s[k+1] - s[k];
    l[i] = s[k] + (h[i] >> 1);
  }
  for(i=2; i<(n/2-1); i++) {
    h[i] += ((-l[i-2] + 5*l[i-1] + 4*l[i] - 8*l[i+1] + 6*h[i+1] + 8)>>4);
  }
}
void i_TransformStep_Even(int n, TYPE s[], TYPE l[], TYPE h[]) {
  int i, k;
  for(i=n/2-2; i>1; i--) {
    h[i] -= ((-l[i-2] + 5*l[i-1] + 4*l[i] - 8*l[i+1] + 6*h[i+1] + 8)>>4);
  }
  for (i = k = 0; k < n; i++, k += 2) {
    s[k] = l[i] - (h[i] >> 1);
    s[k+1] = s[k] + h[i];
  }
}
void TransformStep_Odd(int n, TYPE s[], TYPE l[], TYPE h[]) {
  int i, k;
  for (i = k = 0; k < (n-1); i++, k += 2) {
    h[i] =  s[k+1] - s[k];
    l[i] = s[k] + (h[i] >> 1);
  }
  l[i] = s[k];
  for(i=2; i<(n/2-1); i++) {
    h[i] += ((-l[i-2] + 5*l[i-1] + 4*l[i] - 8*l[i+1] + 6*h[i+1] + 8)>>4);
  }
}
void i_TransformStep_Odd(int n, TYPE s[], TYPE l[], TYPE h[]) {
  int i, k;
  for(i=n/2-2; i>1; i--) {
    h[i] -= ((-l[i-2] + 5*l[i-1] + 4*l[i] - 8*l[i+1] + 6*h[i+1] + 8)>>4);
  }
  for (i = k = 0; k < (n-1); i++, k += 2) {
    s[k] = l[i] - (h[i] >> 1);
    s[k+1] = s[k] + h[i];
  }
  s[k] = l[i];
}
#endif

/* }}} */
/* {{{ 11 */

#ifdef _11_
/* entropias
               +1     +0
  lena     157779 157837
  barb     180555 180578
  boats    162693 162678
  zelda    147247 147272
  goldhill 169913 169970
  fear     707364 707021
*/

char transform_name[40]="11 Transform";

void TransformStep_Even(int n, TYPE s[], TYPE l[], TYPE h[]) {
  int i, k;
  for (i = k = 0; k < n; i++, k += 2) {
#ifndef _COLOR_
    h[i] = s[k+1] - s[k];
    l[i] = s[k] + (h[i] >> 1);
#else /* _COLOR_ */
    h[i].r = s[k+1].r - s[k].r;
    h[i].g = s[k+1].g - s[k].g;
    h[i].b = s[k+1].b - s[k].b;
    l[i].r = s[k].r + (h[i].r >> 1);
    l[i].g = s[k].g + (h[i].g >> 1);
    l[i].b = s[k].b + (h[i].b >> 1);
#endif /* _COLOR_ */
  }
}
void i_TransformStep_Even(int n, TYPE s[], TYPE l[], TYPE h[]) {
  int i, k;
  for (i = k = 0; k < n; i++, k += 2) {
#ifndef _COLOR_
    s[k] = l[i] - (h[i] >> 1);
    s[k+1] = s[k] + h[i];
#else /* _COLOR_ */
    s[k].r = l[i].r - (h[i].r >> 1);
    s[k].g = l[i].g - (h[i].g >> 1);
    s[k].b = l[i].b - (h[i].b >> 1);
    s[k+1].r = s[k].r + h[i].r;
    s[k+1].g = s[k].g + h[i].g;
    s[k+1].b = s[k].b + h[i].b;
#endif /* _COLOR_ */
  }
}
void TransformStep_Odd(int n, TYPE s[], TYPE l[], TYPE h[]) {
  int i, k;
  for (i = k = 0; k < (n-1); i++, k += 2) {
#ifndef _COLOR_
    h[i] =  s[k+1] - s[k];
    l[i] = s[k] + (h[i] >> 1);
#else /* _COLOR_ */
    h[i].r =  s[k+1].r - s[k].r;
    h[i].g =  s[k+1].g - s[k].g;
    h[i].b =  s[k+1].b - s[k].b;
    l[i].r = s[k].r + (h[i].r >> 1);
    l[i].g = s[k].g + (h[i].g >> 1);
    l[i].b = s[k].b + (h[i].b >> 1);
#endif /* _COLOR_ */
  }
  l[i] = s[k];
}
void i_TransformStep_Odd(int n, TYPE s[], TYPE l[], TYPE h[]) {
  int i, k;
  for (i = k = 0; k < (n-1); i++, k += 2) {
#ifndef _COLOR_
    s[k] = l[i] - (h[i] >> 1);
    s[k+1] = s[k] + h[i];
#else /* _COLOR_ */
    s[k].r = l[i].r - (h[i].r >> 1);
    s[k].g = l[i].g - (h[i].g >> 1);
    s[k].b = l[i].b - (h[i].b >> 1);
    s[k+1].r = s[k].r + h[i].r;
    s[k+1].g = s[k].g + h[i].g;
    s[k+1].b = s[k].b + h[i].b;
#endif /* _COLOR_ */
  }
  s[k] = l[i];
}
#endif
#ifdef _11b_
/* entropias
  lena     157778
  barb     180537
  boats    162675
  zelda    147267
  goldhill 169917
  fear     706952
*/
void TransformStep_Even(int n, TYPE s[], TYPE l[], TYPE h[]) {
  int i, k;
  for (i = k = 0; k < n; i++, k += 2) {
    h[i] = s[k] - s[k+1];
    l[i] = s[k] - ((h[i] + 1) >> 1);
  }
}
void i_TransformStep_Even(int n, TYPE s[], TYPE l[], TYPE h[]) {
  int i, k;
  for (i = k = 0; k < n; i++, k += 2) {
    s[k] = l[i] + ((h[i] + 1) >> 1);
    s[k+1] = s[k] - h[i];
  }
}
void TransformStep_Odd(int n, TYPE s[], TYPE l[], TYPE h[]) {
  int i, k;
  for (i = k = 0; k < (n-1); i++, k += 2) {
    h[i] =  s[k] - s[k+1];
    l[i] = s[k] - ((h[i] + 1) >> 1);
  }
  l[i] = s[k];
}
void i_TransformStep_Odd(int n, TYPE s[], TYPE l[], TYPE h[]) {
  int i, k;
  for (i = k = 0; k < (n-1); i++, k += 2) {
    s[k] = l[i] + ((h[i] + 1) >> 1);
    s[k+1] = s[k] - h[i];
  }
  s[k] = l[i];
}
#endif

#ifdef _11c_
void TransformStep_Even(int n, TYPE s[], TYPE l[], TYPE h[]) {
  int i, k;
  for (i = k = 0; k < n; i++, k += 2) {
    l[i] = (s[k] + s[k+1])>>1;
    h[i] = s[k+1] - s[k];
  }
}
void i_TransformStep_Even(int n, TYPE s[], TYPE l[], TYPE h[]) {
  int i, k;
  for (i = k = 0; k < n; i++, k += 2) {
    s[k] = l[i] - ((h[i] + 1) >> 1);
    s[k+1] = s[k] + h[i];
  }
}
void TransformStep_Odd(int n, TYPE s[], TYPE l[], TYPE h[]) {
  int i, k;
  for (i = k = 0; k < (n-1); i++, k += 2) {
    h[i] =  s[k+1] - s[k];
    l[i] = s[k] + ((h[i] + 1) >> 1);
  }
  l[i] = s[k];
}
void i_TransformStep_Odd(int n, TYPE s[], TYPE l[], TYPE h[]) {
  int i, k;
  for (i = k = 0; k < (n-1); i++, k += 2) {
    s[k] = l[i] - ((h[i] + 1) >> 1);
    s[k+1] = s[k] + h[i];
  }
  s[k] = l[i];
}
#endif
/* }}} */
/* {{{ 22 */

#ifdef _22_
/* entropias
  lena     144421
  barb     166539
  boats    151492
  zelda    131990
  goldhill 160541
  fear     694514
*/

char transform_name[40]="22 Transform";

void TransformStep_Even(int n, TYPE s[], TYPE l[], TYPE h[]) {
  int i;
  for(i=0;i<n/2-1;i++) {
    int i2 = i<<1;
    h[i] = s[i2+1] - (s[i2]+s[i2+2])/2;
  }
  h[i] = s[n-1] - s[n-2];

  l[0] = s[0] + ((h[0]+1)>>1);
  for(i=1;i<n/2;i++) {
    int i2 = i<<1;
    l[i] = s[i2] + ((h[i]+h[i-1]+1)>>2);
  }
}
void i_TransformStep_Even(int n, TYPE s[], TYPE l[], TYPE h[]) {
  int i;
  s[0] = l[0] - ((h[0]+1)>>1);
  for(i=1;i<n/2;i++) {
    int i2 = i<<1;
    s[i2] = l[i] - ((h[i]+h[i-1]+1)>>2);
  }

  for(i=0;i<n/2-1;i++) {
    int i2 = i<<1;
    s[i2+1] = h[i] + (s[i2]+s[i2+2])/2;
  }
  s[n-1] = h[i] + s[n-2];
}
void TransformStep_Odd(int n, TYPE s[], TYPE l[], TYPE h[]) {
  int i;
  for(i=0;i<n/2;i++) {
    int i2 = i<<1;
    h[i] = s[i2+1] - (s[i2]+s[i2+2])/2;
  }

  l[0] = s[0] + ((h[0]+1)>>1);
  for(i=1;i<n/2;i++) {
    int i2 = i<<1;
    l[i] = s[i2] + ((h[i]+h[i-1]+1)>>2);
  }
  l[i] = s[n-1] + ((h[i-1]+1)>>1);
}
void i_TransformStep_Odd(int n, TYPE s[], TYPE l[], TYPE h[]) {
  int i;
  s[0] = l[0] - ((h[0]+1)>>1);
  for(i=1;i<n/2;i++) {
    int i2 = i<<1;
    s[i2] = l[i] - ((h[i]+h[i-1]+1)>>2);
  }
  s[n-1] = l[i] - ((h[i-1]+1)>>1);

  for(i=0;i<n/2;i++) {
    int i2 = i<<1;
    s[i2+1] = h[i] + (s[i2]+s[i2+2])/2;
  }
}
#endif

#ifdef _22b_
/* entropias
  lena     144432
  barb     166570
  boats    151509
  zelda    132007
  goldhill 160538
  fear     694332
*/
void TransformStep_Even(int n, TYPE s[], TYPE l[], TYPE h[]) {
  int i;
  for(i=0;i<n/2-1;i++) {
    int i2 = i<<1;
    h[i] = (s[i2]+s[i2+2])/2 - s[i2+1];
  }
  h[i] =  s[n-2] - s[n-1];

  l[0] = s[0] - ((h[0]+1)>>1);
  for(i=1;i<n/2;i++) {
    int i2 = i<<1;
    l[i] = s[i2] - ((h[i]+h[i-1]+1)>>2);
  }
}
void i_TransformStep_Even(int n, TYPE s[], TYPE l[], TYPE h[]) {
  int i;
  s[0] = l[0] + ((h[0]+1)>>1);
  for(i=1;i<n/2;i++) {
    int i2 = i<<1;
    s[i2] = l[i] + ((h[i]+h[i-1]+1)>>2);
  }

  for(i=0;i<n/2-1;i++) {
    int i2 = i<<1;
    s[i2+1] =  (s[i2]+s[i2+2])/2 - h[i];
  }
  s[n-1] = s[n-2] - h[i];
}
void TransformStep_Odd(int n, TYPE s[], TYPE l[], TYPE h[]) {
  int i;
  for(i=0;i<n/2;i++) {
    int i2 = i<<1;
    h[i] = s[i2+1] - (s[i2]+s[i2+2])/2;
  }

  l[0] = s[0] + (h[0]>>1);
  for(i=1;i<n/2;i++) {
    int i2 = i<<1;
    //l[i] = s[i2] + (h[i]+h[i-1])/4;
    //l[i] = s[i2] + ((h[i]+h[i-1]+1)>>2);
    l[i] = s[i2] + ((h[i]+h[i-1])>>2);
  }
  l[i] = s[n-1] + (h[i-1]>>1);
}
void i_TransformStep_Odd(int n, TYPE s[], TYPE l[], TYPE h[]) {
  int i;
  s[0] = l[0] - (h[0]>>1);
  for(i=1;i<n/2;i++) {
    int i2 = i<<1;
    //s[i2] = l[i] - (h[i]+h[i-1])/4;
    //s[i2] = l[i] - ((h[i]+h[i-1]+1)>>2);
    s[i2] = l[i] - ((h[i]+h[i-1])>>2);
  }
  s[n-1] = l[i] - (h[i-1]>>1);

  for(i=0;i<n/2;i++) {
    int i2 = i<<1;
    s[i2+1] = h[i] + (s[i2]+s[i2+2])/2;
  }
}
#endif

/* }}} */
/* {{{ 5/3 */

#ifdef _5_3_
/* entropias
  lena     144555
  barb     166772
  boats    151653
  zelda    132466
  goldhill 160518
  fear     694599
*/

char transform_name[40]="5/3 Transform";

void TransformStep_Even(int n, TYPE s[], TYPE l[], TYPE h[]) {
  int i;
  for(i=0;i<n/2-1;i++) {
    int i2 = i<<1;
    h[i] = s[i2+1] - ((s[i2]+s[i2+2])>>1);
  }
  h[i] = s[n-1] - s[n-2];

  l[0] = s[0] + ((h[0]+1)>>1);
  for(i=1;i<n/2;i++) {
    int i2 = i<<1;
    l[i] = s[i2] + ((h[i]+h[i-1]+2)>>2);
  }
}
void i_TransformStep_Even(int n, TYPE s[], TYPE l[], TYPE h[]) {
  int i;
  s[0] = l[0] - ((h[0]+1)>>1);
  for(i=1;i<n/2;i++) {
    int i2 = i<<1;
    s[i2] = l[i] - ((h[i]+h[i-1]+2)>>2);
  }

  for(i=0;i<n/2-1;i++) {
    int i2 = i<<1;
    s[i2+1] = h[i] + ((s[i2]+s[i2+2])>>1);
  }
  s[n-1] = h[i] + s[n-2];
}
void TransformStep_Odd(int n, TYPE s[], TYPE l[], TYPE h[]) {
  int i;
  for(i=0;i<n/2;i++) {
    int i2 = i<<1;
    h[i] = s[i2+1] - ((s[i2]+s[i2+2])>>1);
  }

  l[0] = s[0] + ((h[0]+1)>>1);
  for(i=1;i<n/2;i++) {
    int i2 = i<<1;
    l[i] = s[i2] + ((h[i]+h[i-1]+2)>>2);
  }
  l[i] = s[n-1] + ((h[i-1]+1)>>1);
}
void i_TransformStep_Odd(int n, TYPE s[], TYPE l[], TYPE h[]) {
  int i;
  s[0] = l[0] - ((h[0]+1)>>1);
  for(i=1;i<n/2;i++) {
    int i2 = i<<1;
    s[i2] = l[i] - ((h[i]+h[i-1]+2)>>2);
  }
  s[n-1] = l[i] - ((h[i-1]+1)>>1);

  for(i=0;i<n/2;i++) {
    int i2 = i<<1;
    s[i2+1] = h[i] + ((s[i2]+s[i2+2])>>1);
  }
}
#endif

/* }}} */
/* {{{ 9/7-F (No Funciona) */

#ifdef _9_7_F_
/* entropias
  lena     
  barb     
  boats    
  zelda    
  goldhill 
  fear     
*/

char transform_name[40]="9/7-F Transform";

void TransformStep_Even(int n, TYPE s[], TYPE l[], TYPE h[]) {
  int i;
  for(i=0;i<n/2-1;i++) {
    int i2 = i<<1;
    h[i] = s[i2+1] + ((203*(-s[i2]-s[i2+2]+64))>>7);
  }
  h[i] = s[n-1] - s[n-2];

  l[0] = s[0] + ((h[0]+1)>>1);
  for(i=1;i<n/2;i++) {
    int i2 = i<<1;
    l[i] = s[i2] + ((217*(-h[i]-h[i-1]+2048))>>12);
  }

  for(i=0;i<n/2;i++) s[i] = l[i];
  for(i=n/2;i<n;i++) s[i] = h[i-n/2];

  for(i=0;i<n/2-1;i++) {
    int i2 = i<<1;
    h[i] = s[i2+1] + ((113*(s[i2]+s[i2+2]+64))>>7);
  }

  for(i=1;i<n/2;i++) {
    int i2 = i<<1;
    l[i] = s[i2] + ((1817*(h[i]+h[i-1]+2048))>>12);
  }
  
}
void i_TransformStep_Even(int n, TYPE s[], TYPE l[], TYPE h[]) {
  int i;

  for(i=1;i<n/2;i++) {
    int i2 = i<<1;
    s[i2] = l[i] - ((1817*(h[i]+h[i-1]+2048))>>12);
  }

  for(i=0;i<n/2-1;i++) {
    int i2 = i<<1;
    s[i2+1] = h[i] - ((113*(s[i2]+s[i2+2]+64))>>7);
  }

  for(i=0;i<n/2;i++) l[i] = s[i];
  for(i=n/2;i<n;i++) h[i-n/2] = s[i];

  s[0] = l[0] - ((h[0]+1)>>1);
  for(i=1;i<n/2;i++) {
    int i2 = i<<1;
    s[i2] = l[i] + ((217*(h[i]+h[i-1]+2048))>>12);
  }

  for(i=0;i<n/2-1;i++) {
    int i2 = i<<1;
    s[i2+1] = h[i] + ((203*(s[i2]+s[i2+2]+64))>>7);
  }
  s[n-1] = h[i] + s[n-2];
}
void TransformStep_Odd(int n, TYPE s[], TYPE l[], TYPE h[]) {
  int i;
  for(i=0;i<n/2;i++) {
    int i2 = i<<1;
    h[i] = s[i2+1] - ((203*(s[i2]+s[i2+2]+64))>>7);
  }

  l[0] = s[0] + ((h[0]+1)>>1);
  for(i=1;i<n/2;i++) {
    int i2 = i<<1;
    l[i] = s[i2] + ((217*(h[i]+h[i-1]+2048))>>12);
  }
  l[i] = s[n-1] + ((h[i-1]+1)>>1);
  /*
  for(i=0;i<n/2;i++) {
    int i2 = i<<1;
    h[i] = s[i2+1] + ((113*(s[i2]+s[i2+2]+64))>>7);
  }

  for(i=1;i<n/2;i++) {
    int i2 = i<<1;
    l[i] = s[i2] - ((1817*(h[i]+h[i-1]+2048))>>12);
  }
  */
}
void i_TransformStep_Odd(int n, TYPE s[], TYPE l[], TYPE h[]) {
  int i;
  /*
  for(i=1;i<n/2;i++) {
    int i2 = i<<1;
    s[i2] = l[i] + ((1817*(h[i]+h[i-1]+2048))>>12);
  }

  for(i=0;i<n/2;i++) {
    int i2 = i<<1;
    s[i2+1] = h[i] - ((113*(s[i2]+s[i2+2]+64))>>7);
  }
  */
  s[0] = l[0] - ((h[0]+1)>>1);
  for(i=1;i<n/2;i++) {
    int i2 = i<<1;
    s[i2] = l[i] - ((217*(h[i]+h[i-1]+2048))>>12);
  }
  s[n-1] = l[i] - ((h[i-1]+1)>>1);

  for(i=0;i<n/2;i++) {
    int i2 = i<<1;
    s[i2+1] = h[i] + ((203*(s[i2]+s[i2+2]+64))>>7);
  }
}
#endif

/* }}} */
/* {{{ 5/11-C */

#ifdef _5_11_C_
/* entropias
  lena     143297
  barb     163072
  boats    150741
  zelda    131388
  goldhill 160229
  fear     693737
*/

char transform_name[40]="5/11-C Transform";

void TransformStep_Even(int n, TYPE s[], TYPE l[], TYPE h[]) {
  int i;
  for(i=0;i<n/2-1;i++) {
    int i2 = i<<1;
    h[i] = s[i2+1] - ((s[i2]+s[i2+2])>>1);
  }
  h[i] = s[n-1] - s[n-2];

  l[0] = s[0] + ((h[0]+1)>>1);
  for(i=1;i<n/2;i++) {
    int i2 = i<<1;
    l[i] = s[i2] + ((h[i]+h[i-1]+2)>>2);
  }

  for(i=1; i<(n/2-2); i++) {
    h[i] += ((l[i+2] - l[i+1] - l[i] + l[i-1] + 8)>>4);
  }
}
void i_TransformStep_Even(int n, TYPE s[], TYPE l[], TYPE h[]) {
  int i;
  for(i=1; i<(n/2-2); i++) {
    h[i] -= ((l[i+2] - l[i+1] - l[i] + l[i-1] + 8)>>4);
  }

  s[0] = l[0] - ((h[0]+1)>>1);
  for(i=1;i<n/2;i++) {
    int i2 = i<<1;
    s[i2] = l[i] - ((h[i]+h[i-1]+2)>>2);
  }

  for(i=0;i<n/2-1;i++) {
    int i2 = i<<1;
    s[i2+1] = h[i] + ((s[i2]+s[i2+2])>>1);
  }
  s[n-1] = h[i] + s[n-2];
}
void TransformStep_Odd(int n, TYPE s[], TYPE l[], TYPE h[]) {
  int i;
  for(i=0;i<n/2;i++) {
    int i2 = i<<1;
    h[i] = s[i2+1] - ((s[i2]+s[i2+2])>>1);
  }

  l[0] = s[0] + ((h[0]+1)>>1);
  for(i=1;i<n/2;i++) {
    int i2 = i<<1;
    l[i] = s[i2] + ((h[i]+h[i-1]+2)>>2);
  }
  l[i] = s[n-1] + ((h[i-1]+1)>>1);

  for(i=1; i<(n/2-2); i++) {
    h[i] += ((l[i+2] - l[i+1] - l[i] + l[i-1] + 8)>>4);
  }
}
void i_TransformStep_Odd(int n, TYPE s[], TYPE l[], TYPE h[]) {
  int i;
  for(i=1; i<(n/2-2); i++) {
    h[i] -= ((l[i+2] - l[i+1] - l[i] + l[i-1] + 8)>>4);
  }

  s[0] = l[0] - ((h[0]+1)>>1);
  for(i=1;i<n/2;i++) {
    int i2 = i<<1;
    s[i2] = l[i] - ((h[i]+h[i-1]+2)>>2);
  }
  s[n-1] = l[i] - ((h[i-1]+1)>>1);

  for(i=0;i<n/2;i++) {
    int i2 = i<<1;
    s[i2+1] = h[i] + ((s[i2]+s[i2+2])>>1);
  }
}
#endif

/* }}} */
/* {{{ 5/11-A */

#ifdef _5_11_A_
/* entropias
  lena     143469
  barb     164676
  boats    150773
  zelda    131564
  goldhill 160078
  fear     692484
*/

char transform_name[40]="5/11-A Transform";

void TransformStep_Even(int n, TYPE s[], TYPE l[], TYPE h[]) {
  int i;
  for(i=0;i<n/2-1;i++) {
    int i2 = i<<1;
    h[i] = s[i2+1] - ((s[i2]+s[i2+2])>>1);
  }
  h[i] = s[n-1] - s[n-2];

  l[0] = s[0] + ((h[0]+1)>>1);
  for(i=1;i<n/2;i++) {
    int i2 = i<<1;
    l[i] = s[i2] + ((h[i]+h[i-1]+2)>>2);
  }

  for(i=1; i<(n/2-2); i++) {
    h[i] += ((l[i+2] - l[i+1] - l[i] + l[i-1] + 16)>>5);
  }
}
void i_TransformStep_Even(int n, TYPE s[], TYPE l[], TYPE h[]) {
  int i;
  for(i=1; i<(n/2-2); i++) {
    h[i] -= ((l[i+2] - l[i+1] - l[i] + l[i-1] + 16)>>5);
  }

  s[0] = l[0] - ((h[0]+1)>>1);
  for(i=1;i<n/2;i++) {
    int i2 = i<<1;
    s[i2] = l[i] - ((h[i]+h[i-1]+2)>>2);
  }

  for(i=0;i<n/2-1;i++) {
    int i2 = i<<1;
    s[i2+1] = h[i] + ((s[i2]+s[i2+2])>>1);
  }
  s[n-1] = h[i] + s[n-2];
}
void TransformStep_Odd(int n, TYPE s[], TYPE l[], TYPE h[]) {
  int i;
  for(i=0;i<n/2;i++) {
    int i2 = i<<1;
    h[i] = s[i2+1] - ((s[i2]+s[i2+2])>>1);
  }

  l[0] = s[0] + ((h[0]+1)>>1);
  for(i=1;i<n/2;i++) {
    int i2 = i<<1;
    l[i] = s[i2] + ((h[i]+h[i-1]+2)>>2);
  }
  l[i] = s[n-1] + ((h[i-1]+1)>>1);

  for(i=1; i<(n/2-2); i++) {
    h[i] += ((l[i+2] - l[i+1] - l[i] + l[i-1] + 16)>>5);
  }
}
void i_TransformStep_Odd(int n, TYPE s[], TYPE l[], TYPE h[]) {
  int i;
  for(i=1; i<(n/2-2); i++) {
    h[i] -= ((l[i+2] - l[i+1] - l[i] + l[i-1] + 16)>>5);
  }

  s[0] = l[0] - ((h[0]+1)>>1);
  for(i=1;i<n/2;i++) {
    int i2 = i<<1;
    s[i2] = l[i] - ((h[i]+h[i-1]+2)>>2);
  }
  s[n-1] = l[i] - ((h[i-1]+1)>>1);

  for(i=0;i<n/2;i++) {
    int i2 = i<<1;
    s[i2+1] = h[i] + ((s[i2]+s[i2+2])>>1);
  }
}
#endif

/* }}} */
/* {{{ 33 */

#ifdef _33_
/* entropias
  lena     142723
  barb     161504
  boats    150592
  zelda    130486
  goldhill 160009
  fear     692452
*/

char transform_name[40]="33 Transform";

void TransformStep_Even(int n, TYPE s[], TYPE l[], TYPE h[]) {
  int i;
  h[0] = s[1] - (s[0]+s[2])/2;
  for(i=1;i<n/2-2;i++) {
    int i2 = i<<1;
    h[i] = s[i2+1] - (9*(s[i2]+s[i2+2]) - (s[i2-2]+s[i2+4]))/16;
  }
  h[n/2-2] = s[n-3] - (s[n-4]+s[n-2])/2;
  h[n/2-1] = s[n-1] - s[n-2];

  l[0] = s[0] + ((h[0])>>1);
  l[1] = s[2] + ((h[0]+h[1])>>2);
  for(i=2; i<n/2-1; i++) {
    int i2 = i<<1;
    l[i] = s[i2] + ((-h[i-2]+9*(h[i-1]+h[i])-h[i+1]+8)>>5);
  }
  l[n/2-1] = s[n-2] + ((h[n/2-2]+h[n/2-1])>>2);
}
void i_TransformStep_Even(int n, TYPE s[], TYPE l[], TYPE h[]) {
  int i;
  s[0] = l[0] - ((h[0])>>1);
  s[2] = l[1] - ((h[0]+h[1])>>2);
  for(i=2; i<n/2-1; i++) {
    int i2 = i<<1;
    s[i2] = l[i] - ((-h[i-2]+9*(h[i-1]+h[i])-h[i+1]+8)>>5);
  }
  s[n-2] = l[n/2-1] - ((h[n/2-2]+h[n/2-1])>>2);

  s[1] = h[0] + (s[0]+s[2])/2;
  for(i=1;i<n/2-2;i++) {
    int i2 = i<<1;
    s[i2+1] = h[i] + (9*(s[i2]+s[i2+2]) - (s[i2-2]+s[i2+4]))/16;
  }
  s[n-3] = h[n/2-2] + (s[n-4]+s[n-2])/2;
  s[n-1] = h[n/2-1] + s[n-2];
}
void TransformStep_Odd(int n, TYPE s[], TYPE l[], TYPE h[]) {
  int i;
  h[0] = s[1] - (s[0]+s[2])/2;
  for(i=1;i<n/2-1;i++) {
    int i2 = i<<1;
    h[i] = s[i2+1] - (9*(s[i2]+s[i2+2]) - (s[i2-2]+s[i2+4]))/16;
  }
  h[n/2-1] = s[n-2] - (s[n-3]+s[n-1])/2;

  l[0] = s[0] + (h[0]>>1);
  l[1] = s[2] + ((h[0]+h[1])>>2);
  for(i=2; i<n/2-1; i++) {
    int i2 = i<<1;
    l[i] = s[i2] + ((-h[i-2]+9*(h[i-1]+h[i])-h[i+1]+8)>>5);
  }
  l[n/2-1] = s[n-3] + ((h[n/2-2]+h[n/2-1])>>2);
  l[n/2] = s[n-1] + (h[n/2-1]>>1);
}
void i_TransformStep_Odd(int n, TYPE s[], TYPE l[], TYPE h[]) {
  int i;
  s[0] = l[0] - (h[0]>>1);
  s[2] = l[1] - ((h[0]+h[1])>>2);
  for(i=2; i<n/2-1; i++) {
    int i2 = i<<1;
    s[i2] = l[i] - ((-h[i-2]+9*(h[i-1]+h[i])-h[i+1]+8)>>5);
  }
  s[n-3] = l[n/2-1] - ((h[n/2-2]+h[n/2-1])>>2);
  s[n-1] = l[n/2] - (h[n/2-1]>>1);

  s[1] = h[0] + (s[0]+s[2])/2;
  for(i=1;i<n/2-1;i++) {
    int i2 = i<<1;
    s[i2+1] = h[i] + (9*(s[i2]+s[i2+2]) - (s[i2-2]+s[i2+4]))/16;
  }
  s[n-2] = h[n/2-1] + (s[n-3]+s[n-1])/2;
}
#endif

#ifdef _33b_
/* entropias
  lena     142767
  barb     161578
  boats    150675
  zelda    130587
  goldhill 160038
  fear     692418
*/
char transform_name[40]="33 Transform";
void TransformStep_Even(int n, TYPE s[], TYPE l[], TYPE h[]) {
  int i;
  h[0] = (s[0]+s[2])/2 - s[1];
  for(i=1;i<n/2-2;i++) {
    int i2 = i<<1;
    h[i] = (9*(s[i2]+s[i2+2]) - (s[i2-2]+s[i2+4]))/16 - s[i2+1];
  }
  h[n/2-2] = (s[n-4]+s[n-2])/2 - s[n-3];
  h[n/2-1] = s[n-2] - s[n-1];

  l[0] = s[0] - ((h[0]+1)>>1);
  l[1] = s[2] - ((h[0]+h[1]+1)>>2);
  for(i=2; i<n/2-1; i++) {
    int i2 = i<<1;
    l[i] = s[i2] - ((-h[i-2]+9*(h[i-1]+h[i])-h[i+1]+8)>>5);
  }
  l[n/2-1] = s[n-2] - ((h[n/2-2]+h[n/2-1]+1)>>2);
}
void i_TransformStep_Even(int n, TYPE s[], TYPE l[], TYPE h[]) {
  int i;
  s[0] = l[0] - ((h[0])>>1);
  s[2] = l[1] - ((h[0]+h[1])>>2);
  for(i=2; i<n/2-1; i++) {
    int i2 = i<<1;
    s[i2] = l[i] - ((-h[i-2]+9*(h[i-1]+h[i])-h[i+1])>>5);
  }
  s[n-2] = l[n/2-1] - ((h[n/2-2]+h[n/2-1])>>2);

  s[1] = h[0] + (s[0]+s[2])/2;
  for(i=1;i<n/2-2;i++) {
    int i2 = i<<1;
    s[i2+1] = h[i] + (9*(s[i2]+s[i2+2]) - (s[i2-2]+s[i2+4]))/16;
  }
  s[n-3] = h[n/2-2] + (s[n-4]+s[n-2])/2;
  s[n-1] = h[n/2-1] + s[n-2];
}
void TransformStep_Odd(int n, TYPE s[], TYPE l[], TYPE h[]) {
  int i;
  h[0] = s[1] - (s[0]+s[2])/2;
  for(i=1;i<n/2-1;i++) {
    int i2 = i<<1;
    h[i] = s[i2+1] - (9*(s[i2]+s[i2+2]) - (s[i2-2]+s[i2+4]))/16;
  }
  h[n/2-1] = s[n-2] - (s[n-3]+s[n-1])/2;
  
  l[0] = s[0] + ((h[0])>>1);
  l[1] = s[2] + ((h[0]+h[1])>>2);
  for(i=2; i<n/2-1; i++) {
    int i2 = i<<1;
    l[i] = s[i2] + ((-h[i-2]+9*(h[i-1]+h[i])-h[i+1])>>5);
  }
  l[n/2-1] = s[n-3] + ((h[n/2-2]+h[n/2-1])>>2);
  l[n/2] = s[n-1] + ((h[n/2-1])>>1);
}
void i_TransformStep_Odd(int n, TYPE s[], TYPE l[], TYPE h[]) {
  int i;
  s[0] = l[0] - ((h[0])>>1);
  s[2] = l[1] - ((h[0]+h[1])>>2);
  for(i=2; i<n/2-1; i++) {
    int i2 = i<<1;
    s[i2] = l[i] - ((-h[i-2]+9*(h[i-1]+h[i])-h[i+1])>>5);
  }
  s[n-3] = l[n/2-1] - ((h[n/2-2]+h[n/2-1])>>2);
  s[n-1] = l[n/2] - ((h[n/2-1])>>1);

  s[1] = h[0] + (s[0]+s[2])/2;
  for(i=1;i<n/2-1;i++) {
    int i2 = i<<1;
    s[i2+1] = h[i] + (9*(s[i2]+s[i2+2]) - (s[i2-2]+s[i2+4]))/16;
  }
  s[n-2] = h[n/2-1] + (s[n-3]+s[n-1])/2;
}
#endif

#ifdef _33c_
/* entropias
  lena     
  barb     
  boats    
  zelda    
  goldhill 
  fear     
*/
void TransformStep_Even(int n, TYPE s[], TYPE l[], TYPE h[]) {
  int i;
  h[0] = s[1] - (s[0]+s[2])/2;
  for(i=1;i<n/2-2;i++) {
    int i2 = i<<1;
    h[i] = s[i2+1] - (9*(s[i2]+s[i2+2]) - (s[i2-2]+s[i2+4]))/16;
  }
  h[n/2-2] = s[n-3] - (s[n-4]+s[n-2])/2;
  h[n/2-1] = s[n-1] - s[n-2];

  l[0] = s[0] + ((h[0])>>1);
  l[1] = s[2] + ((h[0]+h[1])>>2);
  for(i=2; i<n/2-1; i++) {
    int i2 = i<<1;
    l[i] = s[i2] + ((-h[i-2]+9*(h[i-1]+h[i])-h[i+1])>>5);
  }
  l[n/2-1] = s[n-2] + ((h[n/2-2]+h[n/2-1])>>2);
}
void i_TransformStep_Even(int n, TYPE s[], TYPE l[], TYPE h[]) {
  int i;
  s[0] = l[0] - ((h[0])>>1);
  s[2] = l[1] - ((h[0]+h[1])>>2);
  for(i=2; i<n/2-1; i++) {
    int i2 = i<<1;
    s[i2] = l[i] - ((-h[i-2]+9*(h[i-1]+h[i])-h[i+1])>>5);
  }
  s[n-2] = l[n/2-1] - ((h[n/2-2]+h[n/2-1])>>2);

  s[1] = h[0] + (s[0]+s[2])/2;
  for(i=1;i<n/2-2;i++) {
    int i2 = i<<1;
    s[i2+1] = h[i] + (9*(s[i2]+s[i2+2]) - (s[i2-2]+s[i2+4]))/16;
  }
  s[n-3] = h[n/2-2] + (s[n-4]+s[n-2])/2;
  s[n-1] = h[n/2-1] + s[n-2];
}
void TransformStep_Odd(int n, TYPE s[], TYPE l[], TYPE h[]) {
  int i;
  h[0] = s[1] - (s[0]+s[2])/2;
  for(i=1;i<n/2-1;i++) {
    int i2 = i<<1;
    h[i] = s[i2+1] - (9*(s[i2]+s[i2+2]) - (s[i2-2]+s[i2+4]))/16;
  }
  h[n/2-1] = s[n-2] - (s[n-3]+s[n-1])/2;
  
  l[0] = s[0] + (h[0]>>1);
  l[1] = s[2] + ((h[0]+h[1])>>2);
  for(i=2; i<n/2-1; i++) {
    int i2 = i<<1;
    l[i] = s[i2] + ((-h[i-2]+9*(h[i-1]+h[i])-h[i+1])>>5);
  }
  l[n/2-1] = s[n-3] + ((h[n/2-2]+h[n/2-1])>>2);
  l[n/2] = s[n-1] + (h[n/2-1]>>1);
}
void i_TransformStep_Odd(int n, TYPE s[], TYPE l[], TYPE h[]) {
  int i;
  s[0] = l[0] - (h[0]>>1);
  s[2] = l[1] - ((h[0]+h[1])>>2);
  for(i=2; i<n/2-1; i++) {
    int i2 = i<<1;
    s[i2] = l[i] - ((-h[i-2]+9*(h[i-1]+h[i])-h[i+1])>>5);
  }
  s[n-3] = l[n/2-1] - ((h[n/2-2]+h[n/2-1])>>2);
  s[n-1] = l[n/2] - (h[n/2-1]>>1);

  s[1] = h[0] + (s[0]+s[2])/2;
  for(i=1;i<n/2-1;i++) {
    int i2 = i<<1;
    s[i2+1] = h[i] + (9*(s[i2]+s[i2+2]) - (s[i2-2]+s[i2+4]))/16;
  }
  s[n-2] = h[n/2-1] + (s[n-3]+s[n-1])/2;
}
#endif

/* }}} */
/* {{{ 13/7-T */

#ifdef _13_7_T_
/* entropias
  lena     142971
  barb     161994
  boats    150866
  zelda    131412
  goldhill 160027
  fear     692638
*/

#ifndef _COLOR_
char transform_name[40]="13/7-T Transform";
#else /* _COLOR_ */
char transform_name_color[40]="13/7-T Transform";
#endif /* _COLOR_ */

#ifndef _COLOR_
void trans_step_even(int n,int s[], int l[], int h[]) {
#else
void trans_step_even_rgb(int n, struct RGB s[], struct RGB l[], struct RGB h[]) {
#endif /* _COLOR_ */
  int i;
#ifndef _COLOR_
  //h[0] = s[1] - ((s[0]+s[2]+1)>>1);
  h[0] = s[1] - s[0];
#else /* _COLOR_ */
  h[0].r = s[1].r - s[0].r;
  h[0].g = s[1].g - s[0].g;
  h[0].b = s[1].b - s[0].b;
#endif /* _COLOR_ */
  if(n>2) {
    for(i=1;i<n/2-2;i++) {
      int i2 = i<<1;
#ifndef _COLOR_
      h[i] = s[i2+1] - ((9*(s[i2]+s[i2+2]) - (s[i2-2]+s[i2+4])+8)>>4);
#else /* _COLOR_ */
      h[i].r = s[i2+1].r - ((9*(s[i2].r+s[i2+2].r) - (s[i2-2].r+s[i2+4].r)+8)>>4);
      h[i].g = s[i2+1].g - ((9*(s[i2].g+s[i2+2].g) - (s[i2-2].g+s[i2+4].g)+8)>>4);
      h[i].b = s[i2+1].b - ((9*(s[i2].b+s[i2+2].b) - (s[i2-2].b+s[i2+4].b)+8)>>4);
#endif /* _COLOR_ */
    }
#ifndef _COLOR_
    h[n/2-2] = s[n-3] - ((s[n-4]+s[n-2]+1)>>1);
    h[n/2-1] = s[n-1] - s[n-2];
#else /* _COLOR_ */
    h[n/2-2].r = s[n-3].r - ((s[n-4].r+s[n-2].r+1)>>1);
    h[n/2-2].g = s[n-3].g - ((s[n-4].g+s[n-2].g+1)>>1);
    h[n/2-2].b = s[n-3].b - ((s[n-4].b+s[n-2].b+1)>>1);
    h[n/2-1].r = s[n-1].r - s[n-2].r;
    h[n/2-1].g = s[n-1].g - s[n-2].g;
    h[n/2-1].b = s[n-1].b - s[n-2].b;
#endif /* _COLOR_ */
  }

#ifndef _COLOR_
  l[0] = s[0] + ((h[0])>>1);
#else _COLOR_
  l[0].r = s[0].r + ((h[0].r)>>1);
  l[0].g = s[0].g + ((h[0].g)>>1);
  l[0].b = s[0].b + ((h[0].b)>>1);
#endif /* _COLOR_ */
  if(n>2) {
#ifndef _COLOR_
    l[1] = s[2] + ((h[0]+h[1]+1)>>2);
#else /* _COLOR_ */
    l[1].r = s[2].r + ((h[0].r+h[1].r+1)>>2);
    l[1].g = s[2].g + ((h[0].g+h[1].g+1)>>2);
    l[1].b = s[2].b + ((h[0].b+h[1].b+1)>>2);
#endif /* _COLOR_ */
    for(i=2; i<n/2-1; i++) {
      int i2 = i<<1;
#ifndef _COLOR_
      l[i] = s[i2] + ((-h[i-2]+9*(h[i-1]+h[i])-h[i+1]+16)>>5);
#else /* _COLOR_ */
      l[i].r = s[i2].r + ((-h[i-2].r+9*(h[i-1].r+h[i].r)-h[i+1].r+16)>>5);
      l[i].g = s[i2].g + ((-h[i-2].g+9*(h[i-1].g+h[i].g)-h[i+1].g+16)>>5);
      l[i].b = s[i2].b + ((-h[i-2].b+9*(h[i-1].b+h[i].b)-h[i+1].b+16)>>5);
#endif /* _COLOR_ */
    }
#ifndef _COLOR_
    l[n/2-1] = s[n-2] + ((h[n/2-2]+h[n/2-1]+1)>>2);
#else /* _COLOR_ */
    l[n/2-1].r = s[n-2].r + ((h[n/2-2].r+h[n/2-1].r+1)>>2);
    l[n/2-1].g = s[n-2].g + ((h[n/2-2].g+h[n/2-1].g+1)>>2);
    l[n/2-1].b = s[n-2].b + ((h[n/2-2].b+h[n/2-1].b+1)>>2);
#endif /* _COLOR_ */
  }
}

#ifndef _COLOR_
void itrans_step_even(int n, int s[], int l[], int h[]) {
#else
void itrans_step_even_rgb(int n, struct RGB s[], struct RGB l[], struct RGB h[]) {
#endif /* _COLOR_ */
  int i;
#ifndef _COLOR_
  s[0] = l[0] - ((h[0])>>1);
#else /* _COLOR_ */
  s[0].r = l[0].r - ((h[0].r)>>1);
  s[0].g = l[0].g - ((h[0].g)>>1);
  s[0].b = l[0].b - ((h[0].b)>>1);
#endif /* _COLOR_ */
  if(n>2) {
#ifndef _COLOR_
    s[2] = l[1] - ((h[0]+h[1]+1)>>2);
#else /* _COLOR_ */
    s[2].r = l[1].r - ((h[0].r+h[1].r+1)>>2);
    s[2].g = l[1].g - ((h[0].g+h[1].g+1)>>2);
    s[2].b = l[1].b - ((h[0].b+h[1].b+1)>>2);
#endif /* _COLOR_ */
    for(i=2; i<n/2-1; i++) {
      int i2 = i<<1;
#ifndef _COLOR_
      s[i2] = l[i] - ((-h[i-2]+9*(h[i-1]+h[i])-h[i+1]+16)>>5);
#else /* _COLOR_ */
      s[i2].r = l[i].r - ((-h[i-2].r+9*(h[i-1].r+h[i].r)-h[i+1].r+16)>>5);
      s[i2].g = l[i].g - ((-h[i-2].g+9*(h[i-1].g+h[i].g)-h[i+1].g+16)>>5);
      s[i2].b = l[i].b - ((-h[i-2].b+9*(h[i-1].b+h[i].b)-h[i+1].b+16)>>5);
#endif /* _COLOR_ */
    }
#ifndef _COLOR_
    s[n-2] = l[n/2-1] - ((h[n/2-2]+h[n/2-1]+1)>>2);
#else /* _COLOR_ */
    s[n-2].r = l[n/2-1].r - ((h[n/2-2].r+h[n/2-1].r+1)>>2);
    s[n-2].g = l[n/2-1].g - ((h[n/2-2].g+h[n/2-1].g+1)>>2);
    s[n-2].b = l[n/2-1].b - ((h[n/2-2].b+h[n/2-1].b+1)>>2);
#endif /* _COLOR_ */
  }

#ifndef _COLOR_
  //s[1] = h[0] + ((s[0]+s[2]+1)>>1);
  s[1] = h[0] + s[0];
#else /* _COLOR_ */
  s[1].r = h[0].r + s[0].r;
  s[1].g = h[0].g + s[0].g;
  s[1].b = h[0].b + s[0].b;
#endif /* _COLOR_ */
  if(n>2) {
    for(i=1;i<n/2-2;i++) {
      int i2 = i<<1;
#ifndef _COLOR_
      s[i2+1] = h[i] + ((9*(s[i2]+s[i2+2]) - (s[i2-2]+s[i2+4])+8)>>4);
#else /* _COLOR_ */
      s[i2+1].r = h[i].r + ((9*(s[i2].r+s[i2+2].r) - (s[i2-2].r+s[i2+4].r)+8)>>4);
      s[i2+1].g = h[i].g + ((9*(s[i2].g+s[i2+2].g) - (s[i2-2].g+s[i2+4].g)+8)>>4);
      s[i2+1].b = h[i].b + ((9*(s[i2].b+s[i2+2].b) - (s[i2-2].b+s[i2+4].b)+8)>>4);
#endif /* _COLOR_ */
    }
#ifndef _COLOR_
    s[n-3] = h[n/2-2] + ((s[n-4]+s[n-2]+1)>>1);
    s[n-1] = h[n/2-1] + s[n-2];
#else /* _COLOR_ */
    s[n-3].r = h[n/2-2].r + ((s[n-4].r+s[n-2].r+1)>>1);
    s[n-3].g = h[n/2-2].g + ((s[n-4].g+s[n-2].g+1)>>1);
    s[n-3].b = h[n/2-2].b + ((s[n-4].b+s[n-2].b+1)>>1);
    s[n-1].r = h[n/2-1].r + s[n-2].r;
    s[n-1].g = h[n/2-1].g + s[n-2].g;
    s[n-1].b = h[n/2-1].b + s[n-2].b;
#endif /* _COLOR_ */
  }
}

#ifndef _COLOR_
void trans_step_odd(int n, int s[], int l[], int h[]) {
#else
void trans_step_odd_rgb(int n, struct RGB s[], struct RGB l[], struct RGB h[]) {
#endif /* _COLOR_ */
  int i;
#ifndef _COLOR_
  h[0] = s[1] - ((s[0]+s[2]+1)>>1);
#else /* _COLOR_ */
  h[0].r = s[1].r - ((s[0].r+s[2].r+1)>>1);
  h[0].g = s[1].g - ((s[0].g+s[2].g+1)>>1);
  h[0].b = s[1].b - ((s[0].b+s[2].b+1)>>1);
#endif /* _COLOR_ */
  for(i=1;i<n/2-1;i++) {
    int i2 = i<<1;
#ifndef _COLOR_
    h[i] = s[i2+1] - ((9*(s[i2]+s[i2+2]) - (s[i2-2]+s[i2+4])+8)>>4);
#else /* _COLOR_ */
    h[i].r = s[i2+1].r - ((9*(s[i2].r+s[i2+2].r) - (s[i2-2].r+s[i2+4].r)+8)>>4);
    h[i].g = s[i2+1].g - ((9*(s[i2].g+s[i2+2].g) - (s[i2-2].g+s[i2+4].g)+8)>>4);
    h[i].b = s[i2+1].b - ((9*(s[i2].b+s[i2+2].b) - (s[i2-2].b+s[i2+4].b)+8)>>4);
#endif /* _COLOR_ */
  }
#ifndef _COLOR_
  h[n/2-1] = s[n-2] - ((s[n-3]+s[n-1]+1)>>1);  

  l[0] = s[0] + (h[0]>>1);
  l[1] = s[2] + ((h[0]+h[1]+1)>>2);
#else /* _COLOR_ */
  h[n/2-1].r = s[n-2].r - ((s[n-3].r+s[n-1].r+1)>>1);  
  h[n/2-1].g = s[n-2].g - ((s[n-3].g+s[n-1].g+1)>>1);  
  h[n/2-1].b = s[n-2].b - ((s[n-3].b+s[n-1].b+1)>>1);  

  l[0].r = s[0].r + (h[0].r>>1);
  l[0].g = s[0].g + (h[0].g>>1);
  l[0].b = s[0].b + (h[0].b>>1);
  l[1].r = s[2].r + ((h[0].r+h[1].r+1)>>2);
  l[1].g = s[2].g + ((h[0].g+h[1].g+1)>>2);
  l[1].b = s[2].b + ((h[0].b+h[1].b+1)>>2);
#endif /* _COLOR_ */

  for(i=2; i<n/2-1; i++) {
    int i2 = i<<1;
#ifndef _COLOR_
    l[i] = s[i2] + ((-h[i-2]+9*(h[i-1]+h[i])-h[i+1]+16)>>5);
#else /* _COLOR_ */
    l[i].r = s[i2].r + ((-h[i-2].r+9*(h[i-1].r+h[i].r)-h[i+1].r+16)>>5);
    l[i].g = s[i2].g + ((-h[i-2].g+9*(h[i-1].g+h[i].g)-h[i+1].g+16)>>5);
    l[i].b = s[i2].b + ((-h[i-2].b+9*(h[i-1].b+h[i].b)-h[i+1].b+16)>>5);
#endif /* _COLOR_ */
  }
#ifndef _COLOR_
  l[n/2-1] = s[n-3] + ((h[n/2-2]+h[n/2-1]+1)>>2);
  l[n/2] = s[n-1] + (h[n/2-1]>>1);
#else /* _COLOR_ */
  l[n/2-1].r = s[n-3].r + ((h[n/2-2].r+h[n/2-1].r+1)>>2);
  l[n/2-1].g = s[n-3].g + ((h[n/2-2].g+h[n/2-1].g+1)>>2);
  l[n/2-1].b = s[n-3].b + ((h[n/2-2].b+h[n/2-1].b+1)>>2);
  l[n/2].r = s[n-1].r + (h[n/2-1].r>>1);
  l[n/2].g = s[n-1].g + (h[n/2-1].g>>1);
  l[n/2].b = s[n-1].b + (h[n/2-1].b>>1);
#endif /* _COLOR_ */
}

#ifndef _COLOR_
void itrans_step_odd(int n, int s[], int l[], int h[]) {
#else
void itrans_step_odd_rgb(int n, struct RGB s[], struct RGB l[], struct RGB h[]) {
#endif /* _COLOR_ */
  int i;
#ifndef _COLOR_
  s[0] = l[0] - (h[0]>>1);
  s[2] = l[1] - ((h[0]+h[1]+1)>>2);
#else /* _COLOR_ */
  s[0].r = l[0].r - (h[0].r>>1);
  s[0].g = l[0].g - (h[0].g>>1);
  s[0].b = l[0].b - (h[0].b>>1);
  s[2].r = l[1].r - ((h[0].r+h[1].r+1)>>2);
  s[2].g = l[1].g - ((h[0].g+h[1].g+1)>>2);
  s[2].b = l[1].b - ((h[0].b+h[1].b+1)>>2);
#endif /* _COLOR_ */
  for(i=2; i<n/2-1; i++) {
    int i2 = i<<1;
#ifndef _COLOR_
    s[i2] = l[i] - ((-h[i-2]+9*(h[i-1]+h[i])-h[i+1]+16)>>5);
#else /* _COLOR_ */
    s[i2].r = l[i].r - ((-h[i-2].r+9*(h[i-1].r+h[i].r)-h[i+1].r+16)>>5);
    s[i2].g = l[i].g - ((-h[i-2].g+9*(h[i-1].g+h[i].g)-h[i+1].g+16)>>5);
    s[i2].b = l[i].b - ((-h[i-2].b+9*(h[i-1].b+h[i].b)-h[i+1].b+16)>>5);
#endif /* _COLOR_ */
  }
#ifndef _COLOR_
  s[n-3] = l[n/2-1] - ((h[n/2-2]+h[n/2-1]+1)>>2);
  s[n-1] = l[n/2] - (h[n/2-1]>>1);

  s[1] = h[0] + ((s[0]+s[2]+1)>>1);
#else /* _COLOR_ */
  s[n-3].r = l[n/2-1].r - ((h[n/2-2].r+h[n/2-1].r+1)>>2);
  s[n-3].g = l[n/2-1].g - ((h[n/2-2].g+h[n/2-1].g+1)>>2);
  s[n-3].b = l[n/2-1].b - ((h[n/2-2].b+h[n/2-1].b+1)>>2);
  s[n-1].r = l[n/2].r - (h[n/2-1].r>>1);
  s[n-1].g = l[n/2].g - (h[n/2-1].g>>1);
  s[n-1].b = l[n/2].b - (h[n/2-1].b>>1);

  s[1].r = h[0].r + ((s[0].r+s[2].r+1)>>1);
  s[1].g = h[0].g + ((s[0].g+s[2].g+1)>>1);
  s[1].b = h[0].b + ((s[0].b+s[2].b+1)>>1);
#endif /* _COLOR_ */
  for(i=1;i<n/2-1;i++) {
    int i2 = i<<1;
#ifndef _COLOR_
    s[i2+1] = h[i] + ((9*(s[i2]+s[i2+2]) - (s[i2-2]+s[i2+4])+8)>>4);
#else /* _COLOR_ */
    s[i2+1].r = h[i].r + ((9*(s[i2].r+s[i2+2].r) - (s[i2-2].r+s[i2+4].r)+8)>>4);
    s[i2+1].g = h[i].g + ((9*(s[i2].g+s[i2+2].g) - (s[i2-2].g+s[i2+4].g)+8)>>4);
    s[i2+1].b = h[i].b + ((9*(s[i2].b+s[i2+2].b) - (s[i2-2].b+s[i2+4].b)+8)>>4);
#endif /* _COLOR_ */
  }
#ifndef _COLOR_
  s[n-2] = h[n/2-1] + ((s[n-3]+s[n-1]+1)>>1);
#else /* _COLOR_ */
  s[n-2].r = h[n/2-1].r + ((s[n-3].r+s[n-1].r+1)>>1);
  s[n-2].g = h[n/2-1].g + ((s[n-3].g+s[n-1].g+1)>>1);
  s[n-2].b = h[n/2-1].b + ((s[n-3].b+s[n-1].b+1)>>1);
#endif /* _COLOR_ */
}
#endif


/* }}} */
/* {{{ 13/7-C */

#ifdef _13_7_C_
/* entropias
  lena     143240
  barb     161671
  boats    151145
  zelda    131524
  goldhill 160332
  fear     693706
*/

char transform_name[40]="13/7-C Transform";

void TransformStep_Even(int n, TYPE s[], TYPE l[], TYPE h[]) {
  int i;
  //h[0] = s[1] - ((s[0]+s[2]+1)>>1);
  h[0] = s[1] - s[0];
  if(n>2) {
    for(i=1;i<n/2-2;i++) {
      int i2 = i<<1;
      h[i] = s[i2+1] - ((9*(s[i2]+s[i2+2]) - (s[i2-2]+s[i2+4])+8)>>4);
    }
    h[n/2-2] = s[n-3] - ((s[n-4]+s[n-2]+1)>>1);
    h[n/2-1] = s[n-1] - s[n-2];
  }

  l[0] = s[0] + ((h[0])>>1);
  if(n>2) {
    l[1] = s[2] + ((h[0]+h[1]+1)>>2);
    for(i=2; i<n/2-1; i++) {
      int i2 = i<<1;
      l[i] = s[i2] + ((-h[i-2]+5*(h[i-1]+h[i])-h[i+1]+8)>>4);
    }
    l[n/2-1] = s[n-2] + ((h[n/2-2]+h[n/2-1]+1)>>2);
  }
}
void i_TransformStep_Even(int n, TYPE s[], TYPE l[], TYPE h[]) {
  int i;
  s[0] = l[0] - ((h[0])>>1);
  if(n>2) {
    s[2] = l[1] - ((h[0]+h[1]+1)>>2);
    for(i=2; i<n/2-1; i++) {
      int i2 = i<<1;
      s[i2] = l[i] - ((-h[i-2]+5*(h[i-1]+h[i])-h[i+1]+8)>>4);
    }
    s[n-2] = l[n/2-1] - ((h[n/2-2]+h[n/2-1]+1)>>2);
  }

  //s[1] = h[0] + ((s[0]+s[2]+1)>>1);
  s[1] = h[0] + s[0];
  if(n>2) {
    for(i=1;i<n/2-2;i++) {
      int i2 = i<<1;
      s[i2+1] = h[i] + ((9*(s[i2]+s[i2+2]) - (s[i2-2]+s[i2+4])+8)>>4);
    }
    s[n-3] = h[n/2-2] + ((s[n-4]+s[n-2]+1)>>1);
    s[n-1] = h[n/2-1] + s[n-2];
  }
}
void TransformStep_Odd(int n, TYPE s[], TYPE l[], TYPE h[]) {
  int i;
  h[0] = s[1] - ((s[0]+s[2]+1)>>1);
  for(i=1;i<n/2-1;i++) {
    int i2 = i<<1;
    h[i] = s[i2+1] - ((9*(s[i2]+s[i2+2]) - (s[i2-2]+s[i2+4])+8)>>4);
  }
  h[n/2-1] = s[n-2] - ((s[n-3]+s[n-1]+1)>>1);
  
  l[0] = s[0] + (h[0]>>1);
  l[1] = s[2] + ((h[0]+h[1]+1)>>2);
  for(i=2; i<n/2-1; i++) {
    int i2 = i<<1;
    l[i] = s[i2] + ((-h[i-2]+5*(h[i-1]+h[i])-h[i+1]+8)>>4);
  }
  l[n/2-1] = s[n-3] + ((h[n/2-2]+h[n/2-1]+1)>>2);
  l[n/2] = s[n-1] + (h[n/2-1]>>1);
}
void i_TransformStep_Odd(int n, TYPE s[], TYPE l[], TYPE h[]) {
  int i;
  s[0] = l[0] - (h[0]>>1);
  s[2] = l[1] - ((h[0]+h[1]+1)>>2);
  for(i=2; i<n/2-1; i++) {
    int i2 = i<<1;
    s[i2] = l[i] - ((-h[i-2]+5*(h[i-1]+h[i])-h[i+1]+8)>>4);
  }
  s[n-3] = l[n/2-1] - ((h[n/2-2]+h[n/2-1]+1)>>2);
  s[n-1] = l[n/2] - (h[n/2-1]>>1);

  s[1] = h[0] + ((s[0]+s[2]+1)>>1);
  for(i=1;i<n/2-1;i++) {
    int i2 = i<<1;
    s[i2+1] = h[i] + ((9*(s[i2]+s[i2+2]) - (s[i2-2]+s[i2+4])+8)>>4);
  }
  s[n-2] = h[n/2-1] + ((s[n-3]+s[n-1]+1)>>1);
}
#endif

/* }}} */
/* {{{ 9/7-M */

#ifdef _9_7_M_
/* entropias
  lena     143053
  barb     162969
  boats    150970
  zelda    131686
  goldhill 160040
  fear     693020
*/

char transform_name[40]="9/7-M Transform";

void TransformStep_Even(int n, TYPE s[], TYPE l[], TYPE h[]) {
  int i;
  h[0] = s[1] - ((s[0]+s[2])>>1);
  for(i=1;i<n/2-2;i++) {
    int i2 = i<<1;
    h[i] = s[i2+1] - ((9*(s[i2]+s[i2+2]) - (s[i2-2]+s[i2+4])+8)>>4);
  }
  h[n/2-2] = s[n-3] - ((s[n-4]+s[n-2])>>1);
  h[n/2-1] = s[n-1] - s[n-2];

  l[0] = s[0] + ((h[0]+1)>>1);
  for(i=1;i<n/2;i++) {
    int i2 = i<<1;
    l[i] = s[i2] + ((h[i]+h[i-1]+2)>>2);
  }
}
void i_TransformStep_Even(int n, TYPE s[], TYPE l[], TYPE h[]) {
  int i;
  s[0] = l[0] - ((h[0]+1)>>1);
  for(i=1;i<n/2;i++) {
    int i2 = i<<1;
    s[i2] = l[i] - ((h[i]+h[i-1]+2)>>2);
  }

  s[1] = h[0] + ((s[0]+s[2])>>1);
  for(i=1;i<n/2-2;i++) {
    int i2 = i<<1;
    s[i2+1] = h[i] + ((9*(s[i2]+s[i2+2]) - (s[i2-2]+s[i2+4])+8)>>4);
  }
  s[n-3] = h[n/2-2] + ((s[n-4]+s[n-2])>>1);
  s[n-1] = h[n/2-1] + s[n-2];
}
void TransformStep_Odd(int n, TYPE s[], TYPE l[], TYPE h[]) {
  int i;
  h[0] = s[1] - ((s[0]+s[2])>>1);
  for(i=1;i<n/2-1;i++) {
    int i2 = i<<1;
    h[i] = s[i2+1] - ((9*(s[i2]+s[i2+2]) - (s[i2-2]+s[i2+4])+8)>>4);
  }
  h[n/2-1] = s[n-2] - ((s[n-3]+s[n-1])>>1);
  
  l[0] = s[0] + ((h[0]+1)>>1);
  for(i=1;i<n/2;i++) {
    int i2 = i<<1;
    l[i] = s[i2] + ((h[i]+h[i-1]+2)>>2);
  }
  l[i] = s[n-1] + ((h[i-1]+1)>>1);
}
void i_TransformStep_Odd(int n, TYPE s[], TYPE l[], TYPE h[]) {
  int i;
  s[0] = l[0] - ((h[0]+1)>>1);
  for(i=1;i<n/2;i++) {
    int i2 = i<<1;
    s[i2] = l[i] - ((h[i]+h[i-1]+2)>>2);
  }
  s[n-1] = l[i] - ((h[i-1]+1)>>1);

  s[1] = h[0] + ((s[0]+s[2])>>1);
  for(i=1;i<n/2-1;i++) {
    int i2 = i<<1;
    s[i2+1] = h[i] + ((9*(s[i2]+s[i2+2]) - (s[i2-2]+s[i2+4])+8)>>4);
  }
  s[n-2] = h[n/2-1] + ((s[n-3]+s[n-1])>>1);
}
#endif

/* }}} */
/* {{{ 6/14 */

#ifdef _6_14_
/* entropias
  lena     145844
  barb     163705
  boats    154717
  zelda    133640
  goldhill 163154
  fear     700862
*/

char transform_name[40]="6/14 Transform";

void TransformStep_Even(int n, TYPE s[], TYPE l[], TYPE h[]) {
  int i;

  for(i=0;i<n/2;i++) {
    int i2 = i<<1;
    h[i] = s[i2+1] - s[i2];
  }

  l[0] = s[0] + ((h[0]+1)>>1);
  if(n>2) {
    for(i=1;i<n/2-1;i++) {
      int i2 = i<<1;
      l[i] = s[i2] + ((h[i-1]+8*h[i]-h[i+1]+8)>>4);
    }
    l[n/2-1] = s[n-2] + ((h[n/2-2]+h[n/2-1]+1)>>2);
    
    for(i=2; i<(n/2-2); i++) {
      h[i] += ((l[i+2] - l[i-2] + 6*(l[i-1] - l[i+1]) + 8)>>4);
    }
  }
}
void i_TransformStep_Even(int n, TYPE s[], TYPE l[], TYPE h[]) {
  int i;
  if(n>2) {
    for(i=2; i<(n/2-2); i++) {
      h[i] -= ((l[i+2] - l[i-2] + 6*(l[i-1] - l[i+1]) + 8)>>4);
    }
    
    for(i=1;i<n/2-1;i++) {
      int i2 = i<<1;
      s[i2] = l[i] - ((h[i-1]+8*h[i]-h[i+1]+8)>>4);
    }
    s[n-2] = l[n/2-1] - ((h[n/2-2]+h[n/2-1]+1)>>2);
  }
  s[0] = l[0] - ((h[0]+1)>>1);

  for(i=0;i<n/2;i++) {
    int i2 = i<<1;
    s[i2+1] = h[i] + s[i2];
  }
}
void TransformStep_Odd(int n, TYPE s[], TYPE l[], TYPE h[]) {
  int i;
  for(i=0;i<n/2;i++) {
    int i2 = i<<1;
    h[i] = s[i2+1] - s[i2];
  }

  l[0] = s[0] + ((h[0]+1)>>1);
  for(i=1;i<n/2-1;i++) {
    int i2 = i<<1;
    l[i] = s[i2] + ((h[i-1]+8*h[i]-h[i+1]+8)>>4);
  }
  l[n/2-1] = s[n-3] + ((h[n/2-2]+h[n/2-1]+1)>>2);
  l[n/2] = s[n-1] + (h[n/2-1]>>1); 

  for(i=2; i<(n/2-2); i++) {
    h[i] += ((l[i+2] - l[i-2] + 6*(l[i-1] - l[i+1]) + 8)>>4);
  }
}
void i_TransformStep_Odd(int n, TYPE s[], TYPE l[], TYPE h[]) {
  int i;
  for(i=2; i<(n/2-2); i++) {
    h[i] -= ((l[i+2] - l[i-2] + 6*(l[i-1] - l[i+1]) + 8)>>4);
  }

  s[0] = l[0] - ((h[0]+1)>>1);
  for(i=1;i<n/2-1;i++) {
    int i2 = i<<1;
    s[i2] = l[i] - ((h[i-1]+8*h[i]-h[i+1]+8)>>4);
  }
  s[n-3] = l[n/2-1] - ((h[n/2-2]+h[n/2-1]+1)>>2);
  s[n-1] = l[n/2] - (h[n/2-1]>>1);

  for(i=0;i<n/2;i++) {
    int i2 = i<<1;
    s[i2+1] = h[i] + s[i2];
  }
}
#endif

/* }}} */

/* {{{ OLD */

#ifdef _OLD_
/********************************* 1 *********************************/
void PredictStep_1_Even(int n, int s[], int h[]) {
  int i;
  for(i=0;i<n/2;i++) {
    int i2 = i<<1;
    h[i] = s[i2+1] - s[i2];
  }
}

void i_PredictStep_1_Even(int n, int s[], int h[]) {
  int i;
  for(i=0;i<n/2;i++) {
    int i2 = i<<1;
    s[i2+1] = h[i] + s[i2];
  }
}

void PredictStep_1_Odd(int n, int s[], int h[]) {
  int i;
  for(i=0;i<n/2-1;i++) {
    int i2 = i<<1;
    h[i] = s[i2+1] - s[i2];
  }
}

void i_PredictStep_1_Odd(int n, int s[], int h[]) {
  int i;
  for(i=0;i<n/2-1;i++) {
    int i2 = i<<1;
    s[i2+1] = h[i] + s[i2];
  }
}

void UpdateStep_1_Even(int n, int s[], int l[], int h[]) {
  int i;
  for(i=0;i<n/2;i++) {
    int i2 = i<<1;
    //l[i] = s[i2] + ((h[i]+1)>>1);
    //l[i] = s[i2] - ((h[i]+1)>>1);
    //l[i] = s[i2] + h[i]/2;
    l[i] = s[i2] + ((h[i]+1)>>1);
    //l[i] = s[i2] + (int)ceil((double)(h[i])/2.0);
  }
}

void i_UpdateStep_1_Even(int n, int s[], int l[], int h[]) {
  int i;
  for(i=0;i<n/2;i++) {
    int i2 = i<<1;
    //s[i2] = l[i] + (-(h[i]-1)>>1); // es el inverso de l[i] = s[i2] + (h[i]>>1);
    s[i2] = l[i] + (-h[i]>>1); // es el inverso de l[i] = s[i2] + ((h[i]+1)>>1);
    //s[i2] = l[i] + (-(h[i]+1)>>1); // es el inverso de l[i] = s[i2] - ((h[i]+1)>>1);
    //s[i2] = l[i] - (h[i]>>1);
  }
}

void UpdateStep_1_Odd(int n, int s[], int l[], int h[]) {
  int i,i2;
  for(i=0;i<n/2-1;i++) {
    i2 = i<<1;
    l[i] = s[i2] + (h[i]>>1);
    //l[i] = s[i2] + ((h[i]+1)>>1);
  }
  l[/*i*/n/2/*-1*/] = s[n-1/*i2*/];
}

void i_UpdateStep_1_Odd(int n, int s[], int l[], int h[]) {
  int i,i2;
  for(i=0;i<n/2-1;i++) {
    i2 = i<<1;
    s[i2] = l[i] - (h[i]>>1);
    //s[i2] = l[i] + (-h[i]>>1);
  }
  s[n-1/*i2*/] = l[/*i*/n/2/*-1*/];
}


/*********************************** 2 *************************************/
void PredictStep_2_Even(int n, int s[], int h[]) {
  int i;
  for(i=0;i<n/2-1;i++) {
    int i2 = i<<1;
    h[i] = s[i2+1] - (s[i2]+s[i2+2])/2;
    //h[i] = s[i2+1] - ((s[i2]+s[i2+2]+1)>>1);
  }
  h[i] = s[n-1] - s[n-2];
}

void i_PredictStep_2_Even(int n, int s[], int h[]) {
  int i;
  for(i=0;i<n/2-1;i++) {
    int i2 = i<<1;
    s[i2+1] = h[i] + (s[i2]+s[i2+2])/2;
  }
  s[n-1] = h[i] + s[n-2];
}

void PredictStep_2_Odd(int n, int s[], int h[]) {
  int i;
  for(i=0;i<n/2;i++) {
    int i2 = i<<1;
    h[i] = s[i2+1] - (s[i2]+s[i2+2])/2;
  }
}

void i_PredictStep_2_Odd(int n, int s[], int h[]) {
  int i;
  for(i=0;i<n/2;i++) {
    int i2 = i<<1;
    s[i2+1] = h[i] + (s[i2]+s[i2+2])/2;
  }
}
void UpdateStep_2_Even(int n, int s[], int l[], int h[]) {
  int i;
  l[0] = s[0] + (h[0]>>1);
  for(i=1;i<n/2;i++) {
    int i2 = i<<1;
    //l[i] = s[i2] + (h[i]+h[i-1]+1)/4;
    //l[i] = s[i2] + ((h[i]+h[i-1]+1)>>2);
    l[i] = s[i2] + ((h[i]+h[i-1])>>2);
    //l[i] = s[i2] + (h[i]+h[i-1]+2)/4;
    //l[i] = s[i2] + (int)ceil((double)(h[i]+h[i-1])/4.0);
  }
}

void i_UpdateStep_2_Even(int n, int s[], int l[], int h[]) {
  int i;
  s[0] = l[0] - (h[0]>>1);
  for(i=1;i<n/2;i++) {
    int i2 = i<<1;
    //s[i2] = l[i] - (h[i]+h[i-1])/4;
    //s[i2] = l[i] - ((h[i]+h[i-1]+1)>>2);
    s[i2] = l[i] - ((h[i]+h[i-1])>>2);
  }
}

void UpdateStep_2_Odd(int n, int s[], int l[], int h[]) {
  int i;
  l[0] = s[0] + (h[0]>>1);
  for(i=1;i<n/2;i++) {
    int i2 = i<<1;
    //l[i] = s[i2] + (h[i]+h[i-1])/4;
    //l[i] = s[i2] + ((h[i]+h[i-1]+1)>>2);
    l[i] = s[i2] + ((h[i]+h[i-1])>>2);
  }
  l[i] = s[n-1] + (h[i-1]>>1);
}

void i_UpdateStep_2_Odd(int n, int s[], int l[], int h[]) {
  int i;
  for(i=1;i<n/2;i++) {
    int i2 = i<<1;
    //s[i2] = l[i] - (h[i]+h[i-1])/4;
    //s[i2] = l[i] - ((h[i]+h[i-1]+1)>>2);
    l[i] = s[i2] + ((h[i]+h[i-1])>>2);
  }
  s[n-1] = l[i] - (h[i-1]>>1);
}


/****************************** 3 **********************************/
void PredictStep_3_Even(int n, int s[], int h[]) {
  int i;
  h[0] = s[1] - (s[0]+s[2])/2;
  for(i=1;i<n/2-2;i++) {
    int i2 = i<<1;
    h[i] = s[i2+1] - (9*(s[i2]+s[i2+2]) - (s[i2-2]+s[i2+4]))/16;
  }
  h[n/2-2] = s[n-3] - (s[n-4]+s[n-2])/2;
  h[n/2-1] = s[n-1] - s[n-2];
}

void i_PredictStep_3_Even(int n, int s[], int h[]) {
  int i;
  s[1] = h[0] + (s[0]+s[2])/2;
  for(i=1;i<n/2-2;i++) {
    int i2 = i<<1;
    s[i2+1] = h[i] + (9*(s[i2]+s[i2+2]) - (s[i2-2]+s[i2+4]))/16;
  }
  s[n-3] = h[n/2-2] + (s[n-4]+s[n-2])/2;
  s[n-1] = h[n/2-1] + s[n-2];
}

void PredictStep_3_Odd(int n, int s[], int h[]) {
  int i;
  h[0] = s[1] - (s[0]+s[2])/2;
  for(i=1;i<n/2-1;i++) {
    int i2 = i<<1;
    h[i] = s[i2+1] - (9*(s[i2]+s[i2+2]) - (s[i2-2]+s[i2+4]))/16;
  }
  h[n/2-1] = s[n-2] - (s[n-3]+s[n-1])/2;
}

void i_PredictStep_3_Odd(int n, int s[], int h[]) {
  int i;
  s[1] = h[0] + (s[0]+s[2])/2;
  for(i=1;i<n/2-1;i++) {
    int i2 = i<<1;
    s[i2+1] = h[i] + (9*(s[i2]+s[i2+2]) - (s[i2-2]+s[i2+4]))/16;
  }
  s[n-2] = h[n/2-1] + (s[n-3]+s[n-1])/2;
}

void UpdateStep_3_Even(int n, int s[], int l[], int h[]) {
  int i;
  l[0] = s[0] + (h[0]>>1);
  l[1] = s[2] + ((h[0]+h[1])>>2);
  for(i=2; i<n/2-1; i++) {
    int i2 = i<<1;
    //l[i] = s[i2] + (-h[i-2]+9*(h[i-1]+h[i])-h[i+1])/32;
    l[i] = s[i2] + ((-h[i-2]+9*(h[i-1]+h[i])-h[i+1])>>5);
  }
  l[n/2-1] = s[n-2] + ((h[n/2-2]+h[n/2-1])>>2);
}

void i_UpdateStep_3_Even(int n, int s[], int l[], int h[]) {
  int i;
  s[0] = l[0] - (h[0]>>1);
  s[2] = l[1] - ((h[0]+h[1])>>2);
  for(i=2; i<n/2-1; i++) {
    int i2 = i<<1;
    //s[i2] = l[i] - (-h[i-2]+9*(h[i-1]+h[i])-h[i+1])/32;
    s[i2] = l[i] - ((-h[i-2]+9*(h[i-1]+h[i])-h[i+1])>>5);
  }
  s[n-2] = l[n/2-1] - ((h[n/2-2]+h[n/2-1])>>2);
}

void UpdateStep_3_Odd(int n, int s[], int l[], int h[]) {
  int i;
  l[0] = s[0] + (h[0]>>1);
  l[1] = s[2] + ((h[0]+h[1])>>2);
  for(i=2; i<n/2-1; i++) {
    int i2 = i<<1;
    //l[i] = s[i2] + (-h[i-2]+9*(h[i-1]+h[i])-h[i+1])/32;
    l[i] = s[i2] + ((-h[i-2]+9*(h[i-1]+h[i])-h[i+1])>>5);
  }
  l[n/2-1] = s[n-3] + ((h[n/2-2]+h[n/2-1])>>2);
  l[n/2] = s[n-1] + (h[n/2-1]>>1);
}

void i_UpdateStep_3_Odd(int n, int s[], int l[], int h[]) {
  int i;
  s[0] = l[0] - (h[0]>>1);
  s[2] = l[1] - ((h[0]+h[1])>>2);
  for(i=2; i<n/2-1; i++) {
    int i2 = i<<1;
    //s[i2] = l[i] - (-h[i-2]+9*(h[i-1]+h[i])-h[i+1])/32;
    s[i2] = l[i] - ((-h[i-2]+9*(h[i-1]+h[i])-h[i+1])>>5);
  }
  s[n-3] = l[n/2-1] - ((h[n/2-2]+h[n/2-1])>>2);
  s[n-1] = l[n/2] - (h[n/2-1]>>1);
}

/**************************************************************/


void TransformStep_Even(int n, int s[], int l[], int h[]) {
#ifdef _11_
  PredictStep_1_Even(n,s,h);
  UpdateStep_1_Even(n,s,l,h);
#endif
#ifdef _X_
  int i, k;
  for (i = k = 0; k < n; i++, k += 2) {
    l[i] = (s[k] + s[k+1]) >> 1;
  }
  for (i = k = 0; k < n; i++, k += 2) {
    h[i] =  s[k+1] - s[k];
  }
#endif
#ifdef _12_
  PredictStep_1_Even(n,s,h);
  UpdateStep_2_Even(n,s,l,h);
#endif
#ifdef _13_
  PredictStep_1_Even(n,s,h);
  UpdateStep_3_Even(n,s,l,h);
#endif
#ifdef _21_
  PredictStep_2_Even(n,s,h);
  UpdateStep_1_Even(n,s,l,h);
#endif
#ifdef _22_
  PredictStep_2_Even(n,s,h);
  UpdateStep_2_Even(n,s,l,h);
#endif
#ifdef _23_
  PredictStep_2_Even(n,s,h);
  UpdateStep_3_Even(n,s,l,h);
#endif
#ifdef _31_
  PredictStep_3_Even(n,s,h);
  UpdateStep_1_Even(n,s,l,h);
#endif
#ifdef _32_
  PredictStep_3_Even(n,s,h);
  UpdateStep_2_Even(n,s,l,h);
#endif
#ifdef _33_
  PredictStep_3_Even(n,s,h);
  UpdateStep_3_Even(n,s,l,h);
#endif
#ifdef _ST_
  int i, k;
  for (i = k = 0; k < n; i++, k += 2) {
    l[i] = (s[k] + s[k+1]) >> 1;
    h[i] =  s[k] - s[k+1];
  }
#endif
#ifdef _SPT_
  int i, k, mm = n/2 - 1;
  int d1, d2;

  for (i = k = 0; k < n; i++, k += 2) {
    l[i] = (s[k] + s[k+1]) >> 1;
    h[i] =  s[k] - s[k+1];
  }
  //d2 = l[0] - l[1];
  /**/h[0] -= (d2 = l[0] - l[1]) >> 2;
  for (i = 1; i < mm; i++) {
    d1 = d2;  d2 = l[i] - l[i+1];
    h[i] -= (((d1 + d2 - h[i+1]) << 1) + d2 + 3) >> 3;
  }
  /**/h[i] -= d2 >> 2;
#endif
}

void i_TransformStep_Even(int n, int s[], int l[], int h[]) {
#ifdef _11_
  i_UpdateStep_1_Even(n,s,l,h);
  i_PredictStep_1_Even(n,s,h);
#endif
#ifdef _X_
  int i, k;
  for (i = k = 0; k < n; i++, k += 2) {
    s[k] = l[i] + ((h[i] + 1) >> 1);
  }
  for (i = k = 0; k < n; i++, k += 2) {
    s[k+1] = s[k] + h[i];
  }
#endif
#ifdef _12_
  i_UpdateStep_2_Even(n,s,l,h);
  i_PredictStep_1_Even(n,s,h);
#endif
#ifdef _13_
  i_UpdateStep_3_Even(n,s,l,h);
  i_PredictStep_1_Even(n,s,h);
#endif
#ifdef _21_
  i_UpdateStep_1_Even(n,s,l,h);
  i_PredictStep_2_Even(n,s,h);
#endif
#ifdef _22_
  i_UpdateStep_2_Even(n,s,l,h);
  i_PredictStep_2_Even(n,s,h);
#endif
#ifdef _23_
  i_UpdateStep_3_Even(n,s,l,h);
  i_PredictStep_2_Even(n,s,h);
#endif
#ifdef _31_
  i_UpdateStep_1_Even(n,s,l,h);
  i_PredictStep_3_Even(n,s,h);
#endif
#ifdef _32_
  i_UpdateStep_2_Even(n,s,l,h);
  i_PredictStep_3_Even(n,s,h);
#endif
#ifdef _33_
  i_UpdateStep_3_Even(n,s,l,h);
  i_PredictStep_3_Even(n,s,h);
#endif
#ifdef _ST_
  int i, k;
  for (i = k = 0; k < n; i++, k += 2) {
    s[k] = l[i] + ((h[i] + 1) >> 1);
    s[k+1] = s[k] - h[i];
  }
#endif
#ifdef _SPT_
  int i, k;
  int d1, d2, m=n/2;

  //d1 = l[m-2] - l[m-1];
  /**/h[m-1] += (d1 = l[m-2] - l[m-1]) >> 2;
  for (i = m - 2; i > 0; i--) {
    d2 = d1;  d1 = l[i-1] - l[i];
    h[i] += (((d1 + d2 - h[i+1]) << 1) + d2 + 3) >> 3;
  }
  /**/h[0] += d1 >> 2;

  for (i = k = 0; k < n; i++, k += 2) {
    s[k] = l[i] + ((h[i] + 1) >> 1);
    s[k+1] = s[k] - h[i];
  }
#endif
}

void TransformStep_Odd(int n, int s[], int l[], int h[]) {
#ifdef _11_
  PredictStep_1_Odd(n,s,h);
  UpdateStep_1_Odd(n,s,l,h);
#endif
#ifdef _X_
  int i, k;
  for (i = k = 0; k < (n-1); i++, k += 2) {
    l[i] = (s[k] + s[k+1]) >> 1;
  }
  l[i] = s[n-1];
  for (i = k = 0; k < (n-1); i++, k += 2) {
    h[i] =  s[k+1] - s[k];
  }
#endif
#ifdef _12_
  PredictStep_1_Odd(n,s,h);
  UpdateStep_2_Odd(n,s,l,h);
#endif
#ifdef _13_
  PredictStep_1_Odd(n,s,h);
  UpdateStep_3_Odd(n,s,l,h);
#endif
#ifdef _21_
  PredictStep_2_Odd(n,s,h);
  UpdateStep_1_Odd(n,s,l,h);
#endif
#ifdef _22_
  PredictStep_2_Odd(n,s,h);
  UpdateStep_2_Odd(n,s,l,h);
#endif
#ifdef _23_
  PredictStep_2_Odd(n,s,h);
  UpdateStep_3_Odd(n,s,l,h);
#endif
#ifdef _31_
  PredictStep_3_Odd(n,s,h);
  UpdateStep_1_Odd(n,s,l,h);
#endif
#ifdef _32_
  PredictStep_3_Odd(n,s,h);
  UpdateStep_2_Odd(n,s,l,h);
#endif
#ifdef _33_
  PredictStep_3_Odd(n,s,h);
  UpdateStep_3_Odd(n,s,l,h);
#endif
#ifdef _ST_
  int i, k;
  for (i = k = 0; k < (n-1); i++, k += 2) {
    l[i] = (s[k] + s[k+1]) >> 1;
    h[i] =  s[k] - s[k+1];
  }
  l[i] = s[n-1];
#endif
#ifdef _SPT_
  int i, k, mm = n/2 - 1;
  int d1, d2;

  for (i = k = 0; k < (n-1); i++, k += 2) {
    l[i] = (s[k] + s[k+1]) >> 1;
    h[i] =  s[k] - s[k+1];
  }
  l[i] = s[n-1];
  //d2 = l[0] - l[1];
  /**/h[0] -= (d2 = l[0] - l[1]) >> 2;
  for (i = 1; i < mm; i++) {
    d1 = d2;  d2 = l[i] - l[i+1];
    h[i] -= (((d1 + d2 - h[i+1]) << 1) + d2 + 3) >> 3;
  }
  /**/h[i] -= d2 >> 2;
#endif
}

void i_TransformStep_Odd(int n, int s[], int l[], int h[]) {
#ifdef _11_
  i_UpdateStep_1_Odd(n,s,l,h);
  i_PredictStep_1_Odd(n,s,h);
#endif
#ifdef _X_
  int i, k;
  for (i = k = 0; k < (n-1); i++, k += 2) {
    s[k] = l[i] + ((h[i] + 1) >> 1);
  }
  s[k] = l[i];
  for (i = k = 0; k < (n-1); i++, k += 2) {
    s[k+1] = s[k] + h[i];
  }
#endif
#ifdef _12_
  i_UpdateStep_2_Odd(n,s,l,h);
  i_PredictStep_1_Odd(n,s,h);
#endif
#ifdef _13_
  i_UpdateStep_3_Odd(n,s,l,h);
  i_PredictStep_1_Odd(n,s,h);
#endif
#ifdef _21_
  i_UpdateStep_1_Odd(n,s,l,h);
  i_PredictStep_2_Odd(n,s,h);
#endif
#ifdef _22_
  i_UpdateStep_2_Odd(n,s,l,h);
  i_PredictStep_2_Odd(n,s,h);
#endif
#ifdef _23_
  i_UpdateStep_3_Odd(n,s,l,h);
  i_PredictStep_2_Odd(n,s,h);
#endif
#ifdef _31_
  i_UpdateStep_1_Odd(n,s,l,h);
  i_PredictStep_3_Odd(n,s,h);
#endif
#ifdef _32_
  i_UpdateStep_2_Odd(n,s,l,h);
  i_PredictStep_3_Odd(n,s,h);
#endif
#ifdef _33_
  i_UpdateStep_3_Odd(n,s,l,h);
  i_PredictStep_3_Odd(n,s,h);
#endif
#ifdef _ST_
  int i, k;
  for (i = k = 0; k < (n-1); i++, k += 2) {
    s[k] = l[i] + ((h[i] + 1) >> 1);
    s[k+1] = s[k] - h[i];
  }
  s[k] = l[i];
#endif
#ifdef _SPT_
  int i, k;
  int d1, d2, m=n/2;

  //d1 = l[m-2] - l[m-1];
  /**/h[m-1] += (d1 = l[m-2] - l[m-1]) >> 2;
  for (i = m - 2; i > 0; i--) {
    d2 = d1;  d1 = l[i-1] - l[i];
    h[i] += (((d1 + d2 - h[i+1]) << 1) + d2 + 3) >> 3;
  }
  /**/h[0] += d1 >> 2;

  for (i = k = 0; k < (n-1); i++, k += 2) {
    s[k] = l[i] + ((h[i] + 1) >> 1);
    s[k+1] = s[k] - h[i];
  }
  s[k] = l[i];
#endif
}
#endif

/* }}} */
