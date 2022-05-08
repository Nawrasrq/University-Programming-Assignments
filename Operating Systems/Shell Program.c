#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define HIS_SIZE 100
#define TOK_SIZE 64
#define TOK_DELIM " \t\r\n\a"

char* readLine(void);
char** parseLine(char* line);
int run(char **args);
int executeCmd(char **args);

int cd(char **args);
int byebye(char **args);
int listHistory(char **args);
int replay(char **args);
int start(char **args);
int background(char **args);
int terminate(char **args);
int dwelt(char **args);
int maik(char **args);
int coppy(char **args);

static FILE *historyFile;
static char** history;
int currIndex;
int printPID = 0;

int main(int argc, char *argv[]){
	history = malloc(HIS_SIZE * sizeof(char*));
	char **args;
	char *line;

	int status;
	currIndex = 0;
	ssize_t size = 0;
	
	historyFile = fopen("myshell.history" , "a+");
	
	while(getline(&history[currIndex], &size, historyFile) != -1){
		currIndex++;
	}
	
	do {
		printf("$ ");
		line = readLine();
		args = parseLine(line);
		status = executeCmd(args);

		free(line);
		free(args);
	} 
	while (status);
}

char* readLine(void){
	char* line = NULL;
	ssize_t size = 0;
	
	if(getline(&line, &size, stdin) == -1){
		if(feof(stdin)){
			exit(EXIT_SUCCESS);
		}
		else{
			perror("Error");
			exit(EXIT_FAILURE);
		}
	}
	
	if(currIndex >= HIS_SIZE){
		history = realloc(history, (HIS_SIZE + 1) * sizeof(char*));
	}
	
	fprintf(historyFile, "%s", line);
	history[currIndex] = malloc(strlen(line) * sizeof(char*));
	strcpy(history[currIndex], line);
	currIndex++;
	
	return line;
}

char** parseLine(char* line){
	int bufsize = TOK_SIZE;
	int position = 0;
	
	char** tokens = malloc(bufsize * sizeof(char*));
	char* token;
	
	if(!tokens){
		fprintf(stderr, "Error: couldn't allocate\n");
		exit(EXIT_FAILURE);
	}
	
	token = strtok(line, TOK_DELIM);
	
	while(token != NULL){
		tokens[position] = token;
		position++;
		
		if(position >= bufsize){
			bufsize += TOK_SIZE;
			tokens = realloc(tokens, bufsize * sizeof(char*));
			
			if(!tokens){
				fprintf(stderr, "Error: couldn't allocate\n");
				exit(EXIT_FAILURE);
			}
		}

		token = strtok(NULL, TOK_DELIM);
	}	
	
	tokens[position] = NULL;
	return tokens;
	
}

int run(char **args)
{
	pid_t pid; 
	pid_t wpid;
	int status;

	pid = fork();
	
	if(printPID == 1){
		printf("PID: %ld\n", (long)pid);
	}
	
	//pid =0 then child process
	if(pid == 0) {	
		if (execvp(args[0], args) == -1) {
			perror("Error");
		}
		exit(EXIT_FAILURE);
	} 
	//forking error
	else if(pid < 0) {
		perror("Error");
	} 
	//PID > 0 then parent process
	else{
		if(printPID == 0){
			do{
				wpid = waitpid(pid, &status, WUNTRACED);
			} 
			while(!WIFEXITED(status) && !WIFSIGNALED(status));
		}
	}
	printPID = 0;
	return 1;
}

char *builtin_str[] = {
  "cd",
  "byebye",
  "history",
  "replay",
  "start",
  "background",
  "terminate",
  "dwelt",
  "maik",
  "coppy"
};

int (*builtin_func[]) (char **) = {
  &cd,
  &byebye,
  &listHistory,
  &replay,
  &start,
  &background,
  &terminate,
  &dwelt,
  &maik,
  &coppy
};

