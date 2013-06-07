
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>

#include <DumbLineEditor.h>

namespace embedded-commandline {

class TestOutputter : Outputter {
public:
	string text;

	void putc(char c) {
		text.append(c);
	}

	void puts(char* s) {
		text.append(s);
	}

};

class LineHandlerMock : LineHandler {
	MOCK_METHOD1(handleLine);
};

class DumbLineEditorTest : ::testing::Test {
	TestOutputter output;
	StrictMock<LineHandlerMock> handler;
	DumbLineEditor<10> editor;

	Sequence sequence;

	DumbLineEditorTest() editor(output, handler) {}

	void expectCompletedLine(string text) {
		EXPECT_CALL(handler(text.c_str())).InSequence(sequence);
	}
};

TEST_F(DumbLineEditorTest, typedCharactersAreOutput) {
	editor.putc('a');
	editor.putc('b');

	EXPECT_EQ(text, "ab");
}

TEST_F(DumbLineEditorTest, completeLinesAreHandled) {
	expectCompletedLine("hello");

	editor.putc('h');
	editor.putc('e');
	editor.putc('l');
	editor.putc('l');
	editor.putc('o');
	editor.putc('\n');

	EXPECT_EQ(text, "hello\n");
}

TEST_F(DumbLineEditorTest, canEditSeveralLinesAfterEachOther) {
	expectCompletedLine("ab");
	expectCompletedLine("de");
	
	editor.putc('a');
	editor.putc('b');
	editor.putc('\n');

	editor.putc('c');
	editor.putc('d');
	editor.putc('\n');
}

}

