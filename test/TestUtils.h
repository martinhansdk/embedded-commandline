#ifndef _TESTUTILS_H
#define _TESTUTILS_H

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>

#include <InputOutput.h>

using namespace std;

namespace embeddedcommandline {

class TestOutputter : public Outputter {
public:
	string text;

	void putchar(char c) {
		text.append(1, c);
			
	}

	void puts(const char* s) {
		text.append(s);
	}

};

}

#endif