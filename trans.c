#include "myas.h"

extern int is_valid(char *op, char* arg1, char* arg2);

int instr_trans(char *op, char *args, char* mcode)
{
	// check syntax 
	char token[256];
	int i = 0;
	strcpy(token, args);
	char *arg1 = strtok(token, ",");
	char *arg2 = strtok(NULL, ",");
	int RETVAL;
	char opcode[10] = "00";
	printf("%s %s ", arg1, arg2);

	if (!(RETVAL = is_valid(op, arg1, arg2))) {
		printf("Error: %s %s is not valid\n", op, args);
		strcpy(opcode, "error");
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
		strcpy(opcode, "b8");
		break;
	default:
		strcpy(opcode, "error");
	}
	strcpy(mcode, opcode);

	printf("%s\n", mcode);
	return 1;
}

