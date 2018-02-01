all: sql

parser: sql.tab.c sql.tab.h
	bison -d sql.y

lexer: lex.yy.c 
	flex sql.l

sql : lexer parser
	-g++ -I ../Library --std=c++14 ../Library/pugixml/pugixml.cpp lex.yy.c sql.tab.c main.cpp -lfl 2> error.txt
	/mnt/c/Windows/System32/notepad.exe error.txt