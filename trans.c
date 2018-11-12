#include "myas.h"

extern int is_valid(char *op, char* arg1, char* arg2);
extern char* reg[8];
//"%eax","%ecx","%edx","%ebx", "%esp","%ebp","%esi","%edi"
int RegType(char *arg) {
	int i = 0;
	for (i = 0; i < 8; i++) {
		if (strcmp(arg, reg[i]) == 0)
			return i;
	}
}

int instr_trans(char *op, char *args, char* mcode)
{
	// check syntax 
	char token[256];
	int i = 0;
	char hex = 8;
	strcpy(token, args);
	char *arg1 = strtok(token, ",");
	char *arg2 = strtok(NULL, ",");
	int RETVAL;
	char opcode[10] = "00";
	printf("%s %s ", arg1, arg2);

	if (!(RETVAL = is_valid(op, arg1, arg2))) {
		printf("Error: %s %s is not valid\n", op, args);
		strcpy(mcode, "error");
		return 0;
	}
	//{RTR = 1, MTR, MTR_WO, MTR_W, MTR_EAX, RTM, ITR};
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
		hex += RegType(arg2);
		if (hex >= 10)
			hex = 'a' + (hex - 10);
		else
			hex = hex + '0';
		opcode[0] = 'b'; opcode[1] = hex; opcode[2] = 0;
		break;
	default:
		strcpy(opcode, "error");
	}
	strcpy(mcode, opcode);

	printf("%s\n", mcode);
	return 1;
}

