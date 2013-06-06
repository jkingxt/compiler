typedef struct Operand_* Operand;
struct Operand_ {
	enum { VARIABLE, CONSTANT, CONSTANT_FLOAT, ADDRESS, REFERENCE, GOTOOP, LABELOP, RETURNOP} kind;
	union {
		char ID[20];//这个有待考虑
		int value;
		//if操作数
		//其他
	} u;
};

struct ArgList{
	Operand op;
	ArgList* next;
}

struct InterCode
{
	enum { ASSIGN, ADD, SUB, MUL, DIV, MINUS, IF, GOTO, LABEL, RETURN, READ, WRITE, ARG, CALL, DEC, FUNCTION, PARAM, NONE} kind;
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
		//其他
	} u;
} 

struct InterCodes {
	InterCode code; 
	struct InterCodes *prev, *next; 
};

InterCodes* translate_Exp(TreeNode* Exp, Operand place);
InterCodes* translate_Stmt(TreeNode* Stmt);
InterCodes* translate_Cond(TreeNode* Exp, Operand label_true, Operand label_false);
InterCodes* translate_Args(TreeNode* Args, struct ArgList* arg_list);
InterCodes* translate_ExtDecList(TreeNode* ExtDecList);
InterCodes* translate_VarDec(TreeNode* VarDec);
InterCodes* translate_Dec(TreeNode* Dec);
InterCodes* translate_FunDec(TreeNode* FunDec);
InterCodes* translate_CompSt(TreeNode* CompSt);
InterCodes* translate_StmtList(TreeNode* StmtList);
InterCodes* translate_DefList(TreeNode* DefList);
InterCodes* translate_Def(TreeNode* Def);
InterCodes* translate_DecList(TreeNode* DecList);
InterCodes* translate_ExtDefList(TreeNode* ExtDefList);
InterCodes* translate_ExtDef(TreeNode* ExtDef);


InterCodes* GenerateInterCode(TreeNode* root){
	return translate_ExtDefList(root->children);
}

