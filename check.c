#include "myas.h"
extern char* reg[9];

int RegEqual(char *arg) {
	int i = 0;
	for (i = 0; i < 8; i++) {
		if (strcmp(arg, reg[i]) == 0)
			return 1;
	}
	return 0;
}
int is_valid(char *op, char *arg1, char * arg2)
{
	//printf("if valid, return 1\n");
	//printf("otherwise, return 0\n");
	if (strcmp(op, "mov")!=0)
		return 0;
	
	// reg to reg 
	//mem to reg (addressing w.o/ disp.)
	//mem to reg (addressing w/ disp.)
	// mem to reg (eax)
	// reg(eax) to mem
	// immediate to reg 

	// imd to imd x mem to mem x 

	switch (arg1[0]) {
	case '%'://reg
		if(RegEqual(arg1)) {
			switch (arg2[0]) {
				case '('://mem
				case '0'://displace mem
				case '-'://displace mem
					return RTM;
				case '%':
					return RTR;
				default:
					return 0;
			}
		}
		else {
			return 0;
		}
		break;
	case '('://mem
	case '0'://displace mem
	case '-'://displace mem
		if (arg2[0] == '%') {
			return MTR;
		}
		else
			return 0;
		break;
	case '$'://imd
		if (arg2[0] == '%') {
			return ITR;
		}
		else
			return 0;
		break;
	default:
		return 0;
	}
}

