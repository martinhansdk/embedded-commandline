#ifndef _COMMANDMANAGER_H
#define _COMMANDMANAGER_H

#include <InputOutput.h>
#include <Command.h>

namespace embeddedcommandline {

template<int MAX_COMMANDS, int MAX_ARGS>
class CommandManager : public LineHandler {
    Outputter &output;

    Command* commands[MAX_COMMANDS];
    int numberOfCommands;
public:
    CommandManager(Outputter& output) : output(output), numberOfCommands(0) {}
    void addCommand(const char* str, Command& command) {
        if(numberOfCommands < MAX_COMMANDS) {
            commands[numberOfCommands++] = &command;
        }
    }

    virtual void handleLine(const char* line) {
        const char* args[MAX_ARGS];

        commands[0]->execute(args, 0);

    }
};

}

#endif