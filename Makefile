.PHONY: all clean rendu

CC      = gcc
CFLAGS  = 
SRC     = $(wildcard src/*.c)
OBJ     = $(patsubst src/%.c, build/%.o, $(SRC))
BIN     = bin/cpyrrc

all: $(BIN)

$(BIN): build/y.tab.o build/lex.yy.o $(OBJ)
	@echo "→ Création de l'éxécutable..."
	mkdir -p bin
	$(CC) $^ -o $(BIN)

build/%.o: src/%.c
	@echo "→ Compilation de $<"
	mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

build/lex.yy.c: src/grammaire.l build/y.tab.c
	@echo "→ Génération du lex"
	mkdir -p build
	flex -o build/lex.yy.c src/grammaire.l

build/lex.yy.o: build/lex.yy.c
	$(CC) $(CFLAGS) -c build/lex.yy.c -o build/lex.yy.o

build/y.tab.c build/y.tab.h: src/grammaire.y
	@echo "→ Génération du yacc"
	mkdir -p build inc
	byacc -dv -o build/y.tab.c src/grammaire.y
	@mv build/y.tab.h inc/y.tab.h

build/y.tab.o: build/y.tab.c
	$(CC) $(CFLAGS) -c build/y.tab.c -o build/y.tab.o

#####################################
# Cible rendu — NE PAS TOUCHER
#####################################
rendu:
	mkdir -p rendus
	mkdir -p rendus/ARCHIVE$(shell date +%Y%m%d)
	cp -r src tests Makefile inc rendus/ARCHIVE$(shell date +%Y%m%d)/
	cd rendus && zip -r ARCHIVE$(shell date +%Y%m%d).zip ARCHIVE$(shell date +%Y%m%d)

clean:
	rm -rf build bin inc/y.tab.h

