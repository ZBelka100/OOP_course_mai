#include "../header/all.h"

#include <gtest/gtest.h>

bool constructorTest() {
    point p1 = {0, 0}, p2 = {1, 0}, p3 = {0, 1}, p4 = {1, 1};
    Figure f1;
    Figure f2;
    Triangle t1(p1, p2, p3);
    Triangle t2(0, 0, 0, 1, 1, 0);
    Square s1(p1, p2, p3, p4);
    Square s2(1, 1, 0, 1, 1, 0, 0, 0);;
    Rectangle r1(p1, p2, p3, p4);
    Rectangle r2(0, 1, 0, 0, 1, 0, 1, 1);
    
    return (f1 == f2) && (t1 == t2) && (s1 == s2) && (r1 == r2);
}

TEST(test_01, create_test_set) {
    EXPECT_THROW(Square ({0, 0}, {1, 0}, {0, 1}, {0, 0}), std::invalid_argument);
}

TEST(test_02, create_test_set) {
    EXPECT_THROW(Square ({0, 0}, {1, 0}, {0, 1}, {1, 2}), std::invalid_argument);
}

TEST(test_03, create_test_set) {
    EXPECT_THROW(Square ({0, 0}, {2, 0}, {0, 1}, {2, 1}), std::invalid_argument);
}

TEST(test_04, create_test_set) {
    EXPECT_NO_THROW(Rectangle ({0, 0}, {1, 0}, {0, 2}, {1, 2}));
}

TEST(test_05, create_test_set) {
    EXPECT_THROW(Rectangle ({0, 0}, {1, 1000}, {0, 1}, {1, 0}), std::invalid_argument);
}

TEST(test_06, create_test_set) {
    EXPECT_THROW(Triangle ({0, 0}, {0, 0}, {0, 1}), std::invalid_argument);
}

TEST(test_07, create_test_set) {
    EXPECT_NO_THROW(Triangle ({0, 0}, {1, 0}, {2, 0}));
}

TEST(test_08, create_test_set) {
    EXPECT_NO_THROW(Square ({0, 0}, {1, 1}, {0, 2}, {-1, 1}));
}

TEST(FigureCopyConstructor, test) {
    Figure* t;
    Figure* t1 = t;
    ASSERT_TRUE(t == t1);
}

TEST(FigureMoveConstructor, test) {
    Figure** t;
    Figure** t1 = t;
    ASSERT_TRUE(t == t1);
}

TEST(PointOperatorEqual, SamePointEquality) {
    point p1 = {1.0, 2.0};
    point p2 = {1.0, 2.0};
    EXPECT_TRUE(p1 == p2);
}

TEST(PointOperatorEqual, DifferentPointsInequality) {
    point p1 = {1.0, 2.0};
    point p2 = {3.0, 4.0};
    EXPECT_FALSE(p1 == p2);
}

TEST(PointOperatorLess, LessThan) {
    point p1 = {1.0, 2.0};
    point p2 = {3.0, 4.0};
    EXPECT_TRUE(p1 < p2);
}

TEST(PointOperatorLess, GreaterThan) {
    point p1 = {3.0, 4.0};
    point p2 = {1.0, 2.0};
    EXPECT_FALSE(p1 < p2);
}

TEST(PointDistance, CalculatingDistance) {
    point p1 = {0.0, 0.0};
    point p2 = {3.0, 4.0};
    EXPECT_DOUBLE_EQ(Distance(p1, p2), 5.0);
}

TEST(PointComparePoints, Less) {
    point p1 = {1.0, 2.0};
    point p2 = {3.0, 4.0};
    EXPECT_TRUE(comparePoints(p1, p2));
}

TEST(PointComparePoints, Greater) {
    point p1 = {3.0, 4.0};
    point p2 = {1.0, 2.0};
    EXPECT_FALSE(comparePoints(p1, p2));
}

TEST(PointComparePointsY, Less) {
    point p1 = {1.0, 2.0};
    point p2 = {1.0, 4.0};
    EXPECT_FALSE(comparePointsY(p1, p2));
}

