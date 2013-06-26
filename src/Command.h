#ifndef _COMMAND_H
#define _COMMAND_H

namespace embeddedcommandline {

class Command {
public:
	virtual void execute(const char* args[], int nargs) = 0;
};

}

#endif