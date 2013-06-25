#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>

#include <LineHandler.h>
#include <CommandManager.h>
#include <Command.h>
#include <TestUtils.h>

using namespace std;
using ::testing::StrictMock;
using ::testing::Sequence;
using ::testing::StrEq;

namespace embeddedcommandline {

class MockCommand : public Command {
public:
	virtual void execute(char* args[], int nargs) {
		string text;
		bool first=true;
		for(int i=0 ; i<nargs ; i++) {
			text.append(args[i]);
			if(!first) {
				text.append("|");
				first=false;
			}
		}

		execute(text);
	}

	MOCK_METHOD1(execute, void(string text));
};

class CommandManagerTest : public ::testing::Test {
	const int MAX_COMMANDS = 5;
	const int MAX_ARGS = 3;

	StrictMock<MockCommand> cmd1, cmd2, cmd3;
	TestOutputter output;

	CommandManager<MAX_COMMANDS, MAX_ARGS> manager;

	CommandManagerTest() : manager(&output) {}

};

TEST_F(CommandManagerTest, dispatchesCommandWithoutArguments) {
	manager.addCommand("quit", cmd1);

	EXPECT_CALL(cmd1.execute(StrEq("")));

	manager.HandleLine("quit");
}

}