#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_STRING   256
#define MAX_SUBSTRING 80
#define MAX_COMMANDS 100

typedef char String[MAX_STRING];

typedef enum {
	TEXT, // Text operations
	NUM, // Range defined
	ALL // No range defined
} TypeRange;

typedef union {
	String text;
	int range[2];
	int none;
} Range;

typedef enum {
	APPEND,
	INSERT,
	NEWLINE,
	DELETE,
	REPLACE
} Operation;

typedef struct {
	TypeRange type;
	Range     range;
	Operation operand;
	String    data;
} Command;

typedef Command* Operations[MAX_COMMANDS];

Command*  lineParse(String);
int       rangeParse(Command*, String);
int       textParse(Command*, String);
int       norangeParse(Command*, String);
int  rangeCheck(String, int, Command*);
void editString(String, Command*);
void replaceText(String, String);

Command* lineParse(String str) {
	static const Command initialized_cmd = {
		.type = 0,
		.range.text = "",
		.operand = 0,
		.data = ""
	};

	Command *cmd = malloc(sizeof(Command));
	memcpy(cmd, &initialized_cmd, sizeof(Command));

	if (textParse(cmd, str) || rangeParse(cmd, str) || norangeParse(cmd, str))
		return cmd;

	free(cmd);
	return(NULL);
}

Operation operationParse(char operand) {
	switch(operand) {
		case 'A': return APPEND;
		case 'I': return INSERT;
		case 'O': return NEWLINE;
		case 'd': return DELETE;
		case 's': return REPLACE;
	}

	return DELETE;
}


int rangeParse(Command *cmd, String str) {
	if (!isdigit(str[0]))
		return 0;

	(*cmd).type = NUM;
	char *comma = strstr(str, ",");
	char *first_slash = strstr(str, "/");
	(*cmd).range.range[0] = strtol(str, &comma, 10);
	(*cmd).range.range[1] = strtol(comma + 1, &first_slash, 10);
	(*cmd).operand = operationParse(*(first_slash + 1));

	strncpy((*cmd).data, first_slash + 2, MAX_STRING);

	return 1;
}


int textParse(Command *cmd, String str) {
	if (str[0] != '/')
		return 0;

	String mut_str;
	memcpy(mut_str, str, sizeof(String));
	char* range = strtok(mut_str, "/");
	char *rest = str + strlen(range) + 2;
	(*cmd).type = TEXT;
	strncpy((*cmd).range.text, range, MAX_STRING);
	(*cmd).operand = operationParse(rest[0]);
	strncpy((*cmd).data, rest + 1, MAX_STRING);

	return 1;
}


int norangeParse(Command *cmd, String str) {
	(*cmd).type = ALL;
	(*cmd).operand = operationParse(str[0]);
	(*cmd).range.none = 1;
	strncpy((*cmd).data, str + 1, MAX_STRING);

	return 1;
}

int rangeCheck(String str, int lineNum, Command* cmd) {
	switch ((*cmd).type){
		case ALL:
			return 1;
		case NUM:
			if (lineNum >= (*cmd).range.range[0] && lineNum <= (*cmd).range.range[1]) {
				return 1;
			} else {
				break;
			}
		case TEXT:
			if (strstr(str, (*cmd).range.text)) {
				return 1;
			} else {
				break;
			}
	}
	return 0;
}

void editString(String str, Command *cmd) {
	String tmp = "";

	switch ((*cmd).operand) {
		case APPEND:
			// Concatenate data to string (str + data)
			strncat(str, (*cmd).data, MAX_STRING - strlen(str));
			break;
		case INSERT:
			// make space in tmp and copy the string to edit
			memcpy(&tmp, str, sizeof(String));

			// Copy the string to prepend from the cmd "array" to sr
			strncpy(str, (*cmd).data, MAX_STRING);

			// Add tmp string to end of 'str'
			strncat(str, tmp, MAX_STRING - strlen(str));
			break;
		case NEWLINE:
			printf("%s\n", (*cmd).data);
			break;
		case DELETE:
			break; // abort!
		case REPLACE:
			replaceText(str, (*cmd).data); // GOTO replaceText
			break;
		default:
			break;
	}

	return;
}

void replaceText(String input_str, String source) {
	String destination;

	// Make space in memory
	memcpy(destination, source, sizeof(String));

	// Store the token to replace
	const char *find = strtok(destination, "/");

	// Store the token to replace it with
	const char *replace = strtok(NULL, "/");
	const int find_length = strlen(find);

	String result = "";
	char *beginning = &input_str[0];
	char *foundStart;

	// Loop through and find all occurence of find token
	// foundStart becomes the first character in 'beginning'
	while ((foundStart = strstr(beginning, find))) {
		int offset_len = foundStart - beginning;
		// Concatenate result + beginning (and makes space for rest)
		strncat(result, beginning, offset_len);
		// Concatenate previous string with token to replace with
		strncat(result, replace, MAX_STRING - strlen(result));
		beginning = foundStart + (find_length * sizeof(char));
	}

	// Mash the beginning string with the result
	strncat(result, beginning, MAX_STRING - strlen(result));
	// Make sure the space is there in the memory
	memcpy(input_str, result, sizeof(String));

	return;
}

int main(int argc, char *argv[]) {
	FILE *InputFile;
	Operations commands;
	String nline = "";
	String tmp = "";
	int commandNum = 0;
	int stdinNum = 1;

	// Check that a file name was provided
	if (argc != 2) {
		printf("Error: File name not given\n");
		return(EXIT_FAILURE);
	}

	// Open command file
	if ((InputFile = fopen(argv[1], "r")) == NULL) {
		printf("Error: File not found\n");
		return EXIT_FAILURE;
	}

	// Send commands to line parser
	while (fgets(nline, MAX_STRING, InputFile) != NULL) {
		nline[strlen(nline) - 1] = '\0';
		commands[commandNum++] = lineParse(nline);
	}

	// Close command file
	if (fclose(InputFile) == EOF) {
		printf("Error: Can't close file\n");
		return EXIT_FAILURE;
	}

	// Loop through stdin to apply edits
	while (fgets(tmp, MAX_STRING, stdin) != NULL) {
		tmp[strlen(tmp)-1] = '\0'; // close string with null
		int nth_command = 0;
		int check_deleted = 1;

		while (nth_command < commandNum && check_deleted) {
			Command *cmd = commands[nth_command++];

			if (rangeCheck(tmp, stdinNum, cmd)) {
				editString(tmp, cmd);
				if ((*cmd).operand == DELETE) {
					check_deleted = 0;
				}
			}
		}

		if (check_deleted) {
			printf("%s\n", tmp); // don't show if command == delete
		}

		stdinNum++;
	}

	// Free memory that was allocated for commands
	for (int i = 0; i < commandNum; i++) {
		free(commands[i]);
	}

	return(EXIT_SUCCESS);
}

