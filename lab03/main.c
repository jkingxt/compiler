#include "stdio.h"
#include "syntax.tab.h"
#include <stdlib.h>
#include <string.h>
#include "structure.h"
#include "global_variables.h"
#include "function.h"

int main(int argc, char **argv){

	if (argc <= 2) return 1;
	FILE* f = fopen(argv[1], "r");
	if (!f)
	{
		perror(argv[1]);
		return 1;
	}
	yyrestart(f);

	yyparse();
	if (tag < 0)
		return 0;
	if (flag <0)
		return 0;

	CheckTree(treeRoot);
	getVarInterName(symbol_table);
	struct InterCodes* myInerCode = GenerateInterCode(treeRoot);
	//write InterCode from rounine to .ir 
	FILE * fp;
	fp = fopen(argv[2],"w");
	if(fp == NULL) { printf ("file open error\n");   return 0;}
	printCode(myInerCode,fp);
	close(fp);
	return 0;
}
void CheckTree(struct TreeNode *treeRoot){
	struct TreeNode * Stack[5000];
	int top = -1;
	int op;
	struct TreeNode *current = treeRoot;
	Stack[++top] = current;
	while (top > -1){
		current = Stack[top];
		if (current->children !=NULL && current->type== -1){
			current->type = 0;
			op = current->srcop;
			current = current->children;
			while (current != NULL){
				if (op!=-1 && current->srcop == -1)
						current->srcop = op;
			 	Stack[++top] = current;
				current = current->neighbours;
			}
		 }
		 else{
		 	//printf("%s\n",current->name);
			visit(current,current->srcop);

			top--;
		}
	}
	FieldList fl = symbol_table;
	while(fl != NULL){
		if(fl->type->kind == 3){
			if(fl->func_dec != 2){
				printf("Error type:18 at %d line\n",fl->func_lineno);
			}
		}
		fl = fl->tail;
	}
	return;

}
	void visit (struct TreeNode * node, int op){

		if(strcmp(node->name,"Specifier")==0){

			struct TreeNode *p = node->children;
			pType = (Type)malloc(sizeof(struct Type_));
			if ( strcmp(p->name,"TYPE") == 0 ){
				pType->kind = 0;

				if ( strcmp(p->value_str,"int") == 0)
					pType->u.basic = 0;
				else
					pType->u.basic = 1;

			}

			else{
				p = p->children ;
				if ( strcmp(p->name,"RC") == 0 ){
					FieldList item = (FieldList)malloc(sizeof(struct FieldList_));
					p = p->neighbours->neighbours->neighbours->children;
					lookupTable(p->value_str,&item,0);

					 pType = item->type;
				}
				else {
					FieldList item;
					p = p->children;
					if (lookupTable(p->value_str,&item,0) == 1 && item->type->kind == 2)
						pType = item->type;
					else
						printf("Error type:17 at %d line\n",node->lineno);
				}
			}
		}
		else if(strcmp(node->name,"ID")==0){
			switch (op){
				//基本变量定义
				case 0:	{	FieldList index;
							if (lookupTable(node->value_str,&index,0) == 1)
								printf("Error type:3 at %d line\n",node->lineno);
							else {
									index = (FieldList)malloc(sizeof(struct FieldList_));
									index->name = (char*)malloc(sizeof(char)*20);
									strncpy(index->name,node->value_str,strlen(node->value_str));



									if (node->syn_type != NULL){
										Type temp = node->syn_type;
										while (temp->kind == 1)
											temp = temp->u.array.elem;
										if (temp == node->syn_type)
											node->syn_type = pType;
										else
											temp = pType;


										index->type = node->syn_type;
										addItem(index);
									}

									else {
										strncpy(index->name,node->value_str,strlen(node->value_str));
										index->type = (Type)malloc(sizeof(struct Type_));
										index->type = pType;
										addItem(index);
									}
							}
							break;
						}
				//结构体定义
				case 1: {
							FieldList index;
							if (lookupTable(node->value_str,&index,0) == 1)
								printf("Error type:16 at %d line\n",node->lineno);

							else{
								index = (FieldList)malloc(sizeof(struct FieldList_));
								index->name = (char*)malloc(sizeof(char)*20);
								strncpy(index->name,node->value_str,strlen(node->value_str));

								index->type = (Type)malloc(sizeof(struct Type_));
								index->type->kind = 2;
								index->type->u.structure = NULL;
								addItem(index);
								pItem = index;
							}
						break;
						}
				//结构体成员定义
				case 2:	{
							//可能有结构体成员名相同情况，暂时没实现。

							if (pItem->type->u.structure == NULL){
								pItem->type->u.structure = (FieldList)malloc(sizeof(struct FieldList_));
								pItem->type->u.structure->tail = NULL;
								pItem->type->u.structure->name = (char*)malloc(sizeof(char)*20);
								strncpy(pItem->type->u.structure->name,node->value_str,strlen(node->value_str));
								if (node->syn_type != NULL)
									pItem->type->u.structure->type = node->syn_type;
								else 
									pItem->type->u.structure->type = pType;
								break;

							}

							FieldList p = pItem->type->u.structure;

							int find = 0;
							while (p->tail != NULL){
								if(strcmp(p->name,node->value_str)==0){
									printf("Error type:15 at %d line\n",node->lineno);
									find = 1;
								}
								p = p->tail;
							}
							if(strcmp(p->name,node->value_str)==0){
								printf("Error type:15 at %d line\n",node->lineno);
								find = 1;
							}
							if(find == 0){
								FieldList item = (FieldList)malloc(sizeof(struct FieldList_));
								item->name = (char*)malloc(sizeof(char)*20);
								strncpy(item->name,node->value_str,strlen(node->value_str));
								if (node->syn_type != NULL)
									item->type = node->syn_type;
								else 
									item->type = pType;
								item->tail = NULL;
								p->tail = item;
							}
							break;
						}
				//函数参数定义。
				case 3:	{

							if (pFunc->func_dec == 0 || pFunc->func_dec == 1){
								FieldList p = pFunc->type->u.function;
								while(p->tail != NULL)
									p = p->tail;
								FieldList item = (FieldList)malloc(sizeof(struct FieldList_));
								item->name = (char*)malloc(sizeof(char)*20);
								strncpy(item->name,node->value_str,strlen(node->value_str));
								if (node->syn_type != NULL)
									item->type = node->syn_type ;
								else 
									item->type = pType;
								item->tail = NULL;
								p->tail = item;
							}
							else {
									if (pCmp->type == NULL)
										printf("Error type:19 at %d line\n",node->lineno);
									else {
										if (compType(pType,pCmp->type) != 1)
											printf("Error type:19 at %d line\n",node->lineno);
										pCmp = pCmp->tail;
									}
								}
							break;
						}
				//函数定义
				case 4:	{
							FieldList index;
							if (lookupTable(node->value_str,&index,1) == 1 ){
								if (index->func_dec == 2)
									printf("Error type:4 at %d line\n",node->lineno);

								else{
									pFunc = index;
									pCmp = index->type->u.function->tail;

									if (compType(pType,index->type->u.function->type) != 1)
										printf("Error type:19 at %d line\n",node->lineno);

								}
							}
							else{
								index = (FieldList)malloc(sizeof(struct FieldList_));
								index->name = (char*)malloc(sizeof(char)*20);
								index->type = (Type)malloc(sizeof(struct Type_));
								strncpy(index->name,node->value_str,strlen(node->value_str));
								index->type->kind = 3;
								index->type->u.function = (FieldList)malloc(sizeof(struct FieldList_));
								index->type->u.function->type = pType;
								index->type->u.function->tail = NULL;
								index->func_dec = 1;
								index->func_lineno = node->lineno;
								addItem(index);
								pFunc = index;
								index->func_dec = 1;
							}
							break;
					}
				//函数声明
				case 5:	{
							FieldList index;
							if (lookupTable(node->value_str,&index,1) == 1 ){
								pFunc = index;
								pCmp = index->type->u.function->tail;
								if (compType(pType,index->type->u.function->type) != 1)
									printf("Error type:19 at %d line\n",node->lineno);
							}
							else{
								index = (FieldList)malloc(sizeof(struct FieldList_));
								index->name = (char*)malloc(sizeof(char)*20);
								strncpy(index->name,node->value_str,strlen(node->value_str));
								index->type = (Type)malloc(sizeof(struct Type_));
								index->type->kind = 3;
								index->type->u.function = (FieldList)malloc(sizeof(struct FieldList_));
								index->type->u.function->type = pType;
								index->type->u.function->tail = NULL;
								index->func_dec = 0;
								index->func_lineno = node->lineno;
								addItem(index);
								pFunc = index;
								index->func_dec = 0;
						}
						break;
					}
				//使用变量
				case 6:	{
							FieldList index;
							if (lookupTable(node->value_str,&index,0) == 1 ){
								node->syn_type = index->type;
							}
							else{
								FieldList temp = pFunc->type->u.function->tail;
								while(temp != NULL){
									if(strcmp(temp->name,node->value_str) == 0){
										node->syn_type = temp->type;
										break;
									}
									temp = temp->tail;
								}
								if(temp == NULL)
									printf("Error type:1 at %d line\n",node->lineno);
							}
							break;
						}
				//函数调用
				case 7:	{
							if (strcmp(node->value_str,"read") == 0  || strcmp(node->value_str,"write") == 0){
								node->syn_type = (Type)malloc(sizeof(struct Type_));
								node->syn_type->kind = 999;
								break;
							}
							FieldList index;                           //
							if (lookupTable(node->value_str,&index,1) == 1 ){
							// &&( index->func_dec == 2) ){ 	
								node->syn_type = index->type;
							}
							else
								printf("Error type:11 at %d line\n",node->lineno);
							break;
						}

			}
		}
		else if(strcmp(node->name,"Exp")==0){
			struct TreeNode *p = node->children;

			if	(strcmp(p->name,"INT")==0){
				node->syn_type = (Type)malloc(sizeof(struct Type_));
				node->syn_type->kind = basic;
				node->syn_type->u.basic = 0;
				return;
			}

			else if	(strcmp(p->name,"FLOAT")==0){
				node->syn_type = (Type)malloc(sizeof(struct Type_));
				node->syn_type->kind = basic;
				node->syn_type->u.basic = 1;
				return;
			}

			else if	(strcmp(p->name,"ID")==0 && p->neighbours == NULL){
				node->syn_type = p->syn_type;
				return;
			}

			else if	(strcmp(p->name,"ID")==0 && strcmp(p->neighbours->name,"DOT")==0){
				struct TreeNode *pp = p->neighbours->neighbours;
				if (pp->syn_type->kind != 2)
					printf("Error type:13 at %d line\n",node->lineno);
				else{
					FieldList temp = pp->syn_type->u.structure;
					while( temp!= NULL){
						if	(strcmp(temp->name,p->value_str)==0)
							break;
						else
							temp = temp->tail;
					}

					if (temp == NULL){
						printf("Error type:14 at %d line\n",node->lineno);
					}
					else{
						node->syn_type = temp->type;
					}
				}
				return;
			}

			else if (strcmp(p->name,"RB")==0 ){
				struct TreeNode *pp = p->neighbours;

				if (pp->syn_type->kind != 0 || pp->syn_type->u.basic != 0)
					printf("Error type:12 at %d line\n",node->lineno);

				else{
					pp = pp->neighbours->neighbours;

					if ( pp->syn_type->kind != 1)
						printf("Error type:10 at %d line\n",node->lineno);

					else{
						node->syn_type = pp->syn_type->u.array.elem;
					}
				}
				return;
			}

			else if (strcmp(p->name,"RP")==0 && strcmp(p->neighbours->name,"LP") == 0){
				struct TreeNode *pp = p->neighbours->neighbours;
				if (pp->syn_type->kind == 999){
					node->syn_type = pp->syn_type;
					return;
				}
				if ( pp->syn_type->kind != 3)
					printf("Error type:11 at %d line\n",node->lineno);

				else{
					node->syn_type = pp->syn_type->u.function->type;
					if (  pp->syn_type->u.function->tail != NULL )
						printf("Error type:9 at %d line\n",node->lineno);
				}
				return;
			}

			else if (strcmp(p->name,"RP")==0 && strcmp(p->neighbours->name,"Args")==0){
				struct TreeNode *pp = p->neighbours->neighbours->neighbours;
				if (pp->syn_type->kind == 999){
					node->syn_type = pp->syn_type;
					return;
				}
				if ( pp->syn_type == NULL)
					return;

				else{
					node->syn_type = pp->syn_type->u.function->type;
					pp = p->neighbours->neighbours->neighbours;
					if (compFieldList(p->neighbours->syn_type->u.function,pp->syn_type->u.function->tail) != 1)
						printf("Error type:9 at %d line\n",node->lineno);
				}
				return;
			}

			if (strcmp(p->name,"Exp")==0 && strcmp(p->neighbours->name,"NOT")==0){
				node->syn_type = p->syn_type;
				return;
			}

			else if (strcmp(p->name,"Exp")==0 && strcmp(p->neighbours->name,"MINUS")==0 && p->neighbours->neighbours == NULL){
				node->syn_type = p->syn_type;
				return;
			}

			else if (strcmp(p->name,"RP")==0 && strcmp(p->neighbours->name,"Exp")==0){
				node->syn_type = p->neighbours->syn_type;
				return;
			}

			else if (strcmp(p->neighbours->name,"DIV")==0 || strcmp(p->neighbours->name,"STAR")==0 || strcmp(p->neighbours->name,"MINUS")==0 || strcmp(p->neighbours->name,"PLUS")==0 ||strcmp(p->neighbours->name,"RELOP")==0 ||strcmp(p->neighbours->name,"OR")==0 || strcmp(p->neighbours->name,"AND")==0 || strcmp(p->neighbours->name,"ASSIGNOP")==0){
				if (p->syn_type == NULL || p->neighbours->neighbours->syn_type == NULL)
					return;
				struct TreeNode *lval = p->neighbours->neighbours->children;
				if ( lval->neighbours == NULL && strcmp(p->neighbours->name,"ASSIGNOP") == 0 )
					if (strcmp(lval->name,"INT")== 0 ){
						printf("Error type:6 at %d line\n",node->lineno);
						return;
					}
					else if (strcmp(lval->name,"FLOAT") == 0){
						printf("Error type:6 at %d line\n",node->lineno);
						return;
					}
					else if (strcmp(lval->name,"ID") == 0 && lval->srcop == 7){
						printf("Error type:6 at %d line\n",node->lineno);
						return;
					}
				if (compType(p->syn_type,p->neighbours->neighbours->syn_type) != 1){
					if (strcmp(p->neighbours->name,"ASSIGNOP")==0)
						printf("Error type:5 at %d line\n",node->lineno);
					else
						printf("Error type:7 at %d line\n",node->lineno);
				}
				node->syn_type = p->neighbours->neighbours->syn_type;
			}
			return;

		}


		else if(strcmp(node->name,"Stmt")==0 && node->children != NULL){

			struct TreeNode *p = node->children;

			if (strcmp(p->name,"SEMI") == 0  && strcmp(p->neighbours->name,"Exp") == 0 ){
				if (p->neighbours->neighbours != NULL ){
					p = p->neighbours;

					if (compType(pFunc->type->u.function->type,p->syn_type) != 1)

						printf("Error type:8 at %d line\n",node->lineno);
				}
			}
			return;

		}

		else if(strcmp(node->name,"Dec")==0){

			struct TreeNode *p = node->children;
			if (strcmp(p->name,"Exp") == 0  && strcmp(p->neighbours->name,"ASSIGNOP") == 0 && strcmp(p->neighbours->neighbours->name,"VarDec") == 0  ){
					if (op == 2)
						printf("Error type:15 at %d line\n",node->lineno);
			}
		}

		else if(strcmp(node->name,"Args")==0){

			struct TreeNode *p = node->children;
			if (strcmp(p->name,"Exp") == 0){
				node->syn_type = (Type)malloc(sizeof(struct Type_));
				node->syn_type->kind = 3;
				node->syn_type->u.function = (FieldList)malloc(sizeof(struct FieldList_));
				node->syn_type->u.function->type = p->syn_type;
				node->syn_type->u.function->tail = NULL;
			}
			else {
					FieldList temp = (FieldList)malloc(sizeof(struct FieldList_));
					temp->type = p->neighbours->neighbours->syn_type;
					temp->tail = p->syn_type->u.function;
					node->syn_type = (Type)malloc(sizeof(struct Type_));
					node->syn_type->kind = 3;
					node->syn_type->u.function = temp;
				}
		}

		else if(strcmp(node->name,"ExtDef")==0 && node->children != NULL){
			struct TreeNode *p = node->children;

			if (strcmp(p->name,"CompSt") == 0 )
				pFunc->func_dec = 2;

			else if (strcmp(p->name,"SEMI") == 0 && strcmp(p->neighbours->name,"FunDec")==0){
				if (pFunc->func_dec != 2)
					pFunc->func_dec = 3;
			}

		}

	return;
}

