# CFLAGS = -g -Wall -Wno-unused-result -O3
# LDLIBS = -l hiredis -l readline

# all: direita uteis exemplo1 exemplo2 resolutor

# controlador: controlador.c

# exemplo1: campo.h campo.c exemplo1.c

# exemplo2: campo.h campo.c exemplo2.c

# resolutor: campo.h campo.c resolutor.c direita.o

# direita: direita.c direita.h uteis.o

# uteis: uteis.h uteis.c

# clean:
# 	rm -f exemplo1 exemplo2 *.o

CC = gcc
OBJS = resolutor.o direita.o uteis.o campo.o esquerda.o marIA.o
LIBS = -l hiredis -l readline
OUTPUT = 	
CFLAGS = -Wall -O3

all: $(OBJS) exemplo2
	$(CC) $(OBJS) $(LIBS) -o resolutor

exemplo2: campo.h campo.c exemplo2.c
	$(CC) campo.c exemplo2.c $(LIBS) -o exemplo2

resolutor.o: resolutor.c
	$(CC) $(CFLAGS) -c resolutor.c
	
marIA.o: marIA.h marIA.c
	$(CC) $(CFLAGS) -c marIA.c

campo.o: campo.h campo.c
	$(CC) $(CFLAGS) -c campo.c


direita.o: direita.c direita.h
	$(CC) $(CFLAGS) -c direita.c

esquerda.o: esquerda.c esquerda.h
	$(CC) $(CFLAGS) -c esquerda.c

uteis.o: uteis.c uteis.h
	$(CC) $(CFLAGS) -c uteis.c

clean:
	$(RM) *.tmp
	$(RM) $(OBJS)

purge: clean
	rm -f exemplo1 exemplo2 *.o