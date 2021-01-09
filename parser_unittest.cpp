#include <limits.h>
#include <string>
#include <optional>
#include "parser.h"
#include "gtest/gtest.h"
namespace {

// Tests positive input.
TEST(ParserTest, Positive) {
  EXPECT_TRUE( Parser::parseTemperature("15 00 55 05 7f a5 81 66 b7 t=1312") == 1312 );
  EXPECT_TRUE( Parser::parseTemperature("15 00 55 05 7f a5 81 66 b7 t=1412") == 1412 );
  EXPECT_TRUE( Parser::parseTemperature("15 00 55 05 7f a5 81 66 b7 t=0") == 0 );
  EXPECT_TRUE( Parser::parseTemperature("15 00 55 05 7f a5 81 66 b7 t=-1312") == -1312 );
  EXPECT_TRUE( Parser::parseTemperature("15 00 55 05 7f a5 81 66 b7 t=100") == 100 );
}

TEST(ParserTest, Negative) {
  EXPECT_FALSE( Parser::parseTemperature("15 00 55 05 7f a5 81 66 b7 t=1313") == 1.312 );
  EXPECT_FALSE( Parser::parseTemperature("15 00 55 05 7f a5 81 66 b7 t1313") == 1.312 );
  EXPECT_FALSE( Parser::parseTemperature("15 00 55 05 7f a5 81 66 b7 t=131a3") == 1.312 );
  EXPECT_FALSE( Parser::parseTemperature("15 00 55 05 7f a5 81 66 b7 t131a3") == 1.312 );
  EXPECT_FALSE( Parser::parseTemperature("") == 0 );
  auto temperature = Parser::parseTemperature("15 00 55 05 7f a5 81 66 b7 t131a3");
  EXPECT_TRUE( temperature == std::nullopt);
  auto temperature2 = Parser::parseTemperature("15 00 55 05 7f a5 81 66 b7 t=");
  EXPECT_TRUE( temperature2 == std::nullopt);
}

}  // namespace
