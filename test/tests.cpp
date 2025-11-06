#include <gtest/gtest.h>
#include "../include/triangle.h"
#include "../include/square.h"
#include "../include/rectangle.h"

// Проверка площади треугольника
TEST(TriangleTest, Area) {
    Triangle<double> t({
        {0.0, 0.0},
        {1.0, 0.0},
        {0.0, 1.0}
    });
    EXPECT_NEAR(t.area(), 0.5, 1e-6);
}

// Проверка площади квадрата
TEST(SquareTest, Area) {
    Square<double> s({
        {0.0, 0.0},
        {0.0, 2.0},
        {2.0, 2.0},
        {2.0, 0.0}
    });
    EXPECT_NEAR(s.area(), 4.0, 1e-6);
}

// Проверка площади прямоугольника
TEST(RectangleTest, Area) {
    Rectangle<double> r({
        {0.0, 0.0},
        {0.0, 3.0},
        {4.0, 3.0},
        {4.0, 0.0}
    });
    EXPECT_NEAR(r.area(), 12.0, 1e-6);
}

// Проверка эквивалентности фигур через базовый класс
TEST(FigureEquality, CompareSameType) {
    Triangle<double> a({
        {0, 0}, {1, 0}, {0, 1}
    });
    Triangle<double> b({
        {0, 0}, {1, 0}, {0, 1}
    });
    Square<double> s1({
        {0, 0}, {0, 1}, {1, 1}, {1, 0}
    });
    Square<double> s2({
        {0, 0}, {0, 1}, {1, 1}, {1, 0}
    });

    // Явно сравниваем как Figure<T> — устраняет предупреждения C++20
    EXPECT_TRUE(static_cast<const Figure<double>&>(a) == b);
    EXPECT_TRUE(static_cast<const Figure<double>&>(s1) == s2);
}

// Проверка неравенства разных типов фигур
TEST(FigureEquality, CompareDifferentTypes) {
    Triangle<double> t({
        {0, 0}, {1, 0}, {0, 1}
    });
    Square<double> s({
        {0, 0}, {0, 1}, {1, 1}, {1, 0}
    });
    EXPECT_FALSE(static_cast<const Figure<double>&>(t) == s);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
