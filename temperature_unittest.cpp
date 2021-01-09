#include <limits.h>
#include <string>
#include "temperature.h"
#include "gtest/gtest.h"
namespace {

// Tests positive input.
TEST(checkCRCTest, Positive) {
  Temperature temperature;
  EXPECT_TRUE( temperature.checkCRC("2d 00 55 05 7f a5 81 66 61 : crc=61 YES") );
}

TEST(checkCRCTest, Negative) {
  Temperature temperature;
  EXPECT_FALSE( temperature.checkCRC("2d 00 55 05 7f a5 81 66 61 : crc=60 NO") );
  EXPECT_FALSE( temperature.checkCRC("2d 00 55 05 7f a5 81 66 61 : crc=60 OTHER") );
  EXPECT_FALSE( temperature.checkCRC("2d 00 55 05 7f a5 81 66 61 : crc=60 XX") );
}

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

// Step 3. Call RUN_ALL_TESTS() in main().
//
// We do this by linking in src/gtest_main.cc file, which consists of
// a main() function which calls RUN_ALL_TESTS() for us.
//
// This runs all the tests you've defined, prints the result, and
// returns 0 if successful, or 1 otherwise.
//
// Did you notice that we didn't register the tests?  The
// RUN_ALL_TESTS() macro magically knows about all the tests we
// defined.  Isn't this convenient?
