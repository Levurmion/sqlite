#include <gtest/gtest.h>
#include <string>
#include <stdexcept>
#include "argparser.hpp"

using namespace std;

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
};

TEST(PositionalArgumentsTest, PositionalArgumentsCorrectlyLoaded) {
  const char* argv[3] = {"command", "file/path/input", "file/path/output"};
  ArgParser arguments = ArgParser(3, argv);

  EXPECT_EQ(arguments.positional[0], "file/path/input");
  EXPECT_EQ(arguments.positional[1], "file/path/output");
};

TEST(PositionalArgumentsTest, PositionalArgumentCannotBeLoadedAfterFlags) {
  const char* argv[5] = {"command", "file/path/input", "--flag", "file/path/output", "some_positional"};
  EXPECT_THROW(ArgParser(5, argv), std::invalid_argument*);
};

TEST(ShortFlagsTest, ShortFlagsWithNoArgumentsReturnedAsTrueStrings) {
  const char* argv[5] = {"command", "file/path/input", "-x", "-y", "-z"};
  ArgParser arguments = ArgParser(5, argv);

  std::unordered_map<string, bool> expectedFlags = {{"x", true}, {"y", true}, {"z", true}};
  for (const auto& [key, value] : arguments.shortFlags) {
    EXPECT_EQ(value, "true");
    EXPECT_EQ(expectedFlags[key], true);
  }
};

TEST(ShortFlagsTest, ShortFlagsWithArgumentsReturnedWithArgs) {
  const char* argv[6] = {"command", "file/path/input", "-x", "value/for/x", "-y", "value/for/y"};
  ArgParser arguments = ArgParser(6, argv);

  std::unordered_map<string, string> expectedFlagArgs = {{"x", "value/for/x"}, {"y", "value/for/y"}};
  for (const auto& [key, value] : arguments.shortFlags) {
    EXPECT_EQ(expectedFlagArgs[key], value);
  }
};

TEST(LongFlagsTest, LongFlagsWithNoArgumentsReturnedAsTrueStrings) {
  const char* argv[5] = {"command", "file/path/input", "--long", "--flag", "--args"};
  ArgParser arguments = ArgParser(5, argv);

  std::unordered_map<string, bool> expectedFlags = {{"long", true}, {"flag", true}, {"args", true}};
  for (const auto& [key, value] : arguments.longFlags) {
    EXPECT_EQ(value, "true");
    EXPECT_EQ(expectedFlags[key], true);
  }
};

TEST(LongFlagsTest, LongFlagsWithArgumentsReturnedWithArgs) {
  const char* argv[6] = {"command", "file/path/input", "--long", "value/for/long", "--flag", "value/for/flag"};
  ArgParser arguments = ArgParser(6, argv);

  std::unordered_map<string, string> expectedFlagArgs = {{"long", "value/for/long"}, {"flag", "value/for/flag"}};
  for (const auto& [key, value] : arguments.longFlags) {
    EXPECT_EQ(expectedFlagArgs[key], value);
  }
};