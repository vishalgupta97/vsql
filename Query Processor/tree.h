#include<vector>
#include<string>
#include<utility>
#include<iostream>
#include<algorithm>
#include "pugixml/pugixml.hpp"
#include "blfilter.h"
using namespace std;
class Cond_exp
{ public:
	string *lhs;
	bool type;
	union
	{
		string *s_rhs;//type=true
		int i_rhs;//type=false
	}x;
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
};
class Sql_stmt
{ public:
	int type,type_c;
	bool error;
	Sql_stmt(int type1):type(type1),type_c(0){}
	Sql_stmt(int type1,int type_c1):type(type1),type_c(type_c1){}
	virtual void check(pugi::xml_node &root)=0;
	virtual void execute(pugi::xml_node &root)=0;
};
class Update_stmt: public Sql_stmt
{ public:
	string *tbl_name;
	Orderby_stmt *orderby_cond;
	int limit;
	vector<pair<string*,string*>* > *list;
	Update_stmt(string *name,vector<pair<string*,string*>* > *list1,Orderby_stmt *cond,int limit1):Sql_stmt(1),tbl_name(name),limit(limit1),list(list1),orderby_cond(cond){	}
	~Update_stmt(){
		if(tbl_name)
			delete tbl_name;
		if(orderby_cond)
			delete orderby_cond;
	}
	void check(pugi::xml_node &root)
	{
		
	}
	void execute(pugi::xml_node &root)
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
	void check(pugi::xml_node &root)
	{
		
	}
	void execute(pugi::xml_node &root)
	{
		
	}
} ;
class Drop_stmt: public Sql_stmt
{ public:
	Drop_stmt(int type1):Sql_stmt(3,type1){}
	virtual void check(pugi::xml_node &root)=0;
	virtual void execute(pugi::xml_node &root)=0;
} ;
class Db_drop: public Drop_stmt
{ public:
	string *db_name;
	pugi::xml_node db_node;
	Db_drop(string *name):Drop_stmt(1),db_name(name){}
	~Db_drop(){
		if(db_name)
			delete db_name;
	}
	void check(pugi::xml_node &root)
	{
		db_node=root.child(db_name->c_str());
		if(db_node==NULL)
			error=true;
	}
	void execute(pugi::xml_node &root)
	{
		root.remove_child(db_node);
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
	void check(pugi::xml_node &root)
	{
		
	}
	void execute(pugi::xml_node &root)
	{
		
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
	void check(pugi::xml_node &root)
	{
		
	}
	void execute(pugi::xml_node &root)
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
	void check(pugi::xml_node &root)
	{
		
	}
	void execute(pugi::xml_node &root)
	{
		
	}
};
class Create_stmt: public Sql_stmt
{ public:
	Create_stmt(int type1):Sql_stmt(4,type1){}
	virtual void check(pugi::xml_node &root)=0;
	virtual void execute(pugi::xml_node &root)=0;
} ;
class Db_create: public Create_stmt
{ public:
	string *db_name;
	Db_create(string *name):Create_stmt(1),db_name(name){}
	~Db_create() {	
		if(db_name)
			delete db_name;
	}
	void check(pugi::xml_node &root)
	{
		if(!db_name)
		{
			error=true;
			return;
		}
		pugi::xml_node node=root.child(db_name->c_str());
		if(node)
			error=true;
	}
	void execute(pugi::xml_node &root)
	{
		root.append_child(db_name->c_str());
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
	bool operator()(const Create_def* a,const Create_def* b)
	{
		return a->type<b->type;
	}
	void check(pugi::xml_node &curdb)
	{
		if(!tbl_name||!list||curdb.child(tbl_name->c_str()))
		{
			error=true;
			return;
		}
		bfl=new bloom_filter();
		bool primary_key=false;
		string *auto_inc=NULL;
		std::sort(list->begin(),list->end(),*this);
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
							return;
						}
					}
			    }
				for(int i=0;i<cd->list->size();i++)
					switch(cd->list->at(i)->type)
					{
						case 2:auto_inc=cd->col_name;
						case 3:if(primary_key)
								{
									error=true;
									return;
								}
								else
								primary_key=true;
							break;
						case 5:if(curdb.child(cd->list->at(i)->tbl_name->c_str()).child(cd->list->at(i)->col_name->c_str()).attribute("unique")==NULL)
						{
							error=true;
							return;
						}
						break;
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
							return;
						}
					}
					else if(con->col_list->size()!=1||con->col_list->at(0)->compare(*auto_inc)!=0)
					{
						error=true;
						return;
					}
				}
				for(int j=0;j<con->col_list->size();j++)
				{
					if(!bfl->chk_hash(con->col_list->at(j)->c_str()))
					{
						error=true;
						return;
					}
				}
				if(con->type==4)
				{
					if(con->col_list->size()!=con->to_list->size())
					{
						error=true;
						return;
					}
					pugi::xml_node to_tbl=curdb.child(con->tbl_name_to->c_str());
					if(to_tbl==NULL)
					{
						error=true;
						return;
					}
					string s="";
					for(int j=0;j<con->to_list->size();j++)
					{
						if(!bfl->chk_hash(con->col_list->at(j)->c_str())||to_tbl.child(con->to_list->at(j)->c_str())==NULL)
						{
							error=true;
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
						return;
					}
				}
			}
		}	
	}
	void execute(pugi::xml_node &curdb)
	{
		pugi::xml_node tbl=curdb.append_child(tbl_name->c_str());
		for(int i=0;i<list->size();i++)
		{
			if(list->at(i)->type==1)
			{
				Col_def* cd=list->at(i)->x.cd;
				pugi::xml_node clmn=tbl.append_child(cd->col_name->c_str());
				bool not_null=false,ainc=false,primary=false,unique=false,foreign=false;
				Special_ele *se=NULL;
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
					pugi::xml_node chld=tbl.append_child(s.c_str());
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
	void check(pugi::xml_node &root)
	{
		
	}
	void execute(pugi::xml_node &root)
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
	void check(pugi::xml_node &root)
	{
		
	}
	void execute(pugi::xml_node &root)
	{
		
	}
};
class Insert_stmt: public Sql_stmt
{ public:
	string *tbl_name;
	vector<string*> *cols;
	vector<vector<string*>* > *data;
	Insert_stmt(string *name,vector<string*> *cols1,vector<vector<string*>* > *data1):Sql_stmt(5),tbl_name(name),data(data1),cols(cols1){}
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
	void check(pugi::xml_node &root)
	{
		
	}
	void execute(pugi::xml_node &root)
	{
		
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
	void check(pugi::xml_node &root)
	{
		
	}
	void execute(pugi::xml_node &root)
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
	void check(pugi::xml_node &root)
	{
		
	}
	void execute(pugi::xml_node &root)
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
	void check(pugi::xml_node &root)
	{
		
	}
	void execute(pugi::xml_node &root)
	{
		
	}
} ;
class Use_stmt: public Sql_stmt
{ public:
	string *db_name;
	pugi::xml_node db_node;
	Use_stmt(string *name):Sql_stmt(9),db_name(name){}
	~Use_stmt(){
		if(db_name)
			delete db_name;
	}
	void check(pugi::xml_node &root)
	{
		if(db_name==NULL)
		{
			error=true;
			return;
		}
		db_node=root.child(db_name->c_str());
		if(db_node==NULL)
			error=true;
	}
	void execute(pugi::xml_node &root)
	{
		root=db_node;
	}
} ;
class Show_stmt: public Sql_stmt
{ public:
	Show_stmt(int type1):Sql_stmt(10,type1){}
	virtual void check(pugi::xml_node &root)=0;
	virtual void execute(pugi::xml_node &root)=0;
};
class Db_show: public Show_stmt
{ public:
	Db_show():Show_stmt(1){}
	void check(pugi::xml_node &root)
	{
		
	}
	void execute(pugi::xml_node &root)
	{
		std::cout<<"\n";
		for(pugi::xml_node node:root.children())
			std::cout<<node.name()<<"\n";
		std::cout<<"\n";
	}
};
class Tbl_show: public Show_stmt
{ public:
	string *db_name;
	pugi::xml_node db_node;
	Tbl_show(string *name):Show_stmt(2),db_name(name){}
	~Tbl_show(){
		if(db_name)
			delete db_name;
	}
	void check(pugi::xml_node &root)
	{
		if(db_name==NULL)
		{
			error=true;
			return;
		}
		db_node=root.child(db_name->c_str());
		if(db_node==NULL)
			error=true;
	}
	void execute(pugi::xml_node &root)
	{
		std::cout<<"\n";
		for(pugi::xml_node node:db_node.children())
			std::cout<<node.name()<<"\n";
		std::cout<<"\n";
	}
};
class Clmns_show: public Show_stmt
{ public:
	string *db_name,*tbl_name;
	pugi::xml_node tbl_node;
	Clmns_show(string *name,string *name1):Show_stmt(3),tbl_name(name1),db_name(name){}
	~Clmns_show(){
		if(db_name)
			delete db_name;
		if(tbl_name)
			delete tbl_name;
	}
	void check(pugi::xml_node &root)
	{
		if(db_name==NULL||tbl_name==NULL)
		{
			error=true;
			return;
		}
		tbl_node=root.child(db_name->c_str()).child(tbl_name->c_str());
		if(tbl_node==NULL)
			error=true;
	}
	void execute(pugi::xml_node &root)
	{
		std::cout<<"\n";
		for(pugi::xml_node node:tbl_node.children())
			std::cout<<node.name()<<"\n";
		std::cout<<"\n";
	}
};