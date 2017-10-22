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
#line 1 "parser.y" /* yacc.c:339  */

#include "classdef.h"
#include <bits/stdc++.h>

  extern "C" int yylex();
  extern "C" int yyparse();
  extern "C" FILE *yyin;
  extern "C" int line_num;
  extern union Node yylval;
  extern "C" int errors;
  void yyerror(const char *s);
  class program* start = NULL;
  extern "C" int error_flag;
  int errors=0;

#line 82 "parser.tab.c" /* yacc.c:339  */

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

/* In a future release of Bison, this section will be replaced
   by #include "parser.tab.h".  */
#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
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
    DECL = 258,
    CODE = 259,
    NUMBER = 260,
    INT = 261,
    ID = 262,
    ETOK = 263,
    ARR_ID = 264,
    ARR_NUM = 265,
    EQEQ = 266,
    EQUAL = 267,
    IF = 268,
    ELSE = 269,
    OR = 270,
    AND = 271,
    NOTEQ = 272,
    LESSEQ = 273,
    MOREEQ = 274,
    WHILE = 275,
    GOTO = 276,
    LABEL = 277,
    READ = 278,
    TOPRINT = 279,
    PRINT = 280,
    FOR = 281,
    SUBEQ = 282,
    ADDEQ = 283,
    PRINTLN = 284,
    LTEQ = 285,
    GTEQ = 286
  };
#endif

/* Value type.  */

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 174 "parser.tab.c" /* yacc.c:358  */

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
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   182

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  46
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  23
/* YYNRULES -- Number of rules.  */
#define YYNRULES  60
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  124

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   286

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,    14,     9,    43,    11,     2,    12,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    13,    42,
      15,    10,    16,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    44,     2,    45,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    40,     2,    41,     2,     2,     2,     2,
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
       5,     6,     7,     8,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    99,    99,   104,   105,   108,   109,   112,   115,   116,
     119,   120,   121,   122,   124,   125,   126,   128,   129,   130,
     131,   132,   133,   134,   136,   137,   139,   140,   141,   142,
     144,   145,   146,   147,   150,   151,   152,   155,   156,   157,
     158,   159,   160,   162,   163,   164,   166,   167,   169,   173,
     174,   176,   177,   179,   181,   182,   184,   185,   187,   188,
     189
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "DECL", "CODE", "NUMBER", "INT", "ID",
  "ETOK", "'+'", "'='", "'-'", "'/'", "':'", "'*'", "'<'", "'>'", "ARR_ID",
  "ARR_NUM", "EQEQ", "EQUAL", "IF", "ELSE", "OR", "AND", "NOTEQ", "LESSEQ",
  "MOREEQ", "WHILE", "GOTO", "LABEL", "READ", "TOPRINT", "PRINT", "FOR",
  "SUBEQ", "ADDEQ", "PRINTLN", "LTEQ", "GTEQ", "'{'", "'}'", "';'", "','",
  "'['", "']'", "$accept", "program", "terminal", "declblocks",
  "declblock", "variables", "variable", "codeblocks", "codeblock", "Last",
  "exp", "expr", "Assign", "Type", "BoolExp", "If", "While", "For", "Goto",
  "Read", "Print", "Contents", "Content", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,    43,
      61,    45,    47,    58,    42,    60,    62,   264,   265,   266,
     267,   268,   269,   270,   271,   272,   273,   274,   275,   276,
     277,   278,   279,   280,   281,   282,   283,   284,   285,   286,
     123,   125,    59,    44,    91,    93
};
# endif

