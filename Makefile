.PHONY: all clean

all: bin/grammaire

bin/grammaire: build/lex.yy.o build/y.tab.c
	mkdir -p bin
	gcc build/y.tab.c build/lex.yy.o -o bin/grammaire -ly

build/lex.yy.o: build/lex.yy.c build/y.tab.c
	gcc -c build/lex.yy.c -o build/lex.yy.o

build/lex.yy.c: src/grammaire.l
	mkdir -p build
	lex -o build/lex.yy.c src/grammaire.l

build/y.tab.c: src/grammaire.y
	mkdir -p build
	byacc -dvo build/y.tab.c src/grammaire.y

clean:
	rm -rf build bin