int  lookupTable(char *name,FieldList *t,int way){
	FieldList h = symbol_table;
	while ( h != NULL){
		if (strcmp(name,h->name)==0 ){
			if (way == 1) //0表示查找变量，1表示查找函数。
				if (h->type->kind == 3){
					*t = h;
					return 1;
				}
			if (way == 0)
				if (h->type->kind != 3){
					*t = h;
					return 1;
				}
		}
		h = h->tail;

	}
	*t= NULL;
	return -1;
}

void addItem(FieldList newItem){

	newItem->tail = symbol_table;
	symbol_table = newItem;
	return;
}

int compType(Type a, Type b){
	if (a == NULL || b == NULL)
		return 0;
	if (a->kind == 999 || b->kind == 999)
		return 1;
	if(a->kind != b->kind){
		return 0;
	}
	else{
		switch(a->kind){
			case 0:{
				if(a->u.basic == b->u.basic){
					return 1;
				}
				else{
					return 0;
				}
				}
			case 1:{
				if(compType(a->u.array.elem, b->u.array.elem)){
					return 1;
				}
				else{
					return 0;
				}
			}
			case 2:{
				FieldList temp_a = a->u.structure;
				FieldList temp_b = b->u.structure;
				while(temp_a != NULL && temp_b != NULL){
					if(compType(temp_a->type, temp_b->type)){
						temp_a = temp_a->tail;
						temp_b = temp_b->tail;
					}
					else{
						return 0;
					}
				}
				if(temp_a != NULL || temp_b != NULL){
					return 0;
				}
				else{
					return 1;
				}
			}
		}
	}
}
int compFieldList(FieldList a, FieldList b){
	FieldList temp_a = a;
	FieldList temp_b = b;
	while(temp_a != NULL && temp_b != NULL){
		if(compType(temp_a->type, temp_b->type)){
			temp_a = temp_a->tail;
			temp_b = temp_b->tail;
		}
		else{
			return 0;
		}
	}
	if(temp_a != NULL || temp_b != NULL){
		return 0;
	}
	else{
		return 1;
	}
}

  /*3rd code
  */
  /////////////////////////////
  

