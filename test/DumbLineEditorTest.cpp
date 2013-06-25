
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>

#include <DumbLineEditor.h>
#include <LineHandler.h>
#include <TestUtils.h>

using namespace std;
using ::testing::StrictMock;
using ::testing::Sequence;
using ::testing::StrEq;

namespace embeddedcommandline {


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
	editor.putchar('a');
	editor.putchar('b');

	EXPECT_EQ(output.text, "ab");
}

TEST_F(DumbLineEditorTest, completeLinesAreHandled) {
	expectCompletedLine("hello");

	editor.putchar('h');
	editor.putchar('e');
	editor.putchar('l');
	editor.putchar('l');
	editor.putchar('o');
	editor.putchar('\n');

	EXPECT_EQ(output.text, "hello\n");
}

TEST_F(DumbLineEditorTest, canEditSeveralLinesAfterEachOther) {
	expectCompletedLine("ab");
	expectCompletedLine("cd");
	
	editor.putchar('a');
	editor.putchar('b');
	editor.putchar('\n');

	editor.putchar('c');
	editor.putchar('d');
	editor.putchar('\n');
}

TEST_F(DumbLineEditorTest, enforcesMaximumLineLength) {
	expectCompletedLine("abcdefghij");
	
	editor.putchar('a');
	editor.putchar('b');
	editor.putchar('c');
	editor.putchar('d');
	editor.putchar('e');
	editor.putchar('f');
	editor.putchar('g');
	editor.putchar('h');
	editor.putchar('i');
	editor.putchar('j');
	editor.putchar('k');
	editor.putchar('l');
	editor.putchar('m');
	editor.putchar('\n');

	EXPECT_EQ(output.text, "abcdefghij\n");
}

}

