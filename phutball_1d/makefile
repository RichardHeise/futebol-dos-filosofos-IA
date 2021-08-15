CC = gcc
OBJS =  direita.o uteis.o campo.o esquerda.o marIA.o marIAlib.o
LIBS = -l hiredis -l readline
OUTPUT = 	
CFLAGS = -Wall -O3

all: $(OBJS) 
	$(CC) $(OBJS) $(LIBS) -o marIA

marIA.o: marIA.c
	$(CC) $(CFLAGS) -c marIA.c
	
marIAlib.o: marIAlib.h marIAlib.c
	$(CC) $(CFLAGS) -c marIAlib.c

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
	rm -f *.o