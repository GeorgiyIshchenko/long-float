#ifndef LONGFLOAT_H
#define LONGFLOAT_H

#include <cmath>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cstdint>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

namespace LongNums {
    class LongFloat {

        using numType = int64_t;

    private:
        /// TODO: comment bellow
        /// In present i will modify it to bigger notation
        static int base;
        /// Max amount of nums after dot
        static int precision;

        /// Translate char to int
        static inline numType _charToInt(char charValue);

        /// Translate int to chat
        static inline char _intToChar(numType value);

        /// Sign of number
        int sign;
        /// Abs of num as a vector of decimals
        std::vector<numType> nums;
        /// Amount of nums after dot
        int64_t exponent;

        /// Delete zeros from the beginning and the end of LongFloat
        void _deleteZeros();

    public:
        /// Empty constructor
        LongFloat();

        /// Copy constructor
        LongFloat(LongFloat const &lf);

        /// String constructor
        explicit LongFloat(const std::string &value);

        /// Base nums constructors
        LongFloat(int num) : LongFloat(std::to_string(num)) {}

        LongFloat(long long num) : LongFloat(std::to_string(num)) {}

        LongFloat(double num) : LongFloat(std::to_string(num)) {}

        /// @return 1 / LongFloat
        LongFloat getReciprocal();

        /// Use to change the precision of specific object
        LongFloat round() const;

        /// Cast LongFloat to std::string
        std::string toString() const;

        // Basic operators to work with nums

        LongFloat &operator=(const LongFloat &other);


        LongFloat operator-() const;

        friend std::ostream &operator<<(std::ostream &os, const LongFloat &lf);

        friend bool operator>(const LongFloat &lf1, const LongFloat &lf2);

        friend int operator<=>(const LongFloat &lf1, const LongFloat &lf2);
        friend bool operator==(const LongFloat &lf1, const LongFloat &lf2);

        /// equal with precision
        bool isEqual(const LongFloat& other);

        friend LongFloat operator-(const LongFloat &lf1, const LongFloat &lf2);

        friend LongFloat operator+(const LongFloat &lf1, const LongFloat &lf2);

        friend LongFloat operator*(const LongFloat &lf1, const LongFloat &lf2);

        friend LongFloat operator/(const LongFloat &lf1, const LongFloat &lf2);

        friend LongFloat operator ""_LF(const char *str);

        LongFloat sqrt();

        // Getters and Setters

        static int getPrecision();

        static void setPrecision(int precision);

        static void setDefaultPrecision();
    };

    /// My Literal
    LongFloat operator ""_LF(const char *str);
}


#endif
