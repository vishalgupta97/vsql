#include "pugixml.hpp"
#include<iostream>
#include<time.h>
#include<sstream>
#include<thread>
#include "libxl.h"
#include "sql.tab.h"
#include "sql.h"
#include<sys/types.h>
#include<sys/socket.h>
using namespace std;
void send_data(stringstream &output,int connfd)
{
	string s=output.str();
	char *buf=new char[s.length()+1];
	strcpy(buf,s.c_str());
	buf[s.length()]=0;
	send(connfd,buf,s.length()+1,0);
	delete [] buf;
	output.str("");
}
void run(int connfd)
{
	Database* curdb=NULL;
	char buf[1024];
	stringstream output;
	while(true)
	{
		if(curdb)
			output<<curdb->name<<"> ";
		else
			output<<"> ";
		send_data(output,connfd);
		Sql_stmt *stmt1=0;
		yyscan_t scanner;
		yylex_init(&scanner);
		int len=recv(connfd,buf,1022,0);
		if(len==1)
			break;
		buf[len]=0;
		buf[len+1]=0;
		yyset_in(fmemopen(buf,len+2, "r"),scanner);
		int yacc_err=yyparse(scanner,&stmt1);
		yylex_destroy(scanner);
		if(yacc_err>0)
			output<<"Parsing Error\n";
		else
		{
			if(!stmt1)
				break;
			if(!(stmt1->type==9||stmt1->type==10||(stmt1->type==4&&stmt1->type_c==1)||(stmt1->type==3&&stmt1->type_c==1))&&curdb==NULL)
				output<<"Error No Current Database"<<"\n";
			else
			{
				stmt1->check(&curdb);
				if(!stmt1->error)
				{
					stmt1->execute(&curdb);
					if(stmt1->output.tellp()>0)
						output<<stmt1->output.str();
				}
				else
					output<<"Error "<<stmt1->error_msg<<"\n";
			}
		}
		if(stmt1)
		delete stmt1;
	}
	if(curdb)
		curdb->save();
	root->save();
}