#define YYPACT_NINF -77

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-77)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      20,   -37,    24,   -77,   -77,    -2,    43,    48,   -11,     5,
      28,   -77,    23,   -77,    14,    69,    43,   -77,   -77,    77,
      59,   -77,    27,   -77,   -77,    -4,    92,    92,    86,    99,
     -77,   103,   -77,   -77,   -77,    31,    74,   -77,   -77,   -77,
      76,    81,    84,   126,    92,   -77,    83,   125,   -77,   153,
     -77,    19,    67,   110,   -77,    15,   124,    15,    92,    92,
      92,   -77,   -77,   -77,   -77,   -77,    -1,   -77,    92,    92,
      92,    92,   -77,   -77,   -77,   -77,   -77,   -77,    92,    92,
      92,   -77,   -77,    92,   -77,   -77,   -77,    95,    92,    95,
     162,   162,   162,   -77,   132,     0,   -77,   123,   162,   116,
     -77,    44,    55,    46,   -77,   139,   130,   -77,    25,   118,
     -77,   -77,    62,   -77,   -77,    25,    80,    91,   121,   -77,
     -77,   -77,   108,   -77
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     5,     1,     0,     0,     0,     0,    10,
       7,     8,     0,     6,     0,     0,     0,    14,    12,     0,
       0,     9,     0,    13,    11,    24,     0,     0,     0,     0,
      56,     0,    56,     2,    15,     0,     0,    18,    19,    23,
       0,     0,     0,     0,     0,    27,    24,     0,    28,     0,
      26,     0,     0,    52,    53,     0,     0,     0,     0,     0,
       0,    17,    20,    22,    21,    16,     0,    29,     0,     0,
       0,     0,    41,    42,    37,    38,    40,    39,     0,     0,
       0,    14,    14,     0,    60,    58,    59,    54,     0,    55,
      34,    36,    35,    25,    30,    31,    33,    32,    43,    44,
      45,     0,     0,    51,    57,     0,    46,    48,     0,     0,
       4,     3,     0,    14,    14,     0,     0,     0,     0,    47,
      49,    14,     0,    50
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -77,   -77,    41,   -77,   -77,   -77,   150,   -76,   127,   -22,
     -42,   -77,   -77,   -77,   -26,   -77,   -77,   -77,   -77,   -77,
     -77,   143,   120
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,   112,     5,     8,    10,    11,    22,    34,    48,
      49,    50,    36,    78,    51,    37,    38,    39,    40,    41,
      42,    55,    87
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      35,    52,    66,     3,     6,   101,   102,    54,    68,    43,
      69,    70,    70,    71,    71,    14,    90,    91,    92,    18,
      84,    35,    46,     1,     4,    19,    94,    95,    96,    97,
     110,    13,   111,    86,    25,    86,    98,   116,   117,     7,
      44,    58,    79,    80,    93,   122,   105,    85,    26,    15,
       9,    25,    12,    99,   100,    27,    28,   103,    29,    81,
      30,    31,    25,    17,    32,    26,    59,    60,    33,    79,
      80,    16,    27,    28,    20,    29,    26,    30,    31,    35,
      35,    32,    23,    27,    28,   106,    29,    25,    30,    31,
      79,    80,    32,    53,    35,    35,   107,    45,    25,    46,
      35,    26,   114,    47,    24,   115,    46,    82,    27,    28,
      56,    29,    26,    30,    31,    25,    61,    32,    62,    27,
      28,   119,    29,    63,    30,    31,    64,    44,    32,    26,
      67,    83,   120,    46,    88,    70,    27,    28,   104,    29,
      80,    30,    31,    69,    70,    32,    71,    26,    68,   123,
      69,    70,   109,    71,    27,    28,   118,    29,   113,    30,
      31,   121,    68,    32,    69,    70,    21,    71,    72,    73,
      65,    68,    74,    69,    70,    57,    71,    89,    75,    76,
      77,     0,   108
};

