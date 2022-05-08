#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "compiler.h"
#define MAX_CODE_LENGTH 1000
#define MAX_SYMBOL_COUNT 100
#define ERR_DETECT FALSE

instruction * code;
symbol * table;

lexeme token;

int cIndex = 0;	//code index
int tIndex = 0;	//symbol table index
int symidx = 0;	//symbol index
int level = -1;	//lexagraphical level
int listLevel = 0;	//list index
int errDetect = 0;

void emit(int opname, int level, int mvalue);
void addToSymbolTable(int k, char n[], int v, int l, int a, int m);
void printparseerror(int err_code);
void printsymboltable();
void printassemblycode();

void program(instruction *code, lexeme *list);
void block(lexeme *list);
void const_declaration(lexeme *list);
int var_declaration(lexeme *list);
void procedure_declaration(lexeme *list);
void statement(lexeme *list);
void condition(lexeme *list);
void expression(lexeme *list);
void term(lexeme *list);
void factor(lexeme *list);
int findSymbol(int kind);
int multipleDeclaration();
void mark();

instruction* parse(lexeme *list, int printTable, int printCode)
{
	code = malloc(MAX_CODE_LENGTH* sizeof(instruction));
	table = malloc(MAX_SYMBOL_COUNT* sizeof(symbol));

	//program
	token = list[listLevel];

	program(code, list);
  if (errDetect == 1) return code = NULL;
  
	if (printTable == 1)
		printsymboltable();
	if (printCode == 1)
		printassemblycode();

	/*this line is EXTREMELY IMPORTANT, you MUST uncomment it
		when you test your code otherwise IT WILL SEGFAULT in
		vm.o THIS LINE IS HOW THE VM KNOWS WHERE THE CODE ENDS
		WHEN COPYING IT TO THE PAS*/

	code[cIndex].opcode = -1;
	return code;
}

void program(instruction *code, lexeme *list)
{
 	emit(7, 0, 0);	//JMP

	addToSymbolTable(3, "main", 0, 0, 0, -1);

	level = -1;

	// BLOCK function goes here
	block(list);
	if (errDetect == 1) return;
	
	if (token.type != 32)
	{
		errDetect = 1;
		printparseerror(1);
		return;
	}
	
	if(errDetect == 1) return;

	emit(9, 0, 3);	// HALT

	for (int i = 0; i < cIndex; i++)
	{
		if (code[i].opcode == 5)
		{
			code[i].m = table[code[i].m].addr;
		}
	}
	code[0].m = table[0].addr;

}

void block(lexeme *list)
{
	if (errDetect == 1) return;
	level++;
	int procedure_idx = tIndex - 1;

	//check what the token represents
	// CONST DECLARATION
	const_declaration(list);
	if (errDetect == 1) return;

	// VARIABLE DECLARATION
	int x = var_declaration(list);
	if (errDetect == 1 || x == -1) return;

	// PROCEDURE DECLARATION
	procedure_declaration(list);
	if (errDetect == 1) return;

	table[procedure_idx].addr = cIndex * 3;

	if (level == 0)
	{
		// emit INC (M = x)
		emit(6, 0, x);
	}
	else
	{
		//emit INC (M = x + 3)
		emit(6, 0, x + 3);
	}

	statement(list);
  if (errDetect == 1){
  return;
}
	mark();
	level--;
  }

void const_declaration(lexeme *list)
{
	char name[12] = "";

	//const 1
	if (token.type == 1)
	{
		do { 	// get next token
			token = list[++listLevel];
			//error, identsym 14
			if (token.type != 14)
			{
				errDetect = 1;
				printparseerror(2);
				return;
			}

			symidx = multipleDeclaration();

			//error, no symbol found
			if (symidx != -1)
			{
				errDetect = 1;
				printparseerror(5);
				return;
			}

			strcpy(name, token.name);

			//get next token
			token = list[++listLevel];
			//error check assignsym
			if (token.type != 16)
			{
				errDetect = 1;
				printparseerror(16);
				return;
			}

			//get next token
			token = list[++listLevel];

			//error numbersym
			if (token.type != 15)
			{
				errDetect = 1;
				printparseerror(15);
				return;
			}

			//add to symbol table (kind 1, saved name, number, level, 0, unmarked)
			addToSymbolTable(1, name, token.value, level, 0, -1);	// ------

			//get next token
			token = list[++listLevel];	//------
		}
		while (token.type == 31);	//commasym ------
		//semicolonsym error
		if (token.type != 33)
		{
			if (token.type == 14)	//identsym 
			{ 
				errDetect = 1;
				printparseerror(2);
				return;
			}
			else
			{
				errDetect = 1;
				printparseerror(14);
				return;
			}
		}

		//get next token
		token = list[++listLevel];
	}
}

