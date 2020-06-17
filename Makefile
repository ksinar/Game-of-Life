all: cgol
cgol:
	gcc -Wall -ansi -o cgol cgol.c

clean:
	rm cgol