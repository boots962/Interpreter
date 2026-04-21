main : HashMap.o interpreter.o
	gcc -o main HashMap.o interpreter.o

HashMap.o : HashMap.c HashMap.h
	gcc -c HashMap.c

interpreter.o : interpreter.c interpreter.h
	gcc -c interpreter.c

clean :
	rm -f *.o main