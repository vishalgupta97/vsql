%code requires {
#include<stdio.h>
#include "tree.h"
extern bool yacc_err;
int yylex();
int yyerror(const char *s);
}
%code {
Sql_stmt *stmt1=0;
}
%define parse.error verbose
%debug
%union
{
	Cond_exp *cond_exp;
	Where_stmt *where_stmt;
	Orderby_stmt *orderby_stmt;
	Col_def *col_def;
	Constraints *constraints;
	Create_def *create_def;
	Alter_spec *alter_spec;
	Sql_stmt *sql_stmt;
	Update_stmt *update_stmt;
	Select_stmt *select_stmt;
	Drop_stmt *drop_stmt;
	Create_stmt *create_stmt;
	Insert_stmt *insert_stmt;
	Delete_stmt *delete_stmt;
	Rename_stmt *rename_stmt;
	Alter_stmt *alter_stmt;
	Use_stmt *use_stmt;
	Data_val *data_val;
	Show_stmt *show_stmt;
	Special_ele *special_ele;
	std::vector<Special_ele*> *special_list;
	std::vector<Alter_spec*> *alter_spec_list;
	std::vector<Create_def*> *create_def_list;
	std::vector<Col_def*> *col_def_list;
	std::vector<std::string*> *str_list;
	std::vector<std::vector<Data_val*>* > *val_set;
	std::vector<Data_val*> *val_list;
	std::pair<std::string*,Data_val*> *set_single;
	std::string *s;
	int x;
	bool order;
    std::vector<std::pair<std::string*,std::string*>* > *rnm_list;
	std::vector<std::pair<std::string*,Data_val*>* > *set_list;
}

%token <x> insert_k into_k values_k update_k set_k select_k from_k where_k order_k by_k and_k or_k asc_k dec_k delete_k  not_k null_k primary_k key_k auto_k drop_k database_k table_k create_k rename_k alter_k add_k constraint_k limit_k use_k show_k databases_k tables_k columns_k index_k view_k unique_k foreign_k references_k on_k as_k to_k change_k in_k

%token <s> name datatype_k
%token <x> number 

%type <rnm_list> rename_list
%type <set_list> set_list
%type <order> order_type
%type <set_single> set_single
%type <s> data_type opt_name
%type <data_val> data
%type <val_list> val_list val_list1
%type <x> limit_stmt
%type <str_list> col_list_chk name_list select_col_chk
%type <val_set> val_set
%type <cond_exp> cond_exp
%type <where_stmt> where_stmt where_cond
%type <orderby_stmt> orderby_stmt orderby_list
%type <col_def> col_def
%type <special_list> special_list special_list1
%type <special_ele> special_ele 
%type <constraints> constraints
%type <create_def> create_def
%type <create_def_list> create_def_list
%type <alter_spec> alter_spec
%type <sql_stmt> sql sql_stmt
%type <select_stmt> select_stmt
%type <update_stmt> update_stmt
%type <drop_stmt> drop_stmt type_drop
%type <col_def_list> add_col_def col_def_list
%type <create_stmt> create_stmt type_create
%type <insert_stmt> insert_stmt
%type <delete_stmt> delete_stmt
%type <rename_stmt> rename_stmt
%type <alter_spec_list> alter_spec_list
%type <alter_stmt> alter_stmt
%type <use_stmt> use_stmt
%type <show_stmt> show_stmt type_show

%start sql

%%
sql : sql_stmt ';' {stmt1=$1;}
	| {stmt1=NULL;}
;
sql_stmt : update_stmt {$$=$1;}
		 | select_stmt {$$=$1;}
		 | drop_stmt {$$=$1;}
		 | create_stmt {$$=$1;}
		 | insert_stmt {$$=$1;}
		 | delete_stmt {$$=$1;}
		 | rename_stmt {$$=$1;}
		 | alter_stmt {$$=$1;}
		 | use_stmt {$$=$1;}
		 | show_stmt {$$=$1;}
;
drop_stmt : drop_k type_drop{$$=$2;}
;
type_drop : database_k name {$$=new Db_drop($2);}
			| table_k name_list {$$=new Tbl_drop($2);}
			| index_k name on_k name {$$=new Idx_drop($2,$4);}
			| view_k name_list {$$=new View_drop($2);}
;
create_stmt : create_k type_create{$$=$2;}
;
type_create : database_k name {$$=new Db_create($2);}
				| table_k name '(' create_def_list ')'{$$=new Tbl_create($2,$4);}
				| index_k name on_k name '(' name_list ')' {$$=new Idx_create($2,$4,$6);}
				| view_k name col_list_chk as_k select_stmt {$$=new View_create($2,$3,$5);}
;
create_def_list : create_def {vector<Create_def*> *list=new vector<Create_def*>();
								list->push_back($1);
								$$=list;}
				| create_def_list ',' create_def {$$=$1;$$->push_back($3);}
;
create_def : col_def {	$$=new Create_def();$$->type=1;($$->x).cd=$1;}
			| constraints {$$=new Create_def();$$->type=2;($$->x).con=$1; }
;
constraints : primary_k key_k col_list_chk {$$=new Constraints(1,$3);}
			| index_k col_list_chk {$$=new Constraints(2,$2);}
			| unique_k col_list_chk {$$=new Constraints(3,$2);}
			| foreign_k key_k col_list_chk references_k name col_list_chk {$$=new Constraints(4,$3,$5,$6);}
;
col_def : name data_type special_list1 { $$=new Col_def($1,$2,$3);}					
; 
data_type : datatype_k {$$ = $1;}
		  |	datatype_k '(' number ')' { $$=$1;}
;
special_list1 : special_list { $$=$1;}
				| {$$=NULL;}
