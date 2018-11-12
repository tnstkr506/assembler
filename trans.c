#include "myas.h"

extern int is_valid(char *op, char* arg1, char* arg2);
extern char* reg[8];// extern reg array
//"%eax","%ecx","%edx","%ebx", "%esp","%ebp","%esi","%edi"
int RegType(char *arg) {//type of reg
	int i = 0;
	for (i = 0; i < 8; i++) {
		if (strcmp(arg, reg[i]) == 0)//check arg equal regarray
			return i;//type of reg 
	}
}

int instr_trans(char *op, char *args, char* mcode)
{
	// check syntax 
	char token[256];
	int i = 0;
	char hex = 8;//Imd to Reg opcode='b'+hex;
	strcpy(token, args);//token copy args
	char *arg1 = strtok(token, ",");//arg1
	char *arg2 = strtok(NULL, ",");//arg2
	int RETVAL;//return value
	char opcode[10] = "00";
	printf("%s %s ", arg1, arg2);//console print

	if (!(RETVAL = is_valid(op, arg1, arg2))) {//is_valid return 0 ->error
		printf("Error: %s %s is not valid\n", op, args);
		strcpy(mcode, "error");//mcode fprint mov.out error
		return 0;
	}
	//enum {RTR = 1, MTRD, MTR_WO, MTR_W, MTR_EAX, RTM, ITR};
	switch (RETVAL) {
	case RTR://reg to reg
		strcpy(opcode, "89");
		break;
	case RTM://reg(eax) to mem
		strcpy(opcode, "a3");
		break;
	case MTRD://mem(dis) to reg
		strcpy(opcode, "8b");
		break;
	case MTR_EAX://mem to eax
		strcpy(opcode, "a1");
		break;
	case ITR://imd to reg
		//"%eax","%ecx","%edx","%ebx", "%esp","%ebp","%esi","%edi"
		hex += RegType(arg2);//hex= 8+regtype
		if (hex >= 10)//decimal -> hex
			hex = 'a' + (hex - 10);//int-> char
		else//hex<10 eax OR ecx
			hex = hex + '0';//int -> char
		opcode[0] = 'b'; opcode[1] = hex; opcode[2] = 0;//\0
		break;
	default:
		strcpy(opcode, "error");
	}
	strcpy(mcode, opcode);

	printf("%s\n", mcode);//console print
	return 1;
}