int var_declaration(lexeme *list)
{
	int numVars = 0;

	if (token.type == 2)	// varsym
	{
		do {

			// get next token
			token = list[++listLevel];

			//error identsym
			if (token.type != 14)
			{
				errDetect = 1;
				printparseerror(3);
				return -1;
			}

			symidx = multipleDeclaration();
			//error symbol not found
			if (symidx != -1)
			{

				errDetect = 1;
				printparseerror(5);
				return -1;
			}

			if (level == 0)
			{
				numVars++;
				addToSymbolTable(2, token.name, 0, level, numVars - 1, -1);
			}
			else
			{
				numVars++;
				addToSymbolTable(2, token.name, 0, level, numVars + 2, -1);
			}
			// get next token
			token = list[++listLevel];
		}
		while (token.type == 31);	// commma

		if (token.type != 33)	// semicolonsym
		{
			if (token.type == 14)	//identsym 
			{ 
				errDetect = 1;
				printparseerror(13);
				return -1;
			}
			else
			{
				errDetect = 1;
				printparseerror(14);
				return -1;
			}
		}
		// get next token

		token = list[++listLevel];
	}
	return numVars;
}

void procedure_declaration(lexeme *list)
{
	if (errDetect == 1) return;
	while (token.type == 3)	// procsym
	{
		// get next token
		token = list[++listLevel];

		if (token.type != 14)
		{
			errDetect = 1;
			printparseerror(14);
			return;
		}
		symidx = multipleDeclaration();
		if (symidx != -1)
		{
			errDetect = 1;
			printparseerror(5);
			return;
		}

		addToSymbolTable(3, token.name, 0, level, 0, -1);

		// get next token
		token = list[++listLevel];
		if (token.type != 33)
		{
			errDetect = 1;
			printparseerror(4);
			return;
		}

		// get next token
		token = list[++listLevel];

		block(list);
		if (errDetect == 1) return;

		if (token.type != 33)
		{
			errDetect = 1;
			printparseerror(18);
			return;
		}
		// get next token
		token = list[++listLevel];
		emit(2, 0, 0);	//RTN
	}
}

