haar:	DWT_2D.c DWT.c filters.c args.c mallok.c
	c++ -D _Haar_ DWT_2D.c DWT.c filters.c args.c mallok.c -o $@

22:	DWT_2D.c DWT.c filters.c args.c mallok.c
	c++ -D _22_ DWT_2D.c DWT.c filters.c args.c mallok.c -o $@

33:	DWT_2D.c DWT.c filters.c args.c mallok.c
	c++ -D _33_ DWT_2D.c DWT.c filters.c args.c mallok.c -o $@

unitary:	args.c mallok.c
	c++ unitary_2D.c args.c mallok.c -o $@

all:	haar 22 33 unitary

clean:
	rm -f haar 22 33 unitary

