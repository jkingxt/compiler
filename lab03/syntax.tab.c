/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 1



/* Copy the first part of user declarations.  */

/* Line 268 of yacc.c  */
#line 1 "syntax.y"

	#include <stdio.h>
	#include "lex.yy.c"
	#include <stdlib.h>
	#include <string.h>
	typedef struct Type_* Type; 
	typedef struct FieldList_* FieldList; 
	
	int flag =1;
	 
	struct Type_
	{ 
	  enum { basic, array, structure, function, variable } kind; 
	  union 
	  { 
		// 基本类型 
		int basic; 
		// 数组类型信息包括元素类型与数组大小构成 
		struct { Type elem; int size; } array; 
		// 结构体类型信息是一个链表 
		FieldList structure;
		FieldList function; 
		FieldList variable;
	  } u; 
	}; 
	 
	struct FieldList_ 
	{ 
	  char* name;    // 域的名字 
	  Type type;      // 域的类型 
	  int func_dec;    //函数是否被定义
	  FieldList tail;    // 下一个域 
	};
	struct TreeNode{
		char name[20];
		int lineno;
		int depth;
		int value_int;//int型数的值
		char value_str[20];//id的名字或者type类型
		int type;//判断是否为空
		/*一个节点的操作源，-1代表不关注，0代表基本变量定义，1代表结构体定义；2代表结构体成员定义，3代表函数参数定义，4代表函数体定义，5代表函数体声明，6代表使用变量，7代表函数调用,
				  8代表访问结构体成员,9代表使用该结构体定义变量。
		*/
		int srcop;
		Type real_type;//用来数组确定真实属性
		Type return_type;//综合属性，记录return返回类型
		Type syn_type;//综合属性，记录总体类型
		struct TreeNode* neighbours;
		struct TreeNode* children;
	};
	struct TreeNode* treeStack[10];
	int treeStackTop = -1;
	struct TreeNode* treeRoot;
	struct TreeNode* create(char *p,int lineno,char value_str[], int value_int,int type);


/* Line 268 of yacc.c  */
#line 128 "syntax.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     INT = 258,
     PLUS = 259,
     MINUS = 260,
     STAR = 261,
     DIV = 262,
     SEMI = 263,
     COMMA = 264,
     RELOP = 265,
     ASSIGNOP = 266,
     AND = 267,
     OR = 268,
     NOT = 269,
     DOT = 270,
     TYPE = 271,
     LP = 272,
     RP = 273,
     LB = 274,
     RB = 275,
     LC = 276,
     RC = 277,
     STRUCT = 278,
     RETURN = 279,
     IF = 280,
     ELSE = 281,
     WHILE = 282,
     ID = 283,
     FLOAT = 284,
     LOWER_THAN_ELSE = 285
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 293 of yacc.c  */
#line 58 "syntax.y"

int type_int;
char *type_str;
float type_float;



