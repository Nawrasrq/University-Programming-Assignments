/*
	This is the lex.c file for the UCF Fall 2021 Systems Software Project.
	For HW2, you must implement the function lexeme *lexanalyzer(char *input).
	You may add as many constants, global variables, and support functions
	as you desire.
	If you choose to alter the printing functions or delete list or lex_index,
	you MUST make a note of that in you readme file, otherwise you will lose
	5 points.
*/

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "compiler.h"
#define MAX_NUMBER_TOKENS 500
#define MAX_IDENT_LEN 11
#define MAX_NUMBER_LEN 5

lexeme *list;
int lex_index;

void printlexerror(int type);
void printtokens();

lexeme *lexanalyzer(char *input)
{
  int i = 0;
  int k = 0;
  char word[100] = "";

  list = malloc(MAX_NUMBER_TOKENS * sizeof(lexeme));
  lex_index = 0;

  //parse through input
  while(input[i] != '\0'){
    //if comment then skip chars until \n
    if(input[i] == '/'){
      if(input[i+1] == '/'){
        while(input[i] != '\n'){
          i++;
        }
        i++;
      }
    }
    //if letter/number
    if(isalnum(input[i]) && !isspace(input[i])){
      while(isalnum(input[i]) && !isspace(input[i])){
        strncat(word, &input[i], 1);
        i++;
      }
    }
    //if punctuation
    else if(ispunct(input[i])){
      char e = input[i];
      strncat(word, &e, 1);
      i++;
      if(e == '=' || e == '<' || e == '>' || e == ':' || e == '!'){
        if(input[i] == '='){
          strncat(word, &input[i], 1);
          i++;
        } 
      }
    }
    //if neither then it must be an invisible character
    else{
      i++;
    }

    lexeme token;

    //if word is proper reserved word then tokenize it
    if(strcmp(word,"const") == 0){
      token.type = constsym;
      token.value = 1;
      strcpy(token.name, word);

      list[lex_index] = token;
      lex_index = lex_index + 1;
    }
    else if(strcmp(word,"var") == 0){
      token.type = varsym;
      token.value = 2;
      strcpy(token.name, word);

      list[lex_index] = token;
      lex_index = lex_index + 1;
    }
    else if(strcmp(word,"procedure") == 0){
      token.type = procsym;
      token.value = 3;
      strcpy(token.name, word);

      list[lex_index] = token;
      lex_index = lex_index + 1;
    }
    else if(strcmp(word,"call") == 0){
      token.type = callsym;
      token.value = 11;
      strcpy(token.name, word);

      list[lex_index] = token;
      lex_index = lex_index + 1;
    }
    else if(strcmp(word,"if") == 0){
      token.type = ifsym;
      token.value = 8;
      strcpy(token.name, word);

      list[lex_index] = token;
      lex_index = lex_index + 1;
    }
    else if(strcmp(word,"then") == 0){
      token.type = thensym;
      token.value = 9;
      strcpy(token.name, word);

      list[lex_index] = token;
      lex_index = lex_index + 1;
    }
    else if(strcmp(word,"else") == 0){
      token.type = elsesym;
      token.value = 10;
      strcpy(token.name, word);

      list[lex_index] = token;
      lex_index = lex_index + 1;
    }
    else if(strcmp(word,"while") == 0){
      token.type = whilesym;
      token.value = 6;
      strcpy(token.name, word);

      list[lex_index] = token;
      lex_index = lex_index + 1;
    }
    else if(strcmp(word,"do") == 0){
      token.type = dosym;
      token.value = 7;
      strcpy(token.name, word);

      list[lex_index] = token;
      lex_index = lex_index + 1;
    }
    else if(strcmp(word,"begin") == 0){
      token.type = beginsym;
      token.value = 4;
      strcpy(token.name, word);

      list[lex_index] = token;
      lex_index = lex_index + 1;
    }
    else if(strcmp(word,"end") == 0){
      token.type = endsym;
      token.value = 5;
      strcpy(token.name, word);

      list[lex_index] = token;
      lex_index = lex_index + 1;
    }
    else if(strcmp(word,"read") == 0){
      token.type = readsym;
      token.value = 13;
      strcpy(token.name, word);

      list[lex_index] = token;
      lex_index = lex_index + 1;
    }
    else if(strcmp(word,"write") == 0){
      token.type = writesym;
      token.value = 12;
      strcpy(token.name, word);

      list[lex_index] = token;
      lex_index = lex_index + 1;
    }
    else if(strcmp(word,"odd") == 0){
      token.type = oddsym;
      token.value = 28;
      strcpy(token.name, word);

      list[lex_index] = token;
      lex_index = lex_index + 1;
    }
	 else if(strcmp(word, ":=") == 0) {
		 token.type = assignsym;
		 token.value = 16;
		 strcpy(token.name, word);

		 list[lex_index] = token;
		 lex_index = lex_index + 1;
	 }
	 else if(strcmp(word, "+") == 0) {
		 token.type = addsym;
		 token.value = 17;
		 strcpy(token.name, word);

		 list[lex_index] = token;
		 lex_index = lex_index + 1;
	 }
	 else if(strcmp(word, "-") == 0) {
		 token.type = subsym;
		 token.value = 18;
		 strcpy(token.name, word);

		 list[lex_index] = token;
		 lex_index = lex_index + 1;
	 }
	 else if(strcmp(word, "*") == 0) {
		 token.type = multsym;
		 token.value = 19;
		 strcpy(token.name, word);

		 list[lex_index] = token;
		 lex_index = lex_index + 1;
	 }
	 else if(strcmp(word, "/") == 0) {
		 token.type = divsym;
		 token.value = 20;
		 strcpy(token.name, word);

		 list[lex_index] = token;
		 lex_index = lex_index + 1;
	 }
	 else if(strcmp(word, "%") == 0) {
		 token.type = modsym;
		 token.value = 21;
		 strcpy(token.name, word);

		 list[lex_index] = token;
		 lex_index = lex_index + 1;
	 }
	 else if(strcmp(word, "==") == 0) {
		 token.type = eqlsym;
		 token.value = 22;
		 strcpy(token.name, word);

		 list[lex_index] = token;
		 lex_index = lex_index + 1;
	 }
	 else if(strcmp(word, "!=") == 0) {
		 token.type = neqsym;
		 token.value = 23;
		 strcpy(token.name, word);

		 list[lex_index] = token;
		 lex_index = lex_index + 1;
	 }
	 else if(strcmp(word, "<") == 0) {
		 token.type = lsssym;
		 token.value = 24;
		 strcpy(token.name, word);

		 list[lex_index] = token;
		 lex_index = lex_index + 1;
	 }
	 else if(strcmp(word, "<=") == 0) {
		 token.type = leqsym;
		 token.value = 25;
		 strcpy(token.name, word);

		 list[lex_index] = token;
		 lex_index = lex_index + 1;
	 }
	 else if(strcmp(word, ">") == 0) {
		 token.type = gtrsym;
		 token.value = 26;
		 strcpy(token.name, word);

		 list[lex_index] = token;
		 lex_index = lex_index + 1;
	 }
	 else if(strcmp(word, ">=") == 0) {
		 token.type = geqsym;
		 token.value = 27;
		 strcpy(token.name, word);

		 list[lex_index] = token;
		 lex_index = lex_index + 1;
	 }
	 else if(strcmp(word, "(") == 0) {
		 token.type = lparensym;
		 token.value = 29;
		 strcpy(token.name, word);

		 list[lex_index] = token;
		 lex_index = lex_index + 1;
	 }
	 else if(strcmp(word, ")") == 0) {
		 token.type = rparensym;
		 token.value = 30;
		 strcpy(token.name, word);

		 list[lex_index] = token;
		 lex_index = lex_index + 1;
	 }
	 else if(strcmp(word, ",") == 0) {
		 token.type = commasym;
		 token.value = 31;
		 strcpy(token.name, word);

		 list[lex_index] = token;
		 lex_index = lex_index + 1;
	 }
	 else if(strcmp(word, ".") == 0) {
		 token.type = periodsym;
		 token.value = 32;
		 strcpy(token.name, word);

		 list[lex_index] = token;
		 lex_index = lex_index + 1;
	 }
	 else if(strcmp(word, ";") == 0) {
		 token.type = semicolonsym;
		 token.value = 33;
		 strcpy(token.name, word);

		 list[lex_index] = token;
		 lex_index = lex_index + 1;
	 }
   else if(ispunct(word[0])){
     printlexerror(1);
     exit(0);
   }
	 else { // It is either an identifier or a number

		 // The only identifiers that should give an error is if
		 //	they are larger than 12 characters or 5 digits
		 // If a number is followed by a word, it is invalid
		 //	otherwise, everything else is a valid identifier

		 // Iterate through the word and check each character
		 // Max length for identifier is 12
		 // Max length for number is 5
		 for (k = 1; k < 100; k++) { // 100 is the size of the array
			 if (word[k] == ';' || isspace(word[k]) || iscntrl(word[k])) {
				 break;
			 }
			 else if (isdigit(word[0])) {
				 if (k == 5) {
					 printlexerror(3);
					 exit(0);
				 }
				 else if (isalpha(word[k])) {
					 printlexerror(2);
					 exit(0);
				 }
			 }
			 else if (isalpha(word[0])) {
				 if (k > 12) {
					 printlexerror(4);
					 exit(0);
				 }
			 }
		 }

		 // If we reach the end of the loop we add the token
		 if (isdigit(word[0])) { // Check to see if we have a number or a letter
			 token.type = numbersym;
			 token.value = atoi(word);
			 strcpy(token.name, word);

			 list[lex_index] = token;
			 lex_index = lex_index + 1;
		 }
		 else if (isalpha(word[0])) {
			 token.type = identsym;
			 token.value = 14;
			 strcpy(token.name, word);

			 list[lex_index] = token;
			 lex_index = lex_index + 1;
		 }
	 }

    strcpy(word, "");
  }

  printtokens();
	return list;
}

