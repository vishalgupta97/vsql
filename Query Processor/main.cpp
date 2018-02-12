#include "pugixml/pugixml.hpp"
#include<iostream>
#include "tree.h"
extern int yyparse();
extern Sql_stmt *stmt1;
void delete_tree(Sql_stmt *xyz)
{
	switch(xyz->type)
	{
		case 1: delete (Update_stmt*)stmt1;
		break;
		case 2: delete (Select_stmt*)stmt1;
		break;
		case 3: switch(xyz->type_c)
		{
			case 1: delete (Db_drop*)stmt1;
			break;
			case 2: delete (Tbl_drop*)stmt1;
			break;
			case 3: delete (Idx_drop*)stmt1;
			break;
			case 4: delete (View_drop*)stmt1;
			break;
		}
		break;
		case 4: switch(xyz->type_c)
		{
			case 1: delete (Db_create*)stmt1;
			break;
			case 2: delete (Tbl_create*)stmt1;
			break;
			case 3: delete (Idx_create*)stmt1;
			break;
			case 4: delete (View_create*)stmt1;
			break;
		}
		break;
		case 5: delete (Insert_stmt*)stmt1;
		break;
		case 6: delete (Delete_stmt*)stmt1; 
		break;
		case 7: delete (Rename_stmt*)stmt1; 
		break;
		case 8: delete (Alter_stmt*)stmt1;
		break;
		case 9: delete (Use_stmt*)stmt1; 
		break;
		case 10: switch(xyz->type_c)
		{
			case 1: delete (Db_show*)stmt1;
			break;
			case 2: delete (Tbl_show*)stmt1;
			break;
			case 3: delete (Clmns_show*)stmt1;
			break;
		}
		break;
	}
}
int main()
{
	pugi::xml_document doc;
	pugi::xml_parse_result result=doc.load_file("db.xml");
	pugi::xml_node root=doc.child("databases");
	//pugi::xml_node curdb=NULL;
	while(true)
	{
		yyparse();
		if(!stmt1)
			break;
		stmt1->check(root);
		if(!stmt1->error)
			stmt1->execute(root);
		else
			std::cout<<"Error\n";
		delete_tree(stmt1);
	}
	doc.save_file("db.xml");
}