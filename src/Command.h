#ifndef _COMMAND_H
#define _COMMAND_H

namespace embeddedcommandline {

	class Command {
		virtual void execute(char* args[], int nargs) = 0;
	}

}

#endif