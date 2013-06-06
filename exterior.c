

Operand new_temp(){
	static int used_no = 0;
	Operand newop = (Operand)malloc(sizeof(struct Operand_));
	memset(newop,0,sizeof(struct Operand_);
	sprintf(newop->u.ID,"t%d",used_no);
	used_no++;
	return newop;
}

Operand new_lable(){
	static int used_label = 1;
	Operand newLabel = (Operand)malloc(sizeof(struct Operand_));
	memset(newLabel,0,sizeof(struct Operand_);
	sprintf(newLabe->u.ID,"t%d",used_label);
	used_label++;
	return newLabel;
}

void printCode(struct InterCodes *root){

	while (root != NULL){
		switch (root->code.kind){
			case ASSIGN:
						printOperand(root->code.u.assign.left);
						printf(":= ");
						printOperand(root->code.u.assign.right);
						printf("\n");
						break;
			case ADD:
						printOperand(root->code.u.binop.result);
						printf(":= ");
						printOperand(root->code.u.binop.op1);
						printf("+ ");
						printOperand(root->code.u.binop.op2);
						printf("\n");
						break;
			case SUB:
						printOperand(root->code.u.binop.result);
						printf(":= ");
						printOperand(root->code.u.binop.op1);
						printf("- ");
						printOperand(root->code.u.binop.op2);
						printf("\n");
						break;
			case MUL:
						printOperand(root->code.u.binop.result);
						printf(":= ");
						printOperand(root->code.u.binop.op1);
						printf("* ");
						printOperand(root->code.u.binop.op2);
						printf("\n");
						break;
			case DIV:
						printOperand(root->code.u.binop.result);
						printf(":= ");
						printOperand(root->code.u.binop.op1);
						printf("/ ");
						printOperand(root->code.u.binop.op2);
						printf("\n");
						break;
			case MINUS:;
						printf("occur MINUS \n");
						break;
			case IF:
						printf("IF ");
						printOperand(root->code.u.ifcode.op1);
						printf("%s ",root->code.u.ifcode.op_type);
						printOperand(root->code.u.ifcode.op2);
						printf(" GOTO ");
						printOperand(root->code.u.ifcode.label);
						printf("\n");
						break;
			case GOTO:
						printf("GOTO ");
						printOperand(root->code.u.gotocode.label);
						printf("\n");
						break;
			case LABEL:
						printf("LABEL ");
						printOperand(root->code.u.labelocode.label);
						printf("\n");
						break;
			case RETURN:
						printf("RETURN ");
						printOperand(root->code.u.returncode.r);
						printf("\n");
						break;
			case READ:
						printf("READ ");
						printOperand(root->code.u.read.rd);
						printf("\n");
						break;
			case WRITE:
						printf("WRITE ");
						printOperand(root->code.u.write.wr);
						printf("\n");
						break;
			case ARG:
						printf("ARG  ");
						printOperand(root->code.u.arg.argument);
						break;
			case CALL:
						printOperand(root->code.u.call.left);
						printf(":= CALL ");
						printOperand(root->code.u.call.function);
						printf("\n");
						break;
			case DEC:
						printf("DEC ")£»
						printOperand(root->code.u.dec.space);
						printf("%d ",root->code.u.dec.size);
						printf("\n");
						break;
			case FUNCTION:
						printf("FUNCTION ");
						printf("%s :",root->code.u.function.func);
						printf("\n");
						break;
			case PARAM:
						printf("PARAM ");
						printOperand(root->code.u.param.op);
						printf("\n");
			case NONE:
						break;
			default : printf("undifined  op\n");
		}
		root = root->next;
	}
}

void printOperand(Operand op){
	switch (op->kind){
		case VARIABLE:
						printf("%s ",op->u.ID);
						break;
		case CONSTANT:
						printf("#%d ",op->u.value);
						break;
		case ADDRESS:
						printf("&%s ",op->u.ID);
						break;
		case REFERENCE:
						printf("*%s ",op->u.ID);
						break;
		case GOTOOP:
						printf("%s ",op->u.ID);
						break;
		case LABELOP:
						printf("%s ",op->u.ID);
						break;
		case RETURNOP:
						printf("%s ",op->u.ID);
						break;
	}
}


int dec_size(Type item){
	if (item->kind == basic)
		return 4;
	else if (item->kind == array)
		return item->u.array.size * dec_size(item->u.array.elem);
	else if (item->kind == variable ){
		int total = 0;
		FieldList p = item->u.variable;
		while ( p != NULL)
			total += dec_size(p->type);
			p = p->tail;
		}
		return total;
	}
	return -1;
}


int index_size(FieldList father,char *memberName){
	int index = 0;
	while (strcmp(father->name,memberName) != 0){
			index +=  dec_size(father->type);
			father = father->tail;
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