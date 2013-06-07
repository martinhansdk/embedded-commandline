#ifndef INPUTOUTPUT_H
#define INPUTOUTPUT_H

namespace embedded-commandline {

class Inputter {

};

class Outputter {
public:
	void putc(char c) = 0;
	void puts(char* c) = 0;
};


}
#endif