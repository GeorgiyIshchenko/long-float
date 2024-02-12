#include <gtest/gtest.h>
#include <LongFloat.h>

using namespace LongNums;


TEST(Operations, Sum) {
    EXPECT_EQ(
            LongFloat("-5.5") + LongFloat("9"), LongFloat("3.5")
    );
}

TEST(Operations, Sub) {
    EXPECT_EQ(
            LongFloat("-27.5") - LongFloat(
                    "-5.285714285714285714285714285714285714285714285714285714285714285714285714285714285714285714285714286"),
            LongFloat(
                    "-22.214285714285714285714285714285714285714285714285714285714285714285714285714285714285714285714285714")
    );
}

TEST(Operations, Denom) {
    LongFloat::setPrecision(5);
    EXPECT_EQ(
            (LongFloat("1") / LongFloat("-3")),
            LongFloat("-0.33333")
    );
}

TEST(Operations, Multiply) {
    EXPECT_EQ(
            LongFloat("14.2") * LongFloat("49"), LongFloat("695.8")
    );
}

TEST(Operations, Equal) {
    EXPECT_EQ(
            LongFloat("5") == LongFloat("10") / LongFloat("2"), true
    );
}

TEST(Operations, DifSigns) {
    EXPECT_EQ(
            1_LF != -1_LF, true
    );
}

TEST(Operations, Bigger) {
    EXPECT_EQ(
            LongFloat("0.333333333333333333") > LongFloat("0.3"), true
    );
}

TEST(Operations, BiggerFalse) {
    EXPECT_EQ(
            LongFloat("0.3") > LongFloat("0.3"), false
    );
}

TEST(Operations, Smaller) {
    EXPECT_EQ(
            LongFloat("0.2") < LongFloat("0.21"), false
    );
}

TEST(Operations, NineNineMul) {
    EXPECT_EQ(
            9.9_LF * 10_LF, 99_LF
    );
}

TEST(Operations, NineNineDenom) {
    LongFloat::setPrecision(2);
    EXPECT_EQ(
            9.9_LF / 10_LF, 0.99_LF
    );
}

TEST(Operations, NineNineSum) {
    EXPECT_EQ(
            99.99_LF + 0.01_LF, 100_LF
    );
}

TEST(Operations, NineNineSub) {
    EXPECT_EQ(
            100_LF - 0.01_LF, 99.99_LF
    );
}
