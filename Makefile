CC=g++
LIB=Library
CON=Connections
QP=Query\ Processor
ARCH = $(shell getconf LONG_BIT)
ifeq ($(ARCH), 32)
  LIBPATH = $(LIB)/libxl/lib
else
  LIBPATH = $(LIB)/libxl/lib64
endif
CFLAGS = -I $(LIB)/pugixml -I $(LIB)/libxl/include_cpp $(LIB)/pugixml/pugixml.cpp -L $(LIBPATH) -I $(LIB)/LibBool $(LIB)/LibBool/LibBoolEE.cpp --std=c++17 -Wl,-rpath,$(LIBPATH)

all: sql

parser: $(QP)/sql.y
	bison -d --output=$(QP)/sql.tab.c $(QP)/sql.y

lexer: $(QP)/sql.l
	flex --header-file=$(QP)/sql.h --outfile=$(QP)/sql.c $(QP)/sql.l

sql : lexer parser
	-g++ $(CFLAGS) $(QP)/sql.c $(QP)/sql.tab.c $(QP)/metadata.cpp $(QP)/tree.cpp $(QP)/execute.cpp $(CON)/main.cpp -lxl -lfl -pthread 2> error.txt
	/mnt/c/Windows/System32/notepad.exe error.txt