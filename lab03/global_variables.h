#ifndef __GLOBAL_VARIABLES__
#define __GLOBAL_VARIABLES__


extern FILE* yyin;
extern int tag;
extern int flag;
extern struct TreeNode *treeRoot;

FieldList pItem;//ÖžÏò·ûºÅ±íÖÐÄ³Ò»Ïî
FieldList pCmp;//±ÈœÏ²ÎÊý±í¡£
FieldList pFunc; //ÖžÏò·ûºÅ±íÖÐº¯ÊýÏî
Type pType;		//ÖžÏòSpecifierµÄsyn_type
FieldList symbol_table = NULL; //·ûºÅ±í£¬ÓÃÁŽ±íÊµÏÖ¡£


#endif
