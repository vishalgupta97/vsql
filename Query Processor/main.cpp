#include "pugixml.hpp"
#include<iostream>
#include<time.h>
#include "tree.h"
#include "libxl.h"
using namespace std;
extern int yyparse();
extern Sql_stmt *stmt1;
map<string,int> datatype_vals;
Database* curdb;
bool yacc_err;
void initdatatype()
{
	datatype_vals.insert({"int",1});
	datatype_vals.insert({"decimal",2});
	datatype_vals.insert({"timestamp",3});
	datatype_vals.insert({"varchar",4});
}
int main()
{
	initdatatype();
	Root *root=new Root();
	clock_t start,end;
	while(true)
	{
		if(curdb)
			cout<<curdb->name<<"> ";
		else
			cout<<"> ";
		yacc_err=false;
		start = clock();
		yyparse();
		if(!stmt1)
			break;
		if(stmt1->type==9||stmt1->type==10||(stmt1->type==4&&stmt1->type_c==1)||(stmt1->type==3&&stmt1->type_c==1))
		{
			stmt1->check(root);
			if(!stmt1->error)
				stmt1->execute(root);
			else
				cout<<"Error "<<stmt1->error_msg<<"\n";
		}
		else
		{
			if(curdb==NULL)
			{
				cout<<"Error No Current Database"<<"\n";
			}
			else
			{
				stmt1->check(curdb);
				if(!stmt1->error)
					stmt1->execute(curdb);
				else
					cout<<"Error "<<stmt1->error_msg<<"\n";
			}
		}
		end = clock();
		cout<<"Time: "<<(((double) (end - start)) / CLOCKS_PER_SEC)<<" sec\n"<<endl;
		if(stmt1&&!stmt1->error)
		{
			if(curdb)
				curdb->save();
			root->save();
		}
		if(stmt1)
		delete stmt1;
	}
}