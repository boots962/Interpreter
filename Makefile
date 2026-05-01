all: main

main: HashMap.o Parser.o interpreter.o
	gcc -o main HashMap.o Parser.o interpreter.o

HashMap.o: HashMap.c HashMap.h Token.h
	gcc -c HashMap.c

Parser.o: Parser.c Parser.h HashMap.h Stack.h Token.h
	gcc -c Parser.c

interpreter.o: interpreter.c Parser.h HashMap.h Stack.h Token.h
	gcc -c interpreter.c

clean:
	rm -f *.o main

.PHONY: all clean