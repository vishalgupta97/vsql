#include "pugixml.hpp"
#include<iostream>
#include<time.h>
#include "tree.h"
#include "libxl.h"
extern int yyparse();
extern Sql_stmt *stmt1;
map<string,string> datatype_vals;
pugi::xml_node curdb;
bool yacc_err;
void initdatatype()
{
	datatype_vals.insert({"int","1"});
	datatype_vals.insert({"decimal","2"});
	datatype_vals.insert({"timestamp","3"});
	datatype_vals.insert({"varchar","4"});
}
int main()
{
	initdatatype();
	pugi::xml_document doc;
	pugi::xml_parse_result result=doc.load_file("db.xml");
	pugi::xml_node root=doc.child("databases");
	curdb=root.child("market");
	libxl::Book* book=xlCreateBook();
	book->load("market.xls");
	clock_t start,end;
	while(true)
	{
		std::cout<<curdb.name()<<"> ";
		yacc_err=false;
		start = clock();
		yyparse();
		if(!stmt1)
			break;
		if(stmt1->type==9||stmt1->type==10||(stmt1->type==4&&stmt1->type_c==1)||(stmt1->type==3&&stmt1->type_c==1))
		{
			stmt1->check(root,book);
			if(!stmt1->error)
				stmt1->execute(root,book);
			else
				std::cout<<"Error "<<stmt1->error_msg<<"\n";
		}
		else
		{
			stmt1->check(curdb,book);
			if(!stmt1->error)
				stmt1->execute(curdb,book);
			else
				std::cout<<"Error "<<stmt1->error_msg<<"\n";
		}
		end = clock();
		cout<<"Time: "<<(((double) (end - start)) / CLOCKS_PER_SEC)<<" sec\n";
		if(stmt1&&!stmt1->error)
		{
			doc.save_file("db.xml");
			book->save(string(curdb.name()).append(".xls").c_str());
		}
		if(stmt1)
		delete stmt1;
	}
	book->release();
}