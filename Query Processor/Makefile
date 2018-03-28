CC=g++
LIB=../Library
ARCH = $(shell getconf LONG_BIT)
ifeq ($(ARCH), 32)
  LIBPATH = $(LIB)/libxl/lib
else
  LIBPATH = $(LIB)/libxl/lib64
endif
CFLAGS = -I $(LIB)/pugixml -I $(LIB)/libxl/include_cpp $(LIB)/pugixml/pugixml.cpp -L $(LIBPATH) -I $(LIB)/LibBoolEE $(LIB)/LibBoolEE/LibBoolEE.cpp --std=c++14 -Wl,-rpath,$(LIBPATH)

all: sql

parser: sql.tab.c sql.tab.h
	bison -d sql.y

lexer: lex.yy.c 
	flex sql.l

sql : lexer parser
	-g++ $(CFLAGS) lex.yy.c sql.tab.c tree.cpp main.cpp -lxl -lfl 2> error.txt
	/mnt/c/Windows/System32/notepad.exe error.txt