Operand new_temp(){
	static int used_no = 0;
	Operand newop = (Operand)malloc(sizeof(struct Operand_));
	memset(newop,0,sizeof(struct Operand_));
	sprintf(newop->u.ID,"t%d",used_no);
	used_no++;
	return newop;
}

Operand new_label(){
	static int used_label = 1;
	Operand newLabel = (Operand)malloc(sizeof(struct Operand_));
	memset(newLabel,0,sizeof(struct Operand_));
	sprintf(newLabel->u.ID,"label%d",used_label);
	used_label++;
	return newLabel;
}

void printCode(struct InterCodes *root, FILE *fp){

	while (root != NULL){
		switch (root->code.kind){
			case ASSIGN_:
						printOperand(root->code.u.assign.left,fp);
						fprintf(fp,":= ");
						printOperand(root->code.u.assign.right,fp);
						fprintf(fp,"\n");
						break;
			case ADD_:
						printOperand(root->code.u.binop.result,fp);
						fprintf(fp,":= ");
						printOperand(root->code.u.binop.op1,fp);
						fprintf(fp,"+ ");
						printOperand(root->code.u.binop.op2,fp);
						fprintf(fp,"\n");
						break;
			case SUB_:
						printOperand(root->code.u.binop.result,fp);
						fprintf(fp,":= ");
						printOperand(root->code.u.binop.op1,fp);
						fprintf(fp,"- ");
						printOperand(root->code.u.binop.op2,fp);
						fprintf(fp,"\n");
						break;
			case MUL_:
						printOperand(root->code.u.binop.result,fp);
						fprintf(fp,":= ");
						printOperand(root->code.u.binop.op1,fp);
						fprintf(fp,"* ");
						printOperand(root->code.u.binop.op2,fp);
						fprintf(fp,"\n");
						break;
			case DIV_:
						printOperand(root->code.u.binop.result,fp);
						fprintf(fp,":= ");
						printOperand(root->code.u.binop.op1,fp);
						fprintf(fp,"/ ");
						printOperand(root->code.u.binop.op2,fp);
						fprintf(fp,"\n");
						break;
			case MINUS_:;
						printf("occur MINUS \n");
						break;
			case IF_:
						fprintf(fp,"IF ");
						printOperand(root->code.u.ifcode.op1,fp);
						fprintf(fp,"%s ",root->code.u.ifcode.op_type);
						printOperand(root->code.u.ifcode.op2,fp);
						fprintf(fp," GOTO ");
						printOperand(root->code.u.ifcode.label,fp);
						fprintf(fp,"\n");
						break;
			case GOTO_:
						fprintf(fp,"GOTO ");
						printOperand(root->code.u.gotocode.label,fp);
						fprintf(fp,"\n");
						break;
			case LABEL_:
						fprintf(fp,"LABEL ");
						printOperand(root->code.u.labelcode.label,fp);
						fprintf(fp,": ");
						fprintf(fp,"\n");
						break;
			case RETURN_:
						fprintf(fp,"RETURN ");
						printOperand(root->code.u.returncode.r,fp);
						fprintf(fp,"\n");
						break;
			case READ_:
						fprintf(fp,"READ ");
						printOperand(root->code.u.read.rd,fp);
						fprintf(fp,"\n");
						break;
			case WRITE_:
						fprintf(fp,"WRITE ");
						printOperand(root->code.u.write.wr,fp);
						fprintf(fp,"\n");
						break;
			case ARG_:
						fprintf(fp,"ARG  ");
						printOperand(root->code.u.arg.argument,fp);
						fprintf(fp,"\n");
						break;
			case CALL_:
						printOperand(root->code.u.call.left,fp);
						fprintf(fp,":= CALL ");
						printOperand(root->code.u.call.function,fp);
						fprintf(fp,"\n");
						break;
			case DEC_:
						fprintf(fp,"DEC ");
						printOperand(root->code.u.dec.space,fp);
						fprintf(fp,"%d ",root->code.u.dec.size);
						fprintf(fp,"\n");
						break;
			case FUNCTION_:
						fprintf(fp,"FUNCTION ");
						fprintf(fp,"%s :",root->code.u.function.func);
						fprintf(fp,"\n");
						break;
			case PARAM_:
						fprintf(fp,"PARAM ");
						printOperand(root->code.u.param.op,fp);
						fprintf(fp,"\n");
			case NONE_:
						break;
			default : printf("undifined  op\n");
		}
		root = root->next;
	}
}

void printOperand(Operand op, FILE *fp){
	switch (op->kind){
		case VARIABLE:
						fprintf(fp,"%s ",op->u.ID);
						break;
		case CONSTANT:
						fprintf(fp,"#%d ",op->u.value);
						break;
		case ADDRESS:
						fprintf(fp,"&%s ",op->u.ID);
						break;
		case REFERENCE:
						fprintf(fp,"*%s ",op->u.ID);
						break;
		case GOTOOP:
						fprintf(fp,"%s ",op->u.ID);
						break;
		case LABELOP:
						fprintf(fp,"%s ",op->u.ID);
						break;
		case RETURNOP:
						fprintf(fp,"%s ",op->u.ID);
						break;
	}
}


int dec_size(Type item){
	if (item->kind == basic)
		return 4;
	else if (item->kind == array)
		return item->u.array.size * dec_size(item->u.array.elem);
	else if (item->kind == variable){
		int total = 0;
		FieldList p = item->u.variable;
		while ( p != NULL){
			total += dec_size(p->type);
			p = p->tail;
		}
		return total;
	}
	else if (item->kind == structure){
		int total = 0;
		FieldList p = item->u.structure;
		while ( p != NULL){
			total += dec_size(p->type);
			p = p->tail;
		}
		return total;
	}
	return -1;
}



int index_size(FieldList father,char *memberName){
	int index = 0;
	FieldList p = father->type->u.structure;
	while (p != NULL && strcmp(p->name,memberName) != 0){
			index +=  dec_size(p->type);
			p = p->tail;
		}
	return index;
}

int  newlookupTable(char *name,FieldList *t,int way){
	if (lookupTable(name,t,way) == 1 )
			return 1;
	else{
			FieldList temp = pFunc->type->u.function->tail;
			while(temp != NULL){
				if(strcmp(temp->name,name) == 0){
					*t = temp;
					return 0;
				}
				temp = temp->tail;
			}

		}
	return -1;
}

struct InterCodes* GenerateInterCode(struct TreeNode* root){
	return translate_ExtDefList(root->children);
}

