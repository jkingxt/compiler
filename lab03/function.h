#ifndef __FUNCTION__
#define __FUNCTION__


int compFieldList(FieldList a, FieldList b);
int compType(Type a, Type b);
void addItem(FieldList newItem);
int lookupTable(char *name,FieldList *t,int way);
void visit (struct TreeNode * node, int op);
void CheckTree(struct TreeNode *treeRoot);

struct InterCodes* translate_Exp(struct TreeNode* Exp, Operand place);
struct InterCodes* translate_Stmt(struct TreeNode* Stmt);
struct InterCodes* translate_Cond(struct TreeNode* Exp, Operand label_true, Operand label_false);
struct InterCodes* translate_Args(struct TreeNode* Args, struct ArgList** arg_list);
struct InterCodes* translate_ExtDecList(struct TreeNode* ExtDecList);
struct InterCodes* translate_VarDec(struct TreeNode* VarDec);
struct InterCodes* translate_Dec(struct TreeNode* Dec);
struct InterCodes* translate_FunDec(struct TreeNode* FunDec);
struct InterCodes* translate_CompSt(struct TreeNode* CompSt);
struct InterCodes* translate_StmtList(struct TreeNode* StmtList);
struct InterCodes* translate_DefList(struct TreeNode* DefList);
struct InterCodes* translate_Def(struct TreeNode* Def);
struct InterCodes* translate_Defstruct (struct 	TreeNode* Def);
struct InterCodes* translate_DecList(struct TreeNode* DecList);
struct InterCodes* translate_ExtDefList(struct TreeNode* ExtDefList);
struct InterCodes* translate_ExtDef(struct TreeNode* ExtDef);
struct InterCodes* GenerateInterCode(struct TreeNode* root);

void printOperand(Operand op,FILE *fp);
Operand new_label();
void printCode(struct InterCodes *root,FILE *fp);

int dec_size(Type item);
int index_size(FieldList father,char *memberName);
int  newlookupTable(char *name,FieldList *t,int way);
void getVarInterName(FieldList  root);





#endif
