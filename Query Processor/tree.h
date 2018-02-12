#include<vector>
#include<string>
#include<utility>
#include<iostream>
#include "pugixml/pugixml.hpp"
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
				free(*i);
			and_list->clear();
			free(and_list);
		}
		if(or_list)
		{
			for(auto i=or_list->begin();i!=or_list->end();i++)
				free(*i);
			or_list->clear();
			free(or_list);
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
				free((*i)->first);
				free(*i);
			}
			clmns_list->clear();
			free(clmns_list);
		}
	}
};
class Special_ele
{ public:
	int type;
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
				free(*i);
			list->clear();
			free(list);
		}
	}
};
class Constraints
{ public:
	int type;
	Constraints(int type1):type(type){}
};
class Primary_key : public Constraints
{ public:
	vector<string*> *col_list;
	Primary_key(vector<string*> *list):Constraints(3),col_list(list){}
	~Primary_key(){
		if(col_list)
		{
			for(auto i=col_list->begin();i!=col_list->end();i++)
				free(*i);
			col_list->clear();
			free(col_list);
		}
	}
};
class Index_key : public Constraints
{ public:
	vector<string*> *col_list;
	Index_key(vector<string*> *list):Constraints(3),col_list(list){}
	~Index_key(){
		if(col_list)
		{
			for(auto i=col_list->begin();i!=col_list->end();i++)
				free(*i);
			col_list->clear();
			free(col_list);
		}
	}
};
class Unique_key : public Constraints
{ public:
	vector<string*> *col_list;
	Unique_key(vector<string*> *list):Constraints(3),col_list(list){}
	~Unique_key(){
		if(col_list)
		{
			for(auto i=col_list->begin();i!=col_list->end();i++)
				free(*i);
			col_list->clear();
			free(col_list);
		}
	}
};
class Foreign_key : public Constraints
{ public:
	vector<string*> *from_list;
	vector<string*> *to_list;
	string *tbl_name_to;
	Foreign_key(vector<string*> *list1,string *name,vector<string*> *list2):Constraints(4),tbl_name_to(name),from_list(list1),to_list(list2){}
	~Foreign_key(){
		if(from_list)
		{
			for(auto i=from_list->begin();i!=from_list->end();i++)
				free(*i);
			from_list->clear();
			free(from_list);
		}
		if(to_list)
		{
			for(auto i=to_list->begin();i!=to_list->end();i++)
				free(*i);
			to_list->clear();
			free(to_list);
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
	virtual void check(pugi::xml_node root)=0;
	virtual void execute(pugi::xml_node root)=0;
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
	void check(pugi::xml_node root)
	{
		
	}
	void execute(pugi::xml_node root)
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
				free(*i);
			col_list->clear();
			free(col_list);
		}
		if(tbl_name)
			delete tbl_name;
		if(where_cond)
			delete where_cond;
		if(orderby_cond)
			delete orderby_cond;
	}
	void check(pugi::xml_node root)
	{
		
	}
	void execute(pugi::xml_node root)
	{
		
	}
} ;
class Drop_stmt: public Sql_stmt
{ public:
	Drop_stmt(int type1):Sql_stmt(3,type1){}
	virtual void check(pugi::xml_node root)=0;
	virtual void execute(pugi::xml_node root)=0;
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
	void check(pugi::xml_node root)
	{
		db_node=root.child(db_name->c_str());
		if(db_node==NULL)
			error=true;
	}
	void execute(pugi::xml_node root)
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
				free(*i);
			tbl_list->clear();
			free(tbl_list);
		}
	}
	void check(pugi::xml_node root)
	{
		
	}
	void execute(pugi::xml_node root)
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
	void check(pugi::xml_node root)
	{
		
	}
	void execute(pugi::xml_node root)
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
				free(*i);
			view_list->clear();
			free(view_list);
		}
	}
	void check(pugi::xml_node root)
	{
		
	}
	void execute(pugi::xml_node root)
	{
		
	}
};
class Create_stmt: public Sql_stmt
{ public:
	Create_stmt(int type1):Sql_stmt(4,type1){}
	virtual void check(pugi::xml_node root)=0;
	virtual void execute(pugi::xml_node root)=0;
} ;
class Db_create: public Create_stmt
{ public:
	string *db_name;
	Db_create(string *name):Create_stmt(1),db_name(name){}
	~Db_create() {	
		if(db_name)
			delete db_name;
	}
	void check(pugi::xml_node root)
	{
		if(!db_name)
		{
			error=true;
			return;
		}
		string db=*db_name;
		pugi::xml_node node=root.child(db_name->c_str());
		if(node)
			error=true;
	}
	void execute(pugi::xml_node root)
	{
		root.append_child(db_name->c_str());
	}
};
class Tbl_create: public Create_stmt
{ public:
	string *tbl_name;
	vector<Create_def*> *list;
	Tbl_create(string *name,vector<Create_def*> *list1):Create_stmt(2),tbl_name(name),list(list1){}
	~Tbl_create(){
		if(tbl_name)
			delete tbl_name;
		if(list)
		{
			for(auto i=list->begin();i!=list->end();i++)
				free(*i);
			list->clear();
			free(list);
		}
	}
	void check(pugi::xml_node root)
	{
		
	}
	void execute(pugi::xml_node root)
	{
		
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
				free(*i);
			col_list->clear();
			free(col_list);
		}
	}
	void check(pugi::xml_node root)
	{
		
	}
	void execute(pugi::xml_node root)
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
				free(*i);
			col_list->clear();
			free(col_list);
		}
		if(stmt)
			delete stmt;
	}
	void check(pugi::xml_node root)
	{
		
	}
	void execute(pugi::xml_node root)
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
				free(*i);
			cols->clear();
			free(cols);
		}
		if(data)
		{
			for(auto i=data->begin();i!=data->end();i++)
			{
				auto x=*i;
				for(auto j=x->begin();j!=x->end();j++)
					free(*j);
				x->clear();
				free(x);
			}
			data->clear();
			free(data);
		}
	}
	void check(pugi::xml_node root)
	{
		
	}
	void execute(pugi::xml_node root)
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
	void check(pugi::xml_node root)
	{
		
	}
	void execute(pugi::xml_node root)
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
				free((*i)->first);
				free((*i)->second);
				free(*i);
			}
			list->clear();
			free(list);
		}
	}
	void check(pugi::xml_node root)
	{
		
	}
	void execute(pugi::xml_node root)
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
				free(*i);
		}
	}
	void check(pugi::xml_node root)
	{
		
	}
	void execute(pugi::xml_node root)
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
	void check(pugi::xml_node root)
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
	void execute(pugi::xml_node root)
	{
		
	}
} ;
class Show_stmt: public Sql_stmt
{ public:
	Show_stmt(int type1):Sql_stmt(10,type1){}
	virtual void check(pugi::xml_node root)=0;
	void execute(pugi::xml_node root)=0;
};
class Db_show: public Show_stmt
{ public:
	Db_show():Show_stmt(1){}
	void check(pugi::xml_node root)
	{
		
	}
	void execute(pugi::xml_node root)
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
	void check(pugi::xml_node root)
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
	void execute(pugi::xml_node root)
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
	void check(pugi::xml_node root)
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
	void execute(pugi::xml_node root)
	{
		std::cout<<"\n";
		for(pugi::xml_node node:tbl_node.children())
			std::cout<<node.name()<<"\n";
		std::cout<<"\n";
	}
};