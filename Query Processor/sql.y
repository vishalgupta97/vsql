%{
#include<stdio.h>
#include<string.h>	
#define YYSTYPE char*
int yylex();
int yyerror(char *s);
%}
%token insert_k into_k values_k update_k set_k name number select_k from_k where_k order_k by_k and_k or_k asc_k dec_k delete_k datatype_k not_k null_k primary_k key_k auto_k drop_k database_k table_k create_k rename_k alter_k add_k constraint_k limit_k use_k show_k databases_k tables_k columns_k index_k view_k unique_k foreign_k references_k on_k as_k to_k change_k in_k
%start sql
%%
sql : sql_stmt ';' {printf("%s\n",$1);return 0;}
;
sql_stmt : update_stmt ;
		 | select_stmt ;
		 | drop_stmt ;
		 | create_stmt ;
		 | insert_stmt ;
		 | delete_stmt ;
		 | rename_stmt;
		 | alter_stmt;
		 | use_stmt;
		 | show_stmt;
;
drop_stmt : drop_k type_drop{
	char arr[200];
	sprintf(arr,"Drop %s",$2);
	$$ = strdup(arr);}
;
type_drop : database_k name {
										char arr[10000];
										sprintf(arr,"Database %s",$2);
										$$=strdup(arr);}
			| table_k name_list {
								char arr[10000];
								sprintf(arr,"Table %s",$2);
								$$=strdup(arr);}
			| index_k name on_k name { }
			| view_k name_list {}
;
create_stmt : create_k type_create{
										char arr[100000];
										sprintf(arr,"Create %s",$2);
										$$ = strdup(arr);}
;
type_create : database_k name {
										char arr[10000];
										sprintf(arr,"Database %s",$2);
										$$=strdup(arr);}
				| table_k name '(' create_def_list ')'{
								char arr[10000];
								sprintf(arr,"Table %s with Coloumns %s",$2,$4);
								$$=strdup(arr);}
				| index_k name on_k name name '(' name_list ')' {}
				| view_k name col_list_chk as_k select_stmt {}
;
create_def_list : create_def {}
				| create_def_list ',' create_def {}
;
create_def : col_def {	}
			| constraints { }
;
constraints : primary_k key_k col_list_chk {}
			| index_k col_list_chk {}
			| unique_k col_list_chk {}
			| foreign_k key_k col_list_chk references_k name col_list_chk {}
;
col_def : name data_type special_list {  char arr[10000];
														if ($3 == NULL)
															sprintf(arr,"%s with DataType %s",$1,$2);
														else
															sprintf(arr,"%s with DataType %s and Characteristics %s",$1,$2,$3);
														$$ = strdup(arr);}					
; 
data_type : datatype_k {$$ = strdup($1);}
		  |	datatype_k '(' number ')' { char arr[10000];
						sprintf(arr,"%s of size %s",$1,$3); $$=strdup(arr);}
;
special_list : special_ele { }
			| special_list special_ele {}
;
special_ele : null_k {}
			| not_k null_k {}
			| auto_k {}
			| primary_k key_k {}
			| unique_k {}
			| references_k name name {}
;
rename_stmt : rename_k table_k rename_list { }
;
rename_list : name to_k name { }
			| rename_list ',' name to_k name {}
;
use_stmt : use_k name { }
;
show_stmt : show_k type_show { }
;
type_show : databases_k { }
			| tables_k in_k name { }
			| columns_k in_k name in_k opt_db {}
;
opt_db : name { }
		|	{ }
;
insert_stmt : insert_k into_k name col_list_chk values_k val_set{char arr[10000];
	int length=0;
	if($4!=NULL)
	length+=sprintf(arr+length,"Inserting in columns %s values %s",$4,$6);
	else
	length+=sprintf(arr+length,"Inserting in all columns  values %s",$6);
$$=strdup(arr);
	}
;
col_list_chk : '(' name_list ')' {$$=strdup($2);} 
          | {$$=NULL;}; //either col_list or NUll