/* Line 293 of yacc.c  */
#line 202 "syntax.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 227 "syntax.tab.c"

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
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
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
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
	     && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  11
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   259

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  31
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  63
/* YYNRULES -- Number of states.  */
#define YYNSTATES  118

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   285

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     8,     9,    13,    16,    20,    24,
      26,    30,    32,    34,    40,    43,    45,    46,    48,    50,
      55,    60,    64,    68,    70,    73,    78,    81,    82,    85,
      87,    91,    97,   105,   111,   114,   115,   119,   121,   125,
     127,   131,   135,   139,   143,   147,   151,   155,   159,   163,
     167,   170,   173,   178,   182,   187,   191,   193,   195,   197,
     201,   203,   206,   209
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      32,     0,    -1,    33,    -1,    34,    33,    -1,    -1,    36,
      35,     8,    -1,    36,     8,    -1,    36,    41,     8,    -1,
      36,    41,    44,    -1,    40,    -1,    40,     9,    35,    -1,
      16,    -1,    37,    -1,    23,    38,    21,    47,    22,    -1,
      23,    39,    -1,    28,    -1,    -1,    28,    -1,    28,    -1,
      40,    19,     3,    20,    -1,    28,    17,    42,    18,    -1,
      28,    17,    18,    -1,    43,     9,    42,    -1,    43,    -1,
      36,    40,    -1,    21,    47,    45,    22,    -1,    46,    45,
      -1,    -1,    51,     8,    -1,    44,    -1,    24,    51,     8,
      -1,    25,    17,    51,    18,    46,    -1,    25,    17,    51,
      18,    46,    26,    46,    -1,    27,    17,    51,    18,    46,
      -1,    48,    47,    -1,    -1,    36,    49,     8,    -1,    50,
      -1,    50,     9,    49,    -1,    40,    -1,    40,    11,    51,
      -1,    51,    11,    51,    -1,    51,    12,    51,    -1,    51,
      13,    51,    -1,    51,    10,    51,    -1,    51,     4,    51,
      -1,    51,     5,    51,    -1,    51,     6,    51,    -1,    51,
       7,    51,    -1,    17,    51,    18,    -1,     5,    51,    -1,
      14,    51,    -1,    28,    17,    52,    18,    -1,    28,    17,
      18,    -1,    51,    19,    51,    20,    -1,    51,    15,    28,
      -1,    28,    -1,     3,    -1,    29,    -1,    51,     9,    52,
      -1,    51,    -1,     1,     8,    -1,     1,    22,    -1,     1,
      18,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    96,    96,   103,   111,   119,   131,   140,   155,   168,
     176,   192,   212,   222,   243,   256,   266,   272,   285,   297,
     336,   353,   370,   382,   390,   404,   420,   428,   434,   443,
     452,   467,   486,   509,   530,   539,   547,   562,   569,   582,
     590,   605,   617,   628,   640,   651,   663,   675,   687,   699,
     713,   724,   735,   752,   768,   783,   797,   807,   817,   828,
     840,   850,   852,   854
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INT", "PLUS", "MINUS", "STAR", "DIV",
  "SEMI", "COMMA", "RELOP", "ASSIGNOP", "AND", "OR", "NOT", "DOT", "TYPE",
  "LP", "RP", "LB", "RB", "LC", "RC", "STRUCT", "RETURN", "IF", "ELSE",
  "WHILE", "ID", "FLOAT", "LOWER_THAN_ELSE", "$accept", "Program",
  "ExtDefList", "ExtDef", "ExtDecList", "Specifier", "StructSpecifier",
  "OptTag", "Tag", "VarDec", "FunDec", "VarList", "ParamDec", "CompSt",
  "StmtList", "Stmt", "DefList", "Def", "DecList", "Dec", "Exp", "Args", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    31,    32,    33,    33,    34,    34,    34,    34,    35,
      35,    36,    36,    37,    37,    38,    38,    39,    40,    40,
      41,    41,    42,    42,    43,    44,    45,    45,    46,    46,
      46,    46,    46,    46,    47,    47,    48,    49,    49,    50,
      50,    51,    51,    51,    51,    51,    51,    51,    51,    51,
      51,    51,    51,    51,    51,    51,    51,    51,    51,    52,
      52,    46,    44,    51
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     0,     3,     2,     3,     3,     1,
       3,     1,     1,     5,     2,     1,     0,     1,     1,     4,
       4,     3,     3,     1,     2,     4,     2,     0,     2,     1,
       3,     5,     7,     5,     2,     0,     3,     1,     3,     1,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       2,     2,     4,     3,     4,     3,     1,     1,     1,     3,
       1,     2,     2,     2
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,    11,    16,     0,     2,     4,     0,    12,    17,     0,
      14,     1,     3,     6,    18,     0,     9,     0,    35,     0,
       5,     0,     0,     0,     7,    35,     8,     0,     0,    35,
      21,     0,     0,    23,    18,    10,     0,    62,     0,    39,
       0,    37,    13,    34,    24,    20,     0,    19,     0,    57,
       0,     0,     0,     0,     0,     0,    56,    58,    29,     0,
       0,     0,     0,    36,     0,    22,    61,    63,     0,    50,
      51,     0,     0,     0,     0,     0,    25,    26,     0,     0,
       0,     0,    28,     0,     0,     0,     0,     0,     0,    40,
      38,    49,    30,     0,     0,    53,    60,     0,    45,    46,
      47,    48,    44,    41,    42,    43,    55,     0,     0,     0,
       0,    52,    54,    31,    33,    59,     0,    32
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     3,     4,     5,    15,    27,     7,     9,    10,    16,
      17,    32,    33,    58,    59,    60,    28,    29,    40,    41,
      61,    97
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -69
static const yytype_int16 yypact[] =
{
      -1,   -69,   -18,    20,   -69,    -1,     9,   -69,     0,    11,
     -69,   -69,   -69,   -69,    27,    47,    -3,    18,    -1,    57,
     -69,    40,    43,    56,   -69,    -1,   -69,    40,    60,    -1,
     -69,    40,    65,    75,   -69,   -69,    66,   -69,    42,    38,
      79,    80,   -69,   -69,    72,   -69,    -1,   -69,    -4,   -69,
     105,   105,   105,   105,    84,    85,    86,   -69,   -69,    87,
      42,   142,   105,   -69,    40,   -69,   -69,   -69,    89,   240,
      -8,   158,   174,   105,   105,    76,   -69,   -69,   105,   105,
     105,   105,   -69,   105,   105,   105,   105,    69,   105,   238,
     -69,   -69,   -69,   190,   206,   -69,   222,    93,   240,   240,
      -8,    -8,   108,   238,    46,    46,   -69,   125,    71,    71,
     105,   -69,   -69,    90,   -69,   -69,    71,   -69
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -69,   -69,   112,   -69,    97,     8,   -69,   -69,   -69,   -22,
     -69,    78,   -69,   109,    68,   -68,    33,   -69,    61,   -69,
     -50,    29
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -28
static const yytype_int8 yytable[] =
{
      69,    70,    71,    72,    66,    39,    21,    87,     6,    44,
       8,    88,    89,     6,    67,     1,    22,    13,    37,    23,
      11,   -15,     2,    93,    94,    96,    24,    31,    98,    99,
     100,   101,    18,   102,   103,   104,   105,    14,   107,    25,
     113,   114,    39,    48,    19,    49,    36,    50,   117,    62,
      78,    79,    80,    81,    31,    20,    51,    22,    38,    52,
      96,    87,    43,    25,   -27,    88,    53,    54,    34,    55,
      56,    57,    48,     1,    49,    30,    50,    68,    37,    49,
       2,    50,    42,    45,    46,    51,    47,    63,    52,    64,
      51,    22,    25,    52,    95,    53,    54,   106,    55,    56,
      57,    73,    74,    75,    56,    57,    68,    67,    49,    76,
      50,   111,    78,    79,    80,    81,   116,    12,    35,    51,
      85,    86,    52,    87,    65,    90,    26,    88,    77,    78,
      79,    80,    81,    56,    57,    83,    84,    85,    86,   115,
      87,     0,     0,     0,    88,   112,    78,    79,    80,    81,
      82,     0,    83,    84,    85,    86,     0,    87,     0,     0,
       0,    88,    78,    79,    80,    81,     0,     0,    83,    84,
      85,    86,     0,    87,     0,     0,    91,    88,    78,    79,
      80,    81,    92,     0,    83,    84,    85,    86,     0,    87,
       0,     0,     0,    88,    78,    79,    80,    81,     0,     0,
      83,    84,    85,    86,     0,    87,     0,     0,   108,    88,
      78,    79,    80,    81,     0,     0,    83,    84,    85,    86,
       0,    87,     0,     0,   109,    88,    78,    79,    80,    81,
       0,   110,    83,    84,    85,    86,     0,    87,     0,     0,
       0,    88,    78,    79,    80,    81,    80,    81,    83,    84,
      85,    86,     0,    87,     0,    87,     0,    88,     0,    88
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-69))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int8 yycheck[] =
{
      50,    51,    52,    53,     8,    27,     9,    15,     0,    31,
      28,    19,    62,     5,    18,    16,    19,     8,    22,     1,
       0,    21,    23,    73,    74,    75,     8,    19,    78,    79,
      80,    81,    21,    83,    84,    85,    86,    28,    88,    21,
     108,   109,    64,     1,    17,     3,     3,     5,   116,    11,
       4,     5,     6,     7,    46,     8,    14,    19,    25,    17,
     110,    15,    29,    21,    22,    19,    24,    25,    28,    27,
      28,    29,     1,    16,     3,    18,     5,     1,    22,     3,
      23,     5,    22,    18,     9,    14,    20,     8,    17,     9,
      14,    19,    21,    17,    18,    24,    25,    28,    27,    28,
      29,    17,    17,    17,    28,    29,     1,    18,     3,    22,
       5,    18,     4,     5,     6,     7,    26,     5,    21,    14,
      12,    13,    17,    15,    46,    64,    17,    19,    60,     4,
       5,     6,     7,    28,    29,    10,    11,    12,    13,   110,
      15,    -1,    -1,    -1,    19,    20,     4,     5,     6,     7,
       8,    -1,    10,    11,    12,    13,    -1,    15,    -1,    -1,
      -1,    19,     4,     5,     6,     7,    -1,    -1,    10,    11,
      12,    13,    -1,    15,    -1,    -1,    18,    19,     4,     5,
       6,     7,     8,    -1,    10,    11,    12,    13,    -1,    15,
      -1,    -1,    -1,    19,     4,     5,     6,     7,    -1,    -1,
      10,    11,    12,    13,    -1,    15,    -1,    -1,    18,    19,
       4,     5,     6,     7,    -1,    -1,    10,    11,    12,    13,
      -1,    15,    -1,    -1,    18,    19,     4,     5,     6,     7,
      -1,     9,    10,    11,    12,    13,    -1,    15,    -1,    -1,
      -1,    19,     4,     5,     6,     7,     6,     7,    10,    11,
      12,    13,    -1,    15,    -1,    15,    -1,    19,    -1,    19
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    16,    23,    32,    33,    34,    36,    37,    28,    38,
      39,     0,    33,     8,    28,    35,    40,    41,    21,    17,
       8,     9,    19,     1,     8,    21,    44,    36,    47,    48,
      18,    36,    42,    43,    28,    35,     3,    22,    47,    40,
      49,    50,    22,    47,    40,    18,     9,    20,     1,     3,
       5,    14,    17,    24,    25,    27,    28,    29,    44,    45,
      46,    51,    11,     8,     9,    42,     8,    18,     1,    51,
      51,    51,    51,    17,    17,    17,    22,    45,     4,     5,
       6,     7,     8,    10,    11,    12,    13,    15,    19,    51,
      49,    18,     8,    51,    51,    18,    51,    52,    51,    51,
      51,    51,    51,    51,    51,    51,    28,    51,    18,    18,
       9,    18,    20,    46,    46,    52,    26,    46
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (yylocationp);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yylsp, yyrule)
    YYSTYPE *yyvsp;
    YYLTYPE *yylsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, yylsp, Rule); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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
  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  YYSIZE_T yysize1;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = 0;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
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
                yysize1 = yysize + yytnamerr (0, yytname[yyx]);
                if (! (yysize <= yysize1
                       && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                  return 2;
                yysize = yysize1;
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

  yysize1 = yysize + yystrlen (yyformat);
  if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
    return 2;
  yysize = yysize1;

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

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yylocationp)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Location data for the lookahead symbol.  */
YYLTYPE yylloc;

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.
       `yyls': related to locations.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;
  yylsp = yyls;

#if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  /* Initialize the default location before parsing starts.  */
  yylloc.first_line   = yylloc.last_line   = 1;
  yylloc.first_column = yylloc.last_column = 1;
#endif

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
	YYLTYPE *yyls1 = yyls;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);

	yyls = yyls1;
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
	YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

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
      yychar = YYLEX;
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
  *++yyvsp = yylval;
  *++yylsp = yylloc;
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
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1806 of yacc.c  */
#line 96 "syntax.y"
    {
			struct TreeNode* Program = create("Program", (yyloc).first_line, yytext,0,-1);
			
			Program->children = treeStack[treeStackTop];
			treeRoot = Program ;
		}
    break;

  case 3:

/* Line 1806 of yacc.c  */
#line 103 "syntax.y"
    {
			struct TreeNode* ExtDefList = create("ExtDefList", (yyloc).first_line, yytext,0,-1);
			
			ExtDefList->children = treeStack[treeStackTop];
			treeStack[treeStackTop]->neighbours = treeStack[treeStackTop-1];
			treeStackTop = treeStackTop -1;
			treeStack[treeStackTop] = ExtDefList;
		}
    break;

  case 4:

/* Line 1806 of yacc.c  */
#line 111 "syntax.y"
    {
			struct TreeNode* ExtDefList = create("ExtDefList", (yyloc).first_line, yytext,-1,-1);
			
			
			treeStackTop = treeStackTop + 1;
			treeStack[treeStackTop] = ExtDefList;
		}
    break;

  case 5:

/* Line 1806 of yacc.c  */
#line 119 "syntax.y"
    {
			struct TreeNode* ExtDef = create("ExtDef", (yyloc).first_line, yytext,0,-1);
			
			struct TreeNode* SEMI = create("SEMI", (yyloc).first_line, yytext,0,1);
			
			
			ExtDef->children = SEMI;
			SEMI->neighbours = treeStack[treeStackTop];
			treeStack[treeStackTop]->neighbours = treeStack[treeStackTop-1];
			treeStackTop = treeStackTop -1;
			treeStack[treeStackTop] = ExtDef;
		}
    break;

  case 6:

/* Line 1806 of yacc.c  */
#line 131 "syntax.y"
    {
			struct TreeNode* ExtDef = create("ExtDef", (yyloc).first_line, yytext,0,-1);
			
			struct TreeNode* SEMI = create("SEMI", (yyloc).first_line, yytext,0,-1);
			
			ExtDef->children = SEMI;
			SEMI->neighbours = treeStack[treeStackTop];
			treeStack[treeStackTop] = ExtDef;
		}
    break;

  case 7:

/* Line 1806 of yacc.c  */
#line 140 "syntax.y"
    {
		
			struct TreeNode* ExtDef = create("ExtDef", (yyloc).first_line, yytext,0,-1);
			struct TreeNode* SEMI = create("SEMI", (yyloc).first_line, yytext,0,-1);
			
			treeStack[treeStackTop]->srcop = 5;
			
			ExtDef->children = SEMI;
			SEMI->neighbours = treeStack[treeStackTop];
			treeStack[treeStackTop]->neighbours = treeStack[treeStackTop-1];
			
			treeStackTop = treeStackTop - 1;
			treeStack[treeStackTop] = ExtDef;
			
		}
    break;

  case 8:

/* Line 1806 of yacc.c  */
#line 155 "syntax.y"
    {
			struct TreeNode* ExtDef = create("ExtDef", (yyloc).first_line, yytext,0,-1);
			
			treeStack[treeStackTop-1]->srcop = 4;
			
			ExtDef->children = treeStack[treeStackTop];
			treeStack[treeStackTop]->neighbours = treeStack[treeStackTop-1];
			treeStack[treeStackTop-1]->neighbours = treeStack[treeStackTop-2];
			
			treeStackTop = treeStackTop -2;
			treeStack[treeStackTop] = ExtDef;
		}
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 168 "syntax.y"
    {
			struct TreeNode* ExtDecList = create("ExtDecList", (yyloc).first_line, yytext,0,-1);
			
			treeStack[treeStackTop]->srcop = 0;
			
			ExtDecList->children = treeStack[treeStackTop];
			treeStack[treeStackTop] = ExtDecList;
		}
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 176 "syntax.y"
    {
			struct TreeNode* ExtDecList = create("ExtDecList", (yyloc).first_line, yytext,0,-1);
			
			struct TreeNode* COMMA = create("COMMA", (yyloc).first_line, yytext,0,1);
			
			treeStack[treeStackTop-1]->srcop = 0;
			
			ExtDecList->children = treeStack[treeStackTop];
			treeStack[treeStackTop]->neighbours = COMMA;
			COMMA->neighbours = treeStack[treeStackTop-1];
			treeStackTop = treeStackTop - 1;
			treeStack[treeStackTop] = ExtDecList;
		}
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 192 "syntax.y"
    {
			struct TreeNode *TYPE1 = create("TYPE",(yyloc).first_line,(yyvsp[(1) - (1)].type_str),0,1);
			
			
			struct TreeNode *Specifier = create("Specifier",(yyloc).first_line,yytext,0,-1);
			Specifier->syn_type = (Type)malloc(sizeof(struct Type_));
			//获得Specifier的Type

			Specifier->syn_type->kind = 0;
			if(strcmp("int", (yyvsp[(1) - (1)].type_str)) == 0){
				Specifier->syn_type->u.basic = 0;	// 0 表示int
				}
			else if(strcmp("float", (yyvsp[(1) - (1)].type_str)) == 0){     
				Specifier->syn_type->u.basic = 1;       //1 表示float
				}
			
			
			Specifier->children  = TYPE1;
			treeStack[++treeStackTop] = Specifier;
		}
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 212 "syntax.y"
    {
			struct TreeNode *Specifier = create("Specifier",(yyloc).first_line,yytext,0,-1);
			Specifier->syn_type = (Type)malloc(sizeof(struct Type_));
			Specifier->syn_type->kind = treeStack[treeStackTop]->syn_type->kind;
			
			Specifier->children = treeStack[treeStackTop];
			treeStack[treeStackTop] = Specifier;
				
		}
    break;

  case 13:

/* Line 1806 of yacc.c  */
#line 222 "syntax.y"
    {
			struct TreeNode *LC = create("LC",(yyloc).first_line,yytext,0,1);
			struct TreeNode *RC = create("RC",(yyloc).first_line,yytext,0,1);
			struct TreeNode *Struct = create("Struct",(yyloc).first_line,yytext,0,1);
			struct TreeNode *StructSpecifier = create("StructSpecifier",(yyloc).first_line,yytext,0,-1);
			
			treeStack[treeStackTop]->srcop = 2;
			
		
			
			StructSpecifier->syn_type = (Type)malloc(sizeof(struct Type_));
			StructSpecifier->syn_type->kind = 2;
	
			StructSpecifier->children = RC;
			RC->neighbours = treeStack[treeStackTop];
			treeStack[treeStackTop]->neighbours = LC;
			LC->neighbours = treeStack[treeStackTop-1];
			treeStack[treeStackTop-1]->neighbours = Struct;
			treeStackTop -= 1;
			treeStack[treeStackTop] = StructSpecifier;
			}
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 243 "syntax.y"
    {
			struct TreeNode *StructSpecifier = create("StructSpecifier",(yyloc).first_line,yytext,0,-1);
			struct TreeNode *Struct = create("Struct",(yyloc).first_line,yytext,0,1);
			
			StructSpecifier->syn_type = (Type)malloc(sizeof(struct Type_));
			StructSpecifier->syn_type->kind = 2;
			
			StructSpecifier->children = treeStack[treeStackTop];
			treeStack[treeStackTop]->neighbours = Struct;
			treeStack[treeStackTop] = StructSpecifier;
		}
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 256 "syntax.y"
    {
		struct TreeNode *ID = create("ID",(yyloc).first_line,(yyvsp[(1) - (1)].type_str),0,1);
		
		struct TreeNode *OptTag = create("OptTag",(yyloc).first_line,yytext,0,-1);
		
		ID->srcop = 1;
		
		OptTag->children = ID;
		treeStack[++treeStackTop] = OptTag; 
	}
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 266 "syntax.y"
    {
			struct TreeNode *OptTag = create("OptTag",(yyloc).first_line,yytext,-1,-1);
			
			treeStack[++treeStackTop] = OptTag;
			}
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 272 "syntax.y"
    {
		struct TreeNode *ID = create("ID",(yyloc).first_line,(yyvsp[(1) - (1)].type_str),0,1);
		
		struct TreeNode *Tag = create("Tag",(yyloc).first_line,yytext,0,-1);
		ID->srcop = 100;

		
		Tag->children = ID;
		treeStack[++treeStackTop] = Tag;
	}
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 285 "syntax.y"
    {
		struct TreeNode *ID = create("ID",(yyloc).first_line,(yyvsp[(1) - (1)].type_str),0,1);
		
		struct TreeNode *VarDec = create("VarDec",(yyloc).first_line,yytext,0,-1);
		
		ID->syn_type = (Type)malloc(sizeof(struct Type_));
		ID->syn_type->kind = 0;
		VarDec->syn_type = ID->syn_type;
		
		VarDec->children = ID;
		treeStack[++treeStackTop] = VarDec;
	}
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 297 "syntax.y"
    {
		struct TreeNode *LB = create("LB",(yyloc).first_line,yytext,0,1);
		
		struct TreeNode *RB = create("RB",(yyloc).first_line,yytext,0,1);
		
		struct TreeNode *INT = create("INT",(yyloc).first_line,yytext,(yyvsp[(3) - (4)].type_int),1);
		
		struct TreeNode *VarDec = create("VarDec",(yyloc).first_line,yytext,0,-1);
		
		Type h = treeStack[treeStackTop]->syn_type;
		Type newP1; 
		Type newP2 = NULL;
		if (h->kind == 1){
			while (h->u.array.elem->kind ==1)
				h = h->u.array.elem;
			newP1 = (Type)malloc(sizeof(struct Type_));
			newP1->kind = 1;
			newP1->u.array.size = (yyvsp[(3) - (4)].type_int);
			newP1->u.array.elem = h->u.array.elem;
			h->u.array.elem = newP1;
			}
		
		else {
			newP1 = (Type)malloc(sizeof(struct Type_));
			newP1->kind = 0;
			treeStack[treeStackTop]->syn_type->kind =1;
			treeStack[treeStackTop]->syn_type->u.array.size = (yyvsp[(3) - (4)].type_int);
			treeStack[treeStackTop]->syn_type->u.array.elem = newP1;
			}
		VarDec->syn_type = treeStack[treeStackTop]->syn_type;
		
			
		VarDec->children = RB;
		RB->neighbours = INT;
		INT->neighbours = LB;
		LB->neighbours = treeStack[treeStackTop];
		treeStack[treeStackTop] = VarDec;
	}
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 336 "syntax.y"
    {
		struct TreeNode *RP = create("RP",(yyloc).first_line,yytext,0,1);
		
		struct TreeNode *LP = create("LP",(yyloc).first_line,yytext,0,1);
		
		struct TreeNode *ID = create("ID",(yyloc).first_line,(yyvsp[(1) - (4)].type_str),0,1);
		
		struct TreeNode *FunDec = create("FunDec",(yyloc).first_line,yytext,0,-1);
		
		
		FunDec->children = RP;
		RP->neighbours = treeStack[treeStackTop];
		treeStack[treeStackTop]->neighbours = LP;
		LP->neighbours  = ID;
		treeStack[treeStackTop] = FunDec;
		
	}
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 353 "syntax.y"
    {
		struct TreeNode *RP = create("RP",(yyloc).first_line,yytext,0,1);
		
		struct TreeNode *LP = create("LP",(yyloc).first_line,yytext,0,1);
		
		struct TreeNode *ID = create("ID",(yyloc).first_line,(yyvsp[(1) - (3)].type_str),0,1);
		
		struct TreeNode *FunDec = create("FunDec",(yyloc).first_line,yytext,0,-1);
		

		
		FunDec->children = RP;
		RP->neighbours =LP;
		LP->neighbours  = ID;
		treeStack[++treeStackTop] = FunDec;
	}
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 370 "syntax.y"
    {
		struct TreeNode *COMMA =  create("COMMA",(yyloc).first_line,yytext,0,1);
		
		struct TreeNode *VarList =  create("VarList",(yyloc).first_line,yytext,0,-1);
		
		
		VarList->children = treeStack[treeStackTop];
		treeStack[treeStackTop]->neighbours = COMMA;
		COMMA->neighbours = treeStack[treeStackTop-1];
		treeStack[--treeStackTop] = VarList;
		
	}
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 382 "syntax.y"
    {
		struct TreeNode *VarList =  create("VarList",(yyloc).first_line,yytext,0,-1);
		
		
		VarList->children = treeStack[treeStackTop];
		treeStack[treeStackTop] = VarList;
	}
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 390 "syntax.y"
    {
		struct TreeNode *ParamDec =  create("ParamDec",(yyloc).first_line,yytext,0,-1);
		
		
		treeStack[treeStackTop]->srcop = 3;
		
		
		ParamDec->children = treeStack[treeStackTop];
		treeStack[treeStackTop]->neighbours = treeStack[treeStackTop-1];
		treeStack[--treeStackTop] = ParamDec;
	}
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 404 "syntax.y"
    {
		struct TreeNode *RC =  create("RC",(yyloc).first_line,yytext,0,1);
		
		struct TreeNode *LC =  create("LC",(yyloc).first_line,yytext,0,1);
		
		struct TreeNode *CompSt=  create("CompSt",(yyloc).first_line,yytext,0,-1);
		
		treeStack[treeStackTop-1]->srcop = 0;
		
		CompSt->children = RC;
		RC->neighbours = treeStack[treeStackTop];
		treeStack[treeStackTop]->neighbours = treeStack[treeStackTop-1];
		treeStack[treeStackTop-1]->neighbours = LC;
		treeStack[--treeStackTop] = CompSt;
	}
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 420 "syntax.y"
    {
		struct TreeNode *StmtList =  create("StmtList",(yyloc).first_line,yytext,0,-1);
		
		
		StmtList->children = treeStack[treeStackTop];
		treeStack[treeStackTop]->neighbours = treeStack[treeStackTop-1];
		treeStack[--treeStackTop] = StmtList;
	}
    break;

  case 27:

/* Line 1806 of yacc.c  */
#line 428 "syntax.y"
    {
		struct TreeNode *StmtList =  create("StmtList",(yyloc).first_line,yytext,-1,-1);
		
		treeStack[++treeStackTop] = StmtList;
	}
    break;

  case 28:

/* Line 1806 of yacc.c  */
#line 434 "syntax.y"
    {
		struct TreeNode *SEMI =  create("SEMI",(yyloc).first_line,yytext,0,1);
		
		struct TreeNode *Stmt =  create("Stmt",(yyloc).first_line,yytext,0,-1);
		
		Stmt->children = SEMI;
		SEMI->neighbours = treeStack[treeStackTop];
		treeStack[treeStackTop] = Stmt;
	}
    break;

  case 29:

/* Line 1806 of yacc.c  */
#line 443 "syntax.y"
    {
		struct TreeNode *Stmt =  create("Stmt",(yyloc).first_line,yytext,0,-1);
		
		
		
		Stmt->children = treeStack[treeStackTop];
		treeStack[treeStackTop] = Stmt;
	}
    break;

  case 30:

/* Line 1806 of yacc.c  */
#line 452 "syntax.y"
    {
		struct TreeNode *SEMI =  create("SEMI",(yyloc).first_line,yytext,0,1);
		
		struct TreeNode *Stmt =  create("Stmt",(yyloc).first_line,yytext,0,-1);
		
		struct TreeNode *RETURN = create("RETURN",(yyloc).first_line,yytext,0,1);
		
		
		
		
		Stmt->children = SEMI;
		SEMI->neighbours =treeStack[treeStackTop];
		treeStack[treeStackTop]->neighbours = RETURN;
		treeStack[treeStackTop] = Stmt;
	}
    break;

  case 31:

/* Line 1806 of yacc.c  */
#line 467 "syntax.y"
    {
		struct TreeNode *RP =  create("RP",(yyloc).first_line,yytext,0,1);
		
		struct TreeNode *Stmt =  create("Stmt",(yyloc).first_line,yytext,0,-1);
		
		struct TreeNode *LP = create("LP",(yyloc).first_line,yytext,0,1);
		
		struct TreeNode *IF =  create("IF",(yyloc).first_line,yytext,0,1);
		
		
		
		Stmt->children = treeStack[treeStackTop];
		treeStack[treeStackTop]->neighbours = RP;
		RP->neighbours = treeStack[treeStackTop-1];
		treeStack[treeStackTop-1]->neighbours = LP;
		LP->neighbours = IF;
		treeStack[--treeStackTop] = Stmt;
		
	}
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 486 "syntax.y"
    {
		struct TreeNode *RP = create("RP",(yyloc).first_line,yytext,0,1);
		
		struct TreeNode *Stmt = create("Stmt",(yyloc).first_line,yytext,0,-1);
		
		struct TreeNode *LP = create("LP",(yyloc).first_line,yytext,0,1);
		
		struct TreeNode *IF = create("IF",(yyloc).first_line,yytext,0,1);
		
		struct TreeNode *ELSE = create("ELSE",(yyloc).first_line,yytext,0,1);
		
		
		
		Stmt->children = treeStack[treeStackTop];
		treeStack[treeStackTop]->neighbours = ELSE;
		ELSE->neighbours = treeStack[treeStackTop-1];
		treeStack[treeStackTop-1]->neighbours = RP;
		RP->neighbours = treeStack[treeStackTop-2];
		treeStack[treeStackTop-2]->neighbours = LP;
		LP->neighbours = IF;
		treeStackTop -= 2;
		treeStack[treeStackTop] = Stmt;
	}
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 509 "syntax.y"
    {
		struct TreeNode *RP = create("RP",(yyloc).first_line,yytext,0,1);
		
		struct TreeNode *Stmt = create("Stmt",(yyloc).first_line,yytext,0,-1);
		
		struct TreeNode *LP = create("LP",(yyloc).first_line,yytext,0,1);
		
		struct TreeNode *WHILE = create("WHILE",(yyloc).first_line,yytext,0,1);
		
		
		
		Stmt->children = treeStack[treeStackTop];
		treeStack[treeStackTop]->neighbours = RP;
		RP->neighbours = treeStack[treeStackTop-1];
		treeStack[treeStackTop-1]->neighbours = LP;
		LP->neighbours = WHILE;
		treeStack[--treeStackTop] = Stmt;
	}
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 530 "syntax.y"
    {
		struct TreeNode *DefList = create("DefList",(yyloc).first_line,yytext,0,-1);
		
		
		
		DefList->children = treeStack[treeStackTop];
		treeStack[treeStackTop]->neighbours = treeStack[treeStackTop-1];
		treeStack[--treeStackTop] = DefList;
	}
    break;

  case 35:

/* Line 1806 of yacc.c  */
#line 539 "syntax.y"
    {
		struct TreeNode *DefList = create("DefList",(yyloc).first_line,yytext,-1,-1);
		
		
		
		treeStack[++treeStackTop] = DefList;
	}
    break;

  case 36:

/* Line 1806 of yacc.c  */
#line 547 "syntax.y"
    {
		struct TreeNode *SEMI = create("SEMI",(yyloc).first_line,yytext,0,1);
		
		struct TreeNode *Def = create("Def",(yyloc).first_line,yytext,0,-1);
		
		//用Specifier的syn_type,遍历DecList，并设置值
		
	
		
		Def->children = SEMI;
		SEMI->neighbours = treeStack[treeStackTop];
		treeStack[treeStackTop]->neighbours = treeStack[treeStackTop-1];
		treeStack[--treeStackTop] = Def;
	}
    break;

  case 37:

/* Line 1806 of yacc.c  */
#line 562 "syntax.y"
    {
		struct TreeNode *DecList = create("DecList",(yyloc).first_line,yytext,0,-1);
		
		
		DecList->children = treeStack[treeStackTop];
		treeStack[treeStackTop] = DecList;
	}
    break;

  case 38:

/* Line 1806 of yacc.c  */
#line 569 "syntax.y"
    {
		struct TreeNode *DecList = create("DecList",(yyloc).first_line,yytext,0,-1);
		
		struct TreeNode *COMMA = create("COMMA",(yyloc).first_line,yytext,0,1);
		
		
		
		DecList->children = treeStack[treeStackTop];
		treeStack[treeStackTop]->neighbours =COMMA;
		COMMA->neighbours = treeStack[treeStackTop-1];
		treeStack[--treeStackTop] = DecList;
	}
    break;

  case 39:

/* Line 1806 of yacc.c  */
#line 582 "syntax.y"
    {
		struct TreeNode *Dec = create("Dec",(yyloc).first_line,yytext,0,-1);
		
		
		
		Dec->children = treeStack[treeStackTop];
		treeStack[treeStackTop] = Dec;
	}
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 590 "syntax.y"
    {
		struct TreeNode *Dec = create("Dec",(yyloc).first_line,yytext,0,-1);
		
		struct TreeNode *ASSIGNOP = create("ASSIGNOP",(yyloc).first_line,yytext,0,1);
		
		
		
		Dec->children = treeStack[treeStackTop];
		treeStack[treeStackTop]->neighbours = ASSIGNOP;
		ASSIGNOP->neighbours = treeStack[treeStackTop-1];
		treeStack[--treeStackTop] =Dec;
	}
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 605 "syntax.y"
    {
		struct TreeNode *ASSIGNOP = create("ASSIGNOP",(yyloc).first_line,yytext,0,1);
		
		struct TreeNode *Exp = create("Exp",(yyloc).first_line,yytext,0,-1);
		

		
		Exp->children = treeStack[treeStackTop];
		treeStack[treeStackTop]->neighbours = ASSIGNOP;
		ASSIGNOP->neighbours = treeStack[treeStackTop-1];
		treeStack[--treeStackTop] = Exp;
	}
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 617 "syntax.y"
    {
		struct TreeNode *AND = create("AND",(yyloc).first_line,yytext,0,1);
		
		struct TreeNode *Exp = create("Exp",(yyloc).first_line,yytext,0,-1);
		
		
		Exp->children = treeStack[treeStackTop];
		treeStack[treeStackTop]->neighbours = AND;
		AND->neighbours = treeStack[treeStackTop-1];
		treeStack[--treeStackTop] = Exp;
	}
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 628 "syntax.y"
    {
		struct TreeNode *OR = create("OR",(yyloc).first_line,yytext,0,1);
		
		struct TreeNode *Exp = create("Exp",(yyloc).first_line,yytext,0,-1);
		
		
		
		Exp->children = treeStack[treeStackTop];
		treeStack[treeStackTop]->neighbours = OR;
		OR->neighbours = treeStack[treeStackTop-1];
		treeStack[--treeStackTop] = Exp;
	}
    break;

  case 44:

/* Line 1806 of yacc.c  */
#line 640 "syntax.y"
    {
		struct TreeNode *RELOP = create("RELOP",(yyloc).first_line,(yyvsp[(2) - (3)].type_str),0,1);
		
		struct TreeNode *Exp = create("Exp",(yyloc).first_line,yytext,0,-1);
		
		
		Exp->children = treeStack[treeStackTop];
		treeStack[treeStackTop]->neighbours = RELOP;
		RELOP->neighbours = treeStack[treeStackTop-1];
		treeStack[--treeStackTop] = Exp;
	}
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 651 "syntax.y"
    {
		struct TreeNode *PLUS = create("PLUS",(yyloc).first_line,yytext,0,1);
		
		struct TreeNode *Exp = create("Exp",(yyloc).first_line,yytext,0,-1);
		
		
		
		Exp->children = treeStack[treeStackTop];
		treeStack[treeStackTop]->neighbours = PLUS;
		PLUS->neighbours = treeStack[treeStackTop-1];
		treeStack[--treeStackTop] = Exp;
	}
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 663 "syntax.y"
    {
		struct TreeNode *MINUS = create("MINUS",(yyloc).first_line,yytext,0,1);
		
		struct TreeNode *Exp = create("Exp",(yyloc).first_line,yytext,0,-1);
		
	
		
		Exp->children = treeStack[treeStackTop];
		treeStack[treeStackTop]->neighbours = MINUS;
		MINUS->neighbours = treeStack[treeStackTop-1];
		treeStack[--treeStackTop] = Exp;
	}
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 675 "syntax.y"
    {
		struct TreeNode *STAR = create("STAR",(yyloc).first_line,yytext,0,1);
		
		struct TreeNode *Exp = create("Exp",(yyloc).first_line,yytext,0,-1);
		
		
		
		Exp->children = treeStack[treeStackTop];
		treeStack[treeStackTop]->neighbours = STAR;
		STAR->neighbours = treeStack[treeStackTop-1];
		treeStack[--treeStackTop] = Exp;
	}
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 687 "syntax.y"
    {
		struct TreeNode *DIV = create("DIV",(yyloc).first_line,yytext,0,1);
		
		struct TreeNode *Exp = create("Exp",(yyloc).first_line,yytext,0,-1);
		
		
		
		Exp->children = treeStack[treeStackTop];
		treeStack[treeStackTop]->neighbours = DIV;
		DIV->neighbours = treeStack[treeStackTop-1];
		treeStack[--treeStackTop] = Exp;
	}
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 699 "syntax.y"
    {
		struct TreeNode *LP = create("LP",(yyloc).first_line,yytext,0,1);
		
		struct TreeNode *RP = create("RP",(yyloc).first_line,yytext,0,1);
		
		struct TreeNode *Exp = create("Exp",(yyloc).first_line,yytext,0,-1);
		
		
		
		Exp->children = RP;
		RP->neighbours = treeStack[treeStackTop];
		treeStack[treeStackTop]->neighbours = LP;
		treeStack[treeStackTop] = Exp;
	}
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 713 "syntax.y"
    {
		struct TreeNode *MINUS = create("MINUS",(yyloc).first_line,yytext,0,1);
		
		struct TreeNode *Exp = create("Exp",(yyloc).first_line,yytext,0,-1);
		
		
		
		Exp->children = treeStack[treeStackTop];
		treeStack[treeStackTop]->neighbours =MINUS;
		treeStack[treeStackTop] = Exp;
	}
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 724 "syntax.y"
    {
		struct TreeNode *NOT = create("NOT",(yyloc).first_line,yytext,0,1);
		
		struct TreeNode *Exp = create("Exp",(yyloc).first_line,yytext,0,-1);
		
		
		
		Exp->children = treeStack[treeStackTop];
		treeStack[treeStackTop]->neighbours =NOT;
		treeStack[treeStackTop] = Exp;
	}
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 735 "syntax.y"
    {
		struct TreeNode *LP = create("LP",(yyloc).first_line,yytext,0,1);
		
		struct TreeNode *RP = create("RP",(yyloc).first_line,yytext,0,1);
		
		struct TreeNode *Exp = create("Exp",(yyloc).first_line,yytext,0,-1);
		
		struct TreeNode *ID = create("ID",(yyloc).first_line,(yyvsp[(1) - (4)].type_str),0,1);
		
		ID->srcop = 7;
		
		Exp->children = RP;
		RP->neighbours = treeStack[treeStackTop];
		treeStack[treeStackTop]->neighbours = LP;
		LP->neighbours = ID;
		treeStack[treeStackTop] = Exp;
	}
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 752 "syntax.y"
    {
		struct TreeNode *LP = create("LP",(yyloc).first_line,yytext,0,1);
		
		struct TreeNode *RP = create("RP",(yyloc).first_line,yytext,0,1);
		
		struct TreeNode *Exp = create("Exp",(yyloc).first_line,yytext,0,-1);
		
		struct TreeNode *ID = create("ID",(yyloc).first_line,(yyvsp[(1) - (3)].type_str),0,1);
		
		ID->srcop = 7;
		
		Exp->children = RP;
		RP->neighbours = LP;
		LP->neighbours = ID;
		treeStack[++treeStackTop] = Exp;
	}
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 768 "syntax.y"
    {
		struct TreeNode *LB = create("LB",(yyloc).first_line,yytext,0,1);
		
		struct TreeNode *RB = create("RB",(yyloc).first_line,yytext,0,1);
		
		struct TreeNode *Exp = create("Exp",(yyloc).first_line,yytext,0,-1);
		
		
		
		Exp->children = RB;
		RB->neighbours = treeStack[treeStackTop];
		treeStack[treeStackTop]->neighbours = LB;
		LB->neighbours = treeStack[treeStackTop-1];
		treeStack[--treeStackTop] = Exp;
	}
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 783 "syntax.y"
    {
		struct TreeNode *Exp = create("Exp",(yyloc).first_line,yytext,0,-1);
		
		struct TreeNode *DOT = create("DOT",(yyloc).first_line,yytext,0,1);
		
		struct TreeNode *ID = create("ID",(yyloc).first_line,(yyvsp[(3) - (3)].type_str),0,1);
		
		//ID->srcop = 8;
		
		Exp->children = ID;
		ID->neighbours = DOT;
		DOT->neighbours = treeStack[treeStackTop];
		treeStack[treeStackTop] = Exp;
	}
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 797 "syntax.y"
    {
		struct TreeNode *Exp = create("Exp",(yyloc).first_line,yytext,0,-1);
		
		struct TreeNode *ID = create("ID",(yyloc).first_line,(yyvsp[(1) - (1)].type_str),0,1);
		
		ID->srcop = 6;
		
		Exp->children = ID;
		treeStack[++treeStackTop] = Exp;
	}
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 807 "syntax.y"
    {
		struct TreeNode *Exp = create("Exp",(yyloc).first_line,yytext,0,-1);
		
		struct TreeNode *INT= create("INT",(yyloc).first_line,yytext,(yyvsp[(1) - (1)].type_int),1);
		
		
		
		Exp->children = INT;
		treeStack[++treeStackTop] = Exp;
	}
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 817 "syntax.y"
    {
		struct TreeNode *Exp = create("Exp",(yyloc).first_line,yytext,0,-1);
		
		struct TreeNode *FLOAT= create("FLOAT",(yyloc).first_line,yytext,5,1);
		
		
		
		Exp->children = FLOAT;
		treeStack[++treeStackTop] = Exp;
	}
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 828 "syntax.y"
    {
		struct TreeNode *COMMA = create("COMMA",(yyloc).first_line,yytext,0,1);
		
		struct TreeNode *Args= create("Args",(yyloc).first_line,yytext,0,-1);
		
		
		
		Args->children = treeStack[treeStackTop];
		treeStack[treeStackTop]->neighbours = COMMA;
		COMMA->neighbours = treeStack[treeStackTop-1];
		treeStack[--treeStackTop] = Args;
	}
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 840 "syntax.y"
    {
		struct TreeNode *Args= create("Args",(yyloc).first_line,yytext,0,-1);
		
		
		
		Args->children = treeStack[treeStackTop];
		treeStack[treeStackTop] = Args;
	}
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 850 "syntax.y"
    {;}
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 852 "syntax.y"
    {;}
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 854 "syntax.y"
    {;}
    break;



/* Line 1806 of yacc.c  */
#line 2720 "syntax.tab.c"
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
  *++yylsp = yyloc;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
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

  yyerror_range[1] = yylloc;

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
		      yytoken, &yylval, &yylloc);
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

  yyerror_range[1] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

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

#if !defined(yyoverflow) || YYERROR_VERBOSE
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
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, yylsp);
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 2067 of yacc.c  */
#line 856 "syntax.y"


yyerror(char* msg){
	fprintf(stderr, "Error type B at line %d:%s\n", yylloc.first_line, msg);
	flag =-1;
}

struct TreeNode* create(char *p,int lineno,char value_str[],int value_int, int type){
	struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
	strcpy(newNode->name, p);
	newNode->lineno = lineno;
	newNode->type = type;
	newNode->depth = 0;
	newNode->value_int = value_int;
	strncpy(newNode->value_str,value_str,strlen(value_str));
	newNode->neighbours = NULL;
	newNode->children = NULL;
	
	newNode->srcop = -1;
	newNode->real_type = NULL;
	newNode->return_type = NULL;
	newNode->syn_type = NULL;
	return newNode;
}