static const yytype_int8 yycheck[] =
{
      22,    27,    44,    40,     6,    81,    82,    29,     9,    13,
      11,    12,    12,    14,    14,    10,    58,    59,    60,     5,
       5,    43,     7,     3,     0,    11,    68,    69,    70,    71,
       5,    42,     7,    55,     7,    57,    78,   113,   114,    41,
      44,    10,    23,    24,    45,   121,    88,    32,    21,    44,
       7,     7,     4,    79,    80,    28,    29,    83,    31,    40,
      33,    34,     7,    40,    37,    21,    35,    36,    41,    23,
      24,    43,    28,    29,     5,    31,    21,    33,    34,   101,
     102,    37,     5,    28,    29,    41,    31,     7,    33,    34,
      23,    24,    37,     7,   116,   117,    41,     5,     7,     7,
     122,    21,    40,    11,    45,    43,     7,    40,    28,    29,
       7,    31,    21,    33,    34,     7,    42,    37,    42,    28,
      29,    41,    31,    42,    33,    34,    42,    44,    37,    21,
       5,    21,    41,     7,    10,    12,    28,    29,    43,    31,
      24,    33,    34,    11,    12,    37,    14,    21,     9,    41,
      11,    12,    22,    14,    28,    29,   115,    31,    40,    33,
      34,    40,     9,    37,    11,    12,    16,    14,    15,    16,
      43,     9,    19,    11,    12,    32,    14,    57,    25,    26,
      27,    -1,    43
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    47,    40,     0,    49,     6,    41,    50,     7,
      51,    52,     4,    42,    10,    44,    43,    40,     5,    11,
       5,    52,    53,     5,    45,     7,    21,    28,    29,    31,
      33,    34,    37,    41,    54,    55,    58,    61,    62,    63,
      64,    65,    66,    13,    44,     5,     7,    11,    55,    56,
      57,    60,    60,     7,    55,    67,     7,    67,    10,    35,
      36,    42,    42,    42,    42,    54,    56,     5,     9,    11,
      12,    14,    15,    16,    19,    25,    26,    27,    59,    23,
      24,    40,    40,    21,     5,    32,    55,    68,    10,    68,
      56,    56,    56,    45,    56,    56,    56,    56,    56,    60,
      60,    53,    53,    60,    43,    56,    41,    41,    43,    22,
       5,     7,    48,    40,    40,    43,    53,    53,    48,    41,
      41,    40,    53,    41
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    46,    47,    48,    48,    49,    49,    50,    51,    51,
      52,    52,    52,    52,    53,    53,    53,    54,    54,    54,
      54,    54,    54,    54,    55,    55,    56,    56,    56,    56,
      57,    57,    57,    57,    58,    58,    58,    59,    59,    59,
      59,    59,    59,    60,    60,    60,    61,    61,    62,    63,
      63,    64,    64,    65,    66,    66,    67,    67,    68,    68,
      68
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     8,     1,     1,     0,     3,     2,     1,     3,
       1,     4,     3,     4,     0,     2,     4,     2,     1,     1,
       2,     2,     2,     1,     1,     4,     1,     1,     1,     2,
       3,     3,     3,     3,     3,     3,     3,     1,     1,     1,
       1,     1,     1,     3,     3,     3,     5,     9,     5,     9,
      11,     4,     2,     2,     3,     3,     0,     3,     1,     1,
       1
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


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


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


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  unsigned res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (yylocationp);
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
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
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
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
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
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
       'yyls': related to locations.

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
  int yytoken = 0;
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

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
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
     '$$ = $1'.

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
#line 99 "parser.y" /* yacc.c:1646  */
    {
	(yyval.prog) = new program((yyvsp[-5].decls),(yyvsp[-1].codes));
	start = (yyval.prog);
}
#line 1445 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 104 "parser.y" /* yacc.c:1646  */
    { (yyval.unit) = new unitClass("id", string((yyvsp[0].ch))); }
#line 1451 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 105 "parser.y" /* yacc.c:1646  */
    { (yyval.unit) = new unitClass("num", (yyvsp[0].number)); }
#line 1457 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 108 "parser.y" /* yacc.c:1646  */
    { (yyval.decls) = new declblocks(); }
#line 1463 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 109 "parser.y" /* yacc.c:1646  */
    { (yyval.decls)->push_back((yyvsp[-1].decl)); }
#line 1469 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 112 "parser.y" /* yacc.c:1646  */
    { (yyval.decl) = new declblock((yyvsp[0].vars)); }
#line 1475 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 115 "parser.y" /* yacc.c:1646  */
    { (yyval.vars) = new Vars(); (yyval.vars)->push_back((yyvsp[0].var)); }
#line 1481 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 116 "parser.y" /* yacc.c:1646  */
    { (yyval.vars)->push_back((yyvsp[0].var)); }
#line 1487 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 119 "parser.y" /* yacc.c:1646  */
    { (yyval.var) = new Var(string("Normal"), string((yyvsp[0].ch))); }
#line 1493 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 120 "parser.y" /* yacc.c:1646  */
    { (yyval.var) = new Var(string("Array"),string((yyvsp[-3].ch)),(yyvsp[-1].number)); }
#line 1499 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 121 "parser.y" /* yacc.c:1646  */
    { (yyval.var) = new Var(string("NormalInit"),string((yyvsp[-2].ch)),"1",(yyvsp[0].number)); }
#line 1505 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 122 "parser.y" /* yacc.c:1646  */
    { (yyval.var) = new Var(string("NormalInit2"),string((yyvsp[-3].ch)),"1",-1*(yyvsp[0].number)); }
#line 1511 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 124 "parser.y" /* yacc.c:1646  */
    { (yyval.codes) = new codeblocks(); }
#line 1517 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 125 "parser.y" /* yacc.c:1646  */
    { (yyval.codes)->push_back((yyvsp[0].code));  }
#line 1523 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 126 "parser.y" /* yacc.c:1646  */
    { (yyval.codes)->push_back((yyvsp[0].code),(yyvsp[-2].ch)); }
#line 1529 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 128 "parser.y" /* yacc.c:1646  */
    { (yyval.code) = (yyvsp[-1].assign); }
#line 1535 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 129 "parser.y" /* yacc.c:1646  */
    { (yyval.code) = (yyvsp[0].ifst); }
#line 1541 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 130 "parser.y" /* yacc.c:1646  */
    { (yyval.code) = (yyvsp[0].whilest);  }
#line 1547 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 131 "parser.y" /* yacc.c:1646  */
    { (yyval.code) = (yyvsp[-1].gotost); }
#line 1553 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 132 "parser.y" /* yacc.c:1646  */
    { (yyval.code) = (yyvsp[-1].printst); }
#line 1559 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 133 "parser.y" /* yacc.c:1646  */
    { (yyval.code) = (yyvsp[-1].readst); }
#line 1565 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 134 "parser.y" /* yacc.c:1646  */
    { (yyval.code) = (yyvsp[0].forst); }
#line 1571 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 136 "parser.y" /* yacc.c:1646  */
    {(yyval.last) = new last(string((yyvsp[0].ch)),string("Normal"));}
#line 1577 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 137 "parser.y" /* yacc.c:1646  */
    { (yyval.last) = new last(string((yyvsp[-3].ch)),string("Array"),(yyvsp[-1].expr)); }
#line 1583 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 139 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new Expr("expr", (yyvsp[0].binexpr)); }
#line 1589 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 140 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new Expr("num", (yyvsp[0].number)); }
#line 1595 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 141 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new Expr("last", (yyvsp[0].last)); }
#line 1601 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 142 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new Expr("num", -1*(yyvsp[0].number)); }
#line 1607 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 144 "parser.y" /* yacc.c:1646  */
    { (yyval.binexpr) = new binExpr((yyvsp[-2].expr),"+",(yyvsp[0].expr)); }
#line 1613 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 145 "parser.y" /* yacc.c:1646  */
    { (yyval.binexpr) = new binExpr((yyvsp[-2].expr),"-",(yyvsp[0].expr)); }
#line 1619 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 146 "parser.y" /* yacc.c:1646  */
    { (yyval.binexpr) = new binExpr((yyvsp[-2].expr),"*",(yyvsp[0].expr)); }
#line 1625 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 147 "parser.y" /* yacc.c:1646  */
    { (yyval.binexpr) = new binExpr((yyvsp[-2].expr),"/",(yyvsp[0].expr)); }
#line 1631 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 150 "parser.y" /* yacc.c:1646  */
    { (yyval.assign) = new Assign(((yyvsp[-2].last)), "=", (yyvsp[0].expr)); }
#line 1637 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 151 "parser.y" /* yacc.c:1646  */
    { (yyval.assign) = new Assign(((yyvsp[-2].last)), "+=", (yyvsp[0].expr)); }
#line 1643 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 152 "parser.y" /* yacc.c:1646  */
    { (yyval.assign) = new Assign(((yyvsp[-2].last)), "-=", (yyvsp[0].expr)); }
#line 1649 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 155 "parser.y" /* yacc.c:1646  */
    { (yyval.optype) = new OperandType("=="); }
#line 1655 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 156 "parser.y" /* yacc.c:1646  */
    { (yyval.optype) = new OperandType("!="); }
#line 1661 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 157 "parser.y" /* yacc.c:1646  */
    { (yyval.optype) = new OperandType(">="); }
#line 1667 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 158 "parser.y" /* yacc.c:1646  */
    { (yyval.optype) = new OperandType("<="); }
#line 1673 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 159 "parser.y" /* yacc.c:1646  */
    { (yyval.optype) = new OperandType("<"); }
#line 1679 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 160 "parser.y" /* yacc.c:1646  */
    { (yyval.optype) = new OperandType(">"); }
#line 1685 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 162 "parser.y" /* yacc.c:1646  */
    { (yyval.boolex) = new boolExpr("expr",(yyvsp[-2].expr), (yyvsp[-1].optype), (yyvsp[0].expr)); }
#line 1691 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 163 "parser.y" /* yacc.c:1646  */
    { (yyval.boolex) = new boolExpr("bool", (yyvsp[-2].boolex), "OR", (yyvsp[0].boolex)); }
#line 1697 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 164 "parser.y" /* yacc.c:1646  */
    { (yyval.boolex) = new boolExpr("bool", (yyvsp[-2].boolex), "AND", (yyvsp[0].boolex)); }
#line 1703 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 166 "parser.y" /* yacc.c:1646  */
    { (yyval.ifst) = new ifStmt("if", (yyvsp[-3].boolex),(yyvsp[-1].codes)); }
#line 1709 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 167 "parser.y" /* yacc.c:1646  */
    {(yyval.ifst) = new ifStmt("else", (yyvsp[-7].boolex),(yyvsp[-5].codes),(yyvsp[-1].codes));}
#line 1715 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 169 "parser.y" /* yacc.c:1646  */
    { (yyval.whilest) = new whileStmt((yyvsp[-3].boolex),(yyvsp[-1].codes));  }
#line 1721 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 173 "parser.y" /* yacc.c:1646  */
    { (yyval.forst) = new forStmt((yyvsp[-7].ch),(yyvsp[-5].expr),(yyvsp[-3].unit),(yyvsp[-1].codes)); }
#line 1727 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 174 "parser.y" /* yacc.c:1646  */
    { (yyval.forst) = new forStmt((yyvsp[-9].ch),(yyvsp[-7].expr),(yyvsp[-5].unit),(yyvsp[-3].unit),(yyvsp[-1].codes)); }
#line 1733 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 176 "parser.y" /* yacc.c:1646  */
    { (yyval.gotost) = new gotoStmt("cond", (yyvsp[-2].ch), (yyvsp[0].boolex)); }
#line 1739 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 177 "parser.y" /* yacc.c:1646  */
    { (yyval.gotost) = new gotoStmt("uncond", (yyvsp[0].ch)); }
#line 1745 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 179 "parser.y" /* yacc.c:1646  */
    { (yyval.readst) = new readStmt((yyvsp[0].last)); }
#line 1751 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 181 "parser.y" /* yacc.c:1646  */
    { (yyval.printst) = (yyvsp[-1].printst); (yyval.printst)->type = 1; (yyval.printst)->push_back((yyvsp[0].contnt)); }
#line 1757 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 182 "parser.y" /* yacc.c:1646  */
    { (yyval.printst) = (yyvsp[-1].printst); (yyval.printst)->type = 2; (yyval.printst)->push_back((yyvsp[0].contnt)); }
#line 1763 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 184 "parser.y" /* yacc.c:1646  */
    { (yyval.printst) = new printStmt(); }
#line 1769 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 185 "parser.y" /* yacc.c:1646  */
    { (yyval.printst)->push_back((yyvsp[-1].contnt)); }
#line 1775 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 187 "parser.y" /* yacc.c:1646  */
    { (yyval.contnt) = new content((yyvsp[0].ch)); }
#line 1781 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 188 "parser.y" /* yacc.c:1646  */
    { (yyval.contnt) = new content((yyvsp[0].last)); }
#line 1787 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 189 "parser.y" /* yacc.c:1646  */
    { (yyval.contnt) = new content((yyvsp[0].number)); }
#line 1793 "parser.tab.c" /* yacc.c:1646  */
    break;


#line 1797 "parser.tab.c" /* yacc.c:1646  */
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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
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
  return yyresult;
}
#line 200 "parser.y" /* yacc.c:1906  */




int main(int argc, char *argv[])
{
	//error_flag=0;
	if (argc == 1){
		fprintf(stderr, "Correct usage: bcc filename\n");
		exit(1);
	}

	if (argc > 2) {
		fprintf(stderr, "Passing more arguments than necessary.\n");
		fprintf(stderr, "Correct usage: bcc filename\n");
	}

	yyin = fopen(argv[1], "r");
	yyparse();
	Interpreter *it = new Interpreter();
	start->accept(it);
	//if(!error_flag){
	//printf("Done with no syntactic errors!\n");
	//}
}
