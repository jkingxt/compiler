Compile:lexical.l syntax.y main.c
	bison -d syntax.y
	flex lexical.l
	gcc main.c syntax.tab.c  -lfl -ly  -g -o  parser
