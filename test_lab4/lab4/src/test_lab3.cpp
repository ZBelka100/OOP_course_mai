#include "../header/figure.h"
#include "../header/array.h"
#include "../header/triangle.h"
#include "../header/rectangle.h"
#include "../header/square.h"
#include <gtest/gtest.h>

bool constructorTest() {
    point<double, double> p1 = {0, 0}, p2 = {1, 0}, p3 = {0, 1}, p4 = {1, 1};
    Figure<double, double> f1;
    Figure<double, double> f2;
    Triangle<double, double> t1(p1, p2, p3);
    Square<double, double> s1(p1, p2, p3, p4);
    Rectangle<double, double> r1(p1, p2, p3, p4);
    
    return (f1 == f2);
}

TEST(test_01, create_test_set) {
    point<double, double> p1 = {0, 0}, p2 = {1, 0}, p3 = {0, 1}, p4 = {0, 1};
    EXPECT_THROW((Square<double, double> (p1, p2, p3, p4)), std::invalid_argument);
}

TEST(test_02, create_test_set) {
    point<int, int> p1 = {0, 0}, p2 = {1, 0}, p3 = {0, 1}, p4 = {1, 2};
    EXPECT_THROW((Square<int, int> (p1, p2, p3, p4)), std::invalid_argument);
}

TEST(test_03, create_test_set) {
    point<float, double> p1 = {0, 0}, p2 = {1, 0}, p3 = {0, 1}, p4 = {0, 1};
    EXPECT_THROW((Square<float, double> (p1, p2, p3, p4)), std::invalid_argument);
}

TEST(test_04, create_test_set) {
    point<double, double> p1 = {0, 0}, p2 = {1, 0}, p3 = {0, 2}, p4 = {1, 2};
    EXPECT_NO_THROW((Rectangle<double, double> (p1, p2, p3, p4)));
}

TEST(test_05, create_test_set) {
    point<double, double> p1 = {0, 0}, p2 = {1, 1000}, p3 = {0, 1}, p4 = {1, 0};
    EXPECT_THROW((Rectangle<double, double> (p1, p2, p3, p4)), std::invalid_argument);
}

TEST(test_06, create_test_set) {
    point<double, double> p1 = {0, 0}, p2 = {0, 0}, p3 = {0, 1};
    EXPECT_THROW((Triangle<double, double> (p1, p2, p3)), std::invalid_argument);
}

TEST(test_07, create_test_set) {
    point<double, double> p1 = {0, 0}, p2 = {1, 0}, p3 = {2, 0};
    EXPECT_NO_THROW((Triangle<double, double> (p1, p2, p3)));
}

TEST(test_08, create_test_set) {
    point<double, double> p1 = {0, 0}, p2 = {1, 1}, p3 = {0, 2}, p4 = {-1, 1};
    EXPECT_NO_THROW((Square<double, double> (p1, p2, p3, p4)));
}

TEST(PointOperatorEqual, SamePointEquality) {
    point<double, double> p1 = {1.0, 2.0};
    point<double, double> p2 = {1.0, 2.0};
    EXPECT_TRUE(p1 == p2);
}

TEST(PointOperatorEqual, DifferentPointsInequality) {
    point<double, double> p1 = {1.0, 2.0};
    point<double, double> p2 = {3.0, 4.0};
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

TEST(Area, Triangle) {
    point<double, double> p1 = {0, 0}, p2 = {-3, 0}, p3 = {0, -3};
    Triangle<double, double> triangle(p1, p2, p3);
    EXPECT_EQ(double(triangle), 4.5);
}

TEST(Area, Rectangle) {
    point<double, double> p1 = {0, 0}, p2 = {-2, 0}, p3 = {0, -3}, p4 = {-2, -3};
    Rectangle<double, double> rectangle(p1, p2, p3, p4);
    EXPECT_EQ(double(rectangle), 6);
}

TEST(Area, Square) {
    point<int, float> p1 = {0, 0}, p2 = {-3, 0}, p3 = {0, -3}, p4 = {-3, -3};
    Square<int, float> square(p1, p2, p3, p4);
    EXPECT_EQ(double(square), 9);
}

TEST(Area2, Triangle) {
    point<int, float> p1 = {0, 0}, p2 = {-3, 0}, p3 = {0, -3};
    Triangle<int, float> triangle(p1, p2, p3);
    EXPECT_EQ(double(triangle), 4.5);
}

TEST(Area2, Rectangle) {
    point<int, float> p1 = {0, 0}, p2 = {-2, 0}, p3 = {0, -3}, p4 = {-2, -3};
    Rectangle<int, float> rectangle(p1, p2, p3, p4);
    EXPECT_EQ(double(rectangle), 6);
}

TEST(Area2, Square) {
    point<int, float> p1 = {0, 0}, p2 = {-3, 0}, p3 = {0, -3}, p4 = {-3, -3};
    Square<int, float> square(p1, p2, p3, p4);
    EXPECT_EQ(double(square), 9);
}

TEST(FigureArray, AddAndRemoveFigures) {
    DynamicArray<std::shared_ptr<Figure<double, double>>> arr;
    std::shared_ptr<Figure<double, double>> figure1 = std::make_shared<Triangle<double, double>>();
    std::shared_ptr<Figure<double, double>> figure2 = std::make_shared<Rectangle<double, double>>();
    std::shared_ptr<Figure<double, double>> figure3 = std::make_shared<Square<double, double>>();
    arr.pushBack(figure1);
    arr.pushBack(figure2);
    arr.pushBack(figure3);
    EXPECT_EQ(arr.getSize(), 3);   
    arr.remove(1);
    EXPECT_EQ(arr.getSize(), 2);
}

TEST(FigureArray, SumAreas) {
    point<double, double> p1 = {0, 0}, p2 = {2, 0}, p3 = {0, 2}, p4 = {2, 2};
    DynamicArray<std::shared_ptr<Figure<double, double>>> arr;
    std::shared_ptr<Figure<double, double>> figure1 = std::make_shared<Triangle<double, double>>(p1, p2, p3);
    std::shared_ptr<Figure<double, double>> figure2 = std::make_shared<Rectangle<double, double>>(p1, p2, p3, p4);
    std::shared_ptr<Figure<double, double>> figure3 = std::make_shared<Square<double, double>>(p1, p2, p3, p4);
    arr.pushBack(figure1);
    arr.pushBack(figure2);
    arr.pushBack(figure3);

    EXPECT_TRUE(findSumAreas(arr) == 10);
}

/* вынесено в main
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
*/
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
