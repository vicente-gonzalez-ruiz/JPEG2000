#ifdef __cplusplus
extern "C" {
#endif

struct RGB {
  short r,g,b;
};

void RGB_to_YUV(struct RGB *input, struct RGB *output);
void YUV_to_RGB(struct RGB *input, struct RGB *output);

#ifdef __cplusplus
}
#endif
