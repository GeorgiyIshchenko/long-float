#include <LongFloat.h>

namespace LongNums {

    int LongFloat::precision{ 100 };
    int LongFloat::base{ 10 };

    LongFloat::LongFloat() {
        sign = 1;
        nums = std::vector<int>(1, 0);
        exponent = 1;
    }

    LongFloat::LongFloat(LongFloat const &lf) {
        sign = lf.sign;
        exponent = lf.exponent;
        nums = std::vector<int>(lf.nums);
    }

    LongFloat::LongFloat(const std::string &value) {
        int length = value.length();
        int index = 0;

        if (length && value[0] == '-') {
            sign = -1;
            index = 1;
        } else {
            sign = 1;
        }

        // If numeric
        exponent = length - index;

        while (index < length) {
            if (value[index] != '.') {
                nums.push_back(charToInt(value[index]));
            } else {
                if (sign == 1)
                    exponent = index;
                else
                    exponent = index - 1;
            }
            index++;
        }

    }

    int LongFloat::charToInt(const char charValue) {
        return charValue - '0';
    }

    char LongFloat::intToChar(const int intValue) {
        return intValue + '0';
    }

    void LongFloat::deleteZeros() {
        size_t len = MAX(1, exponent);

        while (len < nums.size() && nums[nums.size() - 1] == 0)
            nums.erase(nums.end() - 1);

        while (nums.size() > 1 && nums[0] == 0) {
            exponent--;
            nums.erase(nums.begin());
        }

        while (nums.size() > 1 && nums[nums.size() - 1] == 0)
            nums.erase(nums.end() - 1);

        // If got zero as a result turn it to a real zero

        if (nums.size() == 1 && nums[0] == 0) {
            sign = 1;
            exponent = 1;
        }

    }


    std::ostream &operator<<(std::ostream &os, const LongFloat &lf) {
        os << lf.toString();
        return os;
    }

    LongFloat operator*(const LongFloat &lf1, const LongFloat &lf2) {
        int len = lf1.nums.size() + lf2.nums.size();

        LongFloat res;

        res.sign = lf1.sign * lf2.sign;
        res.nums = std::vector<int>(len, 0);
        res.exponent = lf1.exponent + lf2.exponent;

        for (int i = 0; i < lf1.nums.size(); i++)
            for (int j = 0; j < lf2.nums.size(); j++)
                res.nums[i + j + 1] += lf1.nums[i] * lf2.nums[j];

        for (int i = len - 1; i > 0; i--) {
            res.nums[i - 1] += res.nums[i] / LongFloat::base;
            res.nums[i] %= LongFloat::base;
        }

        res.deleteZeros();

        return res;
    }

    LongFloat LongFloat::operator-() const {
        LongFloat result;
        result.sign = -1 * sign;
        result.exponent = exponent;
        result.nums = std::vector<int>(nums);
        return result;
    }

    bool operator>(const LongFloat &lf1, const LongFloat &lf2) {
        if (lf1.sign != lf2.sign)
            return lf1.sign > lf2.sign;
        if (lf1.exponent != lf2.exponent)
            return (lf1.exponent > lf2.exponent) ^ (lf1.sign == -1);

        size_t minNumSize = MIN(lf1.nums.size(), lf2.nums.size());

        for (size_t iter = 0; iter < minNumSize; iter++) {
            if (lf1.nums[iter] != lf2.nums[iter]) {
                return (lf1.nums[iter] > lf2.nums[iter]) * (lf1.sign == 1);
            }
        }
        return lf1.nums.size() > lf2.nums.size();
    }

    LongFloat operator+(const LongFloat &lf1, const LongFloat &lf2) {
        if (lf1.sign == lf2.sign) {
            int exp1 = lf1.exponent;
            int exp2 = lf2.exponent;
            int maxExp = MAX(exp1, exp2);

            std::vector<int> nums1(lf1.nums);
            std::vector<int> nums2(lf2.nums);

            while (exp1 != maxExp) {
                nums1.insert(nums1.begin(), 0);
                exp1++;
            }

            while (exp2 != maxExp) {
                nums2.insert(nums2.begin(), 0);
                exp2++;
            }

            size_t maxNumSize = MAX(nums1.size(), nums2.size());

            while (nums1.size() != maxNumSize)
                nums1.push_back(0);

            while (nums2.size() != maxNumSize)
                nums2.push_back(0);

            size_t len = maxNumSize + 1;

            LongFloat result;
            result.sign = lf1.sign;
            result.nums = std::vector(len, 0);

            for (size_t iter = 0; iter < maxNumSize; iter++)
                result.nums[iter + 1] = nums1[iter] + nums2[iter];

            for (size_t iter = len - 1; iter > 0; iter--) {
                result.nums[iter - 1] += result.nums[iter] / LongFloat::base;
                result.nums[iter] %= LongFloat::base;
            }
            result.exponent = maxExp + 1;
            result.deleteZeros();
            return result;
        }
        if (lf1.sign == -1)
            return lf2 - (-lf1);
        return lf1 - (-lf2);
    }