//符号表是全局变量
struct InterCodes* translate_Exp(struct TreeNode* Exp, Operand place){
	if (strcmp(Exp->children->name, "RP") == 0 && strcmp(Exp->children->neighbours->name, "Exp") == 0 && strcmp(Exp->children->neighbours->neighbours->name, "LP") == 0){
		return translate_Exp(Exp->children->neighbours, place);
	}
	if (strcmp(Exp->children->name, "INT") == 0){
		//printf("Exp - INT\n");
		if(place != NULL){
			FieldList item = (FieldList)malloc(sizeof(struct FieldList_));
			newlookupTable(Exp->children->value_str,&item,0);

			place->kind = CONSTANT;
			place->u.value = Exp->children->value_int;

			struct InterCodes* temp = (struct InterCodes*)malloc(sizeof(struct InterCodes));
			temp->code.kind = NONE_;
			return temp;
		}
		else{
			struct InterCodes* temp = (struct InterCodes*)malloc(sizeof(struct InterCodes));
			temp->code.kind = NONE_;
			return temp;
		}
	}
	if (strcmp(Exp->children->name, "ID") == 0){
		if(Exp->children->neighbours == NULL){
			//printf("Exp - ID\n");
			if(place != NULL){
				FieldList item = (FieldList)malloc(sizeof(struct FieldList_));
				newlookupTable(Exp->children->value_str,&item,0);

				place->kind = VARIABLE;
				strcpy(place->u.ID, item->inter_name);

				struct InterCodes* temp = (struct InterCodes*)malloc(sizeof(struct InterCodes));
				temp->code.kind = NONE_;
				return temp;
			}
			else{
				struct InterCodes* temp = (struct InterCodes*)malloc(sizeof(struct InterCodes));
				temp->code.kind = NONE_;
				return temp;
			}
		}
		if(strcmp(Exp->children->neighbours->name, "DOT") == 0){
			//printf("Exp - Exp DOT ID\n");
			//Operand t1 = new_temp();
			//struct InterCodes* code1 = translate_Exp(Exp->children->neighbours->neighbours, t1);

			FieldList item = (FieldList)malloc(sizeof(struct FieldList_));
			int i = newlookupTable(Exp->children->neighbours->neighbours->children->value_str,&item,0);
			switch(i){
				case 0:{
					Operand t1 = new_temp();
					struct InterCodes* code1 = (struct InterCodes*)malloc(sizeof(struct InterCodes));
					code1->code.kind = ADD_;
					code1->code.u.binop.result = t1;
					code1->code.u.binop.op1 = (Operand)malloc(sizeof(struct Operand_));
					code1->code.u.binop.op1->kind = VARIABLE;
					strcpy(code1->code.u.binop.op1->u.ID, item->inter_name);
					code1->code.u.binop.op2 = (Operand)malloc(sizeof(struct Operand_));
					code1->code.u.binop.op2->kind = CONSTANT;
					code1->code.u.binop.op2->u.value = index_size(item, Exp->children->value_str);

					place->kind = REFERENCE;
					strcpy(place->u.ID, t1->u.ID);

					return code1;
					//break;
				}
				case 1:{
					Operand t1 = new_temp();
					Operand t2 = new_temp();

					struct InterCodes* code1 = (struct InterCodes*)malloc(sizeof(struct InterCodes));
					code1->code.kind = ASSIGN_;
					code1->code.u.assign.left = t1;
					code1->code.u.assign.right = (Operand)malloc(sizeof(struct Operand_));
					code1->code.u.assign.right->kind = ADDRESS;
					strcpy(code1->code.u.assign.right->u.ID, item->inter_name);

					struct InterCodes* code2 = (struct InterCodes*)malloc(sizeof(struct InterCodes));
					code2->code.kind = ADD_;
					code2->code.u.binop.result = t2;
					code2->code.u.binop.op1 = t1;
					code2->code.u.binop.op2 = (Operand)malloc(sizeof(struct Operand_));
					code2->code.u.binop.op2->kind = CONSTANT;
					code2->code.u.binop.op2->u.value = index_size(item, Exp->children->value_str);

					place->kind = REFERENCE;
					strcpy(place->u.ID, t2->u.ID);

					code1->next = code2;
					code2->prev = code1;

					return code1;
				}
			}
		}
	}
	if (strcmp(Exp->children->name, "Exp") == 0){
		if (strcmp(Exp->children->neighbours->name, "ASSIGNOP") == 0){
			//printf("Exp - Exp ASSIGNOP Exp\n");
			if(place != NULL){
				Operand t1 = new_temp();
				Operand t2 = new_temp();

				struct InterCodes* code1 = translate_Exp(Exp->children, t1);
				struct InterCodes* code2 = translate_Exp(Exp->children->neighbours->neighbours, t2);
				struct InterCodes* code3 = (struct InterCodes*)malloc(sizeof(struct InterCodes));
				code3->code.kind = ASSIGN_;
				code3->code.u.assign.left = t2;
				code3->code.u.assign.right = t1;

				/*struct InterCodes* code3 = (struct InterCodes*)malloc(sizeof(struct InterCodes));
				code3->code.kind = ASSIGN;
				code3->code.u.assign.left = (Operand)malloc(sizeof(struct Operand_));
				code3->code.u.assign.left->kind = VARIABLE;
				strcpy(code3->code.u.assign.left->u.ID, place->u.ID);
				code3->code.u.assign.right = (Operand)malloc(sizeof(struct Operand_));
				code3->code.u.assign.right->kind = VARIABLE;
				strcpy(code3->code.u.assign.right->u.ID, Exp->children->neighbours->neighbours->children->inter_name);*/

				place->kind = VARIABLE;
				strcpy(place->u.ID, t2->u.ID);

				struct InterCodes* p = code1;
				while(p->next != NULL)
					p = p->next;
				p->next = code2;
				code2->prev = p;
				
				p = code2;
				while(p->next != NULL)
					p = p->next;
				p->next = code3;
				code3->prev = p;
				code3->next = NULL;

				return code1;
			}
			else{
				struct InterCodes* code1 = (struct InterCodes*)malloc(sizeof(struct InterCodes));
				code1->code.kind = NONE_;
				return code1;
			}
		}
		if(strcmp(Exp->children->neighbours->name, "PLUS") == 0){
			//printf("Exp - Exp PLUS Exp\n");
			if(place != NULL){
				Operand t1 = new_temp();
				Operand t2 = new_temp();
				struct InterCodes* code1 = translate_Exp(Exp->children->neighbours->neighbours, t1);
				struct InterCodes* code2 = translate_Exp(Exp->children, t2);		
				struct InterCodes* code3 = (struct InterCodes*)malloc(sizeof(struct InterCodes));
				code3->code.kind = ADD_;
				code3->code.u.binop.result = (Operand)malloc(sizeof(struct Operand_));
				code3->code.u.binop.result->kind = VARIABLE;
				strcpy(code3->code.u.binop.result->u.ID, place->u.ID);
				code3->code.u.binop.op1 = t1;
				code3->code.u.binop.op2 = t2;

				struct InterCodes* p = code1;
				while(p->next != NULL)
					p = p->next;
				p->next = code2;

				code2->prev = p;
				p = code2;
				while(p->next != NULL)
					p = p->next;
				p->next = code3;
				code3->prev = p;

				code3->next = NULL;

				return code1;
			}
			else{
				Operand t1 = new_temp();
				Operand t2 = new_temp();
				struct InterCodes* code1 = translate_Exp(Exp->children->neighbours->neighbours, t1);
				struct InterCodes* code2 = translate_Exp(Exp->children, t2);

				struct InterCodes* p = code1;
				while(p->next != NULL)
					p = p->next;
				p->next = code2;
				code2->prev = p;

				code2->next = NULL;

				return code1;
			}
		}
		if(strcmp(Exp->children->neighbours->name, "MINUS") == 0){
			//printf("Exp - Exp MINUS Exp\n");
			if(place != NULL){
				if(Exp->children->neighbours->neighbours != NULL){
					Operand t1 = new_temp();
					Operand t2 = new_temp();
					struct InterCodes* code1 = translate_Exp(Exp->children->neighbours->neighbours, t1);
					struct InterCodes* code2 = translate_Exp(Exp->children, t2);
					struct InterCodes* code3 = (struct InterCodes*)malloc(sizeof(struct InterCodes));
					code3->code.kind = SUB_;
					code3->code.u.binop.result = (Operand)malloc(sizeof(struct Operand_));
					code3->code.u.binop.result->kind = VARIABLE;
					strcpy(code3->code.u.binop.result->u.ID, place->u.ID);
					code3->code.u.binop.op1 = t1;
					code3->code.u.binop.op2 = t2;

					struct InterCodes* p = code1;
					while(p->next != NULL)
						p = p->next;
					p->next = code2;

					code2->prev = p;
					p = code2;
					while(p->next != NULL)
						p = p->next;
					p->next = code3;
					code3->prev = p;

					code3->next = NULL;

					return code1;
				}
				else{
					Operand t1 = new_temp();
					struct InterCodes* code1 = translate_Exp(Exp->children, t1);
					struct InterCodes* code2 = (struct InterCodes*)malloc(sizeof(struct InterCodes));
					code2->code.kind = SUB_;
					code2->code.u.binop.result = (Operand)malloc(sizeof(struct Operand_));
					code2->code.u.binop.result->kind = VARIABLE;
					strcpy(code2->code.u.binop.result->u.ID, place->u.ID);
					code2->code.u.binop.op1 = (Operand)malloc(sizeof(struct Operand_));
					code2->code.u.binop.op1->kind = CONSTANT;
					code2->code.u.binop.op1->u.value = 0;
					code2->code.u.binop.op2 = t1;

					struct InterCodes* p = code1;
					while(p->next != NULL)
						p = p->next;
					p->next = code2;
					code2->prev = p;

					code2->next = NULL;

					return code1;
				}
			}
			else{
				if(Exp->children->neighbours->neighbours != NULL){
					Operand t1 = new_temp();
					Operand t2 = new_temp();
					struct InterCodes* code1 = translate_Exp(Exp->children->neighbours->neighbours, t1);
					struct InterCodes* code2 = translate_Exp(Exp->children, t2);

					struct InterCodes* p = code1;
					while(p->next != NULL)
						p = p->next;
					p->next = code2;
					code2->prev = p;

					code2->next = NULL;

					return code1;
				}
				else{
					Operand t1 = new_temp();
					struct InterCodes* code1 = translate_Exp(Exp->children, t1);

					return code1;
				}
			}
		}
		if(strcmp(Exp->children->neighbours->name, "STAR") == 0){
			//printf("Exp - Exp STAR Exp\n");
			if(place != NULL){
				Operand t1 = new_temp();
				Operand t2 = new_temp();
				struct InterCodes* code1 = translate_Exp(Exp->children->neighbours->neighbours, t1);
				struct InterCodes* code2 = translate_Exp(Exp->children, t2);		
				struct InterCodes* code3 = (struct InterCodes*)malloc(sizeof(struct InterCodes));
				code3->code.kind = MUL_;
				code3->code.u.binop.result = (Operand)malloc(sizeof(struct Operand_));
				code3->code.u.binop.result->kind = VARIABLE;
				strcpy(code3->code.u.binop.result->u.ID, place->u.ID);
				code3->code.u.binop.op1 = t1;
				code3->code.u.binop.op2 = t2;

				struct InterCodes* p = code1;
				while(p->next != NULL)
					p = p->next;
				p->next = code2;

				code2->prev = p;
				p = code2;
				while(p->next != NULL)
					p = p->next;
				p->next = code3;
				code3->prev = p;

				code3->next = NULL;

				return code1;
			}
			else{
				Operand t1 = new_temp();
				Operand t2 = new_temp();
				struct InterCodes* code1 = translate_Exp(Exp->children->neighbours->neighbours, t1);
				struct InterCodes* code2 = translate_Exp(Exp->children, t2);

				struct InterCodes* p = code1;
				while(p->next != NULL)
					p = p->next;
				p->next = code2;
				code2->prev = p;

				code2->next = NULL;

				return code1;
			}
		}
		if(strcmp(Exp->children->neighbours->name, "DIV") == 0){
			//printf("Exp - Exp DIV Exp\n");
			if(place != NULL){
				Operand t1 = new_temp();
				Operand t2 = new_temp();
				struct InterCodes* code1 = translate_Exp(Exp->children->neighbours->neighbours, t1);
				struct InterCodes* code2 = translate_Exp(Exp->children, t2);
				struct InterCodes* code3 = (struct InterCodes*)malloc(sizeof(struct InterCodes));
				code3->code.kind = DIV_;
				code3->code.u.binop.result = (Operand)malloc(sizeof(struct Operand_));
				code3->code.u.binop.result->kind = VARIABLE;
				strcpy(code3->code.u.binop.result->u.ID, place->u.ID);
				code3->code.u.binop.op1 = t1;
				code3->code.u.binop.op2 = t2;

				struct InterCodes* p = code1;
				while(p->next != NULL)
					p = p->next;
				p->next = code2;

				code2->prev = p;
				p = code2;
				while(p->next != NULL)
					p = p->next;
				p->next = code3;
				code3->prev = p;

				code3->next = NULL;

				return code1;
			}
			else{
				Operand t1 = new_temp();
				Operand t2 = new_temp();
				struct InterCodes* code1 = translate_Exp(Exp->children->neighbours->neighbours, t1);
				struct InterCodes* code2 = translate_Exp(Exp->children, t2);

				struct InterCodes* p = code1;
				while(p->next != NULL)
					p = p->next;
				p->next = code2;
				code2->prev = p;

				code2->next = NULL;

				return code1;
			}
		}
		if(strcmp(Exp->children->neighbours->name, "RELOP") == 0 || strcmp(Exp->children->neighbours->name, "NOT") == 0 || strcmp(Exp->children->neighbours->name, "AND") == 0 || strcmp(Exp->children->neighbours->name, "OR") == 0){
			//printf("Exp - Exp Cond Exp\n");
			if(place != NULL){
				Operand label1 = new_label();
				Operand label2 = new_label();
				struct InterCodes* code1 = (struct InterCodes*)malloc(sizeof(struct InterCodes));
				code1->code.kind = ASSIGN_;
				code1->code.u.assign.left = (Operand)malloc(sizeof(struct Operand_));
				code1->code.u.assign.left->kind = VARIABLE;
				strcpy(code1->code.u.assign.left->u.ID, place->u.ID);
				code1->code.u.assign.right = (Operand)malloc(sizeof(struct Operand_));
				code1->code.u.assign.right->kind = CONSTANT;
				code1->code.u.assign.right->u.value = 0;
				struct InterCodes* code2 = translate_Cond(Exp, label1, label2);
				struct InterCodes* code3 = (struct InterCodes*)malloc(sizeof(struct InterCodes));
				code3->code.kind = LABEL_;
				code3->code.u.labelcode.label = label1;
				struct InterCodes* code4 = (struct InterCodes*)malloc(sizeof(struct InterCodes));
				code4->code.kind = ASSIGN_;
				code4->code.u.assign.left = (Operand)malloc(sizeof(struct Operand_));
				code4->code.u.assign.left->kind = VARIABLE;
				strcpy(code4->code.u.assign.left->u.ID, place->u.ID);
				code4->code.u.assign.right = (Operand)malloc(sizeof(struct Operand_));
				code4->code.u.assign.right->kind = CONSTANT;
				code4->code.u.assign.right->u.value = 1;
				struct InterCodes* code5 = (struct InterCodes*)malloc(sizeof(struct InterCodes));
				code5->code.kind = LABEL_;
				code5->code.u.labelcode.label = label2;

				code1->next = code2;
				code2->prev = code1;
				struct InterCodes* p = code2;
				while(p->next != NULL)
					p = p->next;
				p->next = code3;
				code3->prev = p;

				code3->next = code4;
				code4->prev = code3;

				code4->next = code5;
				code5->prev = code4;

				code5->next = NULL;

				return code1;
			}
		}
	}
	if (strcmp(Exp->children->neighbours->name, "LP") == 0){
		//printf("Exp - ID LP RP\n");
		if(strcmp(Exp->children->neighbours->neighbours->value_str, "read") == 0){
			struct InterCodes* code1 = (struct InterCodes*)malloc(sizeof(struct InterCodes));
			code1->code.kind = READ_;
			code1->code.u.read.rd = place;
			return code1;
		}
		else{
			FieldList item = (FieldList)malloc(sizeof(struct FieldList_));
			newlookupTable(Exp->children->neighbours->neighbours->value_str,&item,1);//查函数
			struct InterCodes* code1 = (struct InterCodes*)malloc(sizeof(struct InterCodes));
			code1->code.kind = CALL_;
			code1->code.u.call.left = (Operand)malloc(sizeof(struct Operand_));
			code1->code.u.call.left->kind = VARIABLE;
			strcpy(code1->code.u.call.left->u.ID, place->u.ID);
			code1->code.u.call.function = (Operand)malloc(sizeof(struct Operand_));
			code1->code.u.call.function->kind = VARIABLE;
			strcpy(code1->code.u.call.function->u.ID, item->name);
			return code1;
		}
	}
	if(strcmp(Exp->children->neighbours->name, "Args") == 0){
		//printf("Exp - ID LP Args RP\n");
		struct ArgList* arg_list = NULL;
		struct InterCodes* code1 = translate_Args(Exp->children->neighbours, &arg_list);
		if(strcmp(Exp->children->neighbours->neighbours->neighbours->value_str, "write") == 0){
			struct InterCodes* code2 = (struct InterCodes*)malloc(sizeof(struct InterCodes));
			code2->code.kind = WRITE_;
			code2->code.u.write.wr = arg_list->op;

			struct InterCodes* p = code1;
			while(p->next != NULL)
				p = p->next;
			p->next = code2;
			code2->prev = p;

			code2->next = NULL;

			return code1;
		}
		else{
			FieldList item = (FieldList)malloc(sizeof(struct FieldList_));
			newlookupTable(Exp->children->neighbours->neighbours->neighbours->value_str,&item,1);
			struct ArgList* q = arg_list;
			struct InterCodes* code2 = NULL;
			while(q != NULL){
				struct InterCodes* code3 = (struct InterCodes*)malloc(sizeof(struct InterCodes));
				code3->code.kind = ARG_;
				code3->code.u.arg.argument = q->op;
				if(code2 == NULL){
					code2 = code3;
				}
				else{
					struct InterCodes* p = code2;
					while(p->next != NULL)
						p = p->next;
					p->next = code3;
					code3->prev = p;
				}
				q = q->next;
			}
			struct InterCodes* code4 = (struct InterCodes*)malloc(sizeof(struct InterCodes));
			code4->code.kind = CALL_;
			code4->code.u.call.left = (Operand)malloc(sizeof(struct Operand_));
			code4->code.u.call.left->kind = VARIABLE;
			strcpy(code4->code.u.call.left->u.ID, place->u.ID);
			code4->code.u.call.function = (Operand)malloc(sizeof(struct Operand_));
			code4->code.u.call.function->kind = VARIABLE;
			strcpy(code4->code.u.call.function->u.ID, item->name);

			struct InterCodes* p = code1;
			while(p->next != NULL)
				p = p->next;
			p->next = code2;
			code2->prev = p;

			p = code2;
			while(p->next != NULL)
				p = p->next;
			p->next = code4;
			code4->prev = p;

			code4->next = NULL;

			return code1;
		}
	}
	if (strcmp(Exp->children->name, "RB") == 0){
		//printf("Exp - Exp LB Exp RB\n");
		FieldList item = (FieldList)malloc(sizeof(struct FieldList_));
		newlookupTable(Exp->children->neighbours->neighbours->neighbours->children->value_str,&item,0);

		Operand t1 = new_temp();
		Operand t2 = new_temp();
		Operand t3 = new_temp();

		struct InterCodes* code1 = translate_Exp(Exp->children->neighbours, t1);
		struct InterCodes* code2 = (struct InterCodes*)malloc(sizeof(struct InterCodes));
		code2->code.kind = MUL_;
		code2->code.u.binop.result = t2;
		code2->code.u.binop.op1 = t1;
		code2->code.u.binop.op2 = (Operand)malloc(sizeof(struct Operand_));
		code2->code.u.binop.op2->kind = CONSTANT;
		code2->code.u.binop.op2->u.value = 4;
		struct InterCodes* code3 = (struct InterCodes*)malloc(sizeof(struct InterCodes));
		code3->code.kind = ADD_;	
		code3->code.u.binop.result = t3;
		code3->code.u.binop.op1 = (Operand)malloc(sizeof(struct Operand_));
		code3->code.u.binop.op1->kind = ADDRESS;
		strcpy(code3->code.u.binop.op1->u.ID, item->inter_name);
		code3->code.u.binop.op2 = t2;
		//place = t4;
		place->kind = REFERENCE;
		strcpy(place->u.ID, t3->u.ID);

		struct InterCodes* p = code1;
		while(p->next != NULL)
			p = p->next;
		p->next = code2;
		code2->prev = p;

		code2->next = code3;
		code3->prev = code2;

		code3->next = NULL;

		return code1;
	}
}


