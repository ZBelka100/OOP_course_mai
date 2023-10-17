#include "eleven.h"

#include <gtest/gtest.h>

bool constructorTest()
{
    Eleven s1 {'1', '2', '3'};
    std::string test = "123";
    Eleven s2(test);
    Eleven s3 {'3', '6', '1'}, s4(s3);
    Eleven s5{'0', '0', '0'}, s6("000");

    return (s1 == s2) && (s3 == s4) && (s5 == s6);
}
TEST(test_1_6, basic_test_set) {
    ASSERT_THROW(Eleven el(10, 'K'), std::invalid_argument);
}

TEST(test_1_7, basic_test_set) {
    ASSERT_THROW(Eleven el("1F23A"), std::invalid_argument);
}

TEST(test_1_8, basic_test_set) {
    ASSERT_THROW(Eleven el({'K', 'A', 'R'}), std::invalid_argument);
}

TEST(test_02, basic_test_set) {
    Eleven el{"12571"};
    Eleven el1(el);
    ASSERT_TRUE(el1 == el);
}

TEST(test_03, basic_test_set) {
    Eleven el3{"12571"};
    Eleven el2{"12571"};
    Eleven el1(std::move(el2));
    ASSERT_TRUE(el3 == el1);
}

TEST(test_10, basic_arithmetic_plus_test)
{
    Eleven s1 {'A', '2', '3'};
    Eleven s2 {'2', '3', '5'};
    Eleven s3 {'1', '1', '5', '8'};

    ASSERT_TRUE((s1 + s2) == s3);
}

TEST(test_11, big_arithmetic_plus_test)
{
    Eleven s1 ("49271402");
    Eleven s2 ("42131279AA5");
    Eleven s3 ("4217A5403A7");;

    ASSERT_TRUE((s1 + s2) == s3);
}

TEST(test_12, small_arithmetic_plus_test)
{
    Eleven s1 {'6', 'A'};
    Eleven s2 {'2', '3', '5'};
    Eleven s3 {'2', 'A', '4'};

    ASSERT_TRUE((s1 + s2) == s3);
}

TEST(test_13, small_arithmetic_plus_test)
{
    Eleven s1 ("5");
    Eleven s2 {'2', '3', '5'};
    Eleven s3("23A");

    ASSERT_TRUE((s1 + s2) == s3);
}

TEST(test_14, arithmetic_plus_test)
{
    Eleven s1 ("AAAAA");
    Eleven s2 {'1'};
    Eleven s3("100000");

    ASSERT_TRUE((s1 + s2) == s3);
}

TEST(test_15, arithmetic_plus_test)
{
    Eleven s1 ("AAAAA");
    Eleven s2 {'1'};
    Eleven s3("100000");
    Eleven s4 = s1 + s2;

    ASSERT_TRUE(s4 == s3);
}


TEST(test_16, arithmetic_plus_zero_test)
{
    Eleven s1;
    Eleven s2 {'1'};
    Eleven s3("1");

    ASSERT_TRUE((s1 + s2) == s3);
}

TEST(test_20, big_arithmetic_minus_test)
{
    std::string a = "112321";
    std::string b = "40021";
    std::string c = "82300";
    Eleven s1(a);
    Eleven s2(b);
    Eleven s3(c);

    ASSERT_TRUE((s1 - s2) == s3);
}

TEST(test_21, arithmetic_minus_test)
{
    std::string a = "6A134";
    std::string b = "67510";
    std::string c = "2724";
    Eleven s1(a);
    Eleven s2(b);
    Eleven s3(c);

    ASSERT_TRUE((s1 - s2) == s3);
}

TEST(test_22, big_sub_arithmetic_minus_test)
{
    Eleven s1{'A', '3', '4'};
    Eleven s2{'A', '8', '2', '9', '1', '0'};

    EXPECT_THROW((s1 - s2), std::invalid_argument);
}

TEST(test_23, sub_arithmetic_minus_test)
{
    Eleven s1{'A', '6', '4', '5', '1', '6'};
    Eleven s2{'6', '9', '6', '1', '9', '9'};
    Eleven s3("379328");

    ASSERT_TRUE((s1 - s2) == s3);
}

TEST(test_24, arithmetic_minus_zero_test)
{
    Eleven s1;
    Eleven s2 {'2', 'A'};
    Eleven s3("2A");

    ASSERT_TRUE((s2 - s1) == s3);
}

TEST(test_30, boolean_operator_equal_test)
{
    Eleven s1 {'1', '2', '3'};
    Eleven s2 {'1', '2', '3'};

    ASSERT_TRUE(s1 == s2);
}

TEST(test_31, boolean_operator_more_test)
{
    Eleven s1 {'1', 'A', '3'};
    Eleven s2 {'1', '2', '3'};

    ASSERT_TRUE(s1 > s2);
}

TEST(test_32, boolean_operator_less_test)
{
    Eleven s1 {'1', '2', '4'};
    Eleven s2 {'1', '2', '3'};

    ASSERT_TRUE(s2 < s1);
}

TEST(test_40, add_with_assign_operator_test)
{
    Eleven s1 {'3', '2', '3'};
    Eleven s2 {'1', '1', '1'};
    Eleven s3 {'3', '2', '3'};
    s3 += s2;

    ASSERT_TRUE((s1 + s2) == s3);
}

TEST(test_41, sub_with_assign_operator_test)
{
    Eleven s1 {'3', '2', '3'};
    Eleven s2 {'1', '1', '1'};
    Eleven s3 {'3', '2', '3'};
    s3 -= s2;

    ASSERT_TRUE(s3 == s3);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
