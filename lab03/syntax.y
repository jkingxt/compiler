%{
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
%}

%locations
%union{
int type_int;
char *type_str;
float type_float;
}
	 
%token <type_int>INT
%token PLUS MINUS STAR DIV
%token SEMI COMMA
%token <type_str>RELOP 
%token ASSIGNOP
%token AND OR NOT
%token DOT
%token <type_str>TYPE
%token LP RP LB RB LC RC
%token STRUCT
%token RETURN
%token IF ELSE
%token WHILE
%token <type_str>ID
%token <type_float>FLOAT

%right  ASSIGNOP
%left   RELOP
%left    AND  OR
%left   PLUS  MINUS
%left   STAR  DIV
%right NOT
%left   DOT  LP  RP  LB  RB LC  RC
%nonassoc  STRUCT RETURN IF ELSE WHILE LOWER_THAN_ELSE


%%

/*High-Level Definitions */
/*error  recover */


Program : ExtDefList{
			struct TreeNode* Program = create("Program", @$.first_line, yytext,0,-1);
			
			Program->children = treeStack[treeStackTop];
			treeRoot = Program ;
		}
		;
ExtDefList : ExtDef ExtDefList{
			struct TreeNode* ExtDefList = create("ExtDefList", @$.first_line, yytext,0,-1);
			
			ExtDefList->children = treeStack[treeStackTop];
			treeStack[treeStackTop]->neighbours = treeStack[treeStackTop-1];
			treeStackTop = treeStackTop -1;
			treeStack[treeStackTop] = ExtDefList;
		}
		| /*empty*/{
			struct TreeNode* ExtDefList = create("ExtDefList", @$.first_line, yytext,-1,-1);
			
			
			treeStackTop = treeStackTop + 1;
			treeStack[treeStackTop] = ExtDefList;
		}
		;
ExtDef : Specifier ExtDecList SEMI{
			struct TreeNode* ExtDef = create("ExtDef", @$.first_line, yytext,0,-1);
			
			struct TreeNode* SEMI = create("SEMI", @$.first_line, yytext,0,1);
			
			
			ExtDef->children = SEMI;
			SEMI->neighbours = treeStack[treeStackTop];
			treeStack[treeStackTop]->neighbours = treeStack[treeStackTop-1];
			treeStackTop = treeStackTop -1;
			treeStack[treeStackTop] = ExtDef;
		}
		| Specifier SEMI{
			struct TreeNode* ExtDef = create("ExtDef", @$.first_line, yytext,0,-1);
			
			struct TreeNode* SEMI = create("SEMI", @$.first_line, yytext,0,-1);
			
			ExtDef->children = SEMI;
			SEMI->neighbours = treeStack[treeStackTop];
			treeStack[treeStackTop] = ExtDef;
		}
		| Specifier FunDec SEMI{
		
			struct TreeNode* ExtDef = create("ExtDef", @$.first_line, yytext,0,-1);
			struct TreeNode* SEMI = create("SEMI", @$.first_line, yytext,0,-1);
			
			treeStack[treeStackTop]->srcop = 5;
			
			ExtDef->children = SEMI;
			SEMI->neighbours = treeStack[treeStackTop];
			treeStack[treeStackTop]->neighbours = treeStack[treeStackTop-1];
			
			treeStackTop = treeStackTop - 1;
			treeStack[treeStackTop] = ExtDef;
			
		}
		| Specifier FunDec CompSt{
			struct TreeNode* ExtDef = create("ExtDef", @$.first_line, yytext,0,-1);
			
			treeStack[treeStackTop-1]->srcop = 4;
			
			ExtDef->children = treeStack[treeStackTop];
			treeStack[treeStackTop]->neighbours = treeStack[treeStackTop-1];
			treeStack[treeStackTop-1]->neighbours = treeStack[treeStackTop-2];
			
			treeStackTop = treeStackTop -2;
			treeStack[treeStackTop] = ExtDef;
		}
		;
