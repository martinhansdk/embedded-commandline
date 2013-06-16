
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>

#include <DumbLineEditor.h>
#include <LineHandler.h>

using namespace std;
using ::testing::StrictMock;
using ::testing::Sequence;
using ::testing::StrEq;

namespace embeddedcommandline {

class TestOutputter : public Outputter {
public:
	string text;

	void putc(char c) {
		text.append(1, c);
			
	}

	void puts(char* s) {
		text.append(s);
	}

};

class LineHandlerMock : public LineHandler {
public:
	MOCK_METHOD1(handleLine, void(const char* line));
};

class DumbLineEditorTest : public ::testing::Test {
protected:

	TestOutputter output;
	StrictMock<LineHandlerMock> handler;
	DumbLineEditor<10> editor;

	Sequence sequence;

	DumbLineEditorTest() : editor(output, handler) {}

	void expectCompletedLine(string text) {
		EXPECT_CALL(handler, handleLine(StrEq(text))).InSequence(sequence);
	}
};

TEST_F(DumbLineEditorTest, typedCharactersAreOutput) {
	editor.putc('a');
	editor.putc('b');

	EXPECT_EQ(output.text, "ab");
}

TEST_F(DumbLineEditorTest, completeLinesAreHandled) {
	expectCompletedLine("hello");

	editor.putc('h');
	editor.putc('e');
	editor.putc('l');
	editor.putc('l');
	editor.putc('o');
	editor.putc('\n');

	EXPECT_EQ(output.text, "hello\n");
}

TEST_F(DumbLineEditorTest, canEditSeveralLinesAfterEachOther) {
	expectCompletedLine("ab");
	expectCompletedLine("cd");
	
	editor.putc('a');
	editor.putc('b');
	editor.putc('\n');

	editor.putc('c');
	editor.putc('d');
	editor.putc('\n');
}

TEST_F(DumbLineEditorTest, enforcesMaximumLineLength) {
	expectCompletedLine("abcdefghij");
	
	editor.putc('a');
	editor.putc('b');
	editor.putc('c');
	editor.putc('d');
	editor.putc('e');
	editor.putc('f');
	editor.putc('g');
	editor.putc('h');
	editor.putc('i');
	editor.putc('j');
	editor.putc('k');
	editor.putc('l');
	editor.putc('m');
	editor.putc('\n');

	EXPECT_EQ(output.text, "abcdefghij\n");
}

}

