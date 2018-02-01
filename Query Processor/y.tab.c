/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "sql.y" /* yacc.c:339  */

#include<stdio.h>
#include<string.h>	
#include"tree.h"
#define YYSTYPE char*
int yylex();
int yyerror(char *s);
Sql_stmt stmt;

#line 76 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif


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
    select_k = 263,
    from_k = 264,
    where_k = 265,
    order_k = 266,
    by_k = 267,
    and_k = 268,
    or_k = 269,
    asc_k = 270,
    dec_k = 271,
    delete_k = 272,
    not_k = 273,
    null_k = 274,
    primary_k = 275,
    key_k = 276,
    auto_k = 277,
    drop_k = 278,
    database_k = 279,
    table_k = 280,
    create_k = 281,
    rename_k = 282,
    alter_k = 283,
    add_k = 284,
    constraint_k = 285,
    limit_k = 286,
    use_k = 287,
    show_k = 288,
    databases_k = 289,
    tables_k = 290,
    columns_k = 291,
    index_k = 292,
    view_k = 293,
    unique_k = 294,
    foreign_k = 295,
    references_k = 296,
    on_k = 297,
    as_k = 298,
    to_k = 299,
    change_k = 300,
    in_k = 301,
    name = 302,
    datatype_k = 303,
    number = 304
  };
#endif
/* Tokens.  */
#define insert_k 258
#define into_k 259
#define values_k 260
#define update_k 261
#define set_k 262
#define select_k 263
#define from_k 264
#define where_k 265
#define order_k 266
#define by_k 267
#define and_k 268
#define or_k 269
#define asc_k 270
#define dec_k 271
#define delete_k 272
#define not_k 273
#define null_k 274
#define primary_k 275
#define key_k 276
#define auto_k 277
#define drop_k 278
#define database_k 279
#define table_k 280
#define create_k 281
#define rename_k 282
#define alter_k 283
#define add_k 284
#define constraint_k 285
#define limit_k 286
#define use_k 287
#define show_k 288
#define databases_k 289
#define tables_k 290
#define columns_k 291
#define index_k 292
#define view_k 293
#define unique_k 294
#define foreign_k 295
#define references_k 296
#define on_k 297
#define as_k 298
#define to_k 299
#define change_k 300
#define in_k 301
#define name 302
#define datatype_k 303
#define number 304

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 12 "sql.y" /* yacc.c:355  */

	Cond_exp cond_exp;
	Where_stmt where_stmt;
	Orderby_stmt orderby_stmt;
	Col_def col_def;
	Constraints constraints;
	Create_def create_def;
	Alter_spec alter_spec;
	Sql_stmt sql_stmt;
	Update_stmt update_stmt;
	Select_stmt select_stmt;
	Drop_stmt drop_stmt;
	Create_stmt create_stmt;
	Insert_stmt insert_stmt;
	Delete_stmt delete_stmt;
	Rename_stmt rename_stmt;
	Alter_stmt alter_stmt;
	Use_stmt use_stmt;
	Show_stmt show_stmt;
	Special_ele special_ele;
	vector<Special_ele> special_list
	vector<Alter_spec> alter_spec_list
	vector<Create_def> create_def_list;
	vector<Col_def> col_def_list;
	vector<string> str_list;
	vector<vector<string> > val_set;
	pair<string,string> set_single;
	string s;
	int x;
	bool order;
	vector<pair<string,string> > rnm_list;

#line 244 "y.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);



/* Copy the second part of user declarations.  */

