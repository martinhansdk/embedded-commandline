#ifndef DUMBLINEEDITOR_H
#define DUMBLINEEDITOR_H

#include "LineEditor.h"
#include "InputOutput.h"

namespace embedded-commandline {

template<int MAX_LINELENGTH>
class DumbLineEditor : public LineEditor {
	Outputter &output;
	LineHandler &handler;
	char line[MAX_LINELENGTH];
	int length;
public:
	DumbLineEditor(Outputter &output, LineHandler &handler) 
	   : output(output), handler(handler), length(0) {

	}

	void putc(char c) {
		if(c == '\n') {

		} else if(length < MAX_LINELENGTH) {

		}
	}

};


}
#endif