//符号表是全局变量
InterCodes* translate_Exp(TreeNode* Exp, Operand place){
	if (strcmp(Exp->children->name, "INT")){
		printf("Exp - INT\n");
		if(place != NULL){
			FieldList item = (FieldList)malloc(sizeof(struct FieldList_));
			lookupTable(Exp->children->value_str,&item,0);

			place->kind = CONSTANT;
			place->u.value = Exp->children->value_int;

			struct InterCodes* temp = (struct InterCodes*)malloc(sizeof(struct InterCodes));
			temp->code.kind = NONE;
			return temp;
		}
		else{
			struct InterCodes* temp = (struct InterCodes*)malloc(sizeof(struct InterCodes));
			temp->code.kind = NONE;
			return temp;
		}
	}
	if (strcmp(Exp->children->name, "ID")){
		if(Exp->children->neighbours == NULL){
			printf("Exp - ID\n");
			if(place != NULL){
				FieldList item = (FieldList)malloc(sizeof(struct FieldList_));
				lookupTable(Exp->children->value_str,&item,0);

				place->kind = VARIABLE;
				strcpy(place->u.value, item->inter_name);

				struct InterCodes* temp = (struct InterCodes*)malloc(sizeof(struct InterCodes));
				temp->code.kind = NONE;
				return temp;
			}
			else{
				struct InterCodes* temp = (struct InterCodes*)malloc(sizeof(struct InterCodes));
				temp->code.kind = NONE;
				return temp;
			}
		}
		if(strcmp(Exp->children->neighbours->name, "DOT")){
			printf("Exp - Exp DOT ID\n");
			//Operand t1 = new_temp();
			//struct InterCodes* code1 = translate_Exp(Exp->children->neighbours->neighbours, t1);

			FieldList item = (FieldList)malloc(sizeof(struct FieldList_));
			int i = lookupTable(Exp->children->neighbours->neighbours->value_str,&item,0);
			switch(i){
				case 0:{
					Operand t1 = new_temp();
					struct InterCodes* code1 = (struct InterCodes*)malloc(sizeof(struct InterCodes));
					code1->code.kind = ADD;
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
				case 1{
					Operand t1 = new_temp();
					Operand t1 = new_temp();

					struct InterCodes* code1 = (struct InterCodes*)malloc(sizeof(struct InterCodes));
					code1->code.kind = ASSIGN;
					code1->code.u.assign.left = t1;
					code1->code.u.assign.right = (Operand)malloc(sizeof(struct Operand_));
					code1->code.u.assign.right->kind = ADDRESS;
					strcpy(code1->code.u.assign.right->u.ID, item->inter_name);

					struct InterCodes* code2 = (struct InterCodes*)malloc(sizeof(struct InterCodes));
					code2->code.kind = ADD;
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
	if (strcmp(Exp->children->name, "Exp")){
		if (strcmp(Exp->children->neighbours->name, "ASSIGNOP")){
			if (strcmp(Exp->children->neighbours->neighbours->children->name, "ID")){
				printf("Exp - Exp ASSIGNOP Exp\n");
				if(place != NULL){
					Operand t1 = new_temp();
					FieldList item = (FieldList)malloc(sizeof(struct FieldList_));
					lookupTable(Exp->children->neighbours->neighbours->children->value_str,&item,0);

					struct InterCodes* code1 = translate_Exp(Exp->children, t1);

					struct InterCodes* code2 = (struct InterCodes*)malloc(sizeof(struct InterCodes));
					code2->code.kind = ASSIGN;
					code2->code.u.assign.left = (Operand)malloc(sizeof(struct Operand_));
					code2->code.u.assign.left->kind = VARIABLE;
					strcpy(code2->code.u.assign.left->u.ID, item->inter_name);
					code2->code.u.assign.right = t1;

					/*struct InterCodes* code3 = (struct InterCodes*)malloc(sizeof(struct InterCodes));
					code3->code.kind = ASSIGN;
					code3->code.u.assign.left = (Operand)malloc(sizeof(struct Operand_));
					code3->code.u.assign.left->kind = VARIABLE;
					strcpy(code3->code.u.assign.left->u.ID, place->u.ID);
					code3->code.u.assign.right = (Operand)malloc(sizeof(struct Operand_));
					code3->code.u.assign.right->kind = VARIABLE;
					strcpy(code3->code.u.assign.right->u.ID, Exp->children->neighbours->neighbours->children->inter_name);*/

					place->kind = VARIABLE;
					strcpy(place->u.value, item->inter_name);

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

					struct InterCodes* code2 = (struct InterCodes*)malloc(sizeof(struct InterCodes));
					code2->code.kind = ASSIGN;
					code2->code.u.assign.left = (Operand)malloc(sizeof(struct Operand_));
					code2->code.u.assign.left->kind = VARIABLE;
					strcpy(code2->code.u.assign.left->u.ID, Exp->children->neighbours->neighbours->children->inter_name);
					code2->code.u.assign.right = t1;

					struct InterCodes* p = code1;
					while(p->next != NULL)
						p = p->next;
					p->next = code2;
					code2->prev = p;
					code2->next = NULL;

					return code1;
				}
			}
		}
		if(strcmp(Exp->children->neighbours->name, "PLUS")){
			printf("Exp - Exp PLUS Exp\n");
			if(place != NULL){
				Operand t1 = new_temp();
				Operand t2 = new_temp();
				struct InterCodes* code1 = translate_Exp(Exp->children->neighbours->neighbours, t1);
				struct InterCodes* code2 = translate_Exp(Exp->children, t2);		
				struct InterCodes* code3 = (struct InterCodes*)malloc(sizeof(struct InterCodes));
				code3->code.kind = ADD;
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
		if(strcmp(Exp->children->neighbours->name, "MINUS")){
			printf("Exp - Exp MINUS Exp\n");
			if(place != NULL){
				if(Exp->children->neighbours->neighbours != NULL){
					Operand t1 = new_temp();
					Operand t2 = new_temp();
					struct InterCodes* code1 = translate_Exp(Exp->children->neighbours->neighbours, t1);
					struct InterCodes* code2 = translate_Exp(Exp->children, t2);
					struct InterCodes* code3 = (struct InterCodes*)malloc(sizeof(struct InterCodes));
					code3->code.kind = SUB;
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
					code2->code.kind = SUB;
					code2->code.u.binop.result = (Operand)malloc(sizeof(struct Operand_));
					code2->code.u.binop.result->kind = VARIABLE;
					strcpy(code3->code.u.binop.result->u.ID, place->u.ID);
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
		if(strcmp(Exp->children->neighbours->name, "STAR")){
			printf("Exp - Exp STAR Exp\n");
			if(place != NULL){
				Operand t1 = new_temp();
				Operand t2 = new_temp();
				struct InterCodes* code1 = translate_Exp(Exp->children->neighbours->neighbours, t1);
				struct InterCodes* code2 = translate_Exp(Exp->children, t2);		
				struct InterCodes* code3 = (struct InterCodes*)malloc(sizeof(struct InterCodes));
				code3->code.kind = MUL;
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
		if(strcmp(Exp->children->neighbours->name, "DIV")){
			printf("Exp - Exp DIV Exp\n");
			if(place != NULL){
				Operand t1 = new_temp();
				Operand t2 = new_temp();
				struct InterCodes* code1 = translate_Exp(Exp->children->neighbours->neighbours, t1);
				struct InterCodes* code2 = translate_Exp(Exp->children, t2);
				struct InterCodes* code3 = (struct InterCodes*)malloc(sizeof(struct InterCodes));
				code3->code.kind = DIV;
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
		if(strcmp(Exp->children->neighbours->name, "RELOP") || strcmp(Exp->children->neighbours->name, "NOT") || strcmp(Exp->children->neighbours->name, "AND") || strcmp(Exp->children->neighbours->name, "OR")){
			printf("Exp - Exp Cond Exp\n");
			if(place != NULL){
				Operand label1 = new_label();
				Operand label2 = new_label();
				struct InterCodes* code1 = (struct InterCodes*)malloc(sizeof(struct InterCodes));
				code1->code.kind = ASSIGN;
				code1->code.u.assign.left = (Operand)malloc(sizeof(struct Operand_));
				code1->code.u.assign.left->kind = VARIABLE;
				strcpy(code1->code.u.assign.left->u.ID, place->u.ID);
				code1->code.u.assign.right = (Operand)malloc(sizeof(struct Operand_));
				code1->code.u.assign.right->kind = CONSTANT;
				code1->code.u.assign.right->u.value = 0;
				struct InterCodes* code2 = translate_Cond(Exp, label1, label2);
				struct InterCodes* code3 = (struct InterCodes*)malloc(sizeof(struct InterCodes));
				code3->code.kind = LABEL;
				code3->code.u.labelcode.label = label1;
				struct InterCodes* code4 = (struct InterCodes*)malloc(sizeof(struct InterCodes));
				code4->code.kind = ASSIGN;
				code4->code.u.assign.left = (Operand)malloc(sizeof(struct Operand_));
				code4->code.u.assign.left->kind = VARIABLE;
				strcpy(code4->code.u.assign.left->u.ID, place->u.ID);
				code4->code.u.assign.right = (Operand)malloc(sizeof(struct Operand_));
				code4->code.u.assign.right->kind = CONSTANT;
				code4->code.u.assign.right->u.value = 1;
				struct InterCodes* code5 = (struct InterCodes*)malloc(sizeof(struct InterCodes));
				code5->code.kind = LABEL;
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
	if (strcmp(Exp->children->neighbours->name, "LP")){
		printf("Exp - ID LP RP\n");
		if(strcmp(Exp->children->neighbours->neighbours->value_str, "read") == 0){
			struct InterCodes* code1 = (struct InterCodes*)malloc(sizeof(struct InterCodes));
			code1->code.kind = READ;
			code1->code.u.read.rd = place;
			return code1;
		}
		else{
			FieldList item = (FieldList)malloc(sizeof(struct FieldList_));
			lookupTable(Exp->children->neighbours->neighbours->value_str,&item,1);//查函数
			struct InterCodes* code1 = (struct InterCodes*)malloc(sizeof(struct InterCodes));
			code1->code.kind = CALL;
			code1->code.u.call.left = (Operand)malloc(sizeof(struct Operand_));
			code1->code.u.call.left->kind = VARIABLE;
			strcpy(code1->code.u.assign.left->u.ID, place->u.ID);
			code1->code.u.call.function = (Operand)malloc(sizeof(struct Operand_));
			code1->code.u.call.function->kind = VARIABLE;
			strcpy(code1->code.u.call.function->u.ID, item->name);
			return code1;
		}
	}
	if(strcmp(Exp->children->neighbours->name, "Args")){
		printf("Exp - ID LP Args RP\n");
		ArgList* arg_list = NULL;
		struct InterCodes* code1 = translate_Args(Exp->children->neighbours, arg_list);
		if(strcpy(Exp->children->neighbours->neighbours->neighbours->value_str, "write") == 0){
			struct InterCodes* code2 = (struct InterCodes*)malloc(sizeof(struct InterCodes));
			code2->code.kind = WRITE;
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
			lookupTable(Exp->children->neighbours->neighbours->neighbours->value_str,&item,0);
			ArgList* q = arg_list;
			struct InterCodes* code2 = NULL;
			while(q != NULL){
				struct InterCodes* code3 = (struct InterCodes*)malloc(sizeof(struct InterCodes));
				code3->code.kind = ARG;
				code3->code.u.arg.argument = p->op;
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
			code4->code.kind = CALL;
			code4->code.u.call.left = (Operand)malloc(sizeof(struct Operand_));
			code4->code.u.call.left->kind = VARIABLE;
			strcpy(code4->code.u.assign.left->u.ID, place->u.ID);
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
		printf("Exp - Exp LB Exp RB\n");
		FieldList item = (FieldList)malloc(sizeof(struct FieldList_));
		lookupTable(Exp->children->neighbours->neighbours->neighbours->children->value_str,&item,0);

		Operand t1 = new_temp();
		Operand t2 = new_temp();
		Operand t3 = new_temp();

		struct InterCodes* code1 = translate_Exp(Exp->children->neighbours, t1);
		struct InterCodes* code2 = (struct InterCodes*)malloc(sizeof(struct InterCodes));
		code2->code.kind = MUL;
		code2->code.u.binop.result = t2;
		code2->code.u.binop.op1 = t1;
		code2->code.u.binop.op2 = (Operand)malloc(sizeof(struct Operand_));
		code2->code.u.binop.result->kind = CONSTANT;
		code2->code.u.binop.result->u.value = 4;
		struct InterCodes* code3 = (struct InterCodes*)malloc(sizeof(struct InterCodes));
		code3->code.kind = ADD;
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


InterCodes* translate_Stmt(TreeNode* Stmt){
	if (strcmp(Stmt->children->name, "SEMI") == 0){
		if(Stmt->children->neighbours->neighbours == NULL){
			printf("Stmt - Stmt SEMI\n");
			return translate_Exp(Stmt->children->neighbours, NULL);
		}
		else{
			printf("Stmt - RETURN Stmt SEMI\n");
			Operand t1 = new_temp();
			struct InterCodes* code1 = translate_Exp(Stmt->children->neighbours, t1);
			struct InterCodes* code2 = (struct InterCodes*)malloc(sizeof(struct InterCodes));
			code2->code.kind = RETURN;
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
		printf("Stmt - CompSt\n");
		return translate_CompSt(Stmt->children);
	}
	if(strcmp(Stmt->children->name, "Stmt") == 0){
		if(strcmp(Stmt->children->neighbours->neighbours->neighbours->neighbours->name, "IF") == 0){
			printf("Stmt - IF LP Exp RP Stmt\n");
			Operand label1 = new_label();
			Operand label2 = new_label();
			struct InterCodes* code1 = translate_Cond(Stmt->children->neighbours->neighbours, label1, label2);
			struct InterCodes* code2 = translate_Stmt(Stmt->children);
			struct InterCodes* code3 = (struct InterCodes*)malloc(sizeof(struct InterCodes));
			code3->code.kind = LABEL;
			code3->code.u.labelcode.label = label1;
			struct InterCodes* code4 = (struct InterCodes*)malloc(sizeof(struct InterCodes));
			code4->code.kind = LABEL;
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
			printf("Stmt - WHILE LP Exp RP Stmt\n");
			Operand label1 = new_label();
			Operand label2 = new_label();
			Operand label3 = new_label();
			struct InterCodes* code1 = translate_Cond(Stmt->children->neighbours->neighbours, label2, label3);
			struct InterCodes* code2 = translate_Stmt(Stmt->children->neighbours->neighbours);
			struct InterCodes* code3 = (struct InterCodes*)malloc(sizeof(struct InterCodes));
			code3->code.kind = LABEL;
			code3->code.u.labelcode.label = label1;
			struct InterCodes* code4 = (struct InterCodes*)malloc(sizeof(struct InterCodes));
			code4->code.kind = LABEL;
			code4->code.u.labelcode.label = label2;
			struct InterCodes* code5 = (struct InterCodes*)malloc(sizeof(struct InterCodes));
			code5->code.kind = LABEL;
			code5->code.u.labelcode.label = label3;
			struct InterCodes* code6 = (struct InterCodes*)malloc(sizeof(struct InterCodes));
			code6->code.kind = GOTO;
			code6->code.u.gotocode.label = label3;

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
			printf("Stmt - IF LP Exp RP Stmt ELSE Stmt\n");
			Operand label1 = new_label();
			Operand label2 = new_label();
			Operand label3 = new_label();
			struct InterCodes* code1 = translate_Cond(Stmt->children->neighbours->neighbours, label1, label2);
			struct InterCodes* code2 = translate_Stmt(Stmt->children->neighbours->neighbours);
			struct InterCodes* code3 = translate_Stmt(Stmt->children);
			struct InterCodes* code4 = (struct InterCodes*)malloc(sizeof(struct InterCodes));
			code4->code.kind = LABEL;
			code4->code.u.labelcode.label = label1;
			struct InterCodes* code5 = (struct InterCodes*)malloc(sizeof(struct InterCodes));
			code5->code.kind = LABEL;
			code5->code.u.labelcode.label = label2;
			struct InterCodes* code6 = (struct InterCodes*)malloc(sizeof(struct InterCodes));
			code6->code.kind = LABEL;
			code6->code.u.labelcode.label = label3;
			struct InterCodes* code7 = (struct InterCodes*)malloc(sizeof(struct InterCodes));
			code7->code.kind = GOTO;
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


InterCodes* translate_Cond(TreeNode* Exp, Operand label_true, Operand label_false){
	if(strcmp(Exp->children->neighbours->name, "RELOP") == 0){
		printf("Exp - Exp RELOP Exp\n");
		Operand t1 = new_temp();
		Operand t2 = new_temp();
		struct InterCodes* code1 = translate_Exp(Exp->children->neighbours->neighbours, t1);
		struct InterCodes* code2 = translate_Exp(Exp->children, t2);
		struct InterCodes* code3 = (struct InterCodes*)malloc(sizeof(struct InterCodes));
		code3->code.kind = IF;
		code3->code.u.ifcode.op1 = t1;
		code3->code.u.ifcode.op2 = t2;
		code3->code.u.ifcode.label = label_true;
		strcpy(code3->code.u.ifcode.op_type, Exp->children->neighbours->value_str);
		struct InterCodes* code4 = (struct InterCodes*)malloc(sizeof(struct InterCodes));
		code4->code.kind = GOTO;
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
		printf("Exp - NOT Exp\n");
		return translate_Cond(Stmt->children, label_false, label_true);
	}
	if(strcmp(Exp->children->neighbours->name, "AND") == 0){
		printf("Exp - Exp AND Exp\n");
		Operand label1 = new_label();
		struct InterCodes* code1 = translate_Cond(Exp->children->neighbours->neighbours, label1, label_false);
		struct InterCodes* code2 = translate_Cond(Exp->children, label_true, label_false);
		struct InterCodes* code3 = (struct InterCodes*)malloc(sizeof(struct InterCodes));
		code3->code.kind = LABEL;
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
		printf("Exp - Exp OR Exp\n");
		Operand label1 = new_label();
		struct InterCodes* code1 = translate_Cond(Exp->children->neighbours->neighbours, label_true, label1);
		struct InterCodes* code2 = translate_Cond(Exp->children, label_true, label_false);
		struct InterCodes* code3 = (struct InterCodes*)malloc(sizeof(struct InterCodes));
		code3->code.kind = LABEL;
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
		printf("Exp - ELSE\n");
		Operand t1 = new_temp();
		struct InterCodes* code1 = translate_Exp(Exp, t1);
		struct InterCodes* code2 = (struct InterCodes*)malloc(sizeof(struct InterCodes));
		code2->code.kind = IF;
		code2->code.u.ifcode.op1 = t1;
		code2->code.u.ifcode.op2 = (Operand)malloc(sizeof(struct Operand_));
		code2->code.u.ifcode.op2->kind = CONSTANT;
		code2->code.u.ifcode.op2->value = 0;
		code2->code.u.ifcode.label = label_true;
		char op[2] = {'!', '='};
		strcpy(code2->code.u.ifcode.op_type, op);
		struct InterCodes* code3 = (struct InterCodes*)malloc(sizeof(struct InterCodes));
		code3->code.kind = GOTO;
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

InterCodes* translate_Args(TreeNode* Args, struct ArgList* arg_list){
	if(strcmp(Args->children->name, "Exp") == 0){
		printf("Args - Exp\n");
		Operand t1 = new_temp();
		struct InterCodes* code1 = translate_Exp(Args->children, t1);
		struct ArgList* temp = (ArgList*)malloc(sizeof(struct ArgList));
		temp->op = t1;
		temp->next = arg_list;
		arg_list = temp;
		return code1;
	}
	if(strcmp(Args->children->name, "COMMA") == 0){
		printf("Args - Exp COMMA Args\n");
		Operand t1 = new_temp();
		struct InterCodes* code1 = translate_Exp(Args->children->neighbours->neighbours, t1);
		struct ArgList* temp = (struct ArgList*)malloc(sizeof(struct ArgList));
		temp->op = t1;
		temp->next = arg_list;
		arg_list = temp;
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

InterCodes* translate_ExtDecList(TreeNode* ExtDecList){
	if(strcmp(ExtDecList->children->name, "VarDec") == 0){
		printf("ExtDecList - VarDec\n");
		struct InterCodes* code1 = translate_VarDec(ExtDecList->children);
		return code1;
	}
	if(strcmp(ExtDecList->children->name, "ExtDecList") == 0){
		printf("ExtDecList - VarDec COMMA ExtDecList\n");
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

InterCodes* translate_VarDec(TreeNode* VarDec){
	if(strcmp(VarDec->children->name, "ID") == 0){
		printf("VarDec - ID\n");
		FieldList item = (FieldList)malloc(sizeof(struct FieldList_));
		lookupTable(VarDec->children->value_str,&item,0);
		if(item->kind == structure){
			struct InterCodes* code1 = (struct InterCodes*)malloc(sizeof(struct InterCodes));
			code1->code.kind = DEC;
			Operand code1->code.u.dec.space = (Operand)malloc(sizeof(struct Operand_));
			code1->code.u.dec.space->kind = VARIABLE;
			strcpy(code1->code.u.dec.space->u.ID, item->inter_name);
			Operand code1->code.u.dec.size = size(item->type);
			return code1;
		}
	}
	if(strcmp(VarDec->children->name, "RB") == 0){
		printf("VarDec - VarDec LB INT RB\n");
		FieldList item = (FieldList)malloc(sizeof(struct FieldList_));
		lookupTable(VarDec->children->neighbours->neighbours->neighbours->children->value_str,&item,0);
		struct InterCodes* code1 = (struct InterCodes*)malloc(sizeof(struct InterCodes));
		code1->code.kind = DEC;
		Operand code1->code.u.dec.space = (Operand)malloc(sizeof(struct Operand_));
		code1->code.u.dec.space->kind = VARIABLE;
		strcpy(code1->code.u.dec.space->u.ID, item->inter_name);
		Operand code1->code.u.dec.size = size(item->type);
	}
}

InterCodes* translate_Dec(TreeNode* Dec){
	if(strcmp(Dec->children->name, "Exp") == 0){
		printf("Dec - VarDec ASSIGNOP Exp\n");
		Operand t1 = new_temp();
		FieldList item = (FieldList)malloc(sizeof(struct FieldList_));
		lookupTable(VarDec->children->neighbours->neighbours->children->value_str,&item,0);

		struct InterCodes* code1 = translate_Exp(Dec->children, t1);
		struct InterCodes* code2 = (struct InterCodes*)malloc(sizeof(struct InterCodes));
		code2->code.kind = ASSIGN;
		code2->code.u.assign.left = (Operand)malloc(sizeof(struct Operand_));
		code2->code.u.assign.left->kind = VARIABLE;
		strcpy(code2.code.u.assign.left->u.ID, item->inter_name);
		code2->code.u.assign.right = t1;

		struct InterCodes* p = code1;
		while(p->next != NULL)
			p = p->next;
		p->next = code2;
		code2->prev = p;

		code2->next = NULL;

		return code1;
	}
}

InterCodes* translate_FunDec(TreeNode* FunDec){
	if(strcmp(FunDec->children->neighbours->name, "LP") == 0){
		printf("FunDec - ID LP RP\n");

		lookupTable(FunDec->children->neighbours->neighbours->value_str,&pFunc,1);

		struct InterCodes* code1 = (struct InterCodes*)malloc(sizeof(struct InterCodes));
		code1->code.kind = FUNCTION;
		strcpy(code1->code.u.func, FunDec->children->neighbours->neighbours->value_str);
		return code1;
	}
	if(strcmp(FunDec->children->neighbours->name, "VarList") == 0){
		printf("FunDec - ID LP VarList RP\n");
		struct InterCodes* code1 = (struct InterCodes*)malloc(sizeof(struct InterCodes));
		code1->code.kind = FUNCTION;
		strcpy(code1->code.u.func, FunDec->children->neighbours->neighbours->neighbours->value_str);

		FieldList item = (FieldList)malloc(sizeof(struct FieldList_));
		lookupTable(FunDec->children->neighbours->neighbours->neighbours->value_str,&item,1);
		lookupTable(FunDec->children->neighbours->neighbours->neighbours->value_str,&pFunc,1);

		FieldList p = item->type->u.function->tail;
		while(p != NULL){
			struct InterCodes* code2 = (struct InterCodes*)malloc(sizeof(struct InterCodes));
			code2->code.kind = PARAM;
			code2->code.u.param.op = (Operand)malloc(sizeof(struct Operand_));
			code2->code.u.param.op->kind = VARIABLE;
			strcpy(code2->code.u.param.op->u.ID, p->inter_name);

			struct InterCodes* p = code1;
			while(p->next != NULL)
				p = p->next;
			p->next = code2;
			code2->prev = p;

			code2->next = NULL;

			p = p->next;
		}
		return code1;
	}
}

InterCodes* translate_CompSt(TreeNode* CompSt){
	printf("CompSt - LC DefList StmtList RC\n");
	struct InterCodes* code1 = translate_DefList(CompSt->children->neighbours->neighbours);
	struct InterCodes* code2 = translate_StmtList(CompSt->children->neighbours);

	struct InterCodes* p = code1;
	while(p->next != NULL)
		p = p->next;
	p->next = code2;
	code2->prev = p;

	return code1;
}

InterCodes* translate_StmtList(TreeNode* StmtList){
	if(StmtList->children == NULL){
		struct InterCodes* code1 = (struct InterCodes*)malloc(sizeof(struct InterCodes));
		code1->code.kind = NONE;

		return code1;
	}
	else{
		struct InterCodes* code1 = translate_Stmt(CompSt->children->neighbours);
		struct InterCodes* code2 = translate_StmtList(CompSt->children);

		struct InterCodes* p = code1;
		while(p->next != NULL)
			p = p->next;
		p->next = code2;
		code2->prev = p;

		return code1;
	}
}

InterCodes* translate_DefList(TreeNode* DefList){
	if(DefList->children == NULL){
		struct InterCodes* code1 = (struct InterCodes*)malloc(sizeof(struct InterCodes));
		code1->code.kind = NONE;

		return code1;
	}
	else{
		struct InterCodes* code1 = translate_Def(CompSt->children->neighbours);
		struct InterCodes* code2 = translate_DefList(CompSt->children);

		struct InterCodes* p = code1;
		while(p->next != NULL)
			p = p->next;
		p->next = code2;
		code2->prev = p;

		return code1;
	}
}

InterCodes* translate_Def(TreeNode* Def){
	return translate_DecList(Def->children->neighbours);
}

InterCodes* translate_DecList(TreeNode* DecList){
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

InterCodes* translate_ExtDefList(TreeNode* ExtDefList){
	if(ExtDefList->children == NULL){
		struct InterCodes* code1 = (struct InterCodes*)malloc(sizeof(struct InterCodes));
		code1->code.kind = NONE;

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

InterCodes* translate_ExtDef(TreeNode* ExtDef){
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
}
