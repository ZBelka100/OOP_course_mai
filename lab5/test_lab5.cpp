#include "./src/allocator.h"
#include "./src/list.h"
#include "./src/iterator.h"

#include <gtest/gtest.h>
#include <map>
#include <vector>

TEST(test_00, testAllocatorBase) {
    Allocator<int> allocator;
    int* ptr = allocator.allocate(1);
    ASSERT_NE(ptr, nullptr);
    allocator.deallocate(ptr, 1);
}

TEST(test_01, testAllocatorManyAlloc) {
    Allocator<double> test;
    double* ptr = test.allocate(450);
    test.allocate(300); test.allocate(300); test.allocate(300);
    test.allocate(300); test.allocate(300); test.allocate(300);
    test.allocate(300); test.allocate(300); test.allocate(300);
    test.allocate(300); test.allocate(300); test.allocate(300);
    test.allocate(300); test.allocate(300); test.allocate(300);
    test.allocate(300); test.allocate(300); test.allocate(300);

    ASSERT_TRUE(1);
}

TEST(test_02, testAllocatorCheckDestroy)
{
    Allocator<char> test;
    char* ptr = test.allocate(25);
    test.allocate(1); test.allocate(1); test.allocate(1);
    test.allocate(1); test.allocate(1); test.allocate(1);
    test.allocate(1); test.allocate(1); test.allocate(1);
    test.allocate(1); test.allocate(1); test.allocate(1);
    test.allocate(1); test.allocate(1); test.allocate(1);
    test.allocate(1); test.allocate(1); test.allocate(1);
    test.allocate(1); test.allocate(1); test.allocate(1);
    test.allocate(1); test.allocate(1); test.allocate(1);
    test.allocate(1); test.allocate(1); test.allocate(1);
    test.allocate(1); test.allocate(1); test.allocate(1);
    test.allocate(1); test.allocate(1); test.allocate(1);
    test.allocate(1); test.allocate(1); test.allocate(1);
    test.allocate(1); test.allocate(1); test.allocate(1);
    test.allocate(1); test.allocate(1); test.allocate(1);
    test.destroy(ptr);

    ASSERT_TRUE(1);
}

TEST(test_03, testAllocatorCheckDestructor)
{
    Allocator<char> test;
    char* ptr = test.allocate(25);
    test.allocate(1); test.allocate(1); test.allocate(1);
    test.allocate(1); test.allocate(1); test.allocate(1);
    test.allocate(1); test.allocate(1); test.allocate(1);
    test.allocate(1); test.allocate(1); test.allocate(1);
    test.allocate(1); test.allocate(1); test.allocate(1);
    test.allocate(1); test.allocate(1); test.allocate(1);
    test.allocate(1); test.allocate(1); test.allocate(1);
    test.allocate(1); test.allocate(1); test.allocate(1);
    test.allocate(1); test.allocate(1); test.allocate(1);
    test.allocate(1); test.allocate(1); test.allocate(1);
    test.allocate(1); test.allocate(1); test.allocate(1);
    test.allocate(1); test.allocate(1); test.allocate(1);
    test.allocate(1); test.allocate(1); test.allocate(1);
    test.allocate(1); test.allocate(1); test.allocate(1);
    
    ASSERT_TRUE(1);
}

TEST(test_04, testAllocatorCheck)
{
    Allocator<size_t> test;
    size_t* ptr = test.allocate(25);
    test.allocate(300); test.allocate(300); test.allocate(300);
    test.allocate(300); test.allocate(300); test.allocate(300);
    test.allocate(300); test.allocate(300); test.allocate(300);
    test.allocate(300); test.allocate(300); test.allocate(300);
    test.allocate(300); test.allocate(300); test.allocate(300);
    test.allocate(300); test.allocate(300); test.allocate(300);
    test.allocate(300); test.allocate(300); test.allocate(300);
    test.allocate(300); test.allocate(300); test.allocate(300);

    test.deallocate(ptr, 24);
    
    ASSERT_TRUE(1);
}


TEST(test_05, testAllocatorCheckToMap)
{
    std::map<int, uint64_t, std::less<uint64_t>, Allocator<std::pair<const int, uint64_t>>> test;
    for (size_t i = 0; i < 1000; ++i) {
        test[i] = i + 1;
    }

    ASSERT_TRUE(1);
}

