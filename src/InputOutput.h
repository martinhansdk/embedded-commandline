#ifndef INPUTOUTPUT_H
#define INPUTOUTPUT_H

namespace embeddedcommandline {

class Outputter {
public:
	virtual void putchar(char c) = 0;
	virtual void puts(char* c) = 0;
};


}
#endif