ExtDecList : VarDec{
			struct TreeNode* ExtDecList = create("ExtDecList", @$.first_line, yytext,0,-1);
			
			treeStack[treeStackTop]->srcop = 0;
			
			ExtDecList->children = treeStack[treeStackTop];
			treeStack[treeStackTop] = ExtDecList;
		}
		| VarDec COMMA ExtDecList{
			struct TreeNode* ExtDecList = create("ExtDecList", @$.first_line, yytext,0,-1);
			
			struct TreeNode* COMMA = create("COMMA", @$.first_line, yytext,0,1);
			
			treeStack[treeStackTop-1]->srcop = 0;
			
			ExtDecList->children = treeStack[treeStackTop];
			treeStack[treeStackTop]->neighbours = COMMA;
			COMMA->neighbours = treeStack[treeStackTop-1];
			treeStackTop = treeStackTop - 1;
			treeStack[treeStackTop] = ExtDecList;
		}
		;

/*Specifiers*/
Specifier : TYPE{
			struct TreeNode *TYPE1 = create("TYPE",@$.first_line,$1,0,1);
			
			
			struct TreeNode *Specifier = create("Specifier",@$.first_line,yytext,0,-1);
			Specifier->syn_type = (Type)malloc(sizeof(struct Type_));
			//获得Specifier的Type

			Specifier->syn_type->kind = 0;
			if(strcmp("int", $1) == 0){
				Specifier->syn_type->u.basic = 0;	// 0 表示int
				}
			else if(strcmp("float", $1) == 0){     
				Specifier->syn_type->u.basic = 1;       //1 表示float
				}
			
			
			Specifier->children  = TYPE1;
			treeStack[++treeStackTop] = Specifier;
		}
		| StructSpecifier{
			struct TreeNode *Specifier = create("Specifier",@$.first_line,yytext,0,-1);
			Specifier->syn_type = (Type)malloc(sizeof(struct Type_));
			Specifier->syn_type->kind = treeStack[treeStackTop]->syn_type->kind;
			
			Specifier->children = treeStack[treeStackTop];
			treeStack[treeStackTop] = Specifier;
				
		}
		;
