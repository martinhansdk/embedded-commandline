#ifndef DUMBLINEEDITOR_H
#define DUMBLINEEDITOR_H

#include "LineEditor.h"
#include "InputOutput.h"
#include "LineHandler.h"

namespace embeddedcommandline {

template<int MAX_LINELENGTH>
class DumbLineEditor : public LineEditor {
	Outputter& output;
	LineHandler& handler;
	char line[MAX_LINELENGTH];
	int length;
	const char* prompt;

public:
	DumbLineEditor(Outputter& output, LineHandler& handler)
	   : output(output), handler(handler), length(0), prompt("") {

	}

	virtual void putchar(char c) {
		if(c == '\n') {
			output.putchar(c);
			line[length]='\0';
			if(length > 0) {
				handler.handleLine(line);
			}
			length=0;
			output.puts(prompt);
		} else if(length < MAX_LINELENGTH) {
			output.putchar(c);
			line[length]=c;
			length++;
		}
      output.flush();
	}

	void setPrompt(const char* newprompt) {
		prompt = newprompt;
		output.puts(prompt);
		output.flush();
	}

};


}
#endif