struct InterCodes* translate_Stmt(struct TreeNode* Stmt){
	if (strcmp(Stmt->children->name, "SEMI") == 0){
		if(Stmt->children->neighbours->neighbours == NULL){
			Operand t1 = new_temp();
			//printf("Stmt - Exp SEMI\n");
			return translate_Exp(Stmt->children->neighbours, t1);
		}
		else{
			//printf("Stmt - RETURN Exp SEMI\n");
			Operand t1 = new_temp();
			struct InterCodes* code1 = translate_Exp(Stmt->children->neighbours, t1);
			struct InterCodes* code2 = (struct InterCodes*)malloc(sizeof(struct InterCodes));
			code2->code.kind = RETURN_;
			code2->code.u.returncode.r = t1;
			struct InterCodes* p = code1;
			while(p->next != NULL)
				p = p->next;
			p->next = code2;
			code2->prev = p;

			code2->next = NULL;

			return code1;
		}
	}
	if(strcmp(Stmt->children->name, "CompSt") == 0){
		//printf("Stmt - CompSt\n");
		return translate_CompSt(Stmt->children);
	}
	if(strcmp(Stmt->children->name, "Stmt") == 0){
		if(strcmp(Stmt->children->neighbours->neighbours->neighbours->neighbours->name, "IF") == 0){
			//printf("Stmt - IF LP Exp RP Stmt\n");
			Operand label1 = new_label();
			Operand label2 = new_label();
			struct InterCodes* code1 = translate_Cond(Stmt->children->neighbours->neighbours, label1, label2);
			struct InterCodes* code2 = translate_Stmt(Stmt->children);
			struct InterCodes* code3 = (struct InterCodes*)malloc(sizeof(struct InterCodes));
			code3->code.kind = LABEL_;
			code3->code.u.labelcode.label = label1;
			struct InterCodes* code4 = (struct InterCodes*)malloc(sizeof(struct InterCodes));
			code4->code.kind = LABEL_;
			code4->code.u.labelcode.label = label2;

			struct InterCodes* p = code1;
			while(p->next != NULL)
				p = p->next;
			p->next = code3;
			code3->prev = p;
			code3->next = code2;

			p = code2;
			while(p->next != NULL)
				p = p->next;
			p->next = code4;
			code4->prev = p;
			code4->next = NULL;

			return code1;
		}
		if(strcmp(Stmt->children->neighbours->neighbours->neighbours->neighbours->name, "WHILE") == 0){
			//printf("Stmt - WHILE LP Exp RP Stmt\n");
			Operand label1 = new_label();
			Operand label2 = new_label();
			Operand label3 = new_label();
			struct InterCodes* code1 = translate_Cond(Stmt->children->neighbours->neighbours, label2, label3);
			struct InterCodes* code2 = translate_Stmt(Stmt->children);
			struct InterCodes* code3 = (struct InterCodes*)malloc(sizeof(struct InterCodes));
			code3->code.kind = LABEL_;
			code3->code.u.labelcode.label = label1;
			struct InterCodes* code4 = (struct InterCodes*)malloc(sizeof(struct InterCodes));
			code4->code.kind = LABEL_;
			code4->code.u.labelcode.label = label2;
			struct InterCodes* code5 = (struct InterCodes*)malloc(sizeof(struct InterCodes));
			code5->code.kind = LABEL_;
			code5->code.u.labelcode.label = label3;
			struct InterCodes* code6 = (struct InterCodes*)malloc(sizeof(struct InterCodes));
			code6->code.kind = GOTO_;
			code6->code.u.gotocode.label = label1;

			code3->next = code1;
			code1->prev = code3;

			struct InterCodes* p = code1;
			while(p->next != NULL)
				p = p->next;
			p->next = code4;
			code4->prev = p;
			code4->next = code2;

			p = code2;
			while(p->next != NULL)
				p = p->next;
			p->next = code6;
			code6->prev = p;
			code6->next = code5;
			code5->prev = code6;

			code5->next = NULL;

			return code3;
		}
		if(strcmp(Stmt->children->neighbours->name, "ELSE") == 0){
			//printf("Stmt - IF LP Exp RP Stmt ELSE Stmt\n");
			Operand label1 = new_label();
			Operand label2 = new_label();
			Operand label3 = new_label();
			struct InterCodes* code1 = translate_Cond(Stmt->children->neighbours->neighbours->neighbours->neighbours, label1, label2);
			struct InterCodes* code2 = translate_Stmt(Stmt->children->neighbours->neighbours);
			struct InterCodes* code3 = translate_Stmt(Stmt->children);
			struct InterCodes* code4 = (struct InterCodes*)malloc(sizeof(struct InterCodes));
			code4->code.kind = LABEL_;
			code4->code.u.labelcode.label = label1;
			struct InterCodes* code5 = (struct InterCodes*)malloc(sizeof(struct InterCodes));
			code5->code.kind = LABEL_;
			code5->code.u.labelcode.label = label2;
			struct InterCodes* code6 = (struct InterCodes*)malloc(sizeof(struct InterCodes));
			code6->code.kind = LABEL_;
			code6->code.u.labelcode.label = label3;
			struct InterCodes* code7 = (struct InterCodes*)malloc(sizeof(struct InterCodes));
			code7->code.kind = GOTO_;
			code7->code.u.gotocode.label = label3;

			struct InterCodes* p = code1;
			while(p->next != NULL)
				p = p->next;
			p->next = code4;
			code4->prev = p;
			code4->next = code2;

			p = code2;
			while(p->next != NULL)
				p = p->next;
			p->next = code7;
			code7->prev = p;
			code7->next = code5;

			code5->prev = code7;
			code5->next = code3;

			p = code3;
			while(p->next != NULL)
				p = p->next;
			p->next = code6;
			code6->prev = p;
			code6->next = NULL;

			return code1;
		}
	}
}


