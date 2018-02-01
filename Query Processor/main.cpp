#include "pugixml/pugixml.hpp"
#include<iostream>
#include "tree.h"
extern int yyparse();
extern Sql_stmt *xyz123;
int main()
{
	pugi::xml_document doc;
	pugi::xml_parse_result result=doc.load_file("db.xml");
	pugi::xml_node root=doc.child("databases");
	while(true)
	{
		xyz123=0;
		yyparse();
		if(!xyz123)
			break;
		xyz123->check(root);
		if(!xyz123->error)
			xyz123->execute(root);
		else
			std::cout<<"Error\n";
	}
	doc.save_file("db.xml");
}