#line 261 "y.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  47
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   200

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  57
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  45
/* YYNRULES -- Number of rules.  */
#define YYNRULES  96
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  206

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   304

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    54,
      51,    52,    55,     2,    53,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    50,
       2,    56,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    83,    83,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    96,    98,    99,   100,   101,   103,   105,
     106,   107,   108,   110,   113,   115,   116,   118,   119,   120,
     121,   123,   125,   126,   128,   129,   131,   132,   133,   134,
     135,   137,   139,   140,   142,   144,   146,   147,   148,   150,
     151,   153,   155,   156,   157,   158,   160,   161,   163,   165,
     166,   168,   169,   170,   171,   173,   175,   176,   178,   179,
     181,   182,   183,   185,   186,   188,   189,   191,   192,   194,
     195,   197,   199,   200,   202,   203,   205,   207,   209,   210,
     212,   213,   215,   216,   218,   219,   220
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "insert_k", "into_k", "values_k",
  "update_k", "set_k", "select_k", "from_k", "where_k", "order_k", "by_k",
  "and_k", "or_k", "asc_k", "dec_k", "delete_k", "not_k", "null_k",
  "primary_k", "key_k", "auto_k", "drop_k", "database_k", "table_k",
  "create_k", "rename_k", "alter_k", "add_k", "constraint_k", "limit_k",
  "use_k", "show_k", "databases_k", "tables_k", "columns_k", "index_k",
  "view_k", "unique_k", "foreign_k", "references_k", "on_k", "as_k",
  "to_k", "change_k", "in_k", "name", "datatype_k", "number", "';'", "'('",
  "')'", "','", "'\\''", "'*'", "'='", "$accept", "sql", "sql_stmt",
  "drop_stmt", "type_drop", "create_stmt", "type_create",
  "create_def_list", "create_def", "constraints", "col_def", "data_type",
  "special_list", "special_ele", "rename_stmt", "rename_list", "use_stmt",
  "show_stmt", "type_show", "opt_db", "insert_stmt", "col_list_chk",
  "name_list", "val_set", "val_list1", "val_list", "name1", "delete_stmt",
  "select_stmt", "select_col_chk", "where_stmt", "where_cond", "cond_exp",
  "orderby_stmt", "orderby_list", "order_type", "update_stmt", "set_list",
  "set_single", "limit_stmt", "alter_stmt", "alter_spec_list",
  "add_col_def", "col_def_list", "alter_spec", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
      59,    40,    41,    44,    39,    42,    61
};
# endif