TEST(PointComparePointsY, Greater) {
    point p1 = {1.0, 4.0};
    point p2 = {1.0, 2.0};
    EXPECT_TRUE(comparePointsY(p1, p2));
}

TEST(Area, Triangle) {
    Triangle triangle({0, 0}, {-3, 0}, {0, -3});
    EXPECT_EQ(double(triangle), 4.5);
}

TEST(Area, Rectangle) {
    Rectangle rectangle({0, 0}, {-2, 0}, {0, -3}, {-2, -3});
    EXPECT_EQ(double(rectangle), 6);
}

TEST(Area, Square) {
    Square square({0, 0}, {-3, 0}, {0, -3}, {-3, -3});
    EXPECT_EQ(double(square), 9);
}

TEST(Center, Triangle) {
    Triangle triangle({0, 0}, {-3, 0}, {0, -3});
    point p = {-1, -1};
    EXPECT_TRUE(triangle.findCenter() == p);
}

TEST(Center, Rectangle) {
    Rectangle rectangle({0, 0}, {-2, 0}, {0, -3}, {-2, -3});
    point p = {-1, -1.5};
    EXPECT_TRUE(rectangle.findCenter() == p);
}

TEST(Center, Square) {
    Square square({0, 0}, {-3, 0}, {0, -3}, {-3, -3});
    point p = {-1.5, -1.5};
    EXPECT_TRUE(square.findCenter() == p);
}

TEST(FigureArray, AddAndRemoveFigures) {
    figureArray arr;
    Figure* figure1 = new Figure();
    Figure* figure2 = new Figure();
    
    arr.pushBack(figure1);
    arr.pushBack(figure2);

    EXPECT_EQ(arr.getSize(), 2);
    
    arr.remove(1);
    EXPECT_EQ(arr.getSize(), 1);
}

TEST(FigureArray, SumAreas) {
    figureArray arr;
    Figure* figure1 = new Triangle({0, 0}, {2, 0}, {0, 2});
    Figure* figure2 = new Square ({0, 0}, {2, 0}, {0, 2}, {2, 2});
    Figure* figure3 = new Rectangle ({0, 0}, {1, 0}, {0, 2}, {1, 2});

    arr.pushBack(figure1);
    arr.pushBack(figure2);
    arr.pushBack(figure3);

    EXPECT_TRUE(arr.findSumAreas() == 8);
}

TEST(FigureArrayTest, TestFindAllCenters) {
    figureArray arr;
    Figure* figure1 = new Triangle({0, 0}, {3, 0}, {0, 3});
    Figure* figure2 = new Square ({0, 0}, {2, 0}, {0, 2}, {2, 2});
    Figure* figure3 = new Rectangle ({0, 0}, {1, 0}, {0, 2}, {1, 2});
    arr.pushBack(figure1);
    arr.pushBack(figure2);
    arr.pushBack(figure3);
    std::stringstream capturedOutput;
    std::streambuf* oldCoutBuffer = std::cout.rdbuf();
    std::cout.rdbuf(capturedOutput.rdbuf());
    arr.findAllCenters();
    std::cout.rdbuf(oldCoutBuffer);
    std::string expectedOutput = "1 1  1 1  0.5 1  ";

    ASSERT_EQ(capturedOutput.str(), expectedOutput);
}

TEST(FigureArrayTest, TestFindAllAreas) {
    figureArray arr;
    Figure* figure1 = new Triangle({0, 0}, {2, 0}, {0, 3});
    Figure* figure2 = new Square ({0, 0}, {2, 0}, {0, 2}, {2, 2});
    Figure* figure3 = new Rectangle ({0, 0}, {1, 0}, {0, 2}, {1, 2});
    arr.pushBack(figure1);
    arr.pushBack(figure2);
    arr.pushBack(figure3);
    std::stringstream capturedOutput;
    std::streambuf* oldCoutBuffer = std::cout.rdbuf();
    std::cout.rdbuf(capturedOutput.rdbuf());
    arr.findAllAreas();
    std::cout.rdbuf(oldCoutBuffer);
    std::string expectedOutput = "3 4 2 ";

    ASSERT_EQ(capturedOutput.str(), expectedOutput);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
