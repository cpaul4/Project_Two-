CC = gcc
CFLAGS = -c -ansi -g

all: project2

project2: 	project2.o repository.o
		$(CC) -o project2 project2.o repository.o

clean:
		rm -f *.o

%.o:	%.c
		$(CC) $(CFLAGS) $*.c