int executeCmd(char **args)
{
	int i;
	if(args[0] == NULL) {
		printf("empty command\n");
		return 1;
	}
	
	for(i = 0; i < sizeof(builtin_str) / sizeof(char *); i++) {
		if(strcmp(args[0], builtin_str[i]) == 0) {
			return (*builtin_func[i])(args);
		}
	}

	return run(args);
}

//built in commands

int cd(char **args)
{
	if(args[1] == NULL){
		fprintf(stderr, "Error: no cd");
	} 
	else {
		if (chdir(args[1]) != 0){
			perror("Error");
		}
	}
  return 1;
}

int byebye(char **args){
	
	fclose(historyFile);
	exit(EXIT_FAILURE);
	return 0;
}

int terminate(char **args){
	int status = kill(atoi(args[1]), SIGKILL);

	if(status != -1){
		printf("successfully terminated\n");
	}
	else{
		perror("Error");
	}
	return 1;
}

int background(char **args){
	printPID = 1;
	start(args);
	return 1;
}

int start(char **args){
	
	int size = 0;
	for(int i = 0; args[i] != NULL; i++){size++;}
	
	char **newArgs = malloc((size+1) * sizeof(char*));
	
	if(args[1] != NULL){
		for(int i = 1; args[i] != NULL; i++){
			newArgs[i-1] = malloc(strlen(args[i]) * sizeof(char*));
			strcpy(newArgs[i-1], args[i]);
		}
		
		executeCmd(newArgs);
		return 1;
	}
	else{
		printf("No program entered\n");
	}
	return 1;
}

int replay(char **args){
	
	if(args[1] != NULL){
		if(sizeof(args[1]) == 8 || sizeof(args[1]) == 4 && history[atoi(args[1])] != NULL){
			args = parseLine(history[atoi(args[1])]);
			executeCmd(args);
		}
		else{
			printf("not a valid replay input\n");
			return 1;
		}
	}
	
	return 1;
}

int listHistory(char **args){
	
	if(args[1] != NULL){
		if(strcmp(args[1], "-c") == 0){
			for(int i = 0; i < currIndex; i++){
				free(history[i]);
			}
			free(history);
			history = malloc(HIS_SIZE * sizeof(char*));
			
			fclose(historyFile);
			historyFile = fopen("myshell.history" , "w+");
			
			currIndex = 0;
		}
		else{
			printf("unknown second argument for history cmd\n");
			return 1;
		}
	}
	else{
		for(int i = 0; i < currIndex; i++){
			printf("%d: %s", i, history[i]);
		}
	}
	return 1;
}

int dwelt(char **args){
	struct stat checkFile;
	if(args[1] != NULL){
		if(stat(args[1], &checkFile) == 0){
			if(S_ISDIR(checkFile.st_mode)){
				printf("Abode is.\n");
			}
			else{
				printf("Dwelt indeed.\n");
			}
		}
		else{
			printf("Dwelt not.\n");
		}
	}
	else{
		printf("Not a valid input\n");
	}
	return 1;
}

int maik(char **args){
	
	if(args[1] != NULL){
		FILE *newFile;

		if(newFile = fopen(args[1], "r")){
			printf("Error: File already exists\n");
			fclose(newFile);
		}
		else{
			newFile = fopen(args[1], "a+");
			fprintf(newFile, "Draft\n");
			fclose(newFile);
		}
	}
	return 1;
}

int coppy(char **args){
	
	if(args[1] != NULL && args[2] != NULL){
		FILE *fromFile;
		FILE *toFile;
		char c;
		if(fromFile = fopen(args[1], "r")){
			if(toFile = fopen(args[2], "r")){
				printf("destination file exists\n");
				fclose(toFile);
			}
			else{
				toFile = fopen(args[2], "w+");
				c = fgetc(fromFile);
				
				while(c != EOF){
					fputc(c, toFile);
					c = fgetc(fromFile);
				}
				fclose(toFile);
				
			}
			
			fclose(fromFile);
			
		}
		else{
			printf("source file doesnt exist\n");
		}
	}
	return 1;
}