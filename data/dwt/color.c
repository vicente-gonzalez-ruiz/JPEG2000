#include "color.h"

void RGB_to_YUV(struct RGB *i, struct RGB *o) {
  o->r = (i->r + ((i->g)<<1) + i->b)>>2;
  o->g = i->b - i->g;
  o->b = i->r - i->g;
}

void YUV_to_RGB(struct RGB *i, struct RGB *o) {
  o->g = i->r - ((i->g + i->b)>>2);
  o->r = i->b + o->g;
  o->b = i->g + o->g;
}

#ifdef _TEST_
#include <stdio.h>
#include <stdlib.h>

int main() {
  struct RGB i,tmp;
  struct RGB o;
  int x;
  for(x=0;x<100;x++) {
    i.r = (random()&0xFF)-128; i.g = (random()&0xFF)-128; i.b = (random()&0xFF)-128;
    tmp = i;
    printf("(%4d) R=%d G=%d B=%d\n",x,i.r,i.g,i.b);
    RGB_to_YUV(&i,&o);
    printf("(%4d) Y=%d U=%d V=%d\n",x,o.r,o.g,o.b);
    YUV_to_RGB(&o,&i);
    printf("(%4d) R=%d G=%d B=%d\n",x,i.r,i.g,i.b);
    if(tmp.r!=i.r) break;
    if(tmp.g!=i.g) break;
    if(tmp.b!=i.b) break;
  }
  i.r = 0; i.g = 255; i.b = 255;
  RGB_to_YUV(&i,&o);
  printf("Y=%d U=%d V=%d\n",o.r,o.g,o.b);
}
#endif
