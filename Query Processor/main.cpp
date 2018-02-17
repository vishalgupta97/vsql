#include "pugixml/pugixml.hpp"
#include<iostream>
#include "tree.h"
extern int yyparse();
extern Sql_stmt *stmt1;
int main()
{
	pugi::xml_document doc;
	pugi::xml_parse_result result=doc.load_file("db.xml");
	pugi::xml_node root=doc.child("databases");
	pugi::xml_node curdb;
	while(true)
	{
		yyparse();
		if(!stmt1)
			break;
		if(stmt1->type==9||stmt1->type==10)
		{
			stmt1->check(root);
			if(!stmt1->error)
				stmt1->execute(root);
			else
				std::cout<<"Error\n";
		}
		else
		{
			stmt1->check(curdb);
			if(!stmt1->error)
				stmt1->execute(curdb);
			else
				std::cout<<"Error\n";
		}
		delete stmt1;
	}
	doc.save_file("db.xml");
}