void statement(lexeme *list)
{
	if (errDetect == 1) return;
	int jpcIdx = 0;
	int jmpIdx = 0;
	int loopIdx = 0;

	if (token.type == 14)	// ident sym
	{
		symidx = findSymbol(2);
		//if symidx is -1 then symbol not found
		if (symidx == -1)
		{
			if (findSymbol(1) != findSymbol(3))
			{
				errDetect = 1;
				printparseerror(6);
				return;
			}
			else
			{
				errDetect = 1;
				printparseerror(5);
				return;
			}
		}
		token = list[++listLevel];

		if (token.type != 16)
		{
			errDetect = 1;
			printparseerror(5);
			return;
		}
		token = list[++listLevel];

		// EXPRESSION function
		expression(list);
		if (errDetect == 1) 
			return;

		// emit STO
		emit(4, (level - table[symidx].level), table[symidx].addr);
		return;
	}
	if (token.type == 4)
	{
		do { 	token = list[++listLevel];
				statement(list);
				if (errDetect == 1) return;
		} while (token.type == 33);
		if (token.type != 5)	//if there is no end sym
		{
			if (token.type == 14 ||
				token.type == 4 ||
				token.type == 8 ||
				token.type == 12 ||
				token.type == 13 ||
				token.type == 12 ||
				token.type == 11)
			{
				errDetect = 1;
				printparseerror(15);
				return;
			}
			else
			{	
				errDetect = 1;
				printparseerror(16);
				return;
			}
		}
		token = list[++listLevel];
		return;
	}
	if (token.type == 8)
	{
		token = list[++listLevel];
		condition(list);
		if (errDetect == 1){
		  return;
		}

		jpcIdx = cIndex;
		// emit JPC here
		emit(8, 0, jpcIdx);
		if (token.type != 9)
		{
			errDetect = 1;
			printparseerror(8);
			return;
		}
		token = list[++listLevel];
		statement(list);
		if (errDetect == 1) return;
		if (token.value == 10)
		{
			jmpIdx = cIndex;
			//emit JMP here
			emit(7, 0, jmpIdx);
			code[jpcIdx].m = cIndex * 3;
			token = list[++listLevel];
			statement(list);
			if (errDetect == 1) return;
			code[jmpIdx].m = cIndex * 3;
		}
		else
		{
			code[jpcIdx].m = cIndex * 3;
		}
		return;
	}
	if (token.type == 6)
	{
		token = list[++listLevel];
		loopIdx = cIndex;
		condition(list);
		if (errDetect == 1) return;
		if (token.type != 7)
		{
			errDetect = 1;
			printparseerror(9);
			return;
		}
		token = list[++listLevel];
		jpcIdx = cIndex;
		// emit JPC here
		emit(8, 0, jpcIdx);
		statement(list);
		if (errDetect == 1) return;
		
		// emit jmp m = loopIdx*3
		emit(7, 0, loopIdx *3);
		code[jpcIdx].m = cIndex * 3;
		return;
	}
	if (token.type == 13)
	{
		token = list[++listLevel];
		if (token.type != 14)
		{
			errDetect = 1;
			printparseerror(5);
			return;
		}

		symidx = findSymbol(2);
		if (symidx == -1)
		{
			if (findSymbol(1) != findSymbol(3))
			{
				errDetect = 1;
				printparseerror(18);
				return;
			}
			else
			{
				errDetect = 1;
				printparseerror(5);
				return;
			}
		}
		token = list[++listLevel];
		// emit read
		emit(9, 0, 2);
		// emit sto (L = level - table[tIndex].level) (M = table[tIndex].addr)
		emit(4, level - table[symidx].level, table[symidx].addr);
		return;
	}
	if (token.type == 12)
	{
		token = list[++listLevel];
		expression(list);
		if (errDetect == 1) return;
		// emit write
		emit(9, 0, 1);
		return;
	}
	if (token.type == 11)
	{
		token = list[++listLevel];
		symidx = findSymbol(3);
		if (symidx == -1)
		{
			if (findSymbol(1) != findSymbol(2))
			{
				errDetect = 1;
				printparseerror(7);
				return;
			}
			else
			{
				errDetect = 1;
				printparseerror(-1);
				return;
			}
		}
		token = list[++listLevel];
		// emit CAL (L = level - table[tindex].level, symidx)
		emit(5, level - table[symidx].level, symidx);
	}
}

void condition(lexeme *list)
{
	if (errDetect == 1) return;
	if (token.type == 28)
	{
		token = list[++listLevel];
		expression(list);
		if (errDetect == 1) return;
		// emit odd
		emit(2, 0, 6);
	}
	else
	{
		expression(list);
		if (errDetect == 1) return;
		if (token.type == 22)
		{
			token = list[++listLevel];
			expression(list);
			if (errDetect == 1) return;
			// emit eql
			emit(2, 0, 8);
		}
		else if (token.type == 23)
		{
			token = list[++listLevel];
			expression(list);
			if (errDetect == 1) return;
			// emit neq
			emit(2, 0, 9);
		}
		else if (token.type == 24)
		{
			token = list[++listLevel];
			expression(list);
			if (errDetect == 1) return;
			// emit lss
			emit(2, 0, 10);
		}
		else if (token.type == 25)
		{
			token = list[++listLevel];
			expression(list);
			if (errDetect == 1) return;
			// emit leq
			emit(2, 0, 11);
		}
		else if (token.type == 26)
		{
			token = list[++listLevel];
			expression(list);
			if (errDetect == 1) return;
			// emit gtr
			emit(2, 0, 12);
		}
		else if (token.type == 27)
		{
			token = list[++listLevel];
			expression(list);
			if (errDetect == 1) return;
			// emit geq
			emit(2, 0, 13);
		}
		else
		{
			errDetect = 1;
			printparseerror(10);
      return;
		}
	}
}

void expression(lexeme *list)
{
	if (errDetect == 1) return;
	if (token.type == 18)
	{
		token = list[++listLevel];
		term(list);
		if (errDetect == 1) return;
		// emit NEG
		emit(2, 0, 1);
		while (token.type == 17 || token.type == 18)
		{
			if (token.type == 17)
			{
				token = list[++listLevel];
				term(list);
				if (errDetect == 1) return;
				// emit add
				emit(2, 0, 2);
			}
			else
			{
				token = list[++listLevel];
				term(list);
				if (errDetect == 1) return;
				// emit SUB
				emit(2, 0, 3);
			}
		}
	}
	else
	{
		if (token.type == 17)
			token = list[++listLevel];
		term(list);
		if (errDetect == 1) return;
		while (token.type == 17 || token.type == 18)
		{
			if (token.type == 17)
			{
				token = list[++listLevel];
				term(list);
				if (errDetect == 1) return;
				// emit add
				emit(2, 0, 2);
			}
			else
			{
				token = list[++listLevel];
				term(list);
				if (errDetect == 1) return;
				// emit SUB
				emit(2, 0, 3);
			}
		}
	}
	if (token.type == 29 || token.type == 14 || token.type == 15 || token.type == 28)
	{
		errDetect = 1;
		printparseerror(17);
		return;
	}
}

