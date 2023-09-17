#include <gtest/gtest.h>
#include "extractnumber.h"

TEST(test_01, basic_test_set)
{
    ASSERT_TRUE(extractnumber("1")=="1");
}

TEST(test_02, basic_test_set)
{
    ASSERT_TRUE(extractnumber("")=="");
}

TEST(test_03, basic_test_set)
{
    ASSERT_TRUE(extractnumber("a1b2b3c4")=="1234");
}

TEST(test_04, basic_test_set)
{
    ASSERT_TRUE(extractnumber("aaaa")=="");
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}