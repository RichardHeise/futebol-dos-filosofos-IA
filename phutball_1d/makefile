CFLAGS = -g -Wall -Wno-unused-result -O3
LDLIBS = -l hiredis -l readline

all: exemplo1 exemplo2 resolutor

controlador: controlador.c

exemplo1: campo.h campo.c exemplo1.c

exemplo2: campo.h campo.c exemplo2.c

resolutor: campo.h campo.c resolutor.c inteligencia.o

inteligencia: inteligencia.h inteligencia.c

clean:
	rm -f exemplo1 exemplo2 *.o