void term(lexeme *list)
{	
	if (errDetect == 1) return;
	factor(list);
	if (errDetect == 1) return;

	while (token.type == 19 || token.type == 20 || token.type == 21)
	{
		if (token.type == 19)
		{
			token = list[++listLevel];
			factor(list);
			if (errDetect == 1) return;
			// emit mul
			emit(2, 0, 4);
		}
		else if (token.type == 20)
		{
			token = list[++listLevel];
			factor(list);
			if (errDetect == 1) return;
			// emit div
			emit(2, 0, 5);
		}
		else
		{
			token = list[++listLevel];
			factor(list);
			if (errDetect == 1) return;
			// emit mod
			emit(2, 0, 7);
		}
	}
}

void factor(lexeme *list)
{
	if (errDetect == 1) return;
	if (token.type == 14)
	{
		int symIdx_var = findSymbol(2);
		int symIdx_const = findSymbol(1);

		if (symIdx_var == -1 && symIdx_const == -1)
		{
			//error symbol type 3 not found
			if (findSymbol(3) != -1)
			{
				errDetect = 1;
				printparseerror(11);
				return;
			}
			// error 
			else
			{
				errDetect = 1;
				printparseerror(19);
				return;
			}
		}
		if (symIdx_var == -1)
		{
			// emit LIT M = table[symIdx_const].val
			emit(1, 0, table[symIdx_const].val);
		}
		else if (symIdx_const == -1 || table[symIdx_var].level > table[symIdx_const].level)
		{
			// emit LOD (L = level-table[symIdx_var].level, M = table[symIdx_var].addr)
			emit(3, level - table[symIdx_var].level, table[symIdx_var].addr);
		}
		else
		{
			// emit LIT M = table[symIdx_const].val
			emit(1, 0, table[symIdx_const].val);
		}
		token = list[++listLevel];
	}
	else if (token.type == 15)
	{
		// emit LIT
		emit(1, 0, token.value);
		token = list[++listLevel];
	}
	else if (token.type == 29)
	{
		token = list[++listLevel];
		expression(list);
    if (errDetect == 1) return;

		if (token.type != 30)
		{
			errDetect = 1;
			printparseerror(12);
			return;
		}
		token = list[++listLevel];
	}
	else
	{
		errDetect = 1;
		printparseerror(2);
		return;
	}
}

//search table for specificed symbol and returns max index of symbol
int findSymbol(int kind)
{
	int maxIndex = -1;
	int currentLevel = -1;

	for (int i = 0; i < tIndex; i++)
	{
		if (table[i].kind == kind && strcmp(table[i].name, token.name) == 0 && table[i].mark == -1)
		{
			if (currentLevel < table[i].level)
			{
				currentLevel = table[i].level;
				maxIndex = i;
			}
		}
	}

	//found nothing return -1
	return maxIndex;
}

//search table for specificed symbol and returns index of symbol 
int multipleDeclaration()
{

	for (int i = 0; i < tIndex; i++)
	{
		if (strcmp(table[i].name, token.name) == 0 && table[i].mark == -1)
		{
			if (i == level)
			{
				return i;
			}
		}
	}

	//found nothing return -1
	return -1;
}

// Search the table from the end until an unmarked entry is encountered 
void mark()
{

	for (int i = tIndex; i >= 0; i--)
	{
		if (table[i].level == level && table[i].mark == -1)
		{
			table[i].mark = 1;
		}
		else if (table[i].level < level && table[i].mark == -1)
		{
			break;
		}
	}
}

void emit(int opname, int level, int mvalue)
{
	code[cIndex].opcode = opname;
	code[cIndex].l = level;
	code[cIndex].m = mvalue;
	cIndex++;
}

void addToSymbolTable(int k, char n[], int v, int l, int a, int m)
{
	table[tIndex].kind = k;
	strcpy(table[tIndex].name, n);
	table[tIndex].val = v;
	table[tIndex].level = l;
	table[tIndex].addr = a;
	table[tIndex].mark = m;
	tIndex++;
}

