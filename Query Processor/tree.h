#include<vector>
#include<string>
#include<utility>
#include<iostream>
#include<algorithm>
#include<map>
#include<stdlib.h>
#include "pugixml.hpp"
#include "blfilter.h"
#include "libxl.h"
using namespace std;
extern map<string,string> datatype_vals;
extern pugi::xml_node curdb;
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
class Cond_exp
{ public:
	string *lhs;
	Data_val *rhs;
	~Cond_exp()
	{
		if(lhs)
			delete lhs;
		if(rhs)
			delete rhs;
	}
};
class Where_stmt
{ public:
	vector<Cond_exp*> *and_list;
	vector<Cond_exp*> *or_list;
	Cond_exp *first;
	Where_stmt(Cond_exp *exp):first(exp){}
	~Where_stmt()
	{
		if(and_list)
		{
			for(auto i=and_list->begin();i!=and_list->end();i++)
				delete *i;
			and_list->clear();
			delete and_list;
		}
		if(or_list)
		{
			for(auto i=or_list->begin();i!=or_list->end();i++)
				delete *i;
			or_list->clear();
			delete or_list;
		}
		if(first)
			delete first;
	}
	bool check(pugi::xml_node tbl_clmns)
	{
		pugi::xml_node clmn=tbl_clmns.child(first->lhs->c_str());
			if(clmn==NULL||stoi(clmn.attribute("datatype").value())!=first->rhs->type)
				return false;
		for(int i=0;i<and_list->size();i++)
		{
		    clmn=tbl_clmns.child(and_list->at(i)->lhs->c_str());
			if(clmn==NULL||stoi(clmn.attribute("datatype").value())!=and_list->at(i)->rhs->type)
				return false;
		}
		for(int i=0;i<or_list->size();i++)
		{
			clmn=tbl_clmns.child(or_list->at(i)->lhs->c_str());
			if(clmn==NULL||stoi(clmn.attribute("datatype").value())!=or_list->at(i)->rhs->type)
				return false;
		}
		return true;
	}
};
class Orderby_stmt
{ public:
	vector<pair<string*,bool>* > *clmns_list;//asc=true,desc=false
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
	bool check(pugi::xml_node tbl_clmn)
	{
		for(int i=0;i<clmns_list->size();i++)
		{
			if(tbl_clmn.child(clmns_list->at(i)->first->c_str())==NULL)
			{
				return false;
			}
		}
		return true;
	}
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
	virtual void check(pugi::xml_node &db_node,libxl::Book* &book)=0;
	virtual void execute(pugi::xml_node &db_node,libxl::Book* &book)=0;
	virtual ~Sql_stmt(){}
};
class Update_stmt: public Sql_stmt
{ public:
	string *tbl_name;
	Orderby_stmt *orderby_cond;
	int limit;
	vector<pair<string*,Data_val*>* > *list;
	Update_stmt(string *name,vector<pair<string*,Data_val*>* > *list1,Orderby_stmt *cond,int limit1):Sql_stmt(1),tbl_name(name),limit(limit1),list(list1),orderby_cond(cond){	}
	~Update_stmt(){
		if(tbl_name)
			delete tbl_name;
		if(orderby_cond)
			delete orderby_cond;
	}
	void check(pugi::xml_node &db_node,libxl::Book* &book)
	{
		
	}
	void execute(pugi::xml_node &db_node,libxl::Book* &book)
	{
		
	}
};
class Select_stmt: public Sql_stmt
{ public:
	vector<string*> *col_list;
	string *tbl_name;
	Where_stmt *where_cond;
	Orderby_stmt *orderby_cond;
	int limit;
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
	void check(pugi::xml_node &db_node,libxl::Book* &book)
	{
		
	}
	void execute(pugi::xml_node &db_node,libxl::Book* &book)
	{
		
	}
} ;
class Drop_stmt: public Sql_stmt
{ public:
	Drop_stmt(int type1):Sql_stmt(3,type1){}
	virtual void check(pugi::xml_node &db_node,libxl::Book* &book)=0;
	virtual void execute(pugi::xml_node &db_node,libxl::Book* &book)=0;
	virtual ~Drop_stmt(){}
} ;
class Db_drop: public Drop_stmt
{ public:
	string *db_name;
	pugi::xml_node n_db_node;
	Db_drop(string *name):Drop_stmt(1),db_name(name){}
	~Db_drop(){
		if(db_name)
			delete db_name;
	}
	void check(pugi::xml_node &db_node,libxl::Book* &book)
	{
		if(db_name==NULL)
		{
			error=true;
			error_msg="Database name not provided";
			return;
		}
		if(curdb&&db_name->compare(curdb.name())==0)
		{
			error=true;
			error_msg="Cannot drop current db";
			return;
		}
		n_db_node=db_node.child(db_name->c_str());
		if(n_db_node==NULL)
		{
			error=true;
			error_msg="Database name does not exist";
		}
	}
	void execute(pugi::xml_node &db_node,libxl::Book* &book)
	{
		remove(db_name->append(".xls").c_str());
		db_node.remove_child(n_db_node);
	}
};
class Tbl_drop: public Drop_stmt
{ public:
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
	void check(pugi::xml_node &db_node,libxl::Book* &book)
	{
		for(int i=0;i<tbl_list->size();i++)
			if(db_node.child(tbl_list->at(i)->c_str())==NULL)
			{
				error=true;
				error_msg="Table name does not exist";
				return;
			}
	}
	void execute(pugi::xml_node &db_node,libxl::Book* &book)
	{
		for(int i=0;i<tbl_list->size();i++)
		{
			book->delSheet(atoi(db_node.child(tbl_list->at(i)->c_str()).attribute("index").value()));
			db_node.remove_child(tbl_list->at(i)->c_str());
		}
	}
};
class Idx_drop: public Drop_stmt
{ public:
	string *tbl_name,*idx_name;
	Idx_drop(string *tbl,string *idx):Drop_stmt(3),tbl_name(tbl),idx_name(idx){}
	~Idx_drop(){
		if(tbl_name)
			delete tbl_name;
		if(idx_name)
			delete idx_name;
	}
	void check(pugi::xml_node &db_node,libxl::Book* &book)
	{
		
	}
	void execute(pugi::xml_node &db_node,libxl::Book* &book)
	{
		
	}
};
class View_drop: public Drop_stmt
{ public:
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
	void check(pugi::xml_node &db_node,libxl::Book* &book)
	{
		
	}
	void execute(pugi::xml_node &db_node,libxl::Book* &book)
	{
		
	}
};
class Create_stmt: public Sql_stmt
{ public:
	Create_stmt(int type1):Sql_stmt(4,type1){}
	virtual void check(pugi::xml_node &db_node,libxl::Book* &book)=0;
	virtual void execute(pugi::xml_node &db_node,libxl::Book* &book)=0;
	virtual ~Create_stmt(){}
} ;
class Db_create: public Create_stmt
{ public:
	string *db_name;
	Db_create(string *name):Create_stmt(1),db_name(name){}
	~Db_create() {	
		if(db_name)
			delete db_name;
	}
	void check(pugi::xml_node &db_node,libxl::Book* &book)
	{
		if(!db_name)
		{
			error=true;
			error_msg="Database name not provided";
			return;
		}
		pugi::xml_node node=db_node.child(db_name->c_str());
		if(node)
		{
			error=true;
			error_msg="Database already exist";
		}
	}
	void execute(pugi::xml_node &db_node,libxl::Book* &book)
	{
		libxl::Book* n_book=xlCreateBook();
		pugi::xml_node node=db_node.append_child(db_name->c_str());
		n_book->addSheet(string("Sheet1").c_str());
		n_book->save(db_name->append(".xls").c_str());
		n_book->release();
		pugi::xml_attribute atr=node.append_attribute("count");
		atr.set_value("0");
	}
};
class Tbl_create: public Create_stmt
{ public:
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
	void check(pugi::xml_node &db_node,libxl::Book* &book)
	{
		if(!tbl_name)
		{
			error=true;
			error_msg="Table name not provided";
			return;
		}
		if(!list)
		{
			error=true;
			error_msg="Table defination not provided";
			return;
		}
		if(db_node.child(tbl_name->c_str()))
		{
			error=true;
			error_msg="Table already exist";
			return;
		}
		bfl=new bloom_filter();
		bool primary_key=false;
		string *auto_inc=NULL;
		std::stable_sort(list->begin(),list->end(),[](Create_def* a,Create_def* b){
			return a->type<b->type;
		});
		for(int i=0;i<list->size();i++)
		{
			if(list->at(i)->type==1)
			{
				Col_def *cd=list->at(i)->x.cd;
				if(bfl->chk_hash(cd->col_name->c_str()))
				{
					string s=*(cd->col_name);
					for(int j=0;j<i;j++)
					{
						if(list->at(j)->type==1&&list->at(j)->x.cd->col_name->compare(s)==0)
						{
							error=true;
							error_msg="Columns with same name";
							return;
						}
					}
			    }
				if(cd->list)
				{
					for(int i=0;i<cd->list->size();i++)
						switch(cd->list->at(i)->type)
						{
							case 2:auto_inc=cd->col_name;
							case 3:if(primary_key)
									{
										error=true;
										error_msg="Primary Key already defined";
										return;
									}
									else
									primary_key=true;
								break;
							case 5:if(db_node.child(cd->list->at(i)->tbl_name->c_str()).child("columns").child(cd->list->at(i)->col_name->c_str()).attribute("unique")==NULL)
							{
								error=true;
								error_msg="Foreign Key Column in not unique";
								return;
							}
							break;
						}
				}
			} 
			else
			{
				Constraints *con=list->at(i)->x.con;
				if(con->type==1)
				{
					if(auto_inc!=NULL)
					{
						if(primary_key)
						{
							error=true;
							error_msg="Primary Key already defined";
							return;
						}
					}
					else if(con->col_list->size()!=1||con->col_list->at(0)->compare(*auto_inc)!=0)
					{
						error=true;
						error_msg="Primary Key already defined";
						return;
					}
				}
				for(int j=0;j<con->col_list->size();j++)
				{
					if(!bfl->chk_hash(con->col_list->at(j)->c_str()))
					{
						error=true;
						error_msg="Column does not exist";
						return;
					}
				}
				if(con->type==4)
				{
					if(con->col_list->size()!=con->to_list->size())
					{
						error=true;
						error_msg="Foreign Key list does not match Primary Key list";
						return;
					}
					pugi::xml_node to_tbl=db_node.child(con->tbl_name_to->c_str());
					if(to_tbl==NULL)
					{
						error=true;
						error_msg="Foreign Table does not exist";
						return;
					}
					string s="";
					for(int j=0;j<con->to_list->size();j++)
					{
						if(!bfl->chk_hash(con->col_list->at(j)->c_str())||to_tbl.child(con->to_list->at(j)->c_str())==NULL)
						{
							error=true;
							error_msg="Column does not exist";
							return;
						}
						else
						{
							s+=*(con->to_list->at(i))+"-";
						}
					}
					if(to_tbl.child(s.c_str()).attribute("unique")==NULL)
					{
						error=true;
						error_msg="Foreign Key Columns are not unique";
						return;
					}
				}
			}
		}	
	}
	void execute(pugi::xml_node &db_node,libxl::Book* &book)
	{
		pugi::xml_node tbl=db_node.append_child(tbl_name->c_str());
		pugi::xml_attribute atr=tbl.append_attribute("index");
		atr.set_value(to_string(stoi(db_node.attribute("count").value())+1).c_str());
		db_node.attribute("count").set_value(atr.value());
		atr=tbl.append_attribute("rowcnt");
		atr.set_value("0");
		book->addSheet(tbl_name->c_str());
		pugi::xml_node clmns=tbl.append_child("columns");
		pugi::xml_node attrs=tbl.append_child("attributes");
		for(int i=0;i<list->size();i++)
		{
			if(list->at(i)->type==1)
			{
				Col_def* cd=list->at(i)->x.cd;
				pugi::xml_node clmn=clmns.append_child(cd->col_name->c_str());
				pugi::xml_attribute atr_type=clmn.append_attribute("datatype");
				atr_type.set_value(datatype_vals[*(cd->datatype)].c_str());
				pugi::xml_attribute atr_index=clmn.append_attribute("index");
				atr_index.set_value(to_string(i+1).c_str());
				bool not_null=false,ainc=false,primary=false,unique=false,foreign=false;
				Special_ele *se=NULL;
				if(cd->list)
				{
					for(int j=0;j<cd->list->size();j++)
					{
						switch(cd->list->at(j)->type)
						{
							case 1:not_null=true;break;
							case 2:ainc=true;break;
							case 3:primary=true;not_null=true;ainc=true;unique=true;break;
							case 4:unique=true;break;
							case 5:foreign=true;se=cd->list->at(j);break;
						}
					}
				}
				if(unique)
					clmn.append_attribute("unique");
				if(primary)
					clmn.append_attribute("primary");
				if(ainc)
					clmn.append_attribute("auto_inc");
				if(not_null)
					clmn.append_attribute("not_null");
				if(foreign)
				{
					clmn.append_attribute("foreign");
					pugi::xml_attribute atr=clmn.append_attribute("to_tbl");
					atr.set_value(se->tbl_name->c_str());
					atr=clmn.append_attribute("to_clmn");
					atr.set_value(se->col_name->c_str());
					
				}	
			}
			else
			{
				Constraints *con=list->at(i)->x.con;
				if(con->col_list->size()>1)
				{
					string s="";
					for(int j=0;j<con->col_list->size();j++)
					{
						s+=*(con->col_list->at(j))+"-";
					}
					pugi::xml_node chld=attrs.append_child(s.c_str());
					switch(con->type)
					{
						case 1:chld.append_attribute("unique");
						chld.append_attribute("primary");
						break;
						case 2:chld.append_attribute("index");
						break;
						case 3:chld.append_attribute("unique");
						case 4:pugi::xml_attribute atr=chld.append_attribute("foreign_tbl");
						atr.set_value(con->tbl_name_to->c_str());
						string y="";
						for(int j=0;j<con->to_list->size();j++)
							y+=*(con->to_list->at(j))+"-";
						atr=chld.append_attribute("foreign_clmn");
						atr.set_value(y.c_str());
					}
				}
				else
				{
					pugi::xml_node chld=tbl.child(con->col_list->at(0)->c_str());
					switch(con->type)
					{
						case 1:chld.append_attribute("unique");
						chld.append_attribute("primary");
						chld.append_attribute("auto_inc");
						chld.append_attribute("not_null");
						break;
						case 2:chld.append_attribute("index");break;
						case 3:chld.append_attribute("unique");
						case 4:chld.append_attribute("foreign");
						pugi::xml_attribute atr=chld.append_attribute("to_tbl");
						atr.set_value(con->tbl_name_to->c_str());
						atr=chld.append_attribute("to_clmn");
						atr.set_value(con->to_list->at(0)->c_str());
						break;
					}
				}
			}
		}
	}
};
class Idx_create: public Create_stmt
{ public:
	string *idx_name,*tbl_name;
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
	void check(pugi::xml_node &db_node,libxl::Book* &book)
	{
		
	}
	void execute(pugi::xml_node &db_node,libxl::Book* &book)
	{
		
	}
};
class View_create: public Create_stmt
{ public:
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
	void check(pugi::xml_node &db_node,libxl::Book* &book)
	{
		
	}
	void execute(pugi::xml_node &db_node,libxl::Book* &book)
	{
		
	}
};
class Insert_stmt: public Sql_stmt
{ public:
	string *tbl_name;
	vector<int> checker;
	vector<int> indexes;
	int rowno=0,tbl_idx=0;
	vector<string*> *cols;
	vector<vector<Data_val*>* > *data;
	Insert_stmt(string *name,vector<string*> *cols1,vector<vector<Data_val*>* > *data1):Sql_stmt(5),tbl_name(name),data(data1),cols(cols1){}
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
	/*bool int_check(Data_val *s)
	{
		return s->type==1;
	}
	bool decimal_check(Data_val *s)
	{
		return s->type==2;
	}
	bool timestamp_check(Data_val *s)
	{
		return s->type==3;
	}
	bool varchar_check(Data_val *s)
	{
		return s->type==4;
	}*/
	void check(pugi::xml_node &db_node,libxl::Book* &book)
	{
		pugi::xml_node tbl_clmn=db_node.child(tbl_name->c_str()).child("columns");
		if(tbl_clmn==NULL)
		{
			error=true;
			error_msg="Column does not exist";
			return;
		}
		if(cols==NULL)
		{
			for(auto i=tbl_clmn.begin();i!=tbl_clmn.end();i++)
			{
				if((*i).attribute("primary")==NULL)
				{
					checker.push_back(stoi((*i).attribute("datatype").value()));
					indexes.push_back(stoi((*i).attribute("index").value()));
				}
			}
		}
		else
		{
			for(int i=0;i<cols->size();i++)
			{
				pugi::xml_node clmn=tbl_clmn.child(cols->at(i)->c_str());
				if(clmn==NULL)
				{
					error=true;
					error_msg="Columns does not exist";
					return;
				}
				checker.push_back(stoi(clmn.attribute("datatype").value()));
				indexes.push_back(stoi(clmn.attribute("index").value()));
			}
		}
		for(int i=0;i<data->size();i++)
		{
			vector<Data_val*>* vec=data->at(i);
			if(vec->size()!=checker.size())
			{
				error=true;
				error_msg="Data list size does not match Column list size";
				return;
			}
			for(int j=0;j<checker.size();j++)
			{
				if(checker[j]!=vec->at(j)->type)
				{
					error=true;
					error_msg="Datatype mismatch";
					return;
				}
			}
		}
		rowno=stoi(db_node.child(tbl_name->c_str()).attribute("rowcnt").value());
		tbl_idx=stoi(db_node.child(tbl_name->c_str()).attribute("index").value());
	}
	void execute(pugi::xml_node &db_node,libxl::Book* &book)
	{
		libxl::Sheet *sheet=book->getSheet(tbl_idx);
		for(int i=0;i<data->size();i++)
		{
			vector<Data_val*>* vec=data->at(i);
			rowno++;
			for(int j=0;j<vec->size();j++)
			{
				switch(vec->at(j)->type)
				{
					case 1:sheet->writeNum(rowno,indexes[j],vec->at(j)->x.int_val);
					break;
					case 2:sheet->writeNum(rowno,indexes[j],vec->at(j)->x.dbl_val);break;
					case 3:sheet->writeStr(rowno,indexes[j],vec->at(j)->x.s->c_str());break;
					case 4:sheet->writeStr(rowno,indexes[j],vec->at(j)->x.s->c_str());break;
				}
			}
		}
		db_node.child(tbl_name->c_str()).attribute("rowcnt").set_value(to_string(rowno).c_str());
	}
} ;
class Delete_stmt: public Sql_stmt
{ public:
	string *tbl_name;
	Where_stmt *where_cond;
	Orderby_stmt *orderby_cond;
	int limit;
	Delete_stmt(string *name,Where_stmt *stmt,Orderby_stmt *stmt1,int limit1):Sql_stmt(6),tbl_name(name),limit(limit1),where_cond(stmt),orderby_cond(stmt1){}
	~Delete_stmt(){
		if(tbl_name)
			delete tbl_name;
		if(where_cond)
			delete where_cond;
		if(orderby_cond)
			delete orderby_cond;
	}
	void check(pugi::xml_node &db_node,libxl::Book* &book)
	{
		pugi::xml_node tbl_clmn=db_node.child(tbl_name->c_str()).child("columns");
		if(tbl_clmn==NULL)
		{
			error=true;
			error_msg="Column does not exist";
			return;
		}
		if(!where_cond->check(tbl_clmn))
		{
			error=true;
			error_msg="Error in Where clause";
			return;
		}
		if(!orderby_cond->check(tbl_clmn))
		{
			error=true;
			error_msg="Error in Orderby clause";
			return;
		}
	}
	void execute(pugi::xml_node &db_node,libxl::Book* &book)
	{
		
	}
} ;
class Rename_stmt: public Sql_stmt
{ public:
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
	void check(pugi::xml_node &db_node,libxl::Book* &book)
	{
		
	}
	void execute(pugi::xml_node &db_node,libxl::Book* &book)
	{
		
	}
} ;
class Alter_stmt: public Sql_stmt
{ public:
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
	void check(pugi::xml_node &db_node,libxl::Book* &book)
	{
		
	}
	void execute(pugi::xml_node &db_node,libxl::Book* &book)
	{
		
	}
} ;
class Use_stmt: public Sql_stmt
{ public:
	string *db_name;
	pugi::xml_node n_db_node;
	Use_stmt(string *name):Sql_stmt(9),db_name(name){}
	~Use_stmt(){
		if(db_name)
			delete db_name;
	}
	void check(pugi::xml_node &db_node,libxl::Book* &book)
	{
		if(db_name==NULL)
		{
			error=true;
			error_msg="Database name not provided";
			return;
		}
		n_db_node=db_node.child(db_name->c_str());
		if(n_db_node==NULL)
		{
			error=true;
			error_msg="Database name does not exist";
			return;
		}
	}
	void execute(pugi::xml_node &db_node,libxl::Book* &book)
	{
		book->save(string(curdb.name()).append(".xls").c_str());
		book->release();
		book=xlCreateBook();
		book->load(string(n_db_node.name()).append(".xls").c_str());
		curdb=n_db_node;
	}
} ;
class Show_stmt: public Sql_stmt
{ public:
	Show_stmt(int type1):Sql_stmt(10,type1){}
	virtual void check(pugi::xml_node &db_node,libxl::Book* &book)=0;
	virtual void execute(pugi::xml_node &db_node,libxl::Book* &book)=0;
	virtual ~Show_stmt(){}
};
class Db_show: public Show_stmt
{ public:
	Db_show():Show_stmt(1){}
	void check(pugi::xml_node &db_node,libxl::Book* &book)
	{
		
	}
	void execute(pugi::xml_node &db_node,libxl::Book* &book)
	{
		std::cout<<"\n";
		for(pugi::xml_node node:db_node.children())
			std::cout<<node.name()<<"\n";
		std::cout<<"\n";
	}
};
class Tbl_show: public Show_stmt
{ public:
	string *db_name;
	pugi::xml_node n_db_node;
	Tbl_show(string *name):Show_stmt(2),db_name(name){}
	~Tbl_show(){
		if(db_name)
			delete db_name;
	}
	void check(pugi::xml_node &db_node,libxl::Book* &book)
	{
		if(db_name==NULL)
			n_db_node=curdb;
		else
		n_db_node=db_node.child(db_name->c_str());
		if(n_db_node==NULL)
		{
			error=true;
			error_msg="Database does not exist";
		}
	}
	void execute(pugi::xml_node &db_node,libxl::Book* &book)
	{
		std::cout<<"\n";
		for(pugi::xml_node node:n_db_node.children())
			std::cout<<node.name()<<"\n";
		std::cout<<"\n";
	}
};
class Clmns_show: public Show_stmt
{ public:
	string *db_name,*tbl_name;
	pugi::xml_node tbl_node;
	Clmns_show(string *name,string *name1):Show_stmt(3),tbl_name(name),db_name(name1){}
	~Clmns_show(){
		if(db_name)
			delete db_name;
		if(tbl_name)
			delete tbl_name;
	}
	void check(pugi::xml_node &db_node,libxl::Book* &book)
	{
		if(tbl_name==NULL)
		{
			error=true;
			error_msg="Table name not provided";
			return;
		}
		if(db_name!=NULL)
		tbl_node=db_node.child(db_name->c_str()).child(tbl_name->c_str()).child("columns");
		else
		tbl_node=curdb.child(tbl_name->c_str()).child("columns");
		if(tbl_node==NULL)
		{
			error=true;
			error_msg="Database or Table does not exist";
		}
	}
	void execute(pugi::xml_node &db_node,libxl::Book* &book)
	{
		std::cout<<"\n";
		for(pugi::xml_node node:tbl_node.children())
			std::cout<<node.name()<<"\n";
		std::cout<<"\n";
	}
};