struct InterCodes* translate_Cond(struct TreeNode* Exp, Operand label_true, Operand label_false){
	if(strcmp(Exp->children->name, "RP") == 0 && strcmp(Exp->children->neighbours->name, "Exp") == 0 && strcmp(Exp->children->neighbours->neighbours->name, "LP") == 0){
		return translate_Cond(Exp->children->neighbours,label_true,label_false);
	}
	if(strcmp(Exp->children->neighbours->name, "RELOP") == 0){
		//printf("Exp - Exp RELOP Exp\n");
		Operand t1 = new_temp();
		Operand t2 = new_temp();
		struct InterCodes* code1 = translate_Exp(Exp->children->neighbours->neighbours, t1);
		struct InterCodes* code2 = translate_Exp(Exp->children, t2);
		struct InterCodes* code3 = (struct InterCodes*)malloc(sizeof(struct InterCodes));
		code3->code.kind = IF_;
		code3->code.u.ifcode.op1 = t1;
		code3->code.u.ifcode.op2 = t2;
		code3->code.u.ifcode.label = label_true;
		strcpy(code3->code.u.ifcode.op_type, Exp->children->neighbours->value_str);
		struct InterCodes* code4 = (struct InterCodes*)malloc(sizeof(struct InterCodes));
		code4->code.kind = GOTO_;
		code4->code.u.gotocode.label = label_false;

		struct InterCodes* p = code1;
		while(p->next != NULL)
			p = p->next;
		p->next = code2;
		code2->prev = p;

		p = code2;
		while(p->next != NULL)
			p = p->next;
		p->next = code3;
		code3->prev = p;

		code3->next = code4;
		code4->prev = code3;

		code4->next = NULL;

		return code1;
	}
	if(strcmp(Exp->children->neighbours->name, "NOT") == 0){
		//printf("Exp - NOT Exp\n");
		return translate_Cond(Exp->children, label_false, label_true);
	}
	if(strcmp(Exp->children->neighbours->name, "AND") == 0){
		//printf("Exp - Exp AND Exp\n");
		Operand label1 = new_label();
		struct InterCodes* code1 = translate_Cond(Exp->children->neighbours->neighbours, label1, label_false);
		struct InterCodes* code2 = translate_Cond(Exp->children, label_true, label_false);
		struct InterCodes* code3 = (struct InterCodes*)malloc(sizeof(struct InterCodes));
		code3->code.kind = LABEL_;
		code3->code.u.labelcode.label = label1;

		struct InterCodes* p = code1;
		while(p->next != NULL)
			p = p->next;
		p->next = code3;
		code3->prev = p;

		code3->next = code2;
		code2->prev = code3;

		return code1;
	}
	if(strcmp(Exp->children->neighbours->name, "OR") == 0){
		//printf("Exp - Exp OR Exp\n");
		Operand label1 = new_label();
		struct InterCodes* code1 = translate_Cond(Exp->children->neighbours->neighbours, label_true, label1);
		struct InterCodes* code2 = translate_Cond(Exp->children, label_true, label_false);
		struct InterCodes* code3 = (struct InterCodes*)malloc(sizeof(struct InterCodes));
		code3->code.kind = LABEL_;
		code3->code.u.labelcode.label = label1;

		struct InterCodes* p = code1;
		while(p->next != NULL)
			p = p->next;
		p->next = code3;
		code3->prev = p;

		code3->next = code2;
		code2->prev = code3;

		return code1;
	}
	else{
		//printf("Exp - ELSE\n");
		Operand t1 = new_temp();
		struct InterCodes* code1 = translate_Exp(Exp, t1);
		struct InterCodes* code2 = (struct InterCodes*)malloc(sizeof(struct InterCodes));
		code2->code.kind = IF_;
		code2->code.u.ifcode.op1 = t1;
		code2->code.u.ifcode.op2 = (Operand)malloc(sizeof(struct Operand_));
		code2->code.u.ifcode.op2->kind = CONSTANT;
		code2->code.u.ifcode.op2->u.value = 0;
		code2->code.u.ifcode.label = label_true;
		char op[2] = {'!', '='};
		strcpy(code2->code.u.ifcode.op_type, op);
		struct InterCodes* code3 = (struct InterCodes*)malloc(sizeof(struct InterCodes));
		code3->code.kind = GOTO_;
		code3->code.u.gotocode.label = label_false;

		struct InterCodes* p = code1;
		while(p->next != NULL)
			p = p->next;
		p->next = code2;
		code2->prev = p;

		code2->next = code3;
		code3->prev = code2;

		code3->next = NULL;

		return code1;
	}
}

