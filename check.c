#include "myas.h"
char* reg[8] = { "%eax","%ecx","%edx","%ebx", "%esp","%ebp","%esi","%edi" };
char* memReg[8] = { "(%eax)","(%ecx)","(%edx)","(%ebx)", "(%esp)","(%ebp)","(%esi)","(%edi)" };

int RegEqual(char *arg) {
	int i = 0;
	for (i = 0; i < 8; i++) {
		if (strcmp(arg, reg[i]) == 0)
			return REG;
	}
	return 0;
}
int MemEqual(char *arg) {
	int i = 0;
	for (i = 0; i < 8; i++) {
		if (strstr(arg, memReg[i]) != NULL)
			return DIS;
	}
	if (arg[0]!='$' && strstr(arg, "0x") != NULL)
		return MEM;
	return 0;
}
int is_valid(char *op, char *arg1, char * arg2)
{
	//printf("if valid, return 1\n");
	//printf("otherwise, return 0\n");
	if (strcmp(op, "mov")!=0)
		return 0;
	int MResult1 = MemEqual(arg1);
	int MResult2 = MemEqual(arg2);
	int RResult1 = RegEqual(arg1);
	int RResult2 = RegEqual(arg2);
	if (MResult1 == DIS) {//arg1 : mem(disp) 
	//mem to reg (addressing w.o/w disp.)
		if (RegEqual(arg2)) {//arg2 : reg
			return MTRD;
		}
		else
			return 0;
	}
	else if (MResult1 == MEM) {//arg1 : mem(disp X)
	// mem to reg (eax)
		if (strcmp(arg2, "%eax") == 0) {//arg2 : %eax
			return MTR_EAX;
		}
		else
			return 0;
	}
	else if (RResult1) {//arg1 : reg
		if (strcmp(arg1, "%eax") == 0) {//arg1 : %eax
			// reg(eax) to mem
			if (MemEqual(arg2)) {//arg2 : mem
				return RTM;
			}
		}
		else if (RResult2) {//arg2 : reg
			// reg to reg 
			return RTR;
		}
	}
	else if (strstr(arg1, "$0x") != NULL) {//arg1 : imd
		if (RResult2) {//arg2 : reg
			// immediate to reg 
			return ITR;
		}
		else
			return 0;
	}
	else
		return 0;

}

