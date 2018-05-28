include $(HOME)/Makefile_templates/Makefile

lena.png:
		wget http://www.hpca.ual.es/~vruiz/images/lena.png
TMPs += lena.png

lena.ppm:	lena.png
		convert $< $@
TMPs += lena.ppm

cat.png:
		wget http://www.hpca.ual.es/~vruiz/images/cat.png
TMPs += cat.png

cat.ppm:	cat.png
		convert $< $@
TMPs += cat.ppm

lena_05.jpg:	lena.ppm
		echo Building `pwd`/$@
		cjpeg -quality 30 -optimize $< > $@
TMPs += lena_05.jpg

lena_04.jpg:	lena.ppm
		echo Building `pwd`/$@
		cjpeg -quality 22 -optimize $< > $@
TMPs += lena_04.jpg

lena_03.jpg:	lena.ppm
		echo Building `pwd`/$@
		cjpeg -quality 15 -optimize $< > $@
TMPs += lena_03.jpg

lena_02.jpg:	lena.ppm
		echo Building `pwd`/$@
		cjpeg -quality 8 -optimize $< > $@
TMPs += lena_02.jpg

lena_01.jpg:	lena.ppm
		echo Building `pwd`/$@
		cjpeg -quality 3 -optimize $< > $@
TMPs += lena_01.jpg

lena_01_jp2.png:	lena.ppm
			echo Building `pwd`/$@
			kdu_compress -quiet -i $< -o $@.1.jp2 -slope 44531
			kdu_expand -quiet -i $@.1.jp2 -o $@.1.ppm
			pnmtopng < $@.1.ppm > $@
			rm -f $@.1.jp2 $@.1.ppm
TMPs +=	lena_01_jp2.png

lena_02_jp2.png:	lena.ppm
			echo Building `pwd`/$@
			kdu_compress -quiet -i $< -o $@.1.jp2 -slope 44003
			kdu_expand -quiet -i $@.1.jp2 -o $@.1.ppm
			pnmtopng < $@.1.ppm > $@
			rm -f $@.1.jp2 $@.1.ppm
TMPs +=	lena_02_jp2.png

lena_03_jp2.png:	lena.ppm
			echo Building `pwd`/$@
			kdu_compress -quiet -i $< -o $@.1.jp2 -slope 43670
			kdu_expand -quiet -i $@.1.jp2 -o $@.1.ppm
			pnmtopng < $@.1.ppm > $@
			rm -f $@.1.jp2 $@.1.ppm
TMPs +=	lena_03_jp2.png

lena_04_jp2.png:	lena.ppm
			echo Building `pwd`/$@
			kdu_compress -quiet -i $< -o $@.1.jp2 -slope 43422
			kdu_expand -quiet -i $@.1.jp2 -o $@.1.ppm
			pnmtopng < $@.1.ppm > $@
			rm -f $@.1.jp2 $@.1.ppm
TMPs +=	lena_04_jp2.png

lena_05_jp2.png:	lena.ppm
			echo Building `pwd`/$@
			kdu_compress -quiet -i $< -o $@.1.jp2 -slope 43167
			kdu_expand -quiet -i $@.1.jp2 -o $@.1.ppm
			pnmtopng < $@.1.ppm > $@
			rm -f $@.1.jp2 $@.1.ppm
TMPs +=	lena_05_jp2.png

cat_05.jpg:		cat.ppm
			echo Building `pwd`/$@
			cjpeg -quality 15 -optimize $< > $@
TMPs +=	cat_05.jpg

cat_04.jpg:		cat.ppm
			echo Building `pwd`/$@
			cjpeg -quality 11 -optimize $< > $@
TMPs +=	cat_04.jpg

cat_03.jpg:		cat.ppm
			echo Building `pwd`/$@
			cjpeg -quality 8 -optimize $< > $@
TMPs +=	cat_03.jpg

cat_02.jpg:		cat.ppm
			echo Building `pwd`/$@
			cjpeg -quality 5 -optimize $< > $@
TMPs +=	cat_02.jpg

cat_01.jpg:		cat.ppm
			echo Building `pwd`/$@
			cjpeg -quality 2 -optimize $< > $@
TMPs +=	cat_01.jpg

cat_05_jp2.png:		cat.ppm
			echo Building `pwd`/$@
			kdu_compress -quiet -i $< -o $@.1.jp2 -slope 43619
			kdu_expand -quiet -i $@.1.jp2 -o $@.1.ppm
			pnmtopng < $@.1.ppm > $@
			rm -f $@.1.jp2 $@.1.ppm
TMPs +=	cat_05_jp2.png

cat_04_jp2.png:		cat.ppm
			echo Building `pwd`/$@
			kdu_compress -quiet -i $< -o $@.1.jp2 -slope 43851
			kdu_expand -quiet -i $@.1.jp2 -o $@.1.ppm
			pnmtopng < $@.1.ppm > $@
			rm -f $@.1.jp2 $@.1.ppm
TMPs +=	cat_04_jp2.png

cat_03_jp2.png:		cat.ppm
			echo Building `pwd`/$@
			kdu_compress -quiet -i $< -o $@.1.jp2 -slope 44126
			kdu_expand -quiet -i $@.1.jp2 -o $@.1.ppm
			pnmtopng < $@.1.ppm > $@
			rm -f $@.1.jp2 $@.1.ppm
TMPs +=	cat_03_jp2.png

