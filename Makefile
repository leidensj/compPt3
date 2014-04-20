etapa2: hash.o lex.yy.o main.o y.tab.o astree.o
	gcc hash.o lex.yy.o main.o y.tab.o astree.o -o etapa3
hash.o: hash.c
	gcc -c hash.c 
astree.o: astree.c
	gcc -c astree.c
main.o: main.c
	gcc -c main.c 
y.tab.o: y.tab.c
	gcc -c y.tab.c
lex.yy.o: lex.yy.c
	gcc -c lex.yy.c 
y.tab.c: parser.y
	yacc parser.y -d -v
lex.yy.c: scanner.l
	lex scanner.l

clean:
	rm *.o etapa3 lex.yy.c 
