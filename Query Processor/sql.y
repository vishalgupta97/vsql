%{
#include<stdio.h>
#include<string.h>	
#define YYSTYPE char*
int yylex();
int yyerror(char *s);
%}
%token insert_k into_k values_k update_k set_k name number select_k from_k where_k order_k by_k and_k or_k asc_k dec_k delete_k datatype_k not_k null_k primary_k key_k auto_k drop_k database_k table_k create_k
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
;
drop_stmt : drop_k table_database_drop{
	char arr[200];
	sprintf(arr,"Drop %s",$2);
	$$ = strdup(arr);}
;
table_database_drop : database_k name {
										char arr[10000];
										sprintf(arr,"Database %s",$2);
										$$=strdup(arr);}
				| table_k name {
								char arr[10000];
								sprintf(arr,"Table %s",$2);
								$$=strdup(arr);}
;
create_stmt : create_k table_database_create{
										char arr[100000];
										sprintf(arr,"Create %s",$2);
										$$ = strdup(arr);}
;
table_database_create : database_k name {
										char arr[10000];
										sprintf(arr,"Database %s",$2);
										$$=strdup(arr);}
				| table_k name '(' create_list ',' primary_k key_k '(' primary_key ')' ')'{
								char arr[10000];
								sprintf(arr,"Table %s with Coloumns %s and Primary Key %s",$2,$4,$9);
								$$=strdup(arr);}
;
create_list : col_def { $$ = strdup($1);}					
	     	| create_list ',' col_def {char arr[10000];
									sprintf(arr,"%s , %s",$1,$3);
									$$=strdup(arr);}
;
col_def : name data_type special_characteristics {  char arr[10000];
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
special_characteristics : not_k null_k { char arr[10000]; sprintf(arr,"Not Null"); $$ = strdup(arr); }
						| not_k null_k auto_k { char arr[10000]; sprintf(arr,"Not Null with Auto Increment"); $$ = strdup(arr); }
						| auto_k {char arr[10000]; sprintf(arr,"Auto Increment"); $$ = strdup(arr); }
						| {$$=NULL;}
;
primary_key :  name {$$ = strdup($1);}
			|  primary_key ',' name {char arr[10000];
									sprintf(arr,"%s , %s",$1,$3);
									$$=strdup(arr);}
;
insert_stmt : insert_k into_k name col_list1 values_k val_set{char arr[10000];
	int length=0;
	if($4!=NULL)
	length+=sprintf(arr+length,"Inserting in columns %s values %s",$4,$6);
	else
	length+=sprintf(arr+length,"Inserting in all columns  values %s",$6);
$$=strdup(arr);
	}
;
col_list1 : '(' col_list ')' {$$=strdup($2);} 
          | {$$=NULL;}; //either col_list or NUll
col_list : name{$$=strdup($1);}|col_list ',' name{char arr[100000];
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
delete_stmt: delete_k from_k name where_stmt{char arr[10000];
	int dl=0;
	if($4==NULL)
	dl+=sprintf(arr,"Deleting all records from the table %s",$3);
	else
	dl+=sprintf(arr,"Deleting records from the table %s where %s",$3,$4);
	$$=strdup(arr);
	}
;
select_stmt : select_k select_col_list from_k name where_stmt orderby_stmt{ char arr[10000];
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
select_col_list : '*' {$$=NULL;}
		 | name {$$=strdup($1);}
	     | select_col_list ',' name {char arr[10000];
									sprintf(arr,"%s , %s",$1,$3);
									$$=strdup(arr);}
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
update_stmt : update_k name set_k set_list {
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
