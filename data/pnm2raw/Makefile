args.o:		args.cc args.h
		g++ -c $< -o $@

pnm_in.o:	pnm_in.cc pnm_in.h
		g++ -c $< -o $@

pnm2raw:	pnm2raw.cc args.o pnm_in.o
		g++ $^ -o $@

all:		pnm2raw

default:	all

clean:
		rm *.o pnm2raw
