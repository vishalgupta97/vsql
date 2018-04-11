#include<vector>
#include<string>
#include<unordered_map>
#include<unordered_set>
#include<map>
#include<utility>
#include<string.h>
#include<iostream>
#include "pugixml.hpp"
#include "libxl.h"
#include "LibBoolEE.h"
using namespace std;
class Table;
class Column;
class Database;
class Data
{
	public:int type;
	/*
	0=>Root
	1=>Database
	2=>Table
	3=>Column
	*/
};
class Root:public Data
{
	public:
	unordered_map<string,Database*> databases;
	pugi::xml_node node;
	pugi::xml_document doc;
	Root();
	void save();
};
class Database:public Data
{
	public:
	string name;
	libxl::Book* book;
	pugi::xml_node node;
	int cnt=0;
	unordered_map<string,Table*> tables;
	Database()
	{
		type=1;
	}
	Database(pugi::xml_node &node1);
	void save();
};
class Table:public Data
{
	public:
	string name;
	libxl::Sheet* sheet;
	pugi::xml_node node;
	int idx=0,rowcnt=0,pkcnt=0,col_cnt=0;
	unordered_map<string,Column*> columns;
	map<int,int> rows;//Rows having data
	bool rows_change=false;
	string primary_name;
	unordered_set<string> primary;
	unordered_map<string,unordered_set<string> > keys;
	unordered_map<string,pair<string,string> > foreign_keys;
	Table()
	{
		type=2;
	}
	Table(pugi::xml_node &node1,libxl::Book* book);
	void save();
};
class Column:public Data
{
	public:
	string name;
	int datatype,idx;
	pugi::xml_node node;
	bool attr[5];/*
	0=>unique
	1=>primary
	2=>auto_inc
	3=>not_null
	4=>foreign
	*/
	Column()
	{
		type=3;
	}
	Column(pugi::xml_node &node1);
};