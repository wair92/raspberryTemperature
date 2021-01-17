#include <limits.h>
#include <string>
#include <optional>
#include "parser.h"
#include "gtest/gtest.h"

namespace {

  class QuickTest : public testing::Test {
   protected:
    void SetUp() override { start_time_ = time(nullptr); }
    void TearDown() override {
      const time_t end_time = time(nullptr);
      EXPECT_TRUE(end_time - start_time_ <= 1) << "The test took too long.";
    }
    time_t start_time_;
  };

  class ParserTest : public QuickTest {
  // We don't need any more logic than already in the QuickTest fixture.
  // Therefore the body is empty.
};

// Tests positive input.
TEST_F(ParserTest, parseTemperaturePositive) {
  EXPECT_TRUE( Parser::parseTemperature("15 00 55 05 7f a5 81 66 b7 t=1312") == 1312 );
  EXPECT_TRUE( Parser::parseTemperature("15 00 55 05 7f a5 81 66 b7 t=1412") == 1412 );
  EXPECT_TRUE( Parser::parseTemperature("15 00 55 05 7f a5 81 66 b7 t=0") == 0 );
  EXPECT_TRUE( Parser::parseTemperature("15 00 55 05 7f a5 81 66 b7 t=-1312") == -1312 );
  EXPECT_TRUE( Parser::parseTemperature("15 00 55 05 7f a5 81 66 b7 t=100") == 100 );
}

TEST_F(ParserTest, parseTemperatureNegative) {
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

TEST_F(ParserTest, config){
  auto value = Parser::parseConfig("a=1");
  EXPECT_TRUE(value != std::nullopt);
  EXPECT_TRUE(value->first == "a");
  EXPECT_TRUE(value->second == "1");
  auto value2 = Parser::parseConfig("");
  EXPECT_TRUE(value2 == std::nullopt);
  auto value3 = Parser::parseConfig("a=");
  EXPECT_TRUE(value3 == std::nullopt);
  auto value4 = Parser::parseConfig("=");
  EXPECT_TRUE(value4 == std::nullopt);
  auto value5 = Parser::parseConfig("=");
  EXPECT_TRUE(value5 == std::nullopt);
  auto value6 = Parser::parseConfig("#a=6");
  EXPECT_TRUE(value6 == std::nullopt);
  auto value7 = Parser::parseConfig("a8");
  EXPECT_TRUE(value7 == std::nullopt);
  auto value8 = Parser::parseConfig("1");
  EXPECT_TRUE(value8 == std::nullopt);
}

}  // namespace
