#include<vector>
#include<string>
#include<utility>
#include<iostream>
#include<algorithm>
#include<map>
#include<unordered_set>
#include<set>
#include<stdlib.h>
#include<cstring>
#include "pugixml.hpp"
#include "blfilter.h"
#include "libxl.h"
#include "LibBoolEE.h"
#include "metadata.h"
using namespace std;
extern map<string,int> datatype_vals;
extern Database* curdb;
extern bool yacc_err;
class Data_val
{
	public:int type;
	union
	{
		string *s;//3,4
		int int_val;//1
		double dbl_val;//2
	}x;
	~Data_val()
	{
		if(type==3||type==4)
			delete x.s;
	}
};
class Where_stmt;
class Exp
{
	public:int type;
	bool error=false;
	Exp(int type1):type(type1){}
	virtual void check(Table* tbl)=0;
	virtual std::string gen(int &cnt,Where_stmt* stmt)=0;
	virtual ~Exp(){}
};
class Cond_exp:public Exp//1
{ public:
	string *lhs;
	Data_val *rhs;
	int op_type,col_idx;
	/* types
	= -> 1
	< -> 2
	> -> 3
	<= -> 4
	>= -> 5
	!= -> 6
	*/
	Cond_exp(int op_type1,string *lhs1,Data_val *rhs1):Exp(1),op_type(op_type1),lhs(lhs1),rhs(rhs1){}
	~Cond_exp()
	{
		if(lhs)
			delete lhs;
		if(rhs)
			delete rhs;
	}
	void check(Table* tbl);
	std::string gen(int &cnt,Where_stmt* stmt);
};
class And_exp:public Exp//2
{
	public:
	Exp *lhs,*rhs;
	And_exp(Exp *lhs1,Exp *rhs1):Exp(2),lhs(lhs1),rhs(rhs1){}
	~And_exp()
	{
		if(lhs)
			delete lhs;
		if(rhs)
			delete rhs;
	}
	void check(Table* tbl);
	std::string gen(int &cnt,Where_stmt* stmt);
};
class Or_exp:public Exp//3
{
	public:
	Exp *lhs,*rhs;
	Or_exp(Exp *lhs1,Exp *rhs1):Exp(3),lhs(lhs1),rhs(rhs1){}
	~Or_exp()
	{
		if(lhs)
			delete lhs;
		if(rhs)
			delete rhs;
	}
	void check(Table* tbl);
	std::string gen(int &cnt,Where_stmt* stmt);
};
class Where_stmt
{ public:
	Exp *exp;
	vector<Cond_exp*> exps;
	vector<int> res;//output index;
	Where_stmt(Exp *exp1):exp(exp1){}
	~Where_stmt()
	{
		if(exp)
			delete exp;
	}
	bool check(Table* tbl);
	void execute(Table* tbl,int limit);
};
class Orderby_stmt
{ public:
	vector<pair<string*,bool>* > *clmns_list;//asc=true,desc=false
	vector<int> res;
	libxl::Sheet* sheet;
	vector<pair<int,int> > index_type;//first-index,second-type
	Orderby_stmt(pair<string*,bool> *xyz)
	{
		clmns_list=new vector<pair<string*,bool>* >();
		clmns_list->push_back(xyz);
	}
	~Orderby_stmt()
	{
		if(clmns_list)
		{
			for(auto i=clmns_list->begin();i!=clmns_list->end();i++)
			{
				delete (*i)->first;
				delete *i;
			}
			clmns_list->clear();
			delete clmns_list;
		}
	}
	bool check(Table* tbl);
	void execute(Table* tbl);
};
class Special_ele
{ public:
	int type;//1- Not Null,2- Auto Increment,3- primary key,4- unique key,5- foreign key
	string *tbl_name,*col_name;
	Special_ele(int type1):Special_ele(type1,0,0){}
	Special_ele(int type1,string *name,string *name1):type(type1),tbl_name(name),col_name(name1){}
	~Special_ele(){
		if(tbl_name)
			delete tbl_name;
		if(col_name)
			delete col_name;
	}
};
class Col_def
{ public:
	string *col_name,*datatype;
	vector<Special_ele*> *list;
	Col_def(string *name,string *type,vector<Special_ele*> *list1):col_name(name),datatype(type),list(list1)	{}
	~Col_def(){
		if(col_name)
			delete col_name;
		if(datatype)
			delete datatype;
		if(list)
		{
			for(auto i=list->begin();i!=list->end();i++)
				delete *i;
			list->clear();
			delete list;
		}
	}
};
class Constraints
{ public:
	int type;
	vector<string*> *col_list;
	vector<string*> *to_list;
	string *tbl_name_to;
	Constraints(int type1,vector<string*> *list):type(type),col_list(list),to_list(NULL),tbl_name_to(NULL){}
	Constraints(int type1,vector<string*> *list,string *name,vector<string*> *list1):type(type1),col_list(list),tbl_name_to(name),to_list(list1){}
	~Constraints(){
		if(col_list)
		{
			for(auto i=col_list->begin();i!=col_list->end();i++)
				delete *i;
			col_list->clear();
			delete col_list;
		}
		if(to_list)
		{
			for(auto i=to_list->begin();i!=to_list->end();i++)
				delete *i;
			to_list->clear();
			delete to_list;
		}
		if(tbl_name_to)
			delete tbl_name_to;
	}
};
class Create_def
{ public:
	int type;
	union
	{
		Col_def *cd;//1
		Constraints *con;//2
	}x;
	~Create_def()
	{
		if(type==1&&x.cd)
			delete x.cd;
		else if(type==2&&x.con)
			delete x.con;
	}
};
class Change_col
{ public:
	string *col_name;
	Col_def *col;
	Change_col(string *name,Col_def *col1):col_name(name),col(col1){}
	~Change_col(){
		if(col_name)
			delete col_name;
		if(col)
			delete col;
	}
};
class Alter_spec
{ public:
	int type;
	union
	{
		vector<Col_def*> *add_col;
		Constraints *con;
		Change_col *cng_col;
	}x;
	~Alter_spec()
	{
		if(type==1&&x.add_col)
		{
			for(int i=0;i<x.add_col->size();i++)
				delete x.add_col->at(i);
			x.add_col->clear();
			delete x.add_col;
		}
		else if(type==2&&x.con)
			delete x.con;
		else if(type==3&&x.cng_col)
			delete x.cng_col;
	}
};
class Sql_stmt
{ public:
	int type,type_c;
	bool error=false;
	std::string error_msg;
	Sql_stmt(int type1):type(type1),type_c(0){}
	Sql_stmt(int type1,int type_c1):type(type1),type_c(type_c1){}
	virtual void check(Data *d)=0;
	virtual void execute(Data *d)=0;
	virtual ~Sql_stmt(){}
};
class Update_stmt:public Sql_stmt
{
	public:
	string *tbl_name;
	Orderby_stmt *orderby_cond;
	Where_stmt *where_cond;
	int limit;
	vector<pair<string*,Data_val*>* > *list;
	Update_stmt(string *name,vector<pair<string*,Data_val*>* > *list1,Where_stmt *cond1,Orderby_stmt *cond,int limit1):Sql_stmt(1),tbl_name(name),limit(limit1),list(list1),where_cond(cond1),orderby_cond(cond){	}
	~Update_stmt(){
		if(tbl_name)
			delete tbl_name;
		if(orderby_cond)
			delete orderby_cond;
	}
	void check(Data *d);
	void execute(Data *d);
};
class Select_stmt:public Sql_stmt
{
	public:
	vector<string*> *col_list;
	string *tbl_name;
	Where_stmt *where_cond;
	Orderby_stmt *orderby_cond;
	int limit=0;
	vector<pair<int,int> > index_type;//first-index,second-type
	Select_stmt(vector<string*> *list,string *name,Where_stmt *cond,Orderby_stmt *cond1,int limit1):Sql_stmt(2),tbl_name(name),limit(limit1),where_cond(cond),orderby_cond(cond1),col_list(list){}
	~Select_stmt(){
		if(col_list)
		{
			for(auto i=col_list->begin();i!=col_list->end();i++)
				delete *i;
			col_list->clear();
			delete col_list;
		}
		if(tbl_name)
			delete tbl_name;
		if(where_cond)
			delete where_cond;
		if(orderby_cond)
			delete orderby_cond;
	}
	void check(Data *d);
	void execute(Data *d);
};
class Drop_stmt: public Sql_stmt
{ public:
	Drop_stmt(int type1):Sql_stmt(3,type1){}
	virtual void check(Data *d)=0;
	virtual void execute(Data *d)=0;
	virtual ~Drop_stmt(){}
};
class Db_drop:public Drop_stmt
{
	public:
	string *db_name;
	Db_drop(string *name):Drop_stmt(1),db_name(name){}
	~Db_drop(){
		if(db_name)
			delete db_name;
	}
	void check(Data *d);
	void execute(Data *d);
};
class Tbl_drop:public Drop_stmt
{
	public:
	vector<string*> *tbl_list;
	Tbl_drop(vector<string*> *list):Drop_stmt(2),tbl_list(list){}
	~Tbl_drop(){
		if(tbl_list)
		{
			for(auto i=tbl_list->begin();i!=tbl_list->end();i++)
				delete *i;
			tbl_list->clear();
			delete tbl_list;
		}
	}
	void check(Data *d);
	void execute(Data *d);
};
class Idx_drop:public Drop_stmt
{
	public:
	string *tbl_name,*idx_name;
	Idx_drop(string *tbl,string *idx):Drop_stmt(3),tbl_name(tbl),idx_name(idx){}
	~Idx_drop(){
		if(tbl_name)
			delete tbl_name;
		if(idx_name)
			delete idx_name;
	}
	void check(Data *d);
	void execute(Data *d);
};
class View_drop:public Drop_stmt
{
	public:
	vector<string*> *view_list;
	View_drop(vector<string*> *list):Drop_stmt(4),view_list(list){}
	~View_drop(){
		if(view_list)
		{
			for(auto i=view_list->begin();i!=view_list->end();i++)
				delete *i;
			view_list->clear();
			delete view_list;
		}
	}
	void check(Data *d);
	void execute(Data *d);
};
class Create_stmt: public Sql_stmt
{ public:
	Create_stmt(int type1):Sql_stmt(4,type1){}
	virtual void check(Data *d)=0;
	virtual void execute(Data *d)=0;
	virtual ~Create_stmt(){}
};
class Db_create:public Create_stmt
{
	public:
	string *db_name;
	Db_create(string *name):Create_stmt(1),db_name(name){}
	~Db_create() {	
		if(db_name)
			delete db_name;
	}
	void check(Data *d);
	void execute(Data *d);
};
class Tbl_create:public Create_stmt
{
	public:
	string *tbl_name;
	vector<Create_def*> *list;
	bloom_filter *bfl;
	Tbl_create(string *name,vector<Create_def*> *list1):Create_stmt(2),tbl_name(name),list(list1){}
	~Tbl_create(){
		if(tbl_name)
			delete tbl_name;
		if(list)
		{
			for(auto i=list->begin();i!=list->end();i++)
				delete *i;
			list->clear();
			delete list;
		}
		if(bfl)
			delete bfl;
	}
	void check(Data *d);
	void execute(Data *d);
};
class Idx_create:public Create_stmt
{
	public:
	string *idx_name,*tbl_name,s;
	vector<string*> *col_list;
	Idx_create(string *idx,string *tbl,vector<string*> *list):Create_stmt(3),idx_name(idx),tbl_name(tbl){}
	~Idx_create(){
		if(idx_name)
			delete idx_name;
		if(tbl_name)
			delete tbl_name;
		if(col_list)
		{
			for(auto i=col_list->begin();i!=col_list->end();i++)
				delete *i;
			col_list->clear();
			delete col_list;
		}
	}
	void check(Data *d);
	void execute(Data *d);
};
class View_create:public Create_stmt
{
	public:
	string *view_name;
	vector<string*> *col_list;
	Select_stmt *stmt;
	View_create(string *name,vector<string*> *list,Select_stmt *stmt1):Create_stmt(4),view_name(name),stmt(stmt1),col_list(list){}
	~View_create()
	{
		if(view_name)
			delete view_name;
		if(col_list)
		{
			for(auto i=col_list->begin();i!=col_list->end();i++)
				delete *i;
			col_list->clear();
			delete col_list;
		}
		if(stmt)
			delete stmt;
	}
	void check(Data *d);
	void execute(Data *d);
};

