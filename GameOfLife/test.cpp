#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <iostream>
#include <fstream>
#include "GameModel.h"
#include "CommandParser.h"

using testing::Eq;
using namespace std;

namespace {
    class GameTest : public testing::Test {
    public:

    };
}

TEST_F(GameTest, parser_test_reset) {
    ASSERT_EQ(OK, CommandParser::parseCommand("reset"));
    ASSERT_EQ(OK, CommandParser::parseCommand(" reset  "));
    ASSERT_EQ(INVALID_ARG, CommandParser::parseCommand("reset abcde"));
    ASSERT_EQ(INVALID_CMD, CommandParser::parseCommand(" re set  "));
}

TEST_F(GameTest, parser_test_set) {
    ASSERT_EQ(OK, CommandParser::parseCommand("set A0"));
    ASSERT_EQ(OK, CommandParser::parseCommand(" set  C9   "));
    ASSERT_EQ(INVALID_ARG, CommandParser::parseCommand("set Z2"));
    ASSERT_EQ(INVALID_ARG, CommandParser::parseCommand("set ZZ ABCDE"));
    ASSERT_EQ(INVALID_CMD, CommandParser::parseCommand(" se t A0 "));
}

TEST_F(GameTest, parser_test_clear) {
    ASSERT_EQ(OK, CommandParser::parseCommand("clear B4"));
    ASSERT_EQ(OK, CommandParser::parseCommand(" clear    C2  "));
    ASSERT_EQ(INVALID_ARG, CommandParser::parseCommand("clear 22 asdasd"));
    ASSERT_EQ(INVALID_CMD, CommandParser::parseCommand(" cle ar B7 "));
}

TEST_F(GameTest, parser_test_step) {
    ASSERT_EQ(OK, CommandParser::parseCommand("step"));
    ASSERT_EQ(OK, CommandParser::parseCommand(" step   10  "));
    ASSERT_EQ(INVALID_ARG, CommandParser::parseCommand("step  a"));
    ASSERT_EQ(INVALID_CMD, CommandParser::parseCommand(" s tep 10 "));
}

TEST_F(GameTest, parser_test_back) {
    ASSERT_EQ(OK, CommandParser::parseCommand("back"));
    ASSERT_EQ(OK, CommandParser::parseCommand(" back  "));
    ASSERT_EQ(INVALID_ARG, CommandParser::parseCommand("back abcde"));
    ASSERT_EQ(INVALID_CMD, CommandParser::parseCommand(" ba ck  "));
}

TEST_F(GameTest, parser_test_save) {
    ASSERT_EQ(OK, CommandParser::parseCommand("save \"test\""));
    ASSERT_EQ(OK, CommandParser::parseCommand("  save     \"another_test\"   "));
    ASSERT_EQ(INVALID_ARG, CommandParser::parseCommand("save 2"));
    ASSERT_EQ(INVALID_CMD, CommandParser::parseCommand("sa ve \"s\""));
}

TEST_F(GameTest, parser_test_load) {
    ifstream ld_file("test.txt");
    bool flag = ld_file.is_open();
    ParseResult shouldBe = flag ? OK : FILE_DOESNT_EXIST;
    if (flag) ld_file.close();
    ASSERT_EQ(shouldBe, CommandParser::parseCommand("load \"test\""));
    ASSERT_EQ(shouldBe, CommandParser::parseCommand("   load     \"test\"   "));
    ASSERT_EQ(INVALID_ARG, CommandParser::parseCommand("load 2"));
    ASSERT_EQ(INVALID_CMD, CommandParser::parseCommand("l oad \"s\""));
}