void printparseerror(int err_code)
{
	switch (err_code)
	{
		case 1:
			printf("Parser Error: Program must be closed by a period\n");
			break;
		case 2:
			printf("Parser Error: Constant declarations should follow the pattern 'ident := number {, ident := number}'\n");
			break;
		case 3:
			printf("Parser Error: Variable declarations should follow the pattern 'ident {, ident}'\n");
			break;
		case 4:
			printf("Parser Error: Procedure declarations should follow the pattern 'ident ;'\n");
			break;
		case 5:
			printf("Parser Error: Variables must be assigned using :=\n");
			break;
		case 6:
			printf("Parser Error: Only variables may be assigned to or read\n");
			break;
		case 7:
			printf("Parser Error: call must be followed by a procedure identifier\n");
			break;
		case 8:
			printf("Parser Error: if must be followed by then\n");
			break;
		case 9:
			printf("Parser Error: while must be followed by do\n");
			break;
		case 10:
			printf("Parser Error: Relational operator missing from condition\n");
			break;
		case 11:
			printf("Parser Error: Arithmetic expressions may only contain arithmetic operators, numbers, parentheses, constants, and variables\n");
			break;
		case 12:
			printf("Parser Error: (must be followed by)\n");
			break;
		case 13:
			printf("Parser Error: Multiple symbols in variable and constant declarations must be separated by commas\n");
			break;
		case 14:
			printf("Parser Error: Symbol declarations should close with a semicolon\n");
			break;
		case 15:
			printf("Parser Error: Statements within begin-end must be separated by a semicolon\n");
			break;
		case 16:
			printf("Parser Error: begin must be followed by end\n");
			break;
		case 17:
			printf("Parser Error: Bad arithmetic\n");
			break;
		case 18:
			printf("Parser Error: Confliciting symbol declarations\n");
			break;
		case 19:
			printf("Parser Error: Undeclared identifier\n");
			break;
		default:
			printf("Implementation Error: unrecognized error code\n");
			break;
	}

	free(code);
	free(table);
}

void printsymboltable()
{
	int i;
	printf("Symbol Table:\n");
	printf("Kind | Name        | Value | Level | Address | Mark\n");
	printf("---------------------------------------------------\n");
	for (i = 0; i < tIndex; i++)
		printf("%4d | %11s | %5d | %5d | %5d | %5d\n", table[i].kind, table[i].name, table[i].val, table[i].level, table[i].addr, table[i].mark);

	free(table);
	table = NULL;
}

void printassemblycode()
{
	int i;
	printf("Line\tOP Code\tOP Name\tL\tM\n");
	for (i = 0; i < cIndex; i++)
	{
		printf("%d\t", i);
		printf("%d\t", code[i].opcode);
		switch (code[i].opcode)
		{
			case 1:
				printf("LIT\t");
				break;
			case 2:
				switch (code[i].m)
				{
					case 0:
						printf("RTN\t");
						break;
					case 1:
						printf("NEG\t");
						break;
					case 2:
						printf("ADD\t");
						break;
					case 3:
						printf("SUB\t");
						break;
					case 4:
						printf("MUL\t");
						break;
					case 5:
						printf("DIV\t");
						break;
					case 6:
						printf("ODD\t");
						break;
					case 7:
						printf("MOD\t");
						break;
					case 8:
						printf("EQL\t");
						break;
					case 9:
						printf("NEQ\t");
						break;
					case 10:
						printf("LSS\t");
						break;
					case 11:
						printf("LEQ\t");
						break;
					case 12:
						printf("GTR\t");
						break;
					case 13:
						printf("GEQ\t");
						break;
					default:
						printf("err\t");
						break;
				}
				break;
			case 3:
				printf("LOD\t");
				break;
			case 4:
				printf("STO\t");
				break;
			case 5:
				printf("CAL\t");
				break;
			case 6:
				printf("INC\t");
				break;
			case 7:
				printf("JMP\t");
				break;
			case 8:
				printf("JPC\t");
				break;
			case 9:
				switch (code[i].m)
				{
					case 1:
						printf("WRT\t");
						break;
					case 2:
						printf("RED\t");
						break;
					case 3:
						printf("HAL\t");
						break;
					default:
						printf("err\t");
						break;
				}
				break;
			default:
				printf("err\t");
				break;
		}
		printf("%d\t%d\n", code[i].l, code[i].m);
	}
	if (table != NULL)
		free(table);
}
