parser: lpl.l
	flex -o lpl.yy.c lpl.l
	gcc -o lpl.lexer lpl.yy.c -lfl
