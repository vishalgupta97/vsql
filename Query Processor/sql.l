%{
#include "sql.tab.h"	
%}
name_exp [a-z][a-z0-9]*
number [0-9]+
%%
DELETE|delete return delete_k;
INSERT|insert return insert_k;
UPDATE|update return update_k;
CREATE|create return create_k;
SELECT|select return select_k;
DROP|drop return drop_k;
RENAME|rename return rename_k;
ALTER|alter return alter_k;
ADD|add return add_k;
CONSTRAINT|constraint return constraint_k;
LIMIT|limit return limit_k;
USE|use return use_k;
SHOW|show return show_k;
DATABASES|databases return databases_k;
TABLES|tables return tables_k;
COLUMNS|columns return columns_k;
INTO|into return into_k;
VALUES|values return values_k;
DATABASE|database return database_k;
TABLE|table return table_k;
INDEX|index return index_k;
VIEW|view return view_k;
SET|set return set_k;
FROM|from return from_k;
WHERE|where return where_k;
ORDER|order return order_k;
AND|and return and_k;
OR|or return or_k;
BY|by return by_k;
ASC|asc return asc_k;
DESC|desc return dec_k;
INT|int|DECIMAL|decimal|VARCHAR|varchar|TIMESTAMP|timestamp {yylval.s=new std::string(yytext,yyleng);return datatype_k;}
NOT|not return not_k;
NULL|null return null_k;
AUTO_INCREMENT|auto_increment return auto_k;
PRIMARY|primary return primary_k;
KEY|key return key_k;
UNIQUE|unique return unique_k;
FOREIGN|foreign return foreign_k;
REFERENCES|references return references_k;
ON|on return on_k;
AS|as return as_k;
TO|to return to_k;
IN|in return in_k;
CHANGE|change return change_k;
"="|","|";"|"*"|"("|")"|"\'"|"." return yytext[0];
{name_exp} {yylval.s=new std::string(yytext,yyleng); return name;}
{number} {yylval.x=stoi(yytext); return number;}
"\n" return 0;
[ \t] ;
%%
