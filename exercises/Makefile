include ../Makefile.inc

EXE = $(patsubst %.c, %, $(wildcard *.c))

all : ${EXE}

clean :
	-${RM} ${EXE}

${EXE} : ${TLPI_LIB}

.PHONY: all clean