special_list : special_ele { vector<Special_ele*> *list=new vector<Special_ele*>(); list->push_back($1);$$=list;}
			| special_list special_ele {$$=$1;$$->push_back($2);}
;
special_ele : not_k null_k {$$=new Special_ele(1);}
			| auto_k {$$=new Special_ele(2);}
			| primary_k key_k {$$=new Special_ele(3);}
			| unique_k {$$=new Special_ele(4);}
			| references_k name name {$$=new Special_ele(5,$2,$3);}

;
rename_stmt : rename_k table_k rename_list { $$=new Rename_stmt($3);}
;
rename_list : name to_k name { vector<pair<string*,string*>* > *list=new vector<pair<string*,string*>* >(); list->push_back(new pair<string*,string*>($1,$3));$$=list;}
			| rename_list ',' name to_k name {$$=$1;$$->push_back(new pair<string*,string*>($3,$5));}
;
use_stmt : use_k name { $$=new Use_stmt($2);}
;
show_stmt : show_k type_show {$$=$2; }
;
type_show : databases_k { $$=new Db_show();}
			| tables_k opt_name { $$=new Tbl_show($2);}
			| columns_k in_k name opt_name {$$=new Clmns_show($3,$4);}
;
opt_name : in_k name { $$=$2;}
		|	{ $$=NULL;}
;
insert_stmt : insert_k into_k name col_list_chk values_k val_set{$$=new Insert_stmt($3,$4,$6);}
;
col_list_chk : '(' name_list ')' {$$=$2;} 
          | {$$=NULL;}; //either col_list or NUll
name_list : name {vector<string*> *list=new vector<string*>();list->push_back($1);$$=list;}
		| name_list ',' name{$$=$1;$$->push_back($3);}
;
val_set : val_list1{vector<vector<Data_val*>* > *list=new vector<vector<Data_val*>* >();list->push_back($1);$$=list;} 
	| val_set ',' val_list1{$$=$1;$$->push_back($3);}
;
val_list1 : '(' val_list ')' {$$=$2;}
;
val_list : data {vector<Data_val*> *list=new vector<Data_val*>();list->push_back($1);$$=list;}
		| val_list ',' data{$$=$1;$$->push_back($3);}
;
data : '\'' name '\''{$$=new Data_val();$$->type=4;$$->x.s=$2;}
		| name {$$=new Data_val();$$->type=4;$$->x.s=$1;}
		| number {$$=new Data_val();$$->type=1;$$->x.int_val=$1;}
		| number '.' number {$$=new Data_val();$$->type=2;$$->x.dbl_val=$1+0.1*$3;}
; 
delete_stmt: delete_k from_k name where_stmt orderby_stmt limit_stmt {$$=new Delete_stmt($3,$4,$5,$6);}
;
select_stmt : select_k select_col_chk from_k name where_stmt orderby_stmt limit_stmt {$$=new Select_stmt($2,$4,$5,$6,$7);}
;
select_col_chk : '*' {$$=NULL;}
		 | name_list 
;
where_stmt : where_k where_cond {$$=$2;}
			| {$$=NULL;}
;
where_cond : cond_exp {$$=new Where_stmt($1);}
			| where_cond and_k cond_exp {$$=$1;$$->and_list->push_back($3);}
			| where_cond or_k cond_exp {$$=$1;$$->or_list->push_back($3);}
;
cond_exp : name '=' data {$$=new Cond_exp();$$->lhs=$1;$$->rhs=$3;}
;
orderby_stmt : order_k by_k orderby_list {$$=$3;}
			| {$$=NULL;}
;
orderby_list : name order_type	{$$=new Orderby_stmt(new pair<string*,bool>($1,$2));}
			| orderby_list ',' name order_type {$$=$1;$$->clmns_list->push_back(new pair<string*,bool>($3,$4));}
;
order_type : asc_k {$$=true;} 
			| dec_k {$$=false;}
;
update_stmt : update_k name set_k set_list where_stmt orderby_stmt limit_stmt {$$=new Update_stmt($2,$4,$5,$6,$7);}
;
set_list : set_single {vector<pair<string*,Data_val*>* > *list=new vector<pair<string*,Data_val*>* >(); 		  
						list->push_back($1);$$=list;} 
		| set_list ',' set_single  { $$=$1;$$->push_back($3);}
;
set_single : name '=' data {$$=new pair<string*,Data_val*>($1,$3);}
;
limit_stmt : limit_k number {$$=$2;}
			| {$$=0;}
;
alter_stmt : alter_k table_k name alter_spec_list {$$=new Alter_stmt($3,$4);}
;
alter_spec_list : alter_spec {vector<Alter_spec*> *list=new vector<Alter_spec*>();list->push_back($1);$$=list;}
				| alter_spec_list ',' alter_spec {$$=$1;$$->push_back($3);}
;
add_col_def : col_def {vector<Col_def*> *list=new vector<Col_def*>();list->push_back($1);$$=list;}
			| '(' col_def_list ')' {$$=$2;}
;
col_def_list : col_def {vector<Col_def*> *list=new vector<Col_def*>();list->push_back($1);$$=list;}
			| col_def_list ',' col_def {$$=$1;$$->push_back($3);}
;
alter_spec : add_k add_col_def {$$=new Alter_spec();$$->type=1;($$->x).add_col=$2;}
			| add_k constraint_k constraints {$$=new Alter_spec();$$->type=2;($$->x).con=$3;}
			| change_k name col_def {$$=new Alter_spec();$$->type=3;($$->x).cng_col=new Change_col($2,$3);}
;
%%
int yyerror(const char *s)
{
printf("%s\n",s);
yacc_err=true;
return 1;
}
