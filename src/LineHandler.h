#ifndef _LINEHANDLER_H
#define _LINEHANDLER_H

namespace embeddedcommandline {

class LineHandler {
public:
	virtual void handleLine(const char* line) = 0;
};

}

#endif