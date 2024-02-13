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

TEST(Operations, Inverse) {
    LongFloat::setPrecision(2);
    EXPECT_EQ(
            1_LF * LongFloat(4).getReciprocal(), 0.25_LF
    );
    LongFloat::setDefaultPrecision();
}

TEST(Operations, Denom) {
    LongFloat::setPrecision(5);
    EXPECT_EQ(
            LongFloat("5"),LongFloat("10") / LongFloat("2")
    );
    LongFloat::setDefaultPrecision();
}

TEST(Operations, Denom2) {
    LongFloat::setPrecision(5);
    EXPECT_EQ(
            LongFloat("3"),LongFloat("120") / LongFloat("40")
    );
    LongFloat::setDefaultPrecision();
}

TEST(Operations, Multiply) {
    EXPECT_EQ(
            LongFloat("14.2") * LongFloat("49"), LongFloat("695.8")
    );
}

TEST(Operations, Equal) {
    EXPECT_EQ(
            LongFloat("5") == LongFloat("5.000"), true
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
            LongFloat("-0.3") > LongFloat("0.3"), false
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

TEST(Operation, ToString) {
    EXPECT_EQ((-0.0001_LF).toString(), "-0.0001");
}

TEST(Operation, ZeroEqual1){
    EXPECT_EQ(-0_LF == 0_LF, true);
}

TEST(Operation, ZeroEqual2){
    EXPECT_EQ(LongFloat("-0") == 0_LF, true);
}

TEST(Operation, ZeroSum){
    EXPECT_EQ(
            5.1_LF + 0_LF, 5.1_LF
    );
}

TEST(Operation, ZeroMul){
    EXPECT_EQ(
            5.1_LF * 0_LF, 0_LF
    );
}

TEST(Operation, ZeroDev){
    EXPECT_ANY_THROW(
            5.1_LF / 0_LF
    );
}

TEST(Operation, Sqrt) {
    LongFloat::setPrecision(10);
    EXPECT_EQ((64_LF).sqrt().isEqual(LongFloat(8)), true);
    LongFloat::setDefaultPrecision();
}