struct InterCodes* translate_Args(struct TreeNode* Args, struct ArgList** arg_list){
	if(strcmp(Args->children->name, "Exp") == 0){
		//printf("Args - Exp\n");
		Operand t1 = new_temp();
		struct InterCodes* code1;
		if (strcmp(Args->children->children->name, "ID") == 0){
				code1 = (struct InterCodes*)malloc(sizeof(struct InterCodes));
				FieldList item = (FieldList)malloc(sizeof(struct FieldList_));
				newlookupTable(Args->children->children->value_str,&item,0);
				strcpy(t1->u.ID, item->inter_name);
				if (item->type->kind == structure || item->type->kind == variable)
					t1->kind = ADDRESS;
				else 
					t1->kind = VARIABLE;	
				code1->code.kind = NONE_;	
		}
		else 
			 code1 = translate_Exp(Args->children, t1);
		
		struct ArgList* temp = (struct ArgList*)malloc(sizeof(struct ArgList));
		temp->op = t1;
		temp->next = *arg_list;
		*arg_list = temp;
		return code1;
	}
	if(strcmp(Args->children->name, "COMMA") == 0){
		//printf("Args - Exp COMMA Args\n");
		Operand t1 = new_temp();
		struct InterCodes* code1;
		
		if (strcmp(Args->children->neighbours->neighbours->children->name, "ID") == 0){
				code1 = (struct InterCodes*)malloc(sizeof(struct InterCodes));
				FieldList item = (FieldList)malloc(sizeof(struct FieldList_));
				newlookupTable(Args->children->neighbours->neighbours->children->value_str,&item,0);
				strcpy(t1->u.ID, item->inter_name);
				if (item->type->kind == structure || item->type->kind == variable)
					t1->kind = ADDRESS;
				else 
					t1->kind = VARIABLE;	
				code1->code.kind = NONE_;	
		}
		else
			 code1 = translate_Exp(Args->children->neighbours->neighbours, t1);
			
		struct ArgList* temp = (struct ArgList*)malloc(sizeof(struct ArgList));
		temp->op = t1;
		temp->next = *arg_list;
		*arg_list = temp;
		struct InterCodes* code2 = translate_Args(Args->children, arg_list);

		struct InterCodes* p = code1;
		while(p->next != NULL)
			p = p->next;
		p->next = code2;
		code2->prev = p;

		code2->next = NULL;

		return code1;
	}
}

struct InterCodes* translate_ExtDecList(struct TreeNode* ExtDecList){
	if(strcmp(ExtDecList->children->name, "VarDec") == 0){
		//printf("ExtDecList - VarDec\n");
		struct InterCodes* code1 = translate_VarDec(ExtDecList->children);
		return code1;
	}
	if(strcmp(ExtDecList->children->name, "ExtDecList") == 0){
		//printf("ExtDecList - VarDec COMMA ExtDecList\n");
		struct InterCodes* code1 = translate_VarDec(ExtDecList->children->neighbours->neighbours);
		struct InterCodes* code2 = translate_ExtDecList(ExtDecList->children);

		struct InterCodes* p = code1;
		while(p->next != NULL)
			p = p->next;
		p->next = code2;
		code2->prev = p;

		return code1;
	}
}

