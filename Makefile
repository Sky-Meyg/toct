CC=g++
CFLAGS=-O2
TOCTLIB=libtoct.so
TOCT=toct

all: ${TOCTLIB} ${TOCT}

${TOCTLIB}: library.cpp library.h
	${CC} -fPIC -shared -o ${TOCTLIB} library.cpp

${TOCT}: main.cpp
	${CC} -o ${TOCT} main.cpp -L. -ltoct