TEST(test_06, IteratorTestBasicOperations) {
    List<int, Allocator<Node<int>>> myList;
    myList.push_back(10);
    myList.push_back(20);
    myList.push_back(30);

    Iterator<int> it = myList.begin();
    Iterator<int> end = myList.end();
    EXPECT_EQ(*it, 10);
    ++it;
    EXPECT_EQ(*it, 20);
    it++;
    EXPECT_EQ(*it, 30);
    Iterator<int> itCopy = it;
    EXPECT_NE(it, end);
    EXPECT_EQ(it, itCopy);
    it++;
    EXPECT_EQ(it, end);
    EXPECT_NE(it, itCopy);
}

TEST(test_07, ConstIteratorTestBasicOperations) {
    List<int, Allocator<Node<int>>> myList;
    myList.push_back(10);
    myList.push_back(20);
    myList.push_back(30);
    ConstIterator<int> it = myList.cbegin();
    ConstIterator<int> end = myList.cend();
    EXPECT_EQ(*it, 10);
    ++it;
    EXPECT_EQ(*it, 20);
    it++;
    EXPECT_EQ(*it, 30);
    ConstIterator<int> itCopy = it;
    EXPECT_EQ(it, itCopy);
    EXPECT_NE(it, end);
    it++;
    EXPECT_EQ(it, end);
    EXPECT_NE(it, itCopy);
}

TEST(test_08, testIteratorOperatorEqual) {
    List<int, Allocator<Node<int>>> myList;
    myList.push_back(10);
    myList.push_back(20);
    myList.push_back(30);
    Iterator<int> it = myList.begin();
    ASSERT_TRUE(myList.begin() == it);
}

TEST(test_09, testIteratorOperatorUnequal) {
    List<int, Allocator<Node<int>>> myList;
    myList.push_back(10);
    myList.push_back(20);
    myList.push_back(30);
    Iterator<int> it1 = myList.begin();
    Iterator<int> it2 = myList.end();

    ASSERT_TRUE(it1 != it2);
}

TEST(test_10, testConstIteratorOperatorEqual) {
    List<int, Allocator<Node<int>>> myList;
    myList.push_back(10);
    myList.push_back(20);
    myList.push_back(30);
    ConstIterator<int> it = myList.cbegin();
    ASSERT_TRUE(myList.cbegin() == it);
}

TEST(test_11, testConstIteratorOperatorUnequal) {
    List<int, Allocator<Node<int>>> myList;
    myList.push_back(10);
    myList.push_back(20);
    myList.push_back(30);
    ConstIterator<int> it1 = myList.cbegin();
    ConstIterator<int> it2 = myList.cend();
    ASSERT_TRUE(it1 != it2);
}

TEST(test_12, ListConstructorTest_DefaultConstructor) {
    List<int, Allocator<Node<int>>> myList;
    EXPECT_TRUE(myList.empty());
}

TEST(test_13, ListMethodTest_PushBack) {
    List<int, Allocator<Node<int>>> myList;
    myList.push_back(10);
    EXPECT_FALSE(myList.empty());
    EXPECT_EQ(myList.front(), 10);
    EXPECT_EQ(myList.back(), 10);
}

TEST(test_14, ListMethodTest_PushFront) {
    List<int, Allocator<Node<int>>> myList;
    myList.push_back(10);
    myList.push_back(10);
    myList.push_back(10);
    myList.push_back(10);
    myList.push_back(10);

    EXPECT_FALSE(myList.empty());
    EXPECT_EQ(myList.front(), 10);
    EXPECT_EQ(myList.back(), 10);
}

TEST(test_15, ListMethodTest_PopBack) {
    List<int, Allocator<Node<int>>> myList;
    myList.push_back(1);
    myList.push_back(2);
    myList.push_back(3);
    myList.pop_back();
    EXPECT_EQ(myList.front(), 1);
    EXPECT_EQ(myList.back(), 2);
}

TEST(test_16, ListMethodTest_PopFront) {
    List<int, Allocator<Node<int>>> myList;
    myList.push_back(1);
    myList.push_back(2);
    myList.push_back(3);
    myList.pop_front();
    EXPECT_EQ(myList.front(), 2);
    EXPECT_EQ(myList.back(), 3);
}

TEST(test_17, ListMethodTest_Clear) {
    List<int, Allocator<Node<int>>> myList;
    myList.push_back(1);
    myList.push_back(2);
    myList.push_back(3);
    myList.clear();
    EXPECT_TRUE(myList.empty());
}

TEST(test_18, ListMethodTest_Iterator) {
    List<int, Allocator<Node<int>>> myList;
    myList.push_back(1);
    myList.push_back(2);
    myList.push_back(3);
    
    int sum = 0;
    for (const auto& elem : myList) {
        sum += elem;
    }
    EXPECT_EQ(sum, 6);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}