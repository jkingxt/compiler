#ifndef __STRUCTURE__
#define __STRUCTURE__

#include "stdio.h"
#include "syntax.tab.h"
#include <stdlib.h>
#include <string.h>
typedef struct Type_* Type;
typedef struct FieldList_* FieldList;

struct TreeNode{
		char name[20];
		int lineno;
		int depth;
		int value_int;//intÐÍÊýµÄÖµ
		char value_str[20];//idµÄÃû×Ö»òÕßtypeÀàÐÍ
		int type;//ÅÐ¶ÏÊÇ·ñÎª¿Õ

		/*Ò»žöœÚµãµÄ²Ù×÷ÔŽ£¬-1Žú±í²»¹Ø×¢£¬0Žú±í»ù±Ÿ±äÁ¿¶šÒå£¬1Žú±íœá¹¹Ìå¶šÒå£»2Žú±íœá¹¹Ìå³ÉÔ±¶šÒå£¬3Žú±íº¯Êý²ÎÊý¶šÒå£¬4Žú±íº¯ÊýÌå¶šÒå£¬5Žú±íº¯ÊýÌåÉùÃ÷£¬6Žú±íÊ¹ÓÃ±äÁ¿£¬7Žú±íº¯Êýµ÷ÓÃ,

		*/
		int srcop;
		Type real_type;//ÓÃÀŽÊý×éÈ·¶šÕæÊµÊôÐÔ
		Type return_type;//×ÛºÏÊôÐÔ£¬ŒÇÂŒreturn·µ»ØÀàÐÍ
		Type syn_type;//×ÛºÏÊôÐÔ£¬ŒÇÂŒ×ÜÌåÀàÐÍ
		struct TreeNode* neighbours;
		struct TreeNode* children;
	};
struct Type_
	{
	  enum { basic, array, structure, function, variable } kind;
	  union
	  {
		// »ù±ŸÀàÐÍ
		int basic;
		// Êý×éÀàÐÍÐÅÏ¢°üÀšÔªËØÀàÐÍÓëÊý×éŽóÐ¡¹¹³É
		struct { Type elem; int size; } array;
		// œá¹¹ÌåÀàÐÍÐÅÏ¢ÊÇÒ»žöÁŽ±í
		FieldList structure;
		FieldList function;
		FieldList variable;
	  } u;
	};

struct FieldList_
	{
	  char* name;    // ÓòµÄÃû×Ö
	  Type type;      // ÓòµÄÀàÐÍ
	  int func_dec;    //º¯ÊýÊÇ·ñ±»¶šÒå 0ÎŽ¶šÒå£¬1¶šÒå
	  int func_lineno;
	  char inter_name[20];
	  FieldList tail;    // ÏÂÒ»žöÓò
	};
	
typedef struct Operand_* Operand;
struct Operand_ {
	enum { VARIABLE, CONSTANT, CONSTANT_FLOAT, ADDRESS, REFERENCE, GOTOOP, LABELOP, RETURNOP} kind;
	union {
		char ID[20];//ÕâžöÓÐŽý¿ŒÂÇ
		int value;
		//if²Ù×÷Êý
		//ÆäËû
	} u;
};

struct ArgList{
	Operand op;
	struct ArgList* next;
};

struct InterCode
{
	enum { ASSIGN_, ADD_, SUB_, MUL_, DIV_, MINUS_, IF_, GOTO_, LABEL_, RETURN_, READ_, WRITE_, ARG_, CALL_, DEC_, FUNCTION_, PARAM_, NONE_} kind;
	union {
		struct { Operand right, left; } assign;
		struct { Operand result, op1, op2; } binop;
		struct { Operand result, op1; } sinop;
		struct { Operand op1, op2, label; char op_type[20]; } ifcode;
		struct { Operand label; } gotocode;//GOTO label
		struct { Operand label; } labelcode;//LABEL label
		struct { Operand r; } returncode;
		struct { Operand rd; } read;
		struct { Operand wr; } write;
		struct { Operand argument; } arg;
		struct { Operand left, function; } call;
		struct { Operand space; int size; } dec;
		struct { char func[20]; } function;
		struct { Operand op; } param;
		//ÆäËû
	} u;
} ;


struct InterCodes {
	struct InterCode code; 
	struct InterCodes *prev, *next; 
};
	


#endif
