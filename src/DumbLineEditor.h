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

public:
	DumbLineEditor(Outputter& output, LineHandler& handler) 
	   : output(output), handler(handler), length(0) {

	}

	void putc(char c) {
		if(c == '\n') {
			output.putc(c);
			line[length]='\0';
			handler.handleLine(line);
			length=0;
		} else if(length < MAX_LINELENGTH) {
			output.putc(c);
			line[length]=c;
			length++;
		}
	}

};


}
#endif