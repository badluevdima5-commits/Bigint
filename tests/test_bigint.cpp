#include "../include/BigInt.h"
#include <gtest/gtest.h>


TEST(BigintTest, IntConstructor) {
    Bigint num(12345);
    EXPECT_EQ(num, 12345);
}

TEST(BigintTest, StringConstructor) {
    Bigint num("67890");
    EXPECT_EQ(num, 67890);
}

TEST(BigintTest, Addition) {
    Bigint a(100);
    Bigint b(50);
    EXPECT_EQ(a + b, 150);
}

TEST(BigintTest, Subtraction) {
    Bigint a(100);
    Bigint b(30);
    EXPECT_EQ(a - b, 70);
}

TEST(BigintTest, Multiplication) {
    Bigint a(12);
    Bigint b(5);
    EXPECT_EQ(a * b, 60);
}

TEST(BigintTest, Division) {
    Bigint a(100);
    Bigint b(4);
    EXPECT_EQ(a / b, 25);
}

TEST(BigintTest, Comparison) {
    Bigint a(100);
    Bigint b(50);
    EXPECT_TRUE(a > b);
    EXPECT_TRUE(b < a);
}

TEST(BigintTest, UnaryMinus) {
    Bigint a(123);
    EXPECT_EQ(-a, -123);
}

TEST(BigintTest, CompoundAddition) {
    Bigint a(100);
    a += 50;
    EXPECT_EQ(a, 150);
}

TEST(BigintTest, NegativeNumbers) {
    Bigint a(-100);
    Bigint b(50);
    EXPECT_EQ(a + b, -50);
    EXPECT_EQ(a - b, -150);
}


TEST(BigintTest, BigintTest_Comparison1_Test) {
    Bigint a(100);
    Bigint b("-0");
    EXPECT_EQ(a + b, Bigint(100));
}
