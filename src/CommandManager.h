#ifndef _COMMANDMANAGER_H
#define _COMMANDMANAGER_H

#include <InputOutput.h>
#include <Command.h>
#include <LineHandler.h>

namespace embeddedcommandline {

int streq(const char *a, const char *b, int maxlen) {
	while(maxlen > 0) {
		if(*a != *b) {
			return 0;
		}

		if(*a == '\0') {
			break;
		}
		a++;
		b++;
		maxlen--;
	}
	return 1;
}


template<int MAX_COMMANDS, int MAX_ARGS, int MAX_COMMAND_LEN>
class CommandManager : public LineHandler {
	Outputter &output;

	const char* commandstr[MAX_COMMANDS];
	Command* commands[MAX_COMMANDS];
	int numberOfCommands;
public:
	CommandManager(Outputter& output) : output(output), numberOfCommands(0) {}
	void addCommand(const char* str, Command& command) {
		if(numberOfCommands < MAX_COMMANDS) {
			commandstr[numberOfCommands] = str;
			commands[numberOfCommands++] = &command;
		}
	}

	virtual void handleLine(char* line) {
		const char* args[MAX_ARGS+1];

		int pos=0;
		int noOfArgs=0;
		bool skip=false;
		while(line[pos] != '\0') {
			if(line[pos] == ' ') {
				line[pos]='\0';
				skip=false;
			} else if(!skip) {
				if(noOfArgs >= MAX_ARGS + 1) {
					output.puts("ERROR: Too many arguments\r\n");
					return;
				}

				args[noOfArgs]=&line[pos];
				noOfArgs++;
				skip=true;
			}
			pos++;
		}

		if(noOfArgs==0) {
			return;
		}

		for(int i=0; i<numberOfCommands; i++) {
			if(streq(args[0], commandstr[i], MAX_COMMAND_LEN)) {
				commands[i]->execute(args + 1, noOfArgs-1);
				return;
			}
		}

		output.puts("ERROR: Unknown command \"");
		output.puts(line);
		output.putchar('"');
		output.puts("\r\n");
	}
};




}

#endif