name_list : name {$$=strdup($1);}
		| name_list ',' name{char arr[100000];
		sprintf(arr,"%s , %s ",$1,$3); 
		$$=strdup(arr);}
;
val_set : val_list1{$$=strdup($1);} 
	| val_set ',' val_list1{char arr[1000000];//inserting multiple values seperated by ,
		sprintf(arr,"%s ; %s",$1,$3);
	$$=strdup(arr);};

val_list1 : '(' val_list ')' {$$=strdup($2) ;};
val_list : name1{$$=strdup($1);}|val_list ',' name1{char arr[100000];
	sprintf(arr,"%s , %s",$1,$3); ;
	$$=strdup(arr);}
;
name1 : '\'' name '\''{$$=strdup($2);}
		| name {$$=strdup($1);}
		| number {$$=strdup($1);}; 
delete_stmt: delete_k from_k name where_stmt orderby_stmt limit_stmt {char arr[10000];
	int dl=0;
	if($4==NULL)
	dl+=sprintf(arr,"Deleting all records from the table %s",$3);
	else
	dl+=sprintf(arr,"Deleting records from the table %s where %s",$3,$4);
	$$=strdup(arr);
	}
;
select_stmt : select_k select_col_chk from_k name where_stmt orderby_stmt limit_stmt { char arr[10000];
			int length=0;
			if($2==NULL)
			length+=sprintf(arr+length,"Select All column from table %s",$4);
			else
			length+=sprintf(arr+length,"Select column %s from table %s",$2,$4);
			if($5!=NULL)
			length+=sprintf(arr+length," Where %s",$5);
			if($6!=NULL)
			length+=sprintf(arr+length," Order By %s",$6);
			$$=strdup(arr);}
;
select_col_chk : '*' {$$=NULL;}
		 | name_list {}
;
where_stmt : where_k where_cond {$$=strdup($2);}
			| {$$=NULL;}
;
where_cond : set_single {$$=strdup($1);}
			| where_cond and_k set_single {char arr[10000];
							sprintf(arr,"%s AND %s",$1,$3);
							$$=strdup(arr);}
			| where_cond or_k set_single {
							char arr[10000];
							sprintf(arr,"%s OR %s",$1,$3);
							$$=strdup(arr);}
;
orderby_stmt : order_k by_k orderby_list {$$=strdup($3);}
			| {$$=NULL;}
;
orderby_list : name order_type	{char arr[10000];
							sprintf(arr,"Order column %s by %s",$1,$2);
							$$=strdup(arr);}
			| orderby_list ',' name order_type { char arr[10000];
							sprintf(arr,"%s and Order column %s by %s",$1,$3,$4);
							$$=strdup(arr);}
;
order_type : asc_k {$$=strdup("asc");} 
			| dec_k {$$=strdup("desc");}
;
update_stmt : update_k name set_k set_list where_stmt orderby_stmt limit_stmt {
	char arr[10000];
	sprintf(arr,"Update Table %s with %s",$2,$4);
	$$=strdup(arr);}
;
set_list : set_single {$$=strdup($1);} 
		| set_list ',' set_single  { char arr[10000];
									sprintf(arr,"%s , %s",$1,$3);
									$$=strdup(arr);}
;
set_single : name '=' name { char arr[10000];
							sprintf(arr,"%s=%s",$1,$3);
							$$=strdup(arr);}
			| name '=' number {char arr[10000];
							sprintf(arr,"%s=%s",$1,$3);
							$$=strdup(arr);}
;
limit_stmt : limit_k number {}
;
alter_stmt : alter_k table_k name alter_spec_list {}
;
alter_spec_list : alter_spec {}
				| alter_spec_list ',' alter_spec {}
;
add_col_def : col_def {}
			| '(' col_def_list ')' {}
;
col_def_list : col_def {}
			| col_def_list ',' col_def {}
;
alter_spec : add_k add_col_def {}
			| add_k constraint_k constraints {}
			| change_k name col_def {}
;
%%
int main()
{
printf("Enter Sql Expression:\n");
yyparse();
}
int yyerror(char *s)
{
printf("%s\n",s);
return 1;
}
