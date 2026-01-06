.PHONY: all clean rendu

# --- Détection de l'OS ---
UNAME_S := $(shell uname -s)

# --- Configuration selon l'OS (en priant pour que ça marche à la fac) ---
ifeq ($(UNAME_S), Darwin)
	# Configuration macOS
	YACC   = bison
	LEX    = flex
	LIBS   = 
	YFLAGS = -dv   # -d pour le .h, -v pour le y.output
	LFLAGS = 
else
	# Configuration Linux (par défaut)
	YACC   = yacc
	LEX    = lex
	LIBS   =
	YFLAGS = -dv
	LFLAGS = 
endif

# --- Variables du projet ---
CC      = gcc
CFLAGS  = -Iinc -MMD -MP # -MMD -MP pour recompiler les fichiers dont les .h changent
SRC     = $(shell find src -name "*.c")
OBJ     = $(patsubst src/%.c, build/%.o, $(SRC))
DEPS    = $(patsubst src/%.c, build/%.d, $(SRC))
BIN     = bin/cpyrrc
RED = \033[31m
NC  = \033[0m

all: $(BIN)

-include $(DEPS)

$(BIN): build/y.tab.o build/lex.yy.o $(OBJ)
	@echo "$(RED)\n→ Création de l'éxécutable...$(NC)"
	@mkdir -p bin
	@$(CC) $^ -o $(BIN) $(LIBS) # Ajout de $(LIBS) ici

build/%.o: src/%.c
	@echo "$(RED)\n→ Compilation de $<$(NC)"
	@mkdir -p build
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

build/lex.yy.c: src/grammaire/grammaire.l inc/y.tab.h
	@echo "$(RED)\n→ Génération du lex ($(LEX))...$(NC)"
	@mkdir -p build
	@$(LEX) $(LFLAGS) -o build/lex.yy.c src/grammaire/grammaire.l

build/lex.yy.o: build/lex.yy.c
	@$(CC) $(CFLAGS) -c build/lex.yy.c -o build/lex.yy.o

build/y.tab.c inc/y.tab.h: src/grammaire/grammaire.y
	@echo "$(RED)\n→ Génération du yacc ($(YACC))...$(NC)"
	@mkdir -p build inc
	@$(YACC) $(YFLAGS) -o build/y.tab.c src/grammaire/grammaire.y
	@mv build/y.tab.h inc/y.tab.h

build/y.tab.o: build/y.tab.c
	@$(CC) $(CFLAGS) -c build/y.tab.c -o build/y.tab.o

#####################################
# Cible rendu — NE PAS TOUCHER
#####################################
rendu:
	@echo "$(RED)\n→Création du rendu hebdo$(NC)"
	@mkdir -p rendus
	@mkdir -p rendus/ARCHIVE$(shell date +%Y%m%d)
	@cp -r src tests Makefile inc rendus/ARCHIVE$(shell date +%Y%m%d)/
	@cd rendus && zip -r ARCHIVE$(shell date +%Y%m%d).zip ARCHIVE$(shell date +%Y%m%d)

clean:
	@echo "$(RED)\n→Nettoyage...$(NC)"
	@rm -rf build bin inc/y.tab.h

clean_saves:
	@echo "$(RED)\n→Nettoyage des saves...$(NC)"
	@rm -rf saves