#define YYPACT_NINF -93

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-93)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       2,    46,   -32,   -38,    18,    41,    47,     8,    35,    26,
      20,    69,    17,   -93,   -93,   -93,   -93,   -93,   -93,   -93,
     -93,   -93,   -93,    43,    84,   -93,   -93,    39,    85,    48,
      49,    50,    51,    50,   -93,    52,    53,    54,    55,   -93,
      57,    58,   -93,   -93,    60,    61,   -93,   -93,   -93,    42,
      62,    63,    64,    98,   -93,    39,    70,    39,   -93,    65,
      72,    42,    71,    66,   -22,    73,    74,    50,   112,    68,
      -9,   -93,   -93,    98,    75,   107,    76,     6,    78,    83,
      80,    81,     1,    82,    77,   -93,   -93,    86,   -41,    87,
     -29,   119,    62,   102,   107,    79,    44,   -93,   102,   -93,
     113,    42,    42,   115,    89,    11,   -93,   -93,   -93,    88,
     133,   -93,    99,    22,    95,   -93,   -93,    95,   -22,    97,
     -93,   -33,    92,   -93,   -93,   -93,   100,   -93,   101,   -93,
     102,   -25,    75,    75,   -93,    42,   -93,   -93,    42,   103,
      29,   -93,     6,    50,   -93,   104,   -93,   -93,    23,   -93,
     -93,   -93,   -93,   -93,   -93,   105,    28,   -93,    87,    67,
      93,   -93,   -93,   -93,   -93,   -93,   -93,   -93,   108,   106,
     129,   132,   -93,   -93,   109,    29,   -93,   -93,    34,   -93,
     -93,    95,   110,   -93,   -33,   -93,   -93,   -93,   -93,   111,
     114,   116,   -93,   -93,   118,   -93,   -93,   -93,   -93,   -93,
      67,    42,   -93,   -93,   -93,   -93
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     5,     6,     9,    11,    12,     7,     8,
       4,     3,    10,     0,     0,    54,    66,    67,     0,     0,
       0,     0,     0,     0,    13,     0,     0,     0,     0,    18,
       0,     0,    44,    46,     0,     0,    45,     1,     2,    53,
       0,     0,     0,    69,    14,    15,     0,    17,    19,     0,
       0,    53,     0,    41,     0,     0,     0,     0,     0,     0,
      76,    82,    55,    69,     0,    76,     0,     0,     0,     0,
       0,     0,     0,     0,    87,    88,    47,     0,     0,     0,
       0,     0,     0,     0,    76,     0,    68,    70,     0,    16,
       0,    53,    53,     0,     0,     0,    23,    26,    25,     0,
       0,    42,     0,     0,     0,    90,    94,     0,     0,    50,
      52,     0,    51,    56,    84,    85,     0,    83,     0,    81,
       0,     0,     0,     0,    64,    53,    28,    29,    53,    32,
       0,    20,     0,     0,    22,     0,    95,    92,     0,    96,
      89,    49,    48,    62,    63,     0,     0,    59,     0,     0,
      75,    86,    65,    73,    74,    71,    72,    27,     0,     0,
       0,     0,    37,    39,     0,    31,    34,    24,     0,    43,
      91,     0,     0,    58,     0,    57,    79,    80,    77,     0,
       0,     0,    36,    38,     0,    35,    21,    93,    61,    60,
       0,    53,    33,    40,    78,    30
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -93,   -93,   -93,   -93,   -93,   -93,   -93,   -93,    15,    56,
     -78,   -93,   -93,   -16,   -93,   -93,   -93,   -93,   -93,   -93,
     -93,   -61,   -30,   -93,     4,   -93,   -24,   -93,    90,   -93,
      94,   -93,   -44,   -62,   -93,   -37,   -93,   -93,    91,   -92,
     -93,   -93,   -93,   -93,    59
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    11,    12,    13,    34,    14,    39,   105,   106,   107,
     108,   140,   175,   176,    15,    63,    16,    17,    46,   152,
      18,    68,    27,   122,   123,   156,   157,    19,    20,    28,
      75,    96,    97,    93,   160,   188,    21,    70,    71,   129,
      22,    84,   116,   148,    85
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      79,    55,    91,    57,   115,     1,   134,    82,     2,    25,
       3,   120,    51,    98,   153,    24,   154,    26,   124,     4,
     125,   155,   163,    83,   164,     5,   100,    29,     6,     7,
       8,   113,   130,    40,     9,    10,   147,    88,   162,   149,
     136,   137,   100,   101,    92,   102,   103,   170,   104,   171,
      23,   172,   114,   104,    43,    44,    45,   132,   133,   101,
      41,   102,   103,   141,   142,    30,    31,    48,   173,    47,
     174,    35,    36,    42,   167,   180,   181,   168,    32,    33,
     183,   184,   186,   187,    37,    38,   196,    51,   165,   166,
      49,    50,    51,    67,    52,    53,    54,    25,    56,    58,
      59,    60,    61,   197,    62,    64,    65,    66,    74,    69,
      72,    73,    76,   178,    78,    80,    77,    89,    91,    81,
      86,    87,    95,    99,    90,   109,   110,   111,   112,   117,
     118,   126,   119,   128,   135,   131,   138,   139,   121,   143,
     205,     3,   104,   145,   151,   158,   189,   159,   192,   190,
     161,   179,   182,   193,   169,   191,   194,   177,   200,   195,
     199,   201,   185,   204,   198,   203,     0,    94,   202,   146,
       0,     0,     0,     0,     0,     0,     0,   150,     0,     0,
       0,     0,     0,   127,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     144
};

