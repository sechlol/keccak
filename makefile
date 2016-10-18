rm=/bin/rm -f
CC=cc
DEFS=
INCLUDES=-I.

DEFINES= $(INCLUDES) $(DEFS)
CFLAGS= -std=c99 $(DEFINES) -O2 -fomit-frame-pointer -funroll-loops -g
SRC= src/
TEST= tests/

all: stream_test Keccak_r1024_test KeccakF1600_test stream.o KeccakF1600.o


stream_test: tests/stream_test.c src/stream.c src/KeccakF1600.c stream.o KeccakF1600.o
	$(CC) $(CFLAGS) -o stream_test tests/stream_test.c stream.o KeccakF1600.o

Keccak_r1024_test: tests/Keccak_r1024_test.c KeccakF1600.o Keccak_r1024.o
	$(CC) $(CFLAGS) -o Keccak_r1024_test tests/Keccak_r1024_test.c KeccakF1600.o Keccak_r1024.o

KeccakF1600_test: tests/KeccakF1600_test.c KeccakF1600.o
	$(CC) $(CFLAGS) -o KeccakF1600_test tests/KeccakF1600_test.c KeccakF1600.o

stream.o: src/stream.c src/stream.h
	$(CC) $(CFLAGS) -c src/stream.c $(LIBS)

KeccakF1600.o: src/KeccakF1600.c src/KeccakF1600.h
	$(CC) $(CFLAGS) -c src/KeccakF1600.c $(LIBS)

Keccak_r1024.o: src/Keccak_r1024.c src/Keccak_r1024.h
	$(CC) $(CFLAGS) -c src/Keccak_r1024.c $(LIBS)

clean:
	$(rm) *.o stream_test Keccak_r1024_test KeccakF1600_test *~
