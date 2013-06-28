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
	virtual void execute(const char* args[], int nargs) {
		string text;
		bool first=true;
		for(int i=0 ; i<nargs ; i++) {
			if(!first) {
				text.append("|");
			}

			text.append(args[i]);
			first=false;
		}

		execute(text);
	}

	MOCK_METHOD1(execute, void(string text));
};

class CommandManagerTest : public ::testing::Test {
protected:
	static const int MAX_COMMANDS = 5;
	static const int MAX_ARGS = 3;
	static const int MAX_COMMAND_LEN = 50;

	StrictMock<MockCommand> cmd1, cmd2, cmd3;
	TestOutputter output;

	CommandManager<MAX_COMMANDS, MAX_ARGS, MAX_COMMAND_LEN> manager;

	CommandManagerTest() : manager(output) {}

	void handle(std::string line) {
		char buffer[MAX_COMMAND_LEN+1];
		std::size_t length = line.copy(buffer, MAX_COMMAND_LEN, 0);
		buffer[length]='\0';
		manager.handleLine(buffer);
	}

};

const int CommandManagerTest::MAX_COMMANDS;
const int CommandManagerTest::MAX_ARGS;
const int CommandManagerTest::MAX_COMMAND_LEN;

TEST_F(CommandManagerTest, dispatchesCommandWithoutArguments) {
	manager.addCommand("quit", cmd1);

	EXPECT_CALL(cmd1, execute(StrEq("")));

	handle("quit");
	EXPECT_EQ("", output.text);
}

TEST_F(CommandManagerTest, doesNotDispatchUnlessCommandWasRegistered) {
	manager.addCommand("quit", cmd1);

	handle("help");
	EXPECT_EQ("ERROR: Unknown command \"help\"", output.text);
}

TEST_F(CommandManagerTest, dispatchesToCorrectCommand) {
	manager.addCommand("quit", cmd1);
	manager.addCommand("quitter", cmd1);
	manager.addCommand("quitt", cmd2);
	manager.addCommand("quitte", cmd1);

	EXPECT_CALL(cmd1, execute(StrEq("")));

	handle("quitt");
	EXPECT_EQ("", output.text);
}

TEST_F(CommandManagerTest, separatesArguments) {
	manager.addCommand("write", cmd1);

	EXPECT_CALL(cmd1, execute(StrEq("mem|0x1234|0xdeadbeef")));

	handle("write   mem 0x1234   0xdeadbeef     ");
	EXPECT_EQ("", output.text);
}

TEST_F(CommandManagerTest, doesNothingOnEmptyLine) {
	manager.addCommand("write", cmd1);

	handle("   ");
	EXPECT_EQ("", output.text);
}

TEST_F(CommandManagerTest, tooManyArgsYieldsError) {
	manager.addCommand("write", cmd1);

	handle("write 1 2 3 4");
	EXPECT_EQ("ERROR: Too many arguments", output.text);
}

}