cat_02_jp2.png:		cat.ppm
			echo Building `pwd`/$@
			kdu_compress -quiet -i $< -o $@.1.jp2 -slope 44372
			kdu_expand -quiet -i $@.1.jp2 -o $@.1.ppm
			pnmtopng < $@.1.ppm > $@
			rm -f $@.1.jp2 $@.1.ppm
TMPs +=	cat_02_jp2.png

cat_01_jp2.png:		cat.ppm
			echo Building `pwd`/$@
			kdu_compress -quiet -i $< -o $@.1.jp2 -slope 44982
			kdu_expand -quiet -i $@.1.jp2 -o $@.1.ppm
			pnmtopng < $@.1.ppm > $@
			rm -f $@.1.jp2 $@.1.ppm
TMPs +=	cat_01_jp2.png

lena.pgm:	lena.ppm
		echo Building `pwd`/$@
		ppmtopgm < $< > lena.pgm
TMPs +=	lena.pgm

lena8.png:	lena.pgm
		echo Building `pwd`/$@
		pnmtopng < lena.pgm > lena8.png
TMPs += lena8.png

lena8-cut.png:	lena.pgm
		echo Building `pwd`/$@
		pnmcut -top 250 -right 350 -width 40 -height 40 < lena.pgm | pnmtopng > lena8-cut.png
TMPs += lena8-cut.png

lena_512x512.Y:	lena.ppm
		echo Building `pwd`/$@
		convert $< $@
TMPs += lena_512x512.Y


TEXs += akiyo_compresion_JPEG2000.tex

#TMPs += jpeg.dat
#jpeg.dat:	 RD_JPEG.py
#		./RD_JPEG.py

#TMPs += jpeg2000-1.dat
#jpeg2000-1.dat:	 RD_JPEG2000-1.py
#		./RD_JPEG2000-1.py

#TMPs += jpeg2000-2.dat
#jpeg2000-2.dat:	 RD_JPEG2000-2.py
#		./RD_JPEG2000-2.py

#TMPs += jpeg2000-32.dat
#jpeg2000-32.dat:	 RD_JPEG2000-32.py
#		./RD_JPEG2000-32.py

#LOCAL_TEXINPUTS = "$(HOME)/docencia/doctorado/02-image_coding/02-JPEG/:"

#PDFs += lena.png
#PDFs += lena.S.cols.png
#PDFs += lena.S.cols-fils.png
#PDFs += lena.S.3-levels.png

dwt/22:		dwt/*.h dwt/*.c
		echo Building `pwd`/$@
		make -C dwt 22
TMPs += dwt/22

pnm2raw/pnm2raw:	pnm2raw/*.h pnm2raw/*.cc
			echo Building `pwd`/$@
			make -C pnm2raw all
TMPs += pnm2raw/pnm2raw

mux/demux:	mux/*.c
		echo Building `pwd`/$@
		make -C mux all
TMPs += mux/demux

type/uchar2int:	type/src/*.c
		echo Building `pwd`/$@
		make -C type
TMPs += type/uchar2int

dwt_lena.png:	lena.ppm ./pnm2raw/pnm2raw ./mux/demux ./mux/mux ./dwt/22 ./type/uchar2int 
	echo Building `pwd`/$@
	./pnm2raw/pnm2raw < lena.ppm > $@.1
	./mux/demux 3 0 1 < $@.1 | ./type/uchar2int > $@.R
	./mux/demux 3 1 1 < $@.1 | ./type/uchar2int > $@.G
	./mux/demux 3 2 1 < $@.1 | ./type/uchar2int > $@.B
	./dwt/22 -levels 2 < $@.R | ./type/int2uchar > $@._r
	./dwt/22 -levels 2 < $@.G | ./type/int2uchar > $@._g
	./dwt/22 -levels 2 < $@.B | ./type/int2uchar > $@._b
	./mux/mux 1 1 $@._r < $@._g > $@.1
	./mux/mux 2 1 $@.1 < $@._b > $@.2
	rawtoppm 512 512 < $@.2 | pnmgamma 2 | pnmtopng > dwt_lena.png
	rm  $@.1  $@.2 $@.R $@.G $@.B $@._r $@._g $@._b
TMPs += dwt_lena.png

lena_512x512_rgb.png:	lena.ppm
			echo Building `pwd`/$@
			pnmtopng < $< > lena_512x512_rgb.png
TMPs +=	lena_512x512_rgb.png

lena_512x512_rgb_jp2_roi.png:	lena.ppm
			echo Building `pwd`/$@
			kdu_compress -quiet Rshift=20 -roi "{0.50,0.50},{0.25,0.25}" -i $< -o $@.1.jp2 -slope 51740
			kdu_expand -quiet -i $@.1.jp2 -o $@.1.ppm
			pnmtopng < $@.1.ppm > lena_512x512_rgb_jp2_roi.png
			rm -f $@.1.jp2 $@.1.ppm
TMPs +=	lena_512x512_rgb_jp2_roi.png

ROI.pdf:	dwt_lena.png lena_512x512_rgb_jp2_roi.png ROI.fig
TMPs += ROI.pdf

lena_128x128_rgb.png:	lena.ppm
			echo Building `pwd`/$@
			pnmscale 0.25 < $< | pnmtopng > lena_128x128_rgb.png
TMPs += lena_128x128_rgb.png

lena_256x256_rgb.png:	lena.ppm
			echo Building `pwd`/$@
			pnmscale 0.5 < $< | pnmtopng > lena_256x256_rgb.png
TMPs +=	lena_256x256_rgb.png

default:	$(TMPs)
