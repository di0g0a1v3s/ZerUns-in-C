CFLAGS = -Wall -ansi -O3

zeruns: zeruns.o files.o puzzle.o stack.o bigInts.o puzzlemngt.o
	gcc $(CFLAGS) -o zeruns zeruns.o files.o puzzle.o stack.o bigInts.o puzzlemngt.o

zeruns.o: zeruns.c puzzlemngt.h puzzle.h files.h
	gcc $(CFLAGS) -c zeruns.c

files.o: files.c files.h
	gcc $(CFLAGS) -c files.c
	
puzzle.o: puzzle.c puzzle.h
	gcc $(CFLAGS) -c puzzle.c

stack.o: stack.c stack.h Item.h
	gcc $(CFLAGS) -c stack.c

bigInts.o: bigInts.c bigInts.h
	gcc $(CFLAGS) -c bigInts.c
	
puzzlemngt.o: puzzlemngt.c puzzlemngt.h puzzle.h stack.h Item.h bigInts.h
	gcc $(CFLAGS) -c puzzlemngt.c

clean:
	rm -f *.o *.~ zeruns *.gch
