.PHONY: all clean rendu

CC      = gcc
CFLAGS  = 
SRC     = $(wildcard src/*.c)
OBJ     = $(patsubst src/%.c, build/%.o, $(SRC))
BIN     = bin/cpyrrc
RED = \033[31m
NC  = \033[0m

all: $(BIN)

$(BIN): build/y.tab.o build/lex.yy.o $(OBJ)
	@echo "$(RED)\n→ Création de l'éxécutable...$(NC)"
	mkdir -p bin
	$(CC) $^ -o $(BIN)

build/%.o: src/%.c
	@echo "$(RED)\n→ Compilation de $<$(NC)"
	mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

build/lex.yy.c: src/grammaire.l build/y.tab.c
	@echo "$(RED)\n→ Génération du lex$(NC)"
	mkdir -p build
	flex -o build/lex.yy.c src/grammaire.l

build/lex.yy.o: build/lex.yy.c
	$(CC) $(CFLAGS) -c build/lex.yy.c -o build/lex.yy.o

build/y.tab.c build/y.tab.h: src/grammaire.y
	@echo "$(RED)\n→ Génération du yacc$(NC)"
	mkdir -p build inc
	byacc -dv -o build/y.tab.c src/grammaire.y
	@mv build/y.tab.h inc/y.tab.h

build/y.tab.o: build/y.tab.c
	$(CC) $(CFLAGS) -c build/y.tab.c -o build/y.tab.o

#####################################
# Cible rendu — NE PAS TOUCHER
#####################################
rendu:
	@echo "$(RED)\n→Création du rendu hebdo$(NC)" 
	mkdir -p rendus
	mkdir -p rendus/ARCHIVE$(shell date +%Y%m%d)
	cp -r src tests Makefile inc rendus/ARCHIVE$(shell date +%Y%m%d)/
	cd rendus && zip -r ARCHIVE$(shell date +%Y%m%d).zip ARCHIVE$(shell date +%Y%m%d)

clean:
	@echo "$(RED)\n→Nettoyage...$(NC)"
	rm -rf build bin inc/y.tab.h

