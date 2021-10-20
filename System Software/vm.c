/**
Nawras Rawas Qalaji
Sara Erika De Mesa
Jaralliesse Bastida
Gabriel Kim-Perez
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PAS_LENGTH 500

int base(int L, int BP, int* pas);
void print_execution(int line, char *opname, int *IR, int PC, int BP, int SP,
							int DP, int *pas, int GP);

int main(int argc, char *argv[])
{
	FILE *input;
	input = fopen(argv[1], "r");

	// initial values
	int pas[500] = {0}; // process address space
	int IC = 0; // instruction counter that increases by 3 for each instruction
	int GP = IC; // global pointer that points to DATA segment
	int DP = IC - 1; // data pointer to access variables in main
	int FREE = IC + 40; // points to heap
	int BP = IC; // points to base of DATA or activation records
	int PC = 0; // stack pointer that points to top of stack
	int SP = MAX_PAS_LENGTH;
	int IR[150] = {0};
	int line = 0;

	int i = 0;
	int IC2 = 0;

	if (input == NULL){
		printf("input is equal to NULL");
	 return -1;
  }

	//scan input
	fscanf(input, "%d", &pas[IC]);

	while(!feof(input)){
		IC=IC+1;
		fscanf(input, "%d", &pas[IC]);
	}
	IC=IC+1;

	fclose(input);

	// Setting up registers
	GP = IC;
	DP = IC-1;
	FREE = IC+10;
	BP = IC;
	PC = 0;
	SP = MAX_PAS_LENGTH;
	IC2 = IC;

	printf("                \t\tPC\tBP\tSP\tDP\tdata\n");
	printf("Initial values: \t\t%d\t%d\t%d\t%d\n", PC, BP, SP, DP);

	while (IC > 0)
	{
    //load instructions into IR
		IR[PC] = pas[PC];
		IR[PC+1] = pas[PC+1];
		IR[PC+2] = pas[PC+2];

		// Increment PC by 3 for each new instruction
		PC = PC+3;
		// Instruction has been fetched so remove from total
		IC = IC-3;
	}
 
  //reset head back to zero to execute instructions from beginning
	PC = 0;

	// Execute cycle
	while(IC2 > 0)
	{
    char* opname = malloc((sizeof(char) * 4));
    //check which line we are on, divide PC by 3 since 3 nums per instruction
    line = PC/3; 
    //store current instructions to execute
    int IR2[] = {IR[PC], IR[PC+1], IR[PC+2]}; 
    
    
		//check if JMP or JPC command, if not Increment by 3 to load the next instruction
    if(IR2[0] != 7){
      PC = PC + 3;
    }
    else if(IR2[0] != 8){
      if(pas[SP] != 0 || pas[DP] != 0){
      PC = PC + 3;
      }
    } 
    
		// LIT
		if (IR2[0] == 1)
		{
			if (BP == GP)
			{
				DP = DP + 1;
				pas[DP] = IR2[2];
			} else {
				SP = SP - 1;
				pas[SP] = IR2[2];
			}
			opname = "LIT";
		}

		// OPR 0 #
		if (IR2[0] == 2)
		{

			// RTN
			if (IR2[2] == 0)
			{
				SP = BP + 1;
				BP = pas[SP-2];
				PC = pas[SP-3];
				opname = "RTN";
			}

			// NEG
			if (IR2[2] == 1)
			{
				if (BP == GP)
					pas[DP] = -1 * pas[DP];
				else
					pas[SP] = -1 * pas[SP];
				opname = "NEG";
			}

			//add
			if(IR2[2] == 2){
				if (BP == GP)
				{
				  DP = DP - 1;
				  pas[DP] = pas[DP] + pas[DP + 1];
				}
				else
				{
				  SP = SP + 1;
				  pas[SP] = pas[SP] + pas[SP - 1];
				}
				 opname = "ADD";
			}

			//SUB
			if(IR2[2] == 3){
				if(BP == GP)
				{
				  DP = DP - 1;
				  pas[DP] = pas[DP] - pas[DP + 1];
				}
				else
				{
				  SP = SP + 1;
				  pas[SP] = pas[SP] - pas[SP - 1];
				}
				 opname = "SUB";
			}

			//MUL
			if(IR2[2] == 4){
				if (BP == GP)
				{
					DP = DP - 1;
					pas[DP] = pas[DP] * pas[DP + 1];
				}
				else
				{
					SP = SP + 1;
					pas[SP] = pas[SP] * pas[SP - 1];
				}
					opname = "MUL";
			}

			if(IR2[2] == 5){
				if(BP == GP)
				{
				  DP = DP - 1;
				  pas[DP] = pas[DP] / pas[DP + 1];
				}
				else
				{
				  SP = SP + 1;
				  pas[SP] = pas[SP] / pas[SP - 1];
				}
			opname = "DIV";
			}

			//ODD
			if(IR2[2] == 6){
				if (BP == GP){
					pas[DP] = pas[DP] % 2;
				}
				else{
					pas[SP] = pas[SP] % 2;
				}
				opname = "ODD";
			}

			//MOD
			if(IR2[2] == 7){

				if (BP == GP)
				{
					DP = DP - 1;
					pas[DP] = pas[DP] % pas[DP + 1];
				}
				else
				{
					SP = SP + 1;
					pas[SP] = pas[SP] % pas[SP - 1];
				}
				opname = "MOD";
			}

			//EQL
			if(IR2[2] == 8){
				if(BP == GP)
				{
				  DP = DP - 1;
				  pas[DP] = pas[DP] == pas[DP + 1];
				}
				else
				{
				  SP = SP + 1;
				  pas[SP] = pas[SP] == pas[SP - 1];
				}
				opname = "EQL";
			}

			//NEQ
			if(IR2[2] == 9){
				if(BP == GP)
				{
				  DP = DP - 1;
				  pas[DP] = pas[DP] != pas[DP + 1];
				}
				else
				{
				  SP = SP + 1;
				  pas[SP] = pas[SP] != pas[SP - 1];
				}
				opname = "NEQ";
			}

			//LSS
			if(IR2[2] == 10){
				if(BP == GP)
				{
				  DP = DP - 1;
				  pas[DP] = pas[DP] < pas[DP + 1];
				}
				else
				{
				  SP = SP + 1;
				  pas[SP] = pas[SP] < pas[SP - 1];
				}
				opname = "LSS";
			}

			//LEQ
			if(IR2[2] == 11){
				if(BP == GP)
				{
				  DP = DP - 1;
				  pas[DP] = pas[DP] <= pas[DP + 1];
				}
				else
				{
				  SP = SP + 1;
				  pas[SP] = pas[SP] <= pas[SP - 1];
				}
				opname = "LEQ";
			}

			//GTR
			if(IR2[2] == 12){
				if(BP == GP)
				{
				  DP = DP - 1;
				  pas[DP] = pas[DP] > pas[DP + 1];
				}
				else
				{
				  SP = SP + 1;
				  pas[SP] = pas[SP] > pas[SP - 1];
				}
				opname = "GTR";
			}

			//GEQ
			if(IR2[2] == 13){
				if(BP == GP)
				{
				  DP = DP - 1;
				  pas[DP] = pas[DP] >= pas[DP + 1];
				}
				else
				{
				  SP = SP + 1;
				  pas[SP] = pas[SP] >= pas[SP - 1];
				}
				opname = "GEQ";
			}
		}

		// LOD L, M
		// Note: base(L) is the function given to us, and M is the variable
		// that is loaded from the ISA
		if(IR2[0] == 3){
			if (BP == GP)
			{
				DP = DP + 1;
				pas[DP] = pas[GP + IR2[2]];
			}
			else
			{
				if (base(IR2[1], BP, pas) == GP)
				{
					SP = SP - 1;
					pas[SP] = pas[GP + IR2[2]];
				}
				else
				{
					SP = SP - 1;
					pas[SP] = pas[base(IR2[1], BP, pas) - IR2[2]];
				}
			}
			opname = "LOD";
		}

		// STO L, M
		if(IR2[0] == 4){
			if (BP == GP)
			{
				pas[GP + IR2[2]] = pas[DP];
				DP = DP - 1;
			}
			else
			{
				if (base(IR2[1], BP, pas) == GP)
				{
					pas[GP + IR2[2]] = pas[SP];
					SP = SP + 1;
				}
				else
				{
					pas[base(IR2[1], BP, pas) - IR2[2]] = pas[SP];
					SP = SP + 1;
				}
			}
		opname = "STO";
		}

		//CAL L, M
		if(IR2[0] == 5){
			pas[SP - 1]  = base(IR2[1], BP, pas);     // static link (SL)
			pas[SP - 2]  = BP;          // dynamic link (DL)
			pas[SP - 3]  = PC;          // return address (RA)
			BP = SP - 1;
			PC = IR2[2];
			opname = "CAL";
		}

		//INC 0, M
		if(IR2[0] == 6){
			if (BP == GP)
			{
			  DP = DP + IR2[2];
			}
			else
			{
			  SP = SP - IR2[2];
			}
			opname = "INC";
		}

		//JMP 0, M
		if(IR2[0] == 7){
			PC = IR2[2];
			opname = "JMP";
		}

		//JPC 0, M(IR2[2])
		if(IR2[0] == 8){
			if (BP == GP)
			{
				if (pas[DP] == 0)
				{
					PC = IR2[2];
				}
				DP = DP - 1;
			}
			else
			{
				if(pas[SP] == 0)
				{
					PC = IR2[2];
				}
				SP = SP + 1;
			}
		opname = "JPC";
		}

		//SYS
		if (IR2[0] == 9)
		{
			// SYS 0 1
			if (IR2[2] == 1) //write
			{
				printf("Top of Stack Value: ");
				if (BP == GP)
				{
					printf("%d\n", pas[DP]);
					DP = DP - 1;
				} else {
					printf("%d\n", pas[SP]);
					SP = SP + 1;
				}
			}

			if (IR2[2] == 2) // read
			{ 
				printf("Please Enter an Integer: ");
				if (BP == GP)
				{
					DP = DP + 1;
					scanf("%d", &pas[DP]);
				} else {
					SP = SP - 1;
					scanf("%d", &pas[SP]);
				}
			}

			if (IR2[2] == 3)
			{
				//SYS 0, 3
				//Set Halt flag to zero (End of program).
				//ends while loop containing fetch & execute cycle
				IC2 = 0;
			}
			opname = "SYS";
		}
    
		print_execution(line, opname, IR2, PC, BP, SP, DP, pas, GP);
    
    //Instruction has been executed so remove it from total
		IC2 = IC2 - 3;
		
	}

	return 0;
}

// Base function
int base(int L, int BP, int* pas)
{
	int arb = BP; // arb = activation record base
	while(L > 0)
	{
		arb = pas[arb];
		L--;
	}
	return arb;
}

// Print function
void print_execution(int line, char *opname, int *IR, int PC, int BP, int SP,
							int DP, int *pas, int GP)
{
	int i;
	// print out instructions and registers
	printf("%2d\t%s\t%d\t%d\t%d\t%d\t%d\t%d\t", line, opname, IR[1], IR[2], PC, BP, SP, DP);
	// print data section
	for (i = GP; i <= DP; i++)
		printf("%d ", pas[i]);
	printf("\n");

	// print stack
  printf("\tstack : ");
	for (i = MAX_PAS_LENGTH - 1; i >= SP; i--)
		printf("%d ", pas[i]);
	printf("\n");
}
