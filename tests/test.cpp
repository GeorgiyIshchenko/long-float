#include <gtest/gtest.h>
#include <LongFloat.h>

using namespace LongNums;


TEST(Operations, Sum) {
    EXPECT_EQ(
            LongFloat("-5.5") + LongFloat("9"), LongFloat("3.5")
    );
}

TEST(Operations, Sub1) {
    EXPECT_EQ(
            LongFloat("-27.5") - LongFloat(
                    "-5.285714285714285714285714285714285714285714285714285714285714285714285714285714285714285714285714286"),
            LongFloat(
                    "-22.214285714285714285714285714285714285714285714285714285714285714285714285714285714285714285714285714")
    );
}

TEST(Operations, Sub2) {
    EXPECT_EQ(
            LongFloat("5") - LongFloat(
                    "-6"),
            LongFloat(
                    "11")
    );
}

TEST(Operations, Sub3) {
    EXPECT_EQ(
            LongFloat("100") - LongFloat(
                    "100"),
            LongFloat(
                    "0")
    );
}

TEST(Operations, Sub4) {
    EXPECT_EQ(
            LongFloat("1") - LongFloat(
                    "50"),
            LongFloat(
                    "-49")
    );
}

TEST(Operations, Inverse1) {
    LongFloat::setPrecision(2);
    EXPECT_EQ(
            LongFloat(4).getReciprocal(), 0.25_LF
    );
    LongFloat::setDefaultPrecision();
}

TEST(Operations, Inverse2) {
    LongFloat::setPrecision(2);
    EXPECT_EQ(
            LongFloat(0.25).getReciprocal(), 4_LF
    );
    LongFloat::setDefaultPrecision();
}

TEST(Operations, Denom) {
    LongFloat::setPrecision(5);
    EXPECT_EQ(
            LongFloat("5"), LongFloat("10") / LongFloat("2")
    );
    LongFloat::setDefaultPrecision();
}

TEST(Operations, Denom2) {
    LongFloat::setPrecision(5);
    EXPECT_EQ(
            LongFloat("3"), LongFloat("120") / LongFloat("40")
    );
    LongFloat::setDefaultPrecision();
}

TEST(Operations, Multiply) {
    EXPECT_EQ(
            LongFloat("14.2") * LongFloat("49"), LongFloat("695.8")
    );
}

TEST(Operations, Equal) {
    EXPECT_TRUE(
            LongFloat("5") == LongFloat("5.000")
    );
}

TEST(Operations, DifSigns) {
    EXPECT_TRUE(
            1_LF != -1_LF
    );
}

TEST(Operations, Bigger) {
    EXPECT_TRUE(
            LongFloat("0.333333333333333333") > LongFloat("0.3")
    );
}

TEST(Operations, BiggerFalse) {
    EXPECT_FALSE(
            LongFloat("-0.3") > LongFloat("0.3")
    );
}

TEST(Operations, Smaller) {
    EXPECT_FALSE(
            LongFloat("0.2") < LongFloat("0.21")
    );
}

TEST(Operations, NineNineMul) {
    EXPECT_EQ(
            9.9_LF * 10_LF, 99_LF
    );
}

TEST(Operations, NineNineDenom) {
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

TEST(Operation, Round1) {
    LongFloat::setPrecision(2);
    EXPECT_EQ((0.555_LF).round(), 0.56_LF);
    LongFloat::setDefaultPrecision();
}

TEST(Operation, Round2) {
    LongFloat::setPrecision(5);
    EXPECT_EQ((0.333334333333999999911112313143542_LF).round(), 0.33333_LF);
    LongFloat::setDefaultPrecision();
}

TEST(Operation, ToString1) {
    EXPECT_EQ((-0.0001_LF).toString(), "-0.0001");
}

TEST(Operation, ToString2) {
    EXPECT_EQ((228.282_LF).toString(), "228.282");
}

TEST(Operation, ToString3) {
    EXPECT_EQ((1000_LF + 200_LF).toString(), "1200");
}


TEST(Operation, ZeroEqual1) {
    EXPECT_TRUE(-0_LF == 0_LF);
}

TEST(Operation, ZeroEqual2) {
    EXPECT_TRUE(LongFloat("-0") == 0_LF);
}

TEST(Operation, ZeroSum) {
    EXPECT_EQ(
            5.1_LF + 0_LF, 5.1_LF
    );
}

TEST(Operation, ZeroMul) {
    EXPECT_EQ(
            5.1_LF * 0_LF, 0_LF
    );
}

TEST(Operation, ZeroDev) {
    EXPECT_ANY_THROW(
            5.1_LF / 0_LF
    );
}

TEST(Operation, Sqrt1) {
    LongFloat::setPrecision(10);
    EXPECT_TRUE((64_LF).sqrt().isEqual(LongFloat(8)));
    LongFloat::setDefaultPrecision();
}

TEST(Operation, Sqrt2) {
    EXPECT_ANY_THROW(
            (-5_LF).sqrt();
    );
}

TEST(Operator, Out) {
    EXPECT_NO_THROW(std::cout << LongFloat("123"));
}
