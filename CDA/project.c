#include "spimcore.h"


/* ALU */
/* 10 Points */
void ALU(unsigned A,unsigned B,char ALUControl,unsigned *ALUresult,char *Zero)
{	//Z = A+B
	if(ALUControl == 0) {
		*ALUresult = A + B; 
		if(*ALUresult == 0){*Zero = 1;}
		else {*Zero = 0;}
	}
	//Z = A-B
	else if(ALUControl == 1) {
		*ALUresult = A - B;
		if(*ALUresult == 0){*Zero = 1;}
		else {*Zero = 0;}
	}
	//if A<B, Z=1 else Z=0
	else if(ALUControl == 2) {
		if((signed)A < (signed)B){*ALUresult = 1; *Zero = 0;}
		else{*ALUresult = 0; *Zero = 1;}
	}
	//if A<B, Z=1 else Z=0, (A & B are unsigned ints)
	else if(ALUControl == 3) {
		if(A < B){*ALUresult = 1; *Zero = 0;} //a and b are unsigned ints? maybe cast them as ints?
		else{*ALUresult = 0; *Zero = 1;}
	}
	//Z = A AND B
	else if(ALUControl == 4) {
		*ALUresult = A & B; 
		if(*ALUresult == 0){*Zero = 1;}
		else {*Zero = 0;}
	}
	//Z = A OR B
	else if(ALUControl == 5) {
		*ALUresult = A | B; 
		if(*ALUresult == 0){*Zero = 1;}
		else {*Zero = 0;}
	}
	//Shift left B by 16 bits
	else if(ALUControl == 6) {
		*ALUresult = B<<16; 
		if(*ALUresult == 0){*Zero = 1;}
		else {*Zero = 0;}	
	}
	//Z = NOT A
	else if(ALUControl == 7) {
		*ALUresult = ~A; 
		if(*ALUresult == 0){*Zero = 1;}
		else {*Zero = 0;}	
	}
	
}

/* instruction fetch */
/* 10 Points */
int instruction_fetch(unsigned PC,unsigned *Mem,unsigned *instruction)
{	//check if PC = a byte (word aligned) 
	if(PC % 4 == 0)
	{	//set instruction to instruction sent from pc
		*instruction = Mem[PC >> 2];
		return 0;
	}
	else 
		return 1; // HALT
}


/* instruction partition */
/* 10 Points */
void instruction_partition(unsigned instruction, unsigned *op, unsigned *r1,unsigned *r2, unsigned *r3, unsigned *funct, unsigned *offset, unsigned *jsec)
{	//    (((1<<k) - 1)) & (instruction >> p); k=number of bits to take, p = place to start taking from
	*op = (((1<<6) - 1)) & (instruction >> 26); // instruction [31-26]
	*r1 = (((1<<5) - 1) & (instruction >> 21));// instruction [25-21]
	*r2 = (((1<<5) - 1) & (instruction >> 16));	// instruction [20-16]
	*r3 = (((1<<5) - 1) & (instruction >> 11));	// instruction [15-11]
	*funct = (((1<<6) - 1) & (instruction >> 0));	// instruction [5-0]
	*offset = (((1<<16) - 1) & (instruction >> 0));	// instruction [15-0]
	*jsec = (((1<<26) - 1) & (instruction >> 0));	// instruction [25-0]
}



/* instruction decode */
/* 15 Points */
int instruction_decode(unsigned op,struct_controls *controls)
{
	// hope these are correct
	switch(op)
	{
		case 0: // 000000 R-Type operations 
			controls->RegDst = 1;
			controls->Jump = 0;
			controls->Branch = 0;
			controls->MemRead = 0;
			controls->MemtoReg = 0;
			controls->ALUOp = 7;
			controls->MemWrite = 0;
			controls->ALUSrc = 0;
			controls->RegWrite = 1;
			break;
		case 2: // 000010 jump
			controls->RegDst = 0;
			controls->Jump = 1;
			controls->Branch = 0;
			controls->MemRead = 0;
			controls->MemtoReg = 0;
			controls->ALUOp = 0;
			controls->MemWrite = 0;
			controls->ALUSrc = 0;
			controls->RegWrite = 0;
			break;
		case 4: // 000100 branch on equal
			controls->RegDst = 2;
			controls->Jump = 0;
			controls->Branch = 1;
			controls->MemRead = 0;
			controls->MemtoReg = 2;
			controls->ALUOp = 1;
			controls->MemWrite = 0;
			controls->ALUSrc = 0;
			controls->RegWrite = 0;
			break;
		case 8: // 001000 add immediate
			controls->RegDst = 0;
			controls->Jump = 0;
			controls->Branch = 0;
			controls->MemRead = 0;
			controls->MemtoReg = 0;
			controls->ALUOp = 0;
			controls->MemWrite = 0;
			controls->ALUSrc = 1;
			controls->RegWrite = 1;
			break;
		case 10: // 001010 set less than immediate 
			controls->RegDst = 0;
			controls->Jump = 0;
			controls->Branch = 0;
			controls->MemRead = 0;
			controls->MemtoReg = 0;
			controls->ALUOp = 2;
			controls->MemWrite = 0;
			controls->ALUSrc = 1;
			controls->RegWrite = 1;
			break;
		case 11: // 001011 set less than immediate unsigned 
			controls->RegDst = 0;
			controls->Jump = 0;
			controls->Branch = 0;
			controls->MemRead = 0;
			controls->MemtoReg = 0;
			controls->ALUOp = 3;
			controls->MemWrite = 0;
			controls->ALUSrc = 1;
			controls->RegWrite = 1;
			break;
		case 15: // 001111 load upper immediate 
			controls->RegDst = 0;
			controls->Jump = 0;
			controls->Branch = 0;
			controls->MemRead = 0;
			controls->MemtoReg = 0;
			controls->ALUOp = 6;
			controls->MemWrite = 0;
			controls->ALUSrc = 1;
			controls->RegWrite = 1;
			break;
		case 35: // 100011 load word
			controls->RegDst = 0;
			controls->Jump = 0;
			controls->Branch = 0;
			controls->MemRead = 1;
			controls->MemtoReg = 1;
			controls->ALUOp = 0;
			controls->MemWrite = 0;
			controls->ALUSrc = 1;
			controls->RegWrite = 1;
			break;
		case 43: // 101011 store word 
			controls->RegDst = 2;
			controls->Jump = 0;
			controls->Branch = 0;
			controls->MemRead = 0;
			controls->MemtoReg = 2;
			controls->ALUOp = 0;
			controls->MemWrite = 1;
			controls->ALUSrc = 1;
			controls->RegWrite = 0;
			break;
		
		default: // Halt if no recognizable op code
			return 1;
	}
	return 0;
}