struct InterCodes* translate_VarDec(struct TreeNode* VarDec){
	if(strcmp(VarDec->children->name, "ID") == 0){
		//printf("VarDec - ID\n");
		FieldList item = (FieldList)malloc(sizeof(struct FieldList_));
		newlookupTable(VarDec->children->value_str,&item,0);
		if(item->type->kind == structure){
			struct InterCodes* code1 = (struct InterCodes*)malloc(sizeof(struct InterCodes));
			code1->code.kind = DEC_;
			code1->code.u.dec.space = (Operand)malloc(sizeof(struct Operand_));
			code1->code.u.dec.space->kind = VARIABLE;
			strcpy(code1->code.u.dec.space->u.ID, item->inter_name);
			code1->code.u.dec.size = dec_size(item->type);
			return code1;
		}
		else{
			struct InterCodes* code1 = (struct InterCodes*)malloc(sizeof(struct InterCodes));
			code1->code.kind = NONE_;
			return code1;
		}
	}
	if(strcmp(VarDec->children->name, "RB") == 0){
		//printf("VarDec - VarDec LB INT RB\n");
		if ( strcmp(VarDec->children->neighbours->neighbours->neighbours->children->name,"ID") != 0){
			printf("Can not translate the code: Contain multidimensional array\n");
			exit(0);
			}
		FieldList item = (FieldList)malloc(sizeof(struct FieldList_));
		newlookupTable(VarDec->children->neighbours->neighbours->neighbours->children->value_str,&item,0);
		struct InterCodes* code1 = (struct InterCodes*)malloc(sizeof(struct InterCodes));
		code1->code.kind = DEC_;
		code1->code.u.dec.space = (Operand)malloc(sizeof(struct Operand_));
		code1->code.u.dec.space->kind = VARIABLE;
		strcpy(code1->code.u.dec.space->u.ID, item->inter_name);
		code1->code.u.dec.size = dec_size(item->type);
		
		return code1;
	}
}

struct InterCodes* translate_Dec(struct TreeNode* Dec){
	if(strcmp(Dec->children->name, "Exp") == 0){
		//printf("Dec - VarDec ASSIGNOP Exp\n");
		Operand t1 = new_temp();
		FieldList item = (FieldList)malloc(sizeof(struct FieldList_));
		lookupTable(Dec->children->neighbours->neighbours->children->value_str,&item,0);

		struct InterCodes* code1 = translate_Exp(Dec->children, t1);
		struct InterCodes* code2 = (struct InterCodes*)malloc(sizeof(struct InterCodes));
		code2->code.kind = ASSIGN_;
		code2->code.u.assign.left = (Operand)malloc(sizeof(struct Operand_));
		code2->code.u.assign.left->kind = VARIABLE;
		strcpy(code2->code.u.assign.left->u.ID, item->inter_name);
		code2->code.u.assign.right = t1;

		struct InterCodes* p = code1;
		while(p->next != NULL)
			p = p->next;
		p->next = code2;
		code2->prev = p;

		code2->next = NULL;

		return code1;
	}
	else {
		struct InterCodes* code1 = translate_VarDec(Dec->children);
		
		return code1;
	}
}

struct InterCodes* translate_FunDec(struct TreeNode* FunDec){
	if(strcmp(FunDec->children->neighbours->name, "LP") == 0){
		//printf("FunDec - ID LP RP\n");

		newlookupTable(FunDec->children->neighbours->neighbours->value_str,&pFunc,1);

		struct InterCodes* code1 = (struct InterCodes*)malloc(sizeof(struct InterCodes));
		code1->code.kind = FUNCTION_;
		strcpy(code1->code.u.function.func, FunDec->children->neighbours->neighbours->value_str);
		return code1;
	}
	if(strcmp(FunDec->children->neighbours->name, "VarList") == 0){
		//printf("FunDec - ID LP VarList RP\n");
		struct InterCodes* code1 = (struct InterCodes*)malloc(sizeof(struct InterCodes));
		code1->code.kind = FUNCTION_;
		strcpy(code1->code.u.function.func, FunDec->children->neighbours->neighbours->neighbours->value_str);

		FieldList item = (FieldList)malloc(sizeof(struct FieldList_));
		newlookupTable(FunDec->children->neighbours->neighbours->neighbours->value_str,&item,1);
		newlookupTable(FunDec->children->neighbours->neighbours->neighbours->value_str,&pFunc,1);

		FieldList q = item->type->u.function->tail;
		while(q != NULL){
				
			if (q->type->kind == array){
				printf("Can not translate the code: Contain function parameters of array type!\n");
				exit(0);
				
			}
			
			struct InterCodes* code2 = (struct InterCodes*)malloc(sizeof(struct InterCodes));
			code2->code.kind = PARAM_;
			code2->code.u.param.op = (Operand)malloc(sizeof(struct Operand_));
			code2->code.u.param.op->kind = VARIABLE;
			strcpy(code2->code.u.param.op->u.ID, q->inter_name);

			struct InterCodes* p = code1;
			while(p->next != NULL)
				p = p->next;
			p->next = code2;
			code2->prev = p;

			code2->next = NULL;

			q = q->tail;
		}
		return code1;
	}
}

struct InterCodes* translate_CompSt(struct TreeNode* CompSt){
	//printf("CompSt - LC DefList StmtList RC\n");
	struct InterCodes* code1 = translate_DefList(CompSt->children->neighbours->neighbours);
	struct InterCodes* code2 = translate_StmtList(CompSt->children->neighbours);

	struct InterCodes* p = code1;
	while(p->next != NULL)
		p = p->next;
	p->next = code2;
	code2->prev = p;

	return code1;
}

struct InterCodes* translate_StmtList(struct TreeNode* StmtList){
	if(StmtList->children == NULL){
		struct InterCodes* code1 = (struct InterCodes*)malloc(sizeof(struct InterCodes));
		code1->code.kind = NONE_;

		return code1;
	}
	else{
		struct InterCodes* code1 = translate_Stmt(StmtList->children->neighbours);
		struct InterCodes* code2 = translate_StmtList(StmtList->children);

		struct InterCodes* p = code1;
		while(p->next != NULL)
			p = p->next;
		p->next = code2;
		code2->prev = p;

		return code1;
	}
}

struct InterCodes* translate_DefList(struct TreeNode* DefList){
	if(DefList->children == NULL){
		struct InterCodes* code1 = (struct InterCodes*)malloc(sizeof(struct InterCodes));
		code1->code.kind = NONE_;

		return code1;
	}
	else{
		struct InterCodes* code1 = translate_Def(DefList->children->neighbours);
		struct InterCodes* code2 = translate_DefList(DefList->children);

		struct InterCodes* p = code1;
		while(p->next != NULL)
			p = p->next;
		p->next = code2;
		code2->prev = p;

		return code1;
	}
}

struct InterCodes* translate_Def(struct TreeNode* Def){
	return translate_DecList(Def->children->neighbours);
}

struct InterCodes* translate_DecList(struct TreeNode* DecList){
	if(strcmp(DecList->children->name, "Dec") == 0){
		return translate_Dec(DecList->children);
	}
	if(strcmp(DecList->children->name, "DecList") == 0){
		struct InterCodes* code1 = translate_Dec(DecList->children->neighbours->neighbours);
		struct InterCodes* code2 = translate_DecList(DecList->children);

		struct InterCodes* p = code1;
		while(p->next != NULL)
			p = p->next;
		p->next = code2;
		code2->prev = p;

		return code1;
	}
}

struct InterCodes* translate_ExtDefList(struct TreeNode* ExtDefList){
	if(ExtDefList->children == NULL){
		struct InterCodes* code1 = (struct InterCodes*)malloc(sizeof(struct InterCodes));
		code1->code.kind = NONE_;

		return code1;
	}
	else{
		struct InterCodes* code1 = translate_ExtDef(ExtDefList->children->neighbours);
		struct InterCodes* code2 = translate_ExtDefList(ExtDefList->children);

		struct InterCodes* p = code1;
		while(p->next != NULL)
			p = p->next;
		p->next = code2;
		code2->prev = p;

		return code1;
	}
}

struct InterCodes* translate_ExtDef(struct TreeNode* ExtDef){
	if(strcmp(ExtDef->children->name, "CompSt") == 0){
		struct InterCodes* code1 = translate_FunDec(ExtDef->children->neighbours);
		struct InterCodes* code2 = translate_CompSt(ExtDef->children);

		struct InterCodes* p = code1;
		while(p->next != NULL)
			p = p->next;
		p->next = code2;
		code2->prev = p;

		return code1;
	}
	else{
		struct InterCodes* code1 = (struct InterCodes*)malloc(sizeof(struct InterCodes));
		code1->code.kind = NONE_;

		return code1;
	}
}

void getVarInterName(FieldList  root){
	int no = 1;
	FieldList r = root;
	while (r != NULL){
		if (r->type->kind == function){
			FieldList p = r->type->u.function->tail;
			while ( p != NULL){
				sprintf(p->inter_name,"v%d",no);
				no++;
				p = p->tail;
			}
		}
		else {
			sprintf(r->inter_name,"v%d",no);
			no++;
		}
		r = r->tail;
	}
}