StructSpecifier : STRUCT OptTag LC DefList RC{
			struct TreeNode *LC = create("LC",@$.first_line,yytext,0,1);
			struct TreeNode *RC = create("RC",@$.first_line,yytext,0,1);
			struct TreeNode *Struct = create("Struct",@$.first_line,yytext,0,1);
			struct TreeNode *StructSpecifier = create("StructSpecifier",@$.first_line,yytext,0,-1);
			
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
		| STRUCT Tag{
			struct TreeNode *StructSpecifier = create("StructSpecifier",@$.first_line,yytext,0,-1);
			struct TreeNode *Struct = create("Struct",@$.first_line,yytext,0,1);
			
			StructSpecifier->syn_type = (Type)malloc(sizeof(struct Type_));
			StructSpecifier->syn_type->kind = 2;
			
			StructSpecifier->children = treeStack[treeStackTop];
			treeStack[treeStackTop]->neighbours = Struct;
			treeStack[treeStackTop] = StructSpecifier;
		}
		
		;
OptTag : ID{
		struct TreeNode *ID = create("ID",@$.first_line,$1,0,1);
		
		struct TreeNode *OptTag = create("OptTag",@$.first_line,yytext,0,-1);
		
		ID->srcop = 1;
		
		OptTag->children = ID;
		treeStack[++treeStackTop] = OptTag; 
	}
		| /*empty*/{
			struct TreeNode *OptTag = create("OptTag",@$.first_line,yytext,-1,-1);
			
			treeStack[++treeStackTop] = OptTag;
			}
		;
Tag : ID{
		struct TreeNode *ID = create("ID",@$.first_line,$1,0,1);
		
		struct TreeNode *Tag = create("Tag",@$.first_line,yytext,0,-1);
		ID->srcop = 100;

		
		Tag->children = ID;
		treeStack[++treeStackTop] = Tag;
	}
		;

/*Declarators*/
VarDec : ID{
		struct TreeNode *ID = create("ID",@$.first_line,$1,0,1);
		
		struct TreeNode *VarDec = create("VarDec",@$.first_line,yytext,0,-1);
		
		ID->syn_type = (Type)malloc(sizeof(struct Type_));
		ID->syn_type->kind = 0;
		VarDec->syn_type = ID->syn_type;
		
		VarDec->children = ID;
		treeStack[++treeStackTop] = VarDec;
	}
		| VarDec LB INT RB{
		struct TreeNode *LB = create("LB",@$.first_line,yytext,0,1);
		
		struct TreeNode *RB = create("RB",@$.first_line,yytext,0,1);
		
		struct TreeNode *INT = create("INT",@$.first_line,yytext,$3,1);
		
		struct TreeNode *VarDec = create("VarDec",@$.first_line,yytext,0,-1);
		
		Type h = treeStack[treeStackTop]->syn_type;
		Type newP1; 
		Type newP2 = NULL;
		if (h->kind == 1){
			while (h->u.array.elem->kind ==1)
				h = h->u.array.elem;
			newP1 = (Type)malloc(sizeof(struct Type_));
			newP1->kind = 1;
			newP1->u.array.size = $3;
			newP1->u.array.elem = h->u.array.elem;
			h->u.array.elem = newP1;
			}
		
		else {
			newP1 = (Type)malloc(sizeof(struct Type_));
			newP1->kind = 0;
			treeStack[treeStackTop]->syn_type->kind =1;
			treeStack[treeStackTop]->syn_type->u.array.size = $3;
			treeStack[treeStackTop]->syn_type->u.array.elem = newP1;
			}
		VarDec->syn_type = treeStack[treeStackTop]->syn_type;
		
			
		VarDec->children = RB;
		RB->neighbours = INT;
		INT->neighbours = LB;
		LB->neighbours = treeStack[treeStackTop];
		treeStack[treeStackTop] = VarDec;
	}
		;
FunDec : ID LP VarList RP{
		struct TreeNode *RP = create("RP",@$.first_line,yytext,0,1);
		
		struct TreeNode *LP = create("LP",@$.first_line,yytext,0,1);
		
		struct TreeNode *ID = create("ID",@$.first_line,$1,0,1);
		
		struct TreeNode *FunDec = create("FunDec",@$.first_line,yytext,0,-1);
		
		
		FunDec->children = RP;
		RP->neighbours = treeStack[treeStackTop];
		treeStack[treeStackTop]->neighbours = LP;
		LP->neighbours  = ID;
		treeStack[treeStackTop] = FunDec;
		
	}
		| ID LP RP{
		struct TreeNode *RP = create("RP",@$.first_line,yytext,0,1);
		
		struct TreeNode *LP = create("LP",@$.first_line,yytext,0,1);
		
		struct TreeNode *ID = create("ID",@$.first_line,$1,0,1);
		
		struct TreeNode *FunDec = create("FunDec",@$.first_line,yytext,0,-1);
		

		
		FunDec->children = RP;
		RP->neighbours =LP;
		LP->neighbours  = ID;
		treeStack[++treeStackTop] = FunDec;
	}
		;
VarList : ParamDec COMMA VarList{
		struct TreeNode *COMMA =  create("COMMA",@$.first_line,yytext,0,1);
		
		struct TreeNode *VarList =  create("VarList",@$.first_line,yytext,0,-1);
		
		
		VarList->children = treeStack[treeStackTop];
		treeStack[treeStackTop]->neighbours = COMMA;
		COMMA->neighbours = treeStack[treeStackTop-1];
		treeStack[--treeStackTop] = VarList;
		
	}
		| ParamDec{
		struct TreeNode *VarList =  create("VarList",@$.first_line,yytext,0,-1);
		
		
		VarList->children = treeStack[treeStackTop];
		treeStack[treeStackTop] = VarList;
	}
		;
ParamDec : Specifier VarDec{
		struct TreeNode *ParamDec =  create("ParamDec",@$.first_line,yytext,0,-1);
		
		
		treeStack[treeStackTop]->srcop = 3;
		
		
		ParamDec->children = treeStack[treeStackTop];
		treeStack[treeStackTop]->neighbours = treeStack[treeStackTop-1];
		treeStack[--treeStackTop] = ParamDec;
	}
		;
		
/*Statements*/
CompSt : LC DefList StmtList RC{
		struct TreeNode *RC =  create("RC",@$.first_line,yytext,0,1);
		
		struct TreeNode *LC =  create("LC",@$.first_line,yytext,0,1);
		
		struct TreeNode *CompSt=  create("CompSt",@$.first_line,yytext,0,-1);
		
		treeStack[treeStackTop-1]->srcop = 0;
		
		CompSt->children = RC;
		RC->neighbours = treeStack[treeStackTop];
		treeStack[treeStackTop]->neighbours = treeStack[treeStackTop-1];
		treeStack[treeStackTop-1]->neighbours = LC;
		treeStack[--treeStackTop] = CompSt;
	}
		;
StmtList : Stmt StmtList{
		struct TreeNode *StmtList =  create("StmtList",@$.first_line,yytext,0,-1);
		
		
		StmtList->children = treeStack[treeStackTop];
		treeStack[treeStackTop]->neighbours = treeStack[treeStackTop-1];
		treeStack[--treeStackTop] = StmtList;
	}
		| /*empty*/{
		struct TreeNode *StmtList =  create("StmtList",@$.first_line,yytext,-1,-1);
		
		treeStack[++treeStackTop] = StmtList;
	}
		;
Stmt : Exp SEMI{
		struct TreeNode *SEMI =  create("SEMI",@$.first_line,yytext,0,1);
		
		struct TreeNode *Stmt =  create("Stmt",@$.first_line,yytext,0,-1);
		
		Stmt->children = SEMI;
		SEMI->neighbours = treeStack[treeStackTop];
		treeStack[treeStackTop] = Stmt;
	}
		| CompSt{
		struct TreeNode *Stmt =  create("Stmt",@$.first_line,yytext,0,-1);
		
		
		
		Stmt->children = treeStack[treeStackTop];
		treeStack[treeStackTop] = Stmt;
	}
		
		| RETURN Exp SEMI{
		struct TreeNode *SEMI =  create("SEMI",@$.first_line,yytext,0,1);
		
		struct TreeNode *Stmt =  create("Stmt",@$.first_line,yytext,0,-1);
		
		struct TreeNode *RETURN = create("RETURN",@$.first_line,yytext,0,1);
		
		
		
		
		Stmt->children = SEMI;
		SEMI->neighbours =treeStack[treeStackTop];
		treeStack[treeStackTop]->neighbours = RETURN;
		treeStack[treeStackTop] = Stmt;
	}
		| IF LP Exp RP Stmt  {
		struct TreeNode *RP =  create("RP",@$.first_line,yytext,0,1);
		
		struct TreeNode *Stmt =  create("Stmt",@$.first_line,yytext,0,-1);
		
		struct TreeNode *LP = create("LP",@$.first_line,yytext,0,1);
		
		struct TreeNode *IF =  create("IF",@$.first_line,yytext,0,1);
		
		
		
		Stmt->children = treeStack[treeStackTop];
		treeStack[treeStackTop]->neighbours = RP;
		RP->neighbours = treeStack[treeStackTop-1];
		treeStack[treeStackTop-1]->neighbours = LP;
		LP->neighbours = IF;
		treeStack[--treeStackTop] = Stmt;
		
	}
		| IF LP Exp RP Stmt ELSE Stmt{
		struct TreeNode *RP = create("RP",@$.first_line,yytext,0,1);
		
		struct TreeNode *Stmt = create("Stmt",@$.first_line,yytext,0,-1);
		
		struct TreeNode *LP = create("LP",@$.first_line,yytext,0,1);
		
		struct TreeNode *IF = create("IF",@$.first_line,yytext,0,1);
		
		struct TreeNode *ELSE = create("ELSE",@$.first_line,yytext,0,1);
		
		
		
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
		| WHILE LP Exp RP Stmt{
		struct TreeNode *RP = create("RP",@$.first_line,yytext,0,1);
		
		struct TreeNode *Stmt = create("Stmt",@$.first_line,yytext,0,-1);
		
		struct TreeNode *LP = create("LP",@$.first_line,yytext,0,1);
		
		struct TreeNode *WHILE = create("WHILE",@$.first_line,yytext,0,1);
		
		
		
		Stmt->children = treeStack[treeStackTop];
		treeStack[treeStackTop]->neighbours = RP;
		RP->neighbours = treeStack[treeStackTop-1];
		treeStack[treeStackTop-1]->neighbours = LP;
		LP->neighbours = WHILE;
		treeStack[--treeStackTop] = Stmt;
	}
		;

/*Local Definitions */
DefList : Def DefList{
		struct TreeNode *DefList = create("DefList",@$.first_line,yytext,0,-1);
		
		
		
		DefList->children = treeStack[treeStackTop];
		treeStack[treeStackTop]->neighbours = treeStack[treeStackTop-1];
		treeStack[--treeStackTop] = DefList;
	}
		| /*empty*/{
		struct TreeNode *DefList = create("DefList",@$.first_line,yytext,-1,-1);
		
		
		
		treeStack[++treeStackTop] = DefList;
	}
		;
Def : Specifier DecList SEMI{
		struct TreeNode *SEMI = create("SEMI",@$.first_line,yytext,0,1);
		
		struct TreeNode *Def = create("Def",@$.first_line,yytext,0,-1);
		
		//用Specifier的syn_type,遍历DecList，并设置值
		
	
		
		Def->children = SEMI;
		SEMI->neighbours = treeStack[treeStackTop];
		treeStack[treeStackTop]->neighbours = treeStack[treeStackTop-1];
		treeStack[--treeStackTop] = Def;
	}
		;
DecList : Dec{
		struct TreeNode *DecList = create("DecList",@$.first_line,yytext,0,-1);
		
		
		DecList->children = treeStack[treeStackTop];
		treeStack[treeStackTop] = DecList;
	}
		| Dec COMMA DecList{
		struct TreeNode *DecList = create("DecList",@$.first_line,yytext,0,-1);
		
		struct TreeNode *COMMA = create("COMMA",@$.first_line,yytext,0,1);
		
		
		
		DecList->children = treeStack[treeStackTop];
		treeStack[treeStackTop]->neighbours =COMMA;
		COMMA->neighbours = treeStack[treeStackTop-1];
		treeStack[--treeStackTop] = DecList;
	}
		;
Dec : VarDec{
		struct TreeNode *Dec = create("Dec",@$.first_line,yytext,0,-1);
		
		
		
		Dec->children = treeStack[treeStackTop];
		treeStack[treeStackTop] = Dec;
	}
		| VarDec ASSIGNOP Exp{
		struct TreeNode *Dec = create("Dec",@$.first_line,yytext,0,-1);
		
		struct TreeNode *ASSIGNOP = create("ASSIGNOP",@$.first_line,yytext,0,1);
		
		
		
		Dec->children = treeStack[treeStackTop];
		treeStack[treeStackTop]->neighbours = ASSIGNOP;
		ASSIGNOP->neighbours = treeStack[treeStackTop-1];
		treeStack[--treeStackTop] =Dec;
	}
		;

/*Expressions */
Exp : Exp ASSIGNOP Exp{
		struct TreeNode *ASSIGNOP = create("ASSIGNOP",@$.first_line,yytext,0,1);
		
		struct TreeNode *Exp = create("Exp",@$.first_line,yytext,0,-1);
		

		
		Exp->children = treeStack[treeStackTop];
		treeStack[treeStackTop]->neighbours = ASSIGNOP;
		ASSIGNOP->neighbours = treeStack[treeStackTop-1];
		treeStack[--treeStackTop] = Exp;
	}
		| Exp AND Exp{
		struct TreeNode *AND = create("AND",@$.first_line,yytext,0,1);
		
		struct TreeNode *Exp = create("Exp",@$.first_line,yytext,0,-1);
		
		
		Exp->children = treeStack[treeStackTop];
		treeStack[treeStackTop]->neighbours = AND;
		AND->neighbours = treeStack[treeStackTop-1];
		treeStack[--treeStackTop] = Exp;
	}
		| Exp OR Exp{
		struct TreeNode *OR = create("OR",@$.first_line,yytext,0,1);
		
		struct TreeNode *Exp = create("Exp",@$.first_line,yytext,0,-1);
		
		
		
		Exp->children = treeStack[treeStackTop];
		treeStack[treeStackTop]->neighbours = OR;
		OR->neighbours = treeStack[treeStackTop-1];
		treeStack[--treeStackTop] = Exp;
	}
		| Exp RELOP Exp{
		struct TreeNode *RELOP = create("RELOP",@$.first_line,$2,0,1);
		
		struct TreeNode *Exp = create("Exp",@$.first_line,yytext,0,-1);
		
		
		Exp->children = treeStack[treeStackTop];
		treeStack[treeStackTop]->neighbours = RELOP;
		RELOP->neighbours = treeStack[treeStackTop-1];
		treeStack[--treeStackTop] = Exp;
	}
		| Exp PLUS Exp{
		struct TreeNode *PLUS = create("PLUS",@$.first_line,yytext,0,1);
		
		struct TreeNode *Exp = create("Exp",@$.first_line,yytext,0,-1);
		
		
		
		Exp->children = treeStack[treeStackTop];
		treeStack[treeStackTop]->neighbours = PLUS;
		PLUS->neighbours = treeStack[treeStackTop-1];
		treeStack[--treeStackTop] = Exp;
	}
		| Exp MINUS Exp{
		struct TreeNode *MINUS = create("MINUS",@$.first_line,yytext,0,1);
		
		struct TreeNode *Exp = create("Exp",@$.first_line,yytext,0,-1);
		
	
		
		Exp->children = treeStack[treeStackTop];
		treeStack[treeStackTop]->neighbours = MINUS;
		MINUS->neighbours = treeStack[treeStackTop-1];
		treeStack[--treeStackTop] = Exp;
	}
		| Exp STAR Exp{
		struct TreeNode *STAR = create("STAR",@$.first_line,yytext,0,1);
		
		struct TreeNode *Exp = create("Exp",@$.first_line,yytext,0,-1);
		
		
		
		Exp->children = treeStack[treeStackTop];
		treeStack[treeStackTop]->neighbours = STAR;
		STAR->neighbours = treeStack[treeStackTop-1];
		treeStack[--treeStackTop] = Exp;
	}
		| Exp DIV Exp {
		struct TreeNode *DIV = create("DIV",@$.first_line,yytext,0,1);
		
		struct TreeNode *Exp = create("Exp",@$.first_line,yytext,0,-1);
		
		
		
		Exp->children = treeStack[treeStackTop];
		treeStack[treeStackTop]->neighbours = DIV;
		DIV->neighbours = treeStack[treeStackTop-1];
		treeStack[--treeStackTop] = Exp;
	}
		| LP Exp RP {
		struct TreeNode *LP = create("LP",@$.first_line,yytext,0,1);
		
		struct TreeNode *RP = create("RP",@$.first_line,yytext,0,1);
		
		struct TreeNode *Exp = create("Exp",@$.first_line,yytext,0,-1);
		
		
		
		Exp->children = RP;
		RP->neighbours = treeStack[treeStackTop];
		treeStack[treeStackTop]->neighbours = LP;
		treeStack[treeStackTop] = Exp;
	}
		| MINUS Exp {
		struct TreeNode *MINUS = create("MINUS",@$.first_line,yytext,0,1);
		
		struct TreeNode *Exp = create("Exp",@$.first_line,yytext,0,-1);
		
		
		
		Exp->children = treeStack[treeStackTop];
		treeStack[treeStackTop]->neighbours =MINUS;
		treeStack[treeStackTop] = Exp;
	}
		| NOT Exp {
		struct TreeNode *NOT = create("NOT",@$.first_line,yytext,0,1);
		
		struct TreeNode *Exp = create("Exp",@$.first_line,yytext,0,-1);
		
		
		
		Exp->children = treeStack[treeStackTop];
		treeStack[treeStackTop]->neighbours =NOT;
		treeStack[treeStackTop] = Exp;
	}
		| ID LP Args RP {
		struct TreeNode *LP = create("LP",@$.first_line,yytext,0,1);
		
		struct TreeNode *RP = create("RP",@$.first_line,yytext,0,1);
		
		struct TreeNode *Exp = create("Exp",@$.first_line,yytext,0,-1);
		
		struct TreeNode *ID = create("ID",@$.first_line,$1,0,1);
		
		ID->srcop = 7;
		
		Exp->children = RP;
		RP->neighbours = treeStack[treeStackTop];
		treeStack[treeStackTop]->neighbours = LP;
		LP->neighbours = ID;
		treeStack[treeStackTop] = Exp;
	}
		| ID LP RP{
		struct TreeNode *LP = create("LP",@$.first_line,yytext,0,1);
		
		struct TreeNode *RP = create("RP",@$.first_line,yytext,0,1);
		
		struct TreeNode *Exp = create("Exp",@$.first_line,yytext,0,-1);
		
		struct TreeNode *ID = create("ID",@$.first_line,$1,0,1);
		
		ID->srcop = 7;
		
		Exp->children = RP;
		RP->neighbours = LP;
		LP->neighbours = ID;
		treeStack[++treeStackTop] = Exp;
	}
		| Exp LB Exp RB {
		struct TreeNode *LB = create("LB",@$.first_line,yytext,0,1);
		
		struct TreeNode *RB = create("RB",@$.first_line,yytext,0,1);
		
		struct TreeNode *Exp = create("Exp",@$.first_line,yytext,0,-1);
		
		
		
		Exp->children = RB;
		RB->neighbours = treeStack[treeStackTop];
		treeStack[treeStackTop]->neighbours = LB;
		LB->neighbours = treeStack[treeStackTop-1];
		treeStack[--treeStackTop] = Exp;
	}
		| Exp DOT ID{
		struct TreeNode *Exp = create("Exp",@$.first_line,yytext,0,-1);
		
		struct TreeNode *DOT = create("DOT",@$.first_line,yytext,0,1);
		
		struct TreeNode *ID = create("ID",@$.first_line,$3,0,1);
		
		//ID->srcop = 8;
		
		Exp->children = ID;
		ID->neighbours = DOT;
		DOT->neighbours = treeStack[treeStackTop];
		treeStack[treeStackTop] = Exp;
	}
		| ID {
		struct TreeNode *Exp = create("Exp",@$.first_line,yytext,0,-1);
		
		struct TreeNode *ID = create("ID",@$.first_line,$1,0,1);
		
		ID->srcop = 6;
		
		Exp->children = ID;
		treeStack[++treeStackTop] = Exp;
	}
		| INT{
		struct TreeNode *Exp = create("Exp",@$.first_line,yytext,0,-1);
		
		struct TreeNode *INT= create("INT",@$.first_line,yytext,$1,1);
		
		
		
		Exp->children = INT;
		treeStack[++treeStackTop] = Exp;
	}
		| FLOAT{
		struct TreeNode *Exp = create("Exp",@$.first_line,yytext,0,-1);
		
		struct TreeNode *FLOAT= create("FLOAT",@$.first_line,yytext,5,1);
		
		
		
		Exp->children = FLOAT;
		treeStack[++treeStackTop] = Exp;
	}
		;
Args : Exp COMMA Args{
		struct TreeNode *COMMA = create("COMMA",@$.first_line,yytext,0,1);
		
		struct TreeNode *Args= create("Args",@$.first_line,yytext,0,-1);
		
		
		
		Args->children = treeStack[treeStackTop];
		treeStack[treeStackTop]->neighbours = COMMA;
		COMMA->neighbours = treeStack[treeStackTop-1];
		treeStack[--treeStackTop] = Args;
	}
		| Exp{
		struct TreeNode *Args= create("Args",@$.first_line,yytext,0,-1);
		
		
		
		Args->children = treeStack[treeStackTop];
		treeStack[treeStackTop] = Args;
	}
		;
		
Stmt : error SEMI	{;}
	;
CompSt : error RC	{;}
	;
Exp : error RP		{;}
	;
%%

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
