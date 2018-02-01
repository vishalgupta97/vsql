#include<vector>
#include<string>
#include<utility>
#include<iostream>
#include "pugixml/pugixml.hpp"
using namespace std;
class Cond_exp
{ public:
	string lhs;
	bool type;
	union
	{
		string *s_rhs;//type=true
		int i_rhs;//type=false
	}x;
};
class Where_stmt
{ public:
	vector<Cond_exp> *and_list;
	vector<Cond_exp> *or_list;
	Cond_exp first;
	Where_stmt(Cond_exp *exp):first(*exp){}
};
class Orderby_stmt
{ public:
	vector<pair<string,bool> > *clmns_list;//asc=true,desc=false
	Orderby_stmt(pair<string,bool> xyz)
	{
		clmns_list=new vector<pair<string,bool> >();
		clmns_list->push_back(xyz);
	}
};
class Special_ele
{ public:
	int type;
	string *tbl_name,*col_name;
	Special_ele(int type1):Special_ele(type1,0,0){}
	Special_ele(int type1,string *name,string *name1):type(type1),tbl_name(name),col_name(name1){}
};
class Col_def
{ public:
	string *col_name,*datatype;
	vector<Special_ele> *list;
	string to_tbl_name,to_col_name;
	Col_def(string *name,string *type,vector<Special_ele> *list1):col_name(name),datatype(type),list(list1)	{}
};
class Constraints
{ public:
	int type;
	Constraints(int type1):type(type){}
};
class Primary_key : public Constraints
{ public:
	vector<string> *col_list;
	Primary_key(vector<string> *list):Constraints(3),col_list(list){}
};
class Index_key : public Constraints
{ public:
	vector<string> *col_list;
	Index_key(vector<string> *list):Constraints(3),col_list(list){}
};
class Unique_key : public Constraints
{ public:
	vector<string> *col_list;
	Unique_key(vector<string> *list):Constraints(3),col_list(list){}
};
class Foreign_key : public Constraints
{ public:
	vector<string> *from_list;
	vector<string> *to_list;
	string *tbl_name_to;
	Foreign_key(vector<string> *list1,string *name,vector<string> *list2):Constraints(4),tbl_name_to(name),from_list(list1),to_list(list2){}
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
};
class Alter_spec
{ public:
	int type;
	union
	{
		vector<Col_def> *add_col;
		Constraints *con;
		Change_col *cng_col;
	}x;
};
class Sql_stmt
{ public:
	int type;
	bool error;
	Sql_stmt(int type1):type(type1){}
	virtual void check(pugi::xml_node root)=0;
	virtual void execute(pugi::xml_node root)=0;
};
class Update_stmt: public Sql_stmt
{ public:
	string *tbl_name;
	Orderby_stmt *orderby_cond;
	int limit;
	vector<pair<string,string> > *list;
	Update_stmt(string *name,vector<pair<string,string> > *list1,Orderby_stmt *cond,int limit1):Sql_stmt(1),tbl_name(name),limit(limit1),list(list1),orderby_cond(cond){	}
	void check(pugi::xml_node root)
	{
		
	}
	void execute(pugi::xml_node root)
	{
		
	}
};
class Select_stmt: public Sql_stmt
{ public:
	vector<string> *col_list;
	string *tbl_name;
	Where_stmt *where_cond;
	Orderby_stmt *orderby_cond;
	int limit;
	Select_stmt(vector<string> *list,string *name,Where_stmt *cond,Orderby_stmt *cond1,int limit1):Sql_stmt(2),tbl_name(name),limit(limit1),where_cond(cond),orderby_cond(cond1),col_list(list){}
	void check(pugi::xml_node root)
	{
		
	}
	void execute(pugi::xml_node root)
	{
		
	}
} ;
class Drop_stmt: public Sql_stmt
{ public:
	int type;
	Drop_stmt(int type1):Sql_stmt(3),type(type){}
	virtual void check(pugi::xml_node root)=0;
	virtual void execute(pugi::xml_node root)=0;
} ;
class Db_drop: public Drop_stmt
{ public:
	string *db_name;
	Db_drop(string *name):Drop_stmt(1),db_name(name){}
	void check(pugi::xml_node root)
	{
		pugi::xml_node node=root.child(db_name->c_str());
		if(node==NULL)
			error=true;
	}
	void execute(pugi::xml_node root)
	{
		root.remove_child(db_name->c_str());
	}
};
class Tbl_drop: public Drop_stmt
{ public:
	vector<string> *tbl_list;
	Tbl_drop(vector<string> *list):Drop_stmt(2),tbl_list(list){}
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
	void check(pugi::xml_node root)
	{
		
	}
	void execute(pugi::xml_node root)
	{
		
	}
};
class View_drop: public Drop_stmt
{ public:
	vector<string> *view_list;
	View_drop(vector<string> *list):Drop_stmt(4),view_list(list){}
	void check(pugi::xml_node root)
	{
		
	}
	void execute(pugi::xml_node root)
	{
		
	}
};
class Create_stmt: public Sql_stmt
{ public:
	int type;
	Create_stmt(int type1):Sql_stmt(4),type(type1){}
	virtual void check(pugi::xml_node root)=0;
	virtual void execute(pugi::xml_node root)=0;
} ;
class Db_create: public Create_stmt
{ public:
	string *db_name;
	Db_create(string *name):Create_stmt(1),db_name(name){}
	void check(){}
	void execute() {}
	void check(pugi::xml_node root)
	{
		if(!db_name)
		{
			error=true;
			return;
		}
		string db=*db_name;
		for(pugi::xml_node child:root.children())
		{
			if(string(child.name()).compare(db)==0)
			{
				error=true;
				return;
			}
		}
	}
	void execute(pugi::xml_node root)
	{
		root.append_child(db_name->c_str());
	}
};
class Tbl_create: public Create_stmt
{ public:
	string *tbl_name;
	vector<Create_def> *list;
	Tbl_create(string *name,vector<Create_def> *list1):Create_stmt(2),tbl_name(name),list(list1){}
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
	vector<string> *col_list;
	Idx_create(string *idx,string *tbl,vector<string> *list):Create_stmt(3),idx_name(idx),tbl_name(tbl){}
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
	vector<string> *col_list;
	Select_stmt *stmt;
	View_create(string *name,vector<string> *list,Select_stmt *stmt1):Create_stmt(4),view_name(name),stmt(stmt1),col_list(list){}
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
	vector<string> *cols;
	vector<vector<string> > *data;
	Insert_stmt(string *name,vector<string> *cols1,vector<vector<string> > *data1):Sql_stmt(5),tbl_name(name),data(data1),cols(cols1){}
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
	void check(pugi::xml_node root)
	{
		
	}
	void execute(pugi::xml_node root)
	{
		
	}
} ;
class Rename_stmt: public Sql_stmt
{ public:
	vector<pair<string,string> > *list;
	Rename_stmt(vector<pair<string,string> > *list1):Sql_stmt(7),list(list1){}
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
	vector<Alter_spec> *spec_list;
	Alter_stmt(string *name,vector<Alter_spec> *list):Sql_stmt(8),tbl_name(name),spec_list(list){}
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
	Use_stmt(string *name):Sql_stmt(9),db_name(name){}
	void check(pugi::xml_node root)
	{
		
	}
	void execute(pugi::xml_node root)
	{
		
	}
} ;
class Show_stmt: public Sql_stmt
{ public:
	int type;
	Show_stmt(int type1):Sql_stmt(10),type(type1){}
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
		for(auto i=root.begin();i!=root.end();i++)
			std::cout<<i->name()<<"\n";
	}
};
class Tbl_show: public Show_stmt
{ public:
	string *db_name;
	Tbl_show(string *name):Show_stmt(2),db_name(name){}
	void check(pugi::xml_node root)
	{
		
	}
	void execute(pugi::xml_node root)
	{
		
	}
};
class Clmns_show: public Show_stmt
{ public:
	string *db_name,*tbl_name;
	Clmns_show(string *name,string *name1):Show_stmt(3),tbl_name(name1),db_name(name){}
	void check(pugi::xml_node root)
	{
		
	}
	void execute(pugi::xml_node root)
	{
		
	}
};