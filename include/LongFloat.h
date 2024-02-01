#ifndef LONGFLOAT_H
#define LONGFLOAT_H

#include <cmath>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

namespace LongNums {
    class LongFloat {

    private:
        /// TODO: comment bellow
        /// In present i will modify it to bigger notation
        const int base = 10;

        /// Max amount of nums after dot
        const int precision = 1000;

        /// Translate char to int
        static inline int charToInt(char charValue);

        /// Translate int to chat
        static inline char intToChar(int intValue);

    public:


        /// Sign of number
        char sign;
        /// Abs of num as a vector of decimals
        std::vector<int> nums;
        /// Amount of nums after dot
        int exponent;

        /// Empty constructor
        LongFloat();
        /// String constructor
        explicit LongFloat(const std::string& value);
        /// Delete zeros from the beginning and the end of LongFloat
        void deleteZeros();

        /// @return 1 / LongFloat
        LongFloat getReciprocal();
        /// Cast LongFloat to std::string
        std::string toString() const;
        // Basic operators to work with nums

        LongFloat& operator=(const LongFloat& other);

        LongFloat operator-() const;
        friend std::ostream& operator<<(std::ostream& os, const LongFloat& lf);
        friend bool operator>(const LongFloat& lf1, const LongFloat& lf2);
        friend bool operator==(const LongFloat& lf1, const LongFloat& lf2);
        friend std::strong_ordering operator<=>(const LongFloat& lf1, const LongFloat& lf2);
        friend LongFloat operator-(const LongFloat& lf1, const LongFloat& lf2);
        friend LongFloat operator+(const LongFloat& lf1, const LongFloat& lf2);
        friend LongFloat operator*(const LongFloat& lf1, const LongFloat& lf2);
        friend LongFloat operator/(const LongFloat& lf1, const LongFloat& lf2);
    };

    /// My Literal
    LongFloat operator ""_LF(const char* str);
}


#endif
