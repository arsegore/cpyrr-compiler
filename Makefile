.PHONY: grammaire lex.yy.o lex.yy.c y.tab.c

grammaire: lex.yy.o 
	gcc y.tab.c -o grammaire lex.yy.o -ly

lex.yy.o: lex.yy.c y.tab.c
	gcc -c lex.yy.c

lex.yy.c:
	lex grammaire.l

y.tab.c: 
	byacc -dv grammaire.y

clean: 
	rm -f y.tab.c lex.yy.c y.tab.h grammaire lex.yy.o