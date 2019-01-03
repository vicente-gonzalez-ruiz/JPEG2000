EXE=../

CC=gcc
CFLAGS=-pipe -O3
#CFLAGS=-g -D DEBUG

$(EXE)/%:	%.c
	$(CC) $(CFLAGS) $< -o $@

Cs = $(wildcard *.c)
BINs = $(Cs:%.c=$(EXE)/%)

all:	$(BINs)

clean:
	rm $(BINs)

info:
	@echo $(BINs)
