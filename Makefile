.PHONY: all clean rendu

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

rendu:
	mkdir -p rendus
	mkdir -p rendus/ARCHIVE$(shell date +%Y%m%d)
	cp -r src tests Makefile rendus/ARCHIVE$(shell date +%Y%m%d)/
	cd rendus && zip -r ARCHIVE$(shell date +%Y%m%d).zip ARCHIVE$(shell date +%Y%m%d)

clean:
	rm -rf build bin
