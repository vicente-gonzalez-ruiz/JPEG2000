include $(HOME)/LaTeX_templates/Makefile

default:	$(TMPs)

8x8_DCT_basis:	8x8_DCT_basis.c
		gcc -g 8x8_DCT_basis.c DCT.c -o $@ -lm
TMPs += 8x8_DCT_basis

lena.png:
		wget http://www.hpca.ual.es/~vruiz/images/lena.png
TMPs += lena.png

lena.ppm:	lena.png
		convert $< $@
TMPs += lena.ppm

lena_rgb.png:	lena.ppm
		pnmtopng $< > $@
TMPs += lena_rgb.png

lena_10.jpg:	lena.ppm
		cjpeg -quality 69 -optimize $< > $@
TMPs += lena_10.jpg

lena_05.jpg:	lena.ppm
		cjpeg -quality 30 -optimize $< > $@
TMPs += lena_05.jpg

lena_04.jpg:	lena.ppm
		cjpeg -quality 22 -optimize $< > $@
TMPs += lena_04.jpg

lena_03.jpg:	lena.ppm
		cjpeg -quality 15 -optimize $< > $@
TMPs += lena_03.jpg

lena_02.jpg:	lena.ppm
		cjpeg -quality 8 -optimize $< > $@
TMPs += lena_02.jpg

lena_01.jpg:	lena.ppm
		cjpeg -quality 3 -optimize $< > $@
TMPs += lena_01.jpg

lena.png:
	wget http://www.hpca.ual.es/~vruiz/images/lena.png
TMPs += lena.png

lena.ppm:	lena.png
	convert $< $@

lena.pgm:	lena.ppm
		ppmtopgm < $< > $@
TMPs +=	lena.pgm

lena8.png:	lena.pgm
		pnmtopng < $< > $@
TMPs += lena8.png

lena8-cut.png:	lena.pgm
		pnmcut -top 250 -right 350 -width 40 -height 40 < $< | pnmtopng > $@
TMPs += lena8-cut.png

lena_512x512.Y:	lena.ppm
		ppmtopgm < $< | pnm2raw > $@
TMPs += lena_512x512.Y

8x8_DCT_basis.png:	8x8_DCT_basis
		./8x8_DCT_basis | rawtopgm 72 72 | pnmhisteq | pnmscale 8| pnmtopng > $@
TMPs += 8x8_DCT_basis.png

correlacion_espacial_lena.fig: lena8.png lena8-cut.png

#TMPs += DCT_basis_*.pdf

TEXs += akiyo_compresion_JPEG.tex
