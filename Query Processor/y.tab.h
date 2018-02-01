/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    insert_k = 258,
    into_k = 259,
    values_k = 260,
    update_k = 261,
    set_k = 262,
    name = 263,
    number = 264,
    select_k = 265,
    from_k = 266,
    where_k = 267,
    order_k = 268,
    by_k = 269,
    and_k = 270,
    or_k = 271,
    asc_k = 272,
    dec_k = 273,
    delete_k = 274,
    datatype_k = 275,
    not_k = 276,
    null_k = 277,
    primary_k = 278,
    key_k = 279,
    auto_k = 280,
    drop_k = 281,
    database_k = 282,
    table_k = 283,
    create_k = 284,
    rename_k = 285,
    alter_k = 286,
    add_k = 287,
    constraint_k = 288,
    limit_k = 289,
    use_k = 290,
    show_k = 291,
    databases_k = 292,
    tables_k = 293,
    columns_k = 294,
    index_k = 295,
    view_k = 296,
    unique_k = 297,
    foreign_k = 298,
    references_k = 299,
    on_k = 300,
    as_k = 301,
    to_k = 302,
    change_k = 303,
    in_k = 304
  };
#endif
/* Tokens.  */
#define insert_k 258
#define into_k 259
#define values_k 260
#define update_k 261
#define set_k 262
#define name 263
#define number 264
#define select_k 265
#define from_k 266
#define where_k 267
#define order_k 268
#define by_k 269
#define and_k 270
#define or_k 271
#define asc_k 272
#define dec_k 273
#define delete_k 274
#define datatype_k 275
#define not_k 276
#define null_k 277
#define primary_k 278
#define key_k 279
#define auto_k 280
#define drop_k 281
#define database_k 282
#define table_k 283
#define create_k 284
#define rename_k 285
#define alter_k 286
#define add_k 287
#define constraint_k 288
#define limit_k 289
#define use_k 290
#define show_k 291
#define databases_k 292
#define tables_k 293
#define columns_k 294
#define index_k 295
#define view_k 296
#define unique_k 297
#define foreign_k 298
#define references_k 299
#define on_k 300
#define as_k 301
#define to_k 302
#define change_k 303
#define in_k 304

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
