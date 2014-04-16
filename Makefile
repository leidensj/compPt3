etapa2: y.tab.o hash.o lex.yy.o main.o
	gcc hash.o lex.yy.o main.o y.tab.o -o etapa2
hash.o: hash.c
	gcc -c hash.c 
astree.o: astree.c
     gcc -c asstree.c
main.o: main.c
	gcc -c main.c 
lex.yy.o: lex.yy.c
	gcc -c lex.yy.c 
lex.yy.c: scanner.l
	lex scanner.l
y.tab.o: y.tab.c
	gcc -c y.tab.c
y.tab.c: y.tab.h
	yacc --debug parser.y
y.tab.h: parser.y
	yacc --debug -d parser.y


clean:
	rm *.o etapa2 lex.yy.* y.tab.* y.output
