#include <gtest/gtest.h>
#include "CommandParser.h"

using testing::Eq;
using namespace std;

TEST(GameTest, parser_test_reset) {
    ASSERT_EQ(CommandType::RESET, CommandParser::parseCommand("reset", 10, 10).first);
    ASSERT_EQ(CommandType::RESET, CommandParser::parseCommand(" reset  ", 10, 10).first);
    ASSERT_EQ(CommandType::NONE, CommandParser::parseCommand("reset abcde", 10, 10).first);
    ASSERT_EQ(CommandType::NONE, CommandParser::parseCommand(" re set  ", 10, 10).first);
}

TEST(GameTest, parser_test_set) {
    ASSERT_EQ(CommandType::SET, CommandParser::parseCommand("set A0", 10, 10).first);
    ASSERT_EQ(CommandType::SET, CommandParser::parseCommand(" set  C9   ", 10, 10).first);
    ASSERT_EQ(CommandType::NONE, CommandParser::parseCommand("set Z2", 10, 10).first);
    ASSERT_EQ(CommandType::NONE, CommandParser::parseCommand("set ZZ ABCDE", 10, 10).first);
    ASSERT_EQ(CommandType::NONE, CommandParser::parseCommand(" se t A0 ", 10, 10).first);
}

TEST(GameTest, parser_test_clear) {
    ASSERT_EQ(CommandType::CLEAR, CommandParser::parseCommand("clear B4", 10, 10).first);
    ASSERT_EQ(CommandType::CLEAR, CommandParser::parseCommand(" clear    C2  ", 10, 10).first);
    ASSERT_EQ(CommandType::NONE, CommandParser::parseCommand("clear 22 asdasd", 10, 10).first);
    ASSERT_EQ(CommandType::NONE, CommandParser::parseCommand(" cle ar B7 ", 10, 10).first);
}

TEST(GameTest, parser_test_step) {
    ASSERT_EQ(CommandType::STEP, CommandParser::parseCommand("step", 10, 10).first);
    ASSERT_EQ(CommandType::STEP, CommandParser::parseCommand(" step   10  ", 10, 10).first);
    ASSERT_EQ(CommandType::NONE, CommandParser::parseCommand("step  a", 10, 10).first);
    ASSERT_EQ(CommandType::NONE, CommandParser::parseCommand(" s tep 10 ", 10, 10).first);
}

TEST(GameTest, parser_test_back) {
    ASSERT_EQ(CommandType::BACK, CommandParser::parseCommand("back", 10, 10).first);
    ASSERT_EQ(CommandType::BACK, CommandParser::parseCommand(" back  ", 10, 10).first);
    ASSERT_EQ(CommandType::NONE, CommandParser::parseCommand("back abcde", 10, 10).first);
    ASSERT_EQ(CommandType::NONE, CommandParser::parseCommand(" ba ck  ", 10, 10).first);
}

TEST(GameTest, parser_test_save) {
    ASSERT_EQ(CommandType::SAVE, CommandParser::parseCommand("save \"test\"", 10, 10).first);
    ASSERT_EQ(CommandType::SAVE, CommandParser::parseCommand("  save     \"another_test\"   ", 10, 10).first);
    ASSERT_EQ(CommandType::NONE, CommandParser::parseCommand("save 2 asd", 10, 10).first);
    ASSERT_EQ(CommandType::NONE, CommandParser::parseCommand("sa ve \"s\"", 10, 10).first);
}

TEST(GameTest, parser_test_load) {
    ASSERT_EQ(CommandType::LOAD, CommandParser::parseCommand("load \"test\"", 10, 10).first);
    ASSERT_EQ(CommandType::LOAD, CommandParser::parseCommand("   load     \"test\"   ", 10, 10).first);
    ASSERT_EQ(CommandType::NONE, CommandParser::parseCommand("load 2 asd", 10, 10).first);
    ASSERT_EQ(CommandType::NONE, CommandParser::parseCommand("l oad \"s\"", 10, 10).first);
}