static const yytype_int16 yycheck[] =
{
      61,    31,    11,    33,    82,     3,    98,    29,     6,    47,
       8,    52,    53,    75,    47,    47,    49,    55,    47,    17,
      49,    54,    47,    45,    49,    23,    20,     9,    26,    27,
      28,    30,    94,    25,    32,    33,   114,    67,   130,   117,
     101,   102,    20,    37,    53,    39,    40,    18,    47,    20,
       4,    22,    51,    47,    34,    35,    36,    13,    14,    37,
      25,    39,    40,    52,    53,    24,    25,    50,    39,     0,
      41,    24,    25,    47,   135,    52,    53,   138,    37,    38,
      52,    53,    15,    16,    37,    38,    52,    53,   132,   133,
      47,     7,    53,    51,     9,    47,    47,    47,    47,    47,
      47,    47,    47,   181,    47,    47,    46,    46,    10,    47,
      47,    47,    42,   143,    42,    44,    51,     5,    11,    53,
      47,    47,    47,    47,    56,    47,    43,    47,    47,    47,
      53,    12,    46,    31,    21,    56,    21,    48,    51,    51,
     201,     8,    47,    44,    47,    53,    53,    47,    19,    41,
      49,    47,    47,    21,    51,    49,    47,   142,    47,   175,
     184,    47,   158,   200,    54,    47,    -1,    73,    52,   113,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   118,    -1,    -1,
      -1,    -1,    -1,    92,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     110
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     6,     8,    17,    23,    26,    27,    28,    32,
      33,    58,    59,    60,    62,    71,    73,    74,    77,    84,
      85,    93,    97,     4,    47,    47,    55,    79,    86,     9,
      24,    25,    37,    38,    61,    24,    25,    37,    38,    63,
      25,    25,    47,    34,    35,    36,    75,     0,    50,    47,
       7,    53,     9,    47,    47,    79,    47,    79,    47,    47,
      47,    47,    47,    72,    47,    46,    46,    51,    78,    47,
      94,    95,    47,    47,    10,    87,    42,    51,    42,    78,
      44,    53,    29,    45,    98,   101,    47,    47,    79,     5,
      56,    11,    53,    90,    87,    47,    88,    89,    90,    47,
      20,    37,    39,    40,    47,    64,    65,    66,    67,    47,
      43,    47,    47,    30,    51,    67,    99,    47,    53,    46,
      52,    51,    80,    81,    47,    49,    12,    95,    31,    96,
      90,    56,    13,    14,    96,    21,    78,    78,    21,    48,
      68,    52,    53,    51,    85,    44,    66,    67,   100,    67,
     101,    47,    76,    47,    49,    54,    82,    83,    53,    47,
      91,    49,    96,    47,    49,    89,    89,    78,    78,    51,
      18,    20,    22,    39,    41,    69,    70,    65,    79,    47,
      52,    53,    47,    52,    53,    81,    15,    16,    92,    53,
      41,    49,    19,    21,    47,    70,    52,    67,    54,    83,
      47,    47,    52,    47,    92,    78
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    57,    58,    59,    59,    59,    59,    59,    59,    59,
      59,    59,    59,    60,    61,    61,    61,    61,    62,    63,
      63,    63,    63,    64,    64,    65,    65,    66,    66,    66,
      66,    67,    68,    68,    69,    69,    70,    70,    70,    70,
      70,    71,    72,    72,    73,    74,    75,    75,    75,    76,
      76,    77,    78,    78,    79,    79,    80,    80,    81,    82,
      82,    83,    83,    83,    84,    85,    86,    86,    87,    87,
      88,    88,    88,    89,    89,    90,    90,    91,    91,    92,
      92,    93,    94,    94,    95,    95,    96,    97,    98,    98,
      99,    99,   100,   100,   101,   101,   101
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     2,     2,     4,     2,     2,     2,
       5,     7,     5,     1,     3,     1,     1,     3,     2,     2,
       6,     3,     1,     4,     1,     2,     2,     1,     2,     1,
       3,     3,     3,     5,     2,     2,     1,     3,     5,     1,
       0,     6,     3,     0,     1,     3,     1,     3,     3,     1,
       3,     3,     1,     1,     6,     7,     1,     1,     2,     0,
       1,     3,     3,     3,     3,     3,     0,     2,     4,     1,
       1,     6,     1,     3,     3,     3,     2,     4,     1,     3,
       1,     3,     1,     3,     2,     3,     3
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 83 "sql.y" /* yacc.c:1646  */
    {stmt=(yyvsp[-1].sql_stmt);}
#line 1487 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 85 "sql.y" /* yacc.c:1646  */
    {(yyval.sql_stmt)=(yyvsp[0].update_stmt);}
#line 1493 "y.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 86 "sql.y" /* yacc.c:1646  */
    {(yyval.sql_stmt)=(yyvsp[0].select_stmt);}
#line 1499 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 87 "sql.y" /* yacc.c:1646  */
    {(yyval.sql_stmt)=(yyvsp[0].drop_stmt);}
#line 1505 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 88 "sql.y" /* yacc.c:1646  */
    {(yyval.sql_stmt)=(yyvsp[0].create_stmt);}
#line 1511 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 89 "sql.y" /* yacc.c:1646  */
    {(yyval.sql_stmt)=(yyvsp[0].insert_stmt);}
#line 1517 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 90 "sql.y" /* yacc.c:1646  */
    {(yyval.sql_stmt)=(yyvsp[0].delete_stmt);}
#line 1523 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 91 "sql.y" /* yacc.c:1646  */
    {(yyval.sql_stmt)=(yyvsp[0].rename_stmt);}
#line 1529 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 92 "sql.y" /* yacc.c:1646  */
    {(yyval.sql_stmt)=(yyvsp[0].alter_stmt);}
#line 1535 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 93 "sql.y" /* yacc.c:1646  */
    {(yyval.sql_stmt)=(yyvsp[0].use_stmt);}
#line 1541 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 94 "sql.y" /* yacc.c:1646  */
    {(yyval.sql_stmt)=(yyvsp[0].show_stmt);}
#line 1547 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 96 "sql.y" /* yacc.c:1646  */
    {(yyval.drop_stmt)=(yyvsp[0].drop_stmt);}
#line 1553 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 98 "sql.y" /* yacc.c:1646  */
    {(yyval.drop_stmt)=new Db_drop((yyvsp[0].s));}
#line 1559 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 99 "sql.y" /* yacc.c:1646  */
    {(yyval.drop_stmt)=new Tbl_drop((yyvsp[0].str_list));}
#line 1565 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 100 "sql.y" /* yacc.c:1646  */
    {(yyval.drop_stmt)=new Idx_drop((yyvsp[-2].s),(yyvsp[0].s));}
#line 1571 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 101 "sql.y" /* yacc.c:1646  */
    {(yyval.drop_stmt)=new View_drop((yyvsp[0].str_list));}
#line 1577 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 103 "sql.y" /* yacc.c:1646  */
    {(yyval.create_stmt)=(yyvsp[0].create_stmt);}
#line 1583 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 105 "sql.y" /* yacc.c:1646  */
    {(yyval.create_stmt)=new Db_create((yyvsp[0].s));}
#line 1589 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 106 "sql.y" /* yacc.c:1646  */
    {(yyval.create_stmt)=new Tbl_create((yyvsp[-3].s),(yyvsp[-1].create_def_list));}
#line 1595 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 107 "sql.y" /* yacc.c:1646  */
    {(yyval.create_stmt)=new Idx_create((yyvsp[-5].s),(yyvsp[-3].s),(yyvsp[-1].str_list));}
#line 1601 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 108 "sql.y" /* yacc.c:1646  */
    {(yyval.create_stmt)=new View_create((yyvsp[-3].s),(yyvsp[-2].str_list),(yyvsp[0].select_stmt));}
#line 1607 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 110 "sql.y" /* yacc.c:1646  */
    {vector<Create_def> list;
								list.push_back((yyvsp[0].create_def));
								(yyval.create_def_list)=list;}
#line 1615 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 113 "sql.y" /* yacc.c:1646  */
    {(yyval.create_def_list)=(yyvsp[-2].create_def_list);(yyval.create_def_list).push_back((yyvsp[0].create_def));}
#line 1621 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 115 "sql.y" /* yacc.c:1646  */
    {	(yyval.create_def)=new Create_def();(yyval.create_def).type=1;(yyval.create_def).x.cd=(yyvsp[0].col_def);}
#line 1627 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 116 "sql.y" /* yacc.c:1646  */
    {(yyval.create_def)=new Create_def();(yyval.create_def).type=2;(yyval.create_def).x.con=(yyvsp[0].constraints); }
#line 1633 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 118 "sql.y" /* yacc.c:1646  */
    {(yyval.constraints)=new Primary_key((yyvsp[0].str_list));}
#line 1639 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 119 "sql.y" /* yacc.c:1646  */
    {(yyval.constraints)=new Index_key((yyvsp[0].str_list));}
#line 1645 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 120 "sql.y" /* yacc.c:1646  */
    {(yyval.constraints)=new Unique_key((yyvsp[0].str_list));}
#line 1651 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 121 "sql.y" /* yacc.c:1646  */
    {(yyval.constraints)=new Foreign_key((yyvsp[-3].str_list),(yyvsp[-1].s),(yyvsp[0].str_list));}
#line 1657 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 123 "sql.y" /* yacc.c:1646  */
    { (yyval.col_def)=new Col_def((yyvsp[-2].s),(yyvsp[-1].s),(yyvsp[0].special_list));}
#line 1663 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 125 "sql.y" /* yacc.c:1646  */
    {(yyval.s) = strdup((yyvsp[0].s));}
#line 1669 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 126 "sql.y" /* yacc.c:1646  */
    { (yyval.s)=strdup((yyvsp[-3].s));}
#line 1675 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 128 "sql.y" /* yacc.c:1646  */
    { vector<special_ele> list; list.push_back((yyvsp[0].special_ele));(yyval.special_list)=(yyvsp[0].special_ele);}
#line 1681 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 129 "sql.y" /* yacc.c:1646  */
    {(yyval.special_list)=(yyvsp[-1].special_list);(yyval.special_list).push_back((yyvsp[0].special_ele));}
#line 1687 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 131 "sql.y" /* yacc.c:1646  */
    {(yyval.special_ele)=new Special_ele(1);}
#line 1693 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 132 "sql.y" /* yacc.c:1646  */
    {(yyval.special_ele)=new Special_ele(2);}
#line 1699 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 133 "sql.y" /* yacc.c:1646  */
    {(yyval.special_ele)=new Special_ele(3);}
#line 1705 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 134 "sql.y" /* yacc.c:1646  */
    {(yyval.special_ele)=new Special_ele(4);}
#line 1711 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 135 "sql.y" /* yacc.c:1646  */
    {(yyval.special_ele)=new Special_ele(5,(yyvsp[-1].s),(yyvsp[0].s));}
#line 1717 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 137 "sql.y" /* yacc.c:1646  */
    { (yyval.rename_stmt)=new Rename_stmt((yyvsp[0].rnm_list));}
#line 1723 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 139 "sql.y" /* yacc.c:1646  */
    { vector<pair<string,string> > list;list.push_back(make_pair((yyvsp[-2].s),(yyvsp[0].s)));(yyval.rnm_list)=list;}
#line 1729 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 140 "sql.y" /* yacc.c:1646  */
    {(yyval.rnm_list)=(yyvsp[-4].rnm_list);(yyval.rnm_list).push_back(make_pair((yyvsp[-4].rnm_list),(yyvsp[-2].s)));}
#line 1735 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 142 "sql.y" /* yacc.c:1646  */
    { (yyval.use_stmt)=new Use_stmt((yyvsp[0].s));}
#line 1741 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 144 "sql.y" /* yacc.c:1646  */
    {(yyval.show_stmt)=(yyvsp[0].show_stmt); }
#line 1747 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 146 "sql.y" /* yacc.c:1646  */
    { (yyval.show_stmt)=new Db_show();}
#line 1753 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 147 "sql.y" /* yacc.c:1646  */
    { (yyval.show_stmt)=new new Tbl_show((yyvsp[0].s));}
#line 1759 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 148 "sql.y" /* yacc.c:1646  */
    {(yyval.show_stmt)=new Clmns_show((yyvsp[-2].s),(yyvsp[0].s));}
#line 1765 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 150 "sql.y" /* yacc.c:1646  */
    { (yyval.s)=strdup((yyvsp[0].s));}
#line 1771 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 151 "sql.y" /* yacc.c:1646  */
    { (yyval.s)=NULL;}
#line 1777 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 153 "sql.y" /* yacc.c:1646  */
    {(yyval.insert_stmt)=new Insert_stmt((yyvsp[-3].s),(yyvsp[-2].str_list),(yyvsp[0].val_set));}
#line 1783 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 155 "sql.y" /* yacc.c:1646  */
    {(yyval.str_list)=(yyvsp[-1].str_list);}
#line 1789 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 156 "sql.y" /* yacc.c:1646  */
    {(yyval.str_list)=NULL;}
#line 1795 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 157 "sql.y" /* yacc.c:1646  */
    {vector<string> list;list.push_back((yyvsp[0].s));(yyval.str_list)=list;}
#line 1801 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 158 "sql.y" /* yacc.c:1646  */
    {(yyval.str_list)=(yyvsp[-2].str_list);(yyval.str_list).push_back((yyvsp[0].s));}
#line 1807 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 160 "sql.y" /* yacc.c:1646  */
    {vector<vector<string> > list;list.push_back((yyvsp[0].str_list));(yyval.val_set)=list;}
#line 1813 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 161 "sql.y" /* yacc.c:1646  */
    {(yyval.val_set)=(yyvsp[-2].val_set);(yyval.val_set).push_back((yyvsp[0].str_list));}
#line 1819 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 163 "sql.y" /* yacc.c:1646  */
    {(yyval.str_list)=(yyvsp[-1].str_list);}
#line 1825 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 165 "sql.y" /* yacc.c:1646  */
    {vector<string> list;list.push_back((yyvsp[0].s));(yyval.str_list)=list;}
#line 1831 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 166 "sql.y" /* yacc.c:1646  */
    {(yyval.str_list)=(yyvsp[-2].str_list);(yyval.str_list).push_back((yyvsp[0].s));}
#line 1837 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 168 "sql.y" /* yacc.c:1646  */
    {(yyval.s)=strdup((yyvsp[-1].s));}
#line 1843 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 169 "sql.y" /* yacc.c:1646  */
    {(yyval.s)=strdup((yyvsp[0].s));}
#line 1849 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 170 "sql.y" /* yacc.c:1646  */
    {(yyval.s)=strdup((yyvsp[0].s));}
#line 1855 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 171 "sql.y" /* yacc.c:1646  */
    {(yyval.delete_stmt)=new Delete_stmt((yyvsp[-3].s),(yyvsp[-2].where_stmt),(yyvsp[-1].orderby_stmt),(yyvsp[0].x));}
#line 1861 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 173 "sql.y" /* yacc.c:1646  */
    {(yyval.select_stmt)=new Select_stmt((yyvsp[-5].str_list),(yyvsp[-3].s),(yyvsp[-2].where_stmt),(yyvsp[-1].orderby_stmt),(yyvsp[0].x));}
#line 1867 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 175 "sql.y" /* yacc.c:1646  */
    {(yyval.str_list)=NULL;}
#line 1873 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 178 "sql.y" /* yacc.c:1646  */
    {(yyval.where_stmt)=(yyvsp[0].where_stmt);}
#line 1879 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 179 "sql.y" /* yacc.c:1646  */
    {(yyval.where_stmt)=NULL;}
#line 1885 "y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 181 "sql.y" /* yacc.c:1646  */
    {(yyval.where_stmt)=new Where_stmt((yyvsp[0].cond_exp));}
#line 1891 "y.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 182 "sql.y" /* yacc.c:1646  */
    {(yyval.where_stmt)=(yyvsp[-2].where_stmt);(yyval.where_stmt).and_list.push_back((yyvsp[0].cond_exp));}
#line 1897 "y.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 183 "sql.y" /* yacc.c:1646  */
    {(yyval.where_stmt)=(yyvsp[-2].where_stmt);(yyval.where_stmt).or_list.push_back((yyvsp[0].cond_exp));}
#line 1903 "y.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 185 "sql.y" /* yacc.c:1646  */
    {(yyval.cond_exp)=new Cond_exp();(yyval.cond_exp).type=1;(yyval.cond_exp).lhs=(yyvsp[-2].s),(yyval.cond_exp).x.s_rhs=(yyvsp[0].s);}
#line 1909 "y.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 186 "sql.y" /* yacc.c:1646  */
    {(yyval.cond_exp)=new Cond_exp();(yyval.cond_exp).type=2;(yyval.cond_exp).lhs=(yyvsp[-2].s),(yyval.cond_exp).x.i_rhs=(yyvsp[0].s);}
#line 1915 "y.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 188 "sql.y" /* yacc.c:1646  */
    {(yyval.orderby_stmt)=(yyvsp[0].orderby_stmt);}
#line 1921 "y.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 189 "sql.y" /* yacc.c:1646  */
    {(yyval.orderby_stmt)=NULL;}
#line 1927 "y.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 191 "sql.y" /* yacc.c:1646  */
    {(yyval.orderby_stmt)=new Orderby_stmt(make_pair((yyvsp[-1].s),(yyvsp[0].order)));}
#line 1933 "y.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 192 "sql.y" /* yacc.c:1646  */
    {(yyval.orderby_stmt)=(yyvsp[-3].orderby_stmt);(yyval.orderby_stmt).clmns_list.push_back(make_pair((yyvsp[-1].s),(yyvsp[0].order)));}
#line 1939 "y.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 194 "sql.y" /* yacc.c:1646  */
    {(yyval.order)=true;}
#line 1945 "y.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 195 "sql.y" /* yacc.c:1646  */
    {(yyval.order)=false;}
#line 1951 "y.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 197 "sql.y" /* yacc.c:1646  */
    {(yyval.update_stmt)=new Update_stmt((yyvsp[-4].s),(yyvsp[-2].rnm_list),(yyvsp[-1].orderby_stmt),(yyvsp[0].x));}
#line 1957 "y.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 199 "sql.y" /* yacc.c:1646  */
    {vector<pair<string,string> > list;list.push_back((yyvsp[0].set_single));(yyval.rnm_list)=list;}
#line 1963 "y.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 200 "sql.y" /* yacc.c:1646  */
    { (yyval.rnm_list)=(yyvsp[-2].rnm_list);(yyval.rnm_list).push_back((yyvsp[0].set_single));}
#line 1969 "y.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 202 "sql.y" /* yacc.c:1646  */
    {(yyval.set_single)=make_pair((yyvsp[-2].s),(yyvsp[0].s));}
#line 1975 "y.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 203 "sql.y" /* yacc.c:1646  */
    {(yyval.set_single)=make_pair((yyvsp[-2].s),strdup((yyvsp[0].s)));}
#line 1981 "y.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 205 "sql.y" /* yacc.c:1646  */
    {(yyval.x)=(yyvsp[0].s);}
#line 1987 "y.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 207 "sql.y" /* yacc.c:1646  */
    {(yyval.alter_stmt)=new Alter_stmt((yyvsp[-1].s),(yyvsp[0].alter_spec_list));}
#line 1993 "y.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 209 "sql.y" /* yacc.c:1646  */
    {vector<Alter_spec> list;list.push_back((yyvsp[0].alter_spec));(yyval.alter_spec_list)=(yyvsp[0].alter_spec);}
#line 1999 "y.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 210 "sql.y" /* yacc.c:1646  */
    {(yyval.alter_spec_list)=(yyvsp[-2].alter_spec_list);(yyval.alter_spec_list).push_back((yyvsp[0].alter_spec));}
#line 2005 "y.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 212 "sql.y" /* yacc.c:1646  */
    {vector<Col_def> list;list.push_back((yyvsp[0].col_def));(yyval.col_def_list)=(yyvsp[0].col_def);}
#line 2011 "y.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 213 "sql.y" /* yacc.c:1646  */
    {(yyval.col_def_list)=(yyvsp[-1].col_def_list);}
#line 2017 "y.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 215 "sql.y" /* yacc.c:1646  */
    {vector<Col_def> list;list.push_back((yyvsp[0].col_def));(yyval.col_def_list)=(yyvsp[0].col_def);}
#line 2023 "y.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 216 "sql.y" /* yacc.c:1646  */
    {(yyval.col_def_list)=(yyvsp[-2].col_def_list);(yyval.col_def_list).push_back((yyvsp[0].col_def));}
#line 2029 "y.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 218 "sql.y" /* yacc.c:1646  */
    {(yyval.alter_spec)=new Alter_spec();(yyval.alter_spec).type=1;(yyval.alter_spec).x.add_col=(yyvsp[0].col_def_list);}
#line 2035 "y.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 219 "sql.y" /* yacc.c:1646  */
    {(yyval.alter_spec)=new Alter_spec();(yyval.alter_spec).type=2;(yyval.alter_spec).x.con=(yyvsp[0].constraints);}
#line 2041 "y.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 220 "sql.y" /* yacc.c:1646  */
    {(yyval.alter_spec)=new Alter_spec();(yyval.alter_spec).type=3;(yyval.alter_spec).x.cng_col=new Change_col((yyvsp[-1].s),(yyvsp[0].col_def));}
#line 2047 "y.tab.c" /* yacc.c:1646  */
    break;


#line 2051 "y.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 222 "sql.y" /* yacc.c:1906  */

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