    LongFloat operator-(const LongFloat &lf1, const LongFloat &lf2) {
        if (lf1.sign == 1 && lf2.sign == 1) {
            bool aBiggerB = lf1 > lf2;
            int exp1 = aBiggerB ? lf1.exponent : lf2.exponent;
            int exp2 = aBiggerB ? lf2.exponent : lf1.exponent;
            int maxExp = MAX(exp1, exp2);

            std::vector<int> nums1(aBiggerB ? lf1.nums : lf2.nums);
            std::vector<int> nums2(aBiggerB ? lf2.nums : lf1.nums);

            while (exp1 != maxExp) {
                nums1.insert(nums1.begin(), 0);
                exp1++;
            }

            while (exp2 != maxExp) {
                nums2.insert(nums2.begin(), 0);
                exp2++;
            }

            size_t maxNumSize = MAX(nums1.size(), nums2.size());

            while (nums1.size() != maxNumSize)
                nums1.push_back(0);

            while (nums2.size() != maxNumSize)
                nums2.push_back(0);

            size_t len = 1 + maxNumSize;
            LongFloat result;
            result.sign = aBiggerB ? 1 : -1;
            result.nums = std::vector(len, 0);

            for (size_t iter = 0; iter < maxNumSize; iter++)
                result.nums[iter + 1] = nums1[iter] - nums2[iter];

            for (size_t iter = len - 1; iter > 0; iter--) {
                if (result.nums[iter] < 0) {
                    result.nums[iter] += 10;
                    result.nums[iter - 1] -= 1;
                }
            }

            result.exponent = maxExp + 1;
            result.deleteZeros();

            return result;
        }
        if (lf1.sign == -1 && lf2.sign == -1)
            return (-lf2) - (-lf1);
        return lf1 + (-lf2);
    }

    LongFloat LongFloat::getReciprocal() {

        if (nums.size() == 1 && nums[0] == 0)
            throw std::string("Division by zero!");

        LongFloat copy(*this);
        copy.sign = 1;
        LongFloat one("1");

        LongFloat result;
        result.sign = sign;
        result.exponent = 1;
        result.nums = std::vector<int>();

        while (one > copy) {
            copy.exponent++;
            result.exponent++;
        }

        while (one < copy) {
            one.exponent++;
        }

        result.exponent -= one.exponent - 1;

        size_t numSize = 0;
        size_t totalPrecision = LongFloat::precision + MAX(0, result.exponent);

        do {
            int div = 0;
            while (one >= copy) {
                div++;
                one = (one - copy);
            }
            one.exponent++;
            one.deleteZeros();
            result.nums.push_back(div);
            numSize++;
        } while (one != LongFloat() && numSize < totalPrecision);
        return result;
    }

    bool operator==(const LongFloat &lf1, const LongFloat &lf2) {
        if (lf1.exponent != lf2.exponent)
            return false;
        if (lf1.nums.size() != lf2.nums.size())
            return false;
        for (size_t i = 0; i < lf1.nums.size(); i++)
            if (lf1.nums[i] != lf2.nums[i])
                return false;
        return true;
    }

    std::strong_ordering operator<=>(const LongFloat &lf1, const LongFloat &lf2) {
        if (lf2 > lf1)
            return std::strong_ordering::less;
        if (lf1 == lf2)
            return std::strong_ordering::equal;
        return std::strong_ordering::greater;
    }

    LongFloat &LongFloat::operator=(const LongFloat &other) {
        if (&other != this) {
            sign = other.sign;
            exponent = other.exponent;
            nums = std::vector<int>(other.nums);
        }
        return *this;
    }

    LongFloat operator/(const LongFloat &lf1, const LongFloat &lf2) {
        LongFloat lf2_inverse = LongFloat(lf2).getReciprocal();
        LongFloat result = lf1 * lf2_inverse;

        size_t iter = result.nums.size() - 1 - MAX(0, lf1.exponent);
        size_t n = MAX(0, result.exponent);

        if (iter > n && result.nums[iter] == 9) {
            while (iter > n && result.nums[iter] == 9) {
                iter--;
            }
            if (result.nums[iter] == 9) {
                result.nums.erase(result.nums.begin() + n, result.nums.end());
                result = result + LongFloat(std::to_string(result.sign));
            } else {
                result.nums.erase(result.nums.begin() + iter + 1, result.nums.end());
                result.nums[iter]++;
            }
        }
        return result;
    }

    std::string LongFloat::toString() const {
        std::string result;

        if (sign == -1)
            result += '-';

        if (exponent > 0) {
            int iter = 0;

            while (iter < nums.size() && iter < exponent)
                result += intToChar(nums[iter++]);

            while (iter < exponent) {
                result += "0";
                iter++;
            }

            if (iter < nums.size()) {
                result += ".";
                while (iter < nums.size()  && iter < precision + 1)
                    result += intToChar(nums[iter++]);
            }
        } else {
            result += "0.";
            for (int i = 0; i < -exponent; i++)
                result += "0";
            for (int i: nums)
                result += intToChar(i);
        }
        return result;
    }

    LongFloat operator ""_LF(const char *str) {
        return LongFloat(std::string(str));
    }

    int LongFloat::getPrecision(){
        return LongFloat::precision;
    }

    void LongFloat::setPrecision(int value) {
        if (value > 0)
            precision = value;
    }

    int LongFloat::getExponent() const {
        return exponent;
    }

    void LongFloat::setExponent(int value) {
        exponent = value;
    }

    LongFloat LongFloat::sqrt() {
        if (sign == 1) {
            LongFloat L{};
            LongFloat R = LongFloat(*this);
            LongFloat result;
            for (int i = 0; i < 5 * precision; i++) {
                result = (L + R) / 2_LF;
                if (result * result < *this)
                    L = result;
                else
                    R = result;
            }
            return result;
        }
        return NAN;
    }

}


