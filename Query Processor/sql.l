%{
#include "y.tab.h"	
%}
name_exp [a-z][a-z0-9]*
number [0-9]+
%%
DELETE|delete return delete_k;
INSERT|insert return insert_k;
INTO|into return into_k;
VALUES|values return values_k;
DROP|drop return drop_k;
DATABASE|database return database_k;
TABLE|table return table_k;
UPDATE|update return update_k;
CREATE|create return create_k;
SET|set return set_k;
SELECT|select return select_k;
FROM|from return from_k;
WHERE|where return where_k;
ORDER|order return order_k;
AND|and return and_k;
OR|or return or_k;
BY|by return by_k;
ASC|asc return asc_k;
DESC|desc return dec_k;
BIGINT|bigint|INT|int|SMALLINT|smallint|TINYINT|tinyint|BIT|bit|DECIMAL|decimal|NUMERIC|numeric|MONEY|money|SMALLMONEY|smallmoney|FLOAT|float|REAL|real|DATETIME|datetime|SMALLDATETIME|smalldatetime|DATE|date|TIME|time {yylval=strdup(yytext);return datatype_k;}
NOT|not return not_k;
NULL|null return null_k;
AUTO_INCREMENT|auto_increment return auto_k;
PRIMARY|primary return primary_k;
KEY|key return key_k;
"="|","|";"|"*"|"("|")"|"\'" return yytext[0];
{name_exp} {yylval=strdup(yytext); return name;}
{number} {yylval=strdup(yytext); return number;}
[ \t\n] ;
%%