class Insert_stmt:public Sql_stmt
{
	public:
	struct check
	{
		int idx,datatype;
		unordered_set<string> *key;
		bool foreign;
	};
	string *tbl_name;
	Column* auto_inc;
	vector<check> checker;
	int rowno=0,tbl_idx=0,pkcnt=0,auto_index=1;
	vector<string*> *cols;
	vector<vector<Data_val*>* > *data;
	pugi::xml_node tbl;
	Insert_stmt(string *name,vector<string*> *cols1,vector<vector<Data_val*>* > *data1):Sql_stmt(5),tbl_name(name),data(data1),cols(cols1),auto_inc(NULL){}
	~Insert_stmt(){
		if(tbl_name)
			delete tbl_name;
		if(cols)
		{
			for(auto i=cols->begin();i!=cols->end();i++)
				delete *i;
			cols->clear();
			delete cols;
		}
		if(data)
		{
			for(auto i=data->begin();i!=data->end();i++)
			{
				auto x=*i;
				for(auto j=x->begin();j!=x->end();j++)
					delete *j;
				x->clear();
				delete x;
			}
			data->clear();
			delete data;
		}
	}
	void check(Data *d);
	void execute(Data *d);
};
class Delete_stmt:public Sql_stmt
{
	public:
	string *tbl_name;
	Where_stmt *where_cond;
	Orderby_stmt *orderby_cond;
	int limit=0;
	struct check
	{
		int datatype,idx;
		unordered_set<string> *key;
	};
	vector<check> checker;
	Delete_stmt(string *name,Where_stmt *stmt,Orderby_stmt *stmt1,int limit1):Sql_stmt(6),tbl_name(name),limit(limit1),where_cond(stmt),orderby_cond(stmt1){}
	~Delete_stmt(){
		if(tbl_name)
			delete tbl_name;
		if(where_cond)
			delete where_cond;
		if(orderby_cond)
			delete orderby_cond;
	}
	void check(Data *d);
	void execute(Data *d);
	void compress(vector<int> &res,map<int,int> &vals);
};
class Rename_stmt:public Sql_stmt
{
	public:
	vector<pair<string*,string*>* > *list;
	Rename_stmt(vector<pair<string*,string*>* > *list1):Sql_stmt(7),list(list1){}
	~Rename_stmt()
	{
		if(list)
		{
			for(auto i=list->begin();i!=list->end();i++)
			{
				delete (*i)->first;
				delete (*i)->second;
				delete *i;
			}
			list->clear();
			delete list;
		}
	}
	void check(Data *d);
	void execute(Data *d);
};
class Alter_stmt:public Sql_stmt
{
	public:
	string *tbl_name;
	vector<Alter_spec*> *spec_list;
	Alter_stmt(string *name,vector<Alter_spec*> *list):Sql_stmt(8),tbl_name(name),spec_list(list){}
	~Alter_stmt(){
		if(tbl_name)
			delete tbl_name;
		if(spec_list)
		{
			for(auto i=spec_list->begin();i!=spec_list->end();i++)
				delete *i;
		}
	}
	void check(Data *d);
	void execute(Data *d);
};
class Use_stmt:public Sql_stmt
{
	public:
	string *db_name;
	Use_stmt(string *name):Sql_stmt(9),db_name(name){}
	~Use_stmt(){
		if(db_name)
			delete db_name;
	}
	void check(Data *d);
	void execute(Data *d);
};
class Show_stmt: public Sql_stmt
{ public:
	Show_stmt(int type1):Sql_stmt(10,type1){}
	virtual void check(Data *d)=0;
	virtual void execute(Data *d)=0;
	virtual ~Show_stmt(){}
};
class Db_show:public Show_stmt
{
	public:
	Db_show():Show_stmt(1){}
	void check(Data *d);
	void execute(Data *d);
};
class Tbl_show:public Show_stmt
{
	public:
	string *db_name;
	Tbl_show(string *name):Show_stmt(2),db_name(name){}
	~Tbl_show(){
		if(db_name)
			delete db_name;
	}
	void check(Data *d);
	void execute(Data *d);
};
class Clmns_show:public Show_stmt
{
	public:
	string *db_name,*tbl_name;
	Clmns_show(string *name,string *name1):Show_stmt(3),tbl_name(name),db_name(name1){}
	~Clmns_show(){
		if(db_name)
			delete db_name;
		if(tbl_name)
			delete tbl_name;
	}
	void check(Data *d);
	void execute(Data *d);
};