/* Read Register */
/* 5 Points */
void read_register(unsigned r1,unsigned r2,unsigned *Reg,unsigned *data1,unsigned *data2)
{	//assign data 1 and 2 = r1 and r2 from the register
	*data1 = Reg[r1]; 
	*data2 = Reg[r2];
}


/* Sign Extend */
/* 10 Points */
void sign_extend(unsigned offset,unsigned *extended_value) // MINE
{
	unsigned firstBit = offset >> 15; // first bit of the 16 bit offset
	
	if(firstBit == 1) // if the first bit is 1, it is negative 
		*extended_value = offset | 0xFFFF0000; // 11111111111111110000000000000000
	else 
		*extended_value = offset & 0x0000FFFF; // 00000000000000001111111111111111
}

/* ALU operations */
/* 10 Points */
int ALU_operations(unsigned data1,unsigned data2,unsigned extended_value,unsigned funct,char ALUOp,char ALUSrc,unsigned *ALUresult,char *Zero)
{
	//ALUOp and funct determines what operation is being made
	if(ALUOp == 7){//instruction is an R-type function so use funct instead of ALUresult
		switch(funct)
		{
			case 32: 
				funct = 0;
				break;
			case 34:
				funct = 1;
				break;
			case 42:
				funct = 2;
				break;
			case 43:
				funct = 3;
				break;
			case 36:
				funct = 4;
				break;
			case 37: 
				funct = 5;
				break;
			case 6:
				funct = 6;
				break;
			case 39:
				funct = 7;
				break;
			default:
				return 1;
		}
		if(ALUSrc == 0){//ALUSrc determines whether to use extended value (when ALUSrc is 1) or data2 (when ALUSrc is 0)
			ALU(data1, data2, funct, ALUresult, Zero);
		}
		else if (ALUSrc == 1){
			ALU(data1, extended_value, funct, ALUresult, Zero);
		}
	}
	else //use ALUresult instead of funct
	{
		if(ALUSrc == 0){//ALUSrc determines whether to use extended value (when ALUSrc is 1) or data2 (when ALUSrc is 0)
			ALU(data1, data2, ALUOp, ALUresult, Zero);
		}
		else if (ALUSrc == 1){
			ALU(data1, extended_value, ALUOp, ALUresult, Zero);
		}
	}
	return 0;
}

/* Read / Write Memory */
/* 10 Points */
int rw_memory(unsigned ALUresult,unsigned data2,char MemWrite,char MemRead,unsigned *memdata,unsigned *Mem)
{	
	if(MemRead == 1)
	{
		if(ALUresult % 4 != 0) 
			return 1;
		*memdata = Mem[ALUresult >> 2];
	}
	if(MemWrite == 1) 
	{
		if(ALUresult % 4 != 0) 
			return 1;
		Mem[ALUresult >> 2] = data2;
	}
	
	return 0;
}


/* Write Register */
/* 10 Points */
void write_register(unsigned r2,unsigned r3,unsigned memdata,unsigned ALUresult,char RegWrite,char RegDst,char MemtoReg,unsigned *Reg)
{
	if(RegWrite == 1){
		if(MemtoReg == 0){//means from ALU
			if(RegDst == 0){ Reg[r2] = ALUresult;}//if RegDst is 0 then Reg[r2]
			else if(RegDst == 1){Reg[r3] = ALUresult;}//if RegDst then Reg[r3]
		}
		else if (MemtoReg == 1){//means from memory
				if(RegDst == 0)Reg[r2] = memdata;
				else if(RegDst == 1){Reg[r3] = memdata;}
		}
	}
}

/* PC update */
/* 10 Points */
void PC_update(unsigned jsec,unsigned extended_value,char Branch,char Jump,char Zero,unsigned *PC)
{
	*PC += 4;
	// Left shift bits of jsec by 2 and use upper 4 bits of PC
	if(Jump == 1) 
		*PC = (*PC & 0xF0000000) | (jsec << 2);
	// Branch forward with extended_value
	if(Branch == 1 && Zero == 1)
		*PC += extended_value << 2;
}