void printtokens()
{
	int i;
	printf("Lexeme Table:\n");
	printf("lexeme\t\ttoken type\n");
  for (i = 0; i < lex_index; i++)
	{
		switch (list[i].type)
		{
			case oddsym:
				printf("%11s\t%d", "odd", oddsym);
				break;
			case eqlsym:
				printf("%11s\t%d", "==", eqlsym);
				break;
			case neqsym:
				printf("%11s\t%d", "!=", neqsym);
				break;
			case lsssym:
				printf("%11s\t%d", "<", lsssym);
				break;
			case leqsym:
				printf("%11s\t%d", "<=", leqsym);
				break;
			case gtrsym:
				printf("%11s\t%d", ">", gtrsym);
				break;
			case geqsym:
				printf("%11s\t%d", ">=", geqsym);
				break;
			case modsym:
				printf("%11s\t%d", "%", modsym);
				break;
			case multsym:
				printf("%11s\t%d", "*", multsym);
				break;
			case divsym:
				printf("%11s\t%d", "/", divsym);
				break;
			case addsym:
				printf("%11s\t%d", "+", addsym);
				break;
			case subsym:
				printf("%11s\t%d", "-", subsym);
				break;
			case lparensym:
				printf("%11s\t%d", "(", lparensym);
				break;
			case rparensym:
				printf("%11s\t%d", ")", rparensym);
				break;
			case commasym:
				printf("%11s\t%d", ",", commasym);
				break;
			case periodsym:
				printf("%11s\t%d", ".", periodsym);
				break;
			case semicolonsym:
				printf("%11s\t%d", ";", semicolonsym);
				break;
			case assignsym:
				printf("%11s\t%d", ":=", assignsym);
				break;
			case beginsym:
				printf("%11s\t%d", "begin", beginsym);
				break;
			case endsym:
				printf("%11s\t%d", "end", endsym);
				break;
			case ifsym:
				printf("%11s\t%d", "if", ifsym);
				break;
			case thensym:
				printf("%11s\t%d", "then", thensym);
				break;
			case elsesym:
				printf("%11s\t%d", "else", elsesym);
				break;
			case whilesym:
				printf("%11s\t%d", "while", whilesym);
				break;
			case dosym:
				printf("%11s\t%d", "do", dosym);
				break;
			case callsym:
				printf("%11s\t%d", "call", callsym);
				break;
			case writesym:
				printf("%11s\t%d", "write", writesym);
				break;
			case readsym:
				printf("%11s\t%d", "read", readsym);
				break;
			case constsym:
				printf("%11s\t%d", "const", constsym);
				break;
			case varsym:
				printf("%11s\t%d", "var", varsym);
				break;
			case procsym:
				printf("%11s\t%d", "procedure", procsym);
				break;
			case identsym:
				printf("%11s\t%d", list[i].name, identsym);
				break;
			case numbersym:
				printf("%11d\t%d", list[i].value, numbersym);
				break;
		}
		printf("\n");
	}
	printf("\n");
	printf("Token List:\n");
	for (i = 0; i < lex_index; i++)
	{
		if (list[i].type == numbersym)
			printf("%d %d ", numbersym, list[i].value);
		else if (list[i].type == identsym)
			printf("%d %s ", identsym, list[i].name);
		else
			printf("%d ", list[i].type);
	}
	printf("\n");
	list[lex_index++].type = -1;
}

void printlexerror(int type)
{
	if (type == 1)
		printf("Lexical Analyzer Error: Invalid Symbol\n");
	else if (type == 2)
		printf("Lexical Analyzer Error: Invalid Identifier\n");
	else if (type == 3)
		printf("Lexical Analyzer Error: Excessive Number Length\n");
	else if (type == 4)
		printf("Lexical Analyzer Error: Excessive Identifier Length\n");
	else
		printf("Implementation Error: Unrecognized Error Type\n");

	free(list);
	return;
}