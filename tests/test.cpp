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
    EXPECT_EQ(
            LongFloat("1") / LongFloat("-3"),
            LongFloat(
                    "-0.3333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333")
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
            LongFloat("0.2") < LongFloat("0.20000000000000000000000000000000000000000000000000000000001"), true
    );
}