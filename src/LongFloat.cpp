#include <LongFloat.h>

namespace LongNums {

    int LongFloat::precision{1000};
    int LongFloat::base{10};

    LongFloat::LongFloat() {
        sign = 1;
        nums = std::vector<numType>(1, 0);
        exponent = 1;
    }

    LongFloat::LongFloat(LongFloat const &lf) {
        sign = lf.sign;
        exponent = lf.exponent;
        nums = std::vector<numType>(lf.nums);
    }

    LongFloat::LongFloat(const std::string &value) {
        size_t length = value.length();
        int index = 0;

        if (length && value[0] == '-') {
            sign = -1;
            index = 1;
        } else {
            sign = 1;
        }

        // If numeric
        exponent = (long long) length - index;

        while (index < length) {
            if (value[index] != '.') {
                nums.push_back(_charToInt(value[index]));
            } else {
                if (sign == 1)
                    exponent = index;
                else
                    exponent = index - 1;
            }
            index++;
        }

        this->_deleteZeros();
    }

    LongFloat::numType LongFloat::_charToInt(const char charValue) {
        return charValue - '0';
    }

    char LongFloat::_intToChar(const numType value) {
        return (char) (value + '0');
    }

    void LongFloat::_deleteZeros() {

        while (nums.size() > std::max(1ll, exponent) &&
               !nums.back()) {
            nums.pop_back();
        }

        while (!nums.empty() && !nums.front()) {
            nums.erase(nums.begin());
            exponent--;
        }

    }


    std::ostream &operator<<(std::ostream &os, const LongFloat &lf) {
        os << lf.toString();
        return os;
    }

    LongFloat operator*(const LongFloat &lf1, const LongFloat &lf2) {
        size_t len = lf1.nums.size() + lf2.nums.size();

        LongFloat res;

        res.sign = lf1.sign * lf2.sign;
        res.nums = std::vector<LongFloat::numType>(len, 0);
        res.exponent = lf1.exponent + lf2.exponent;

        for (int i = 0; i < lf1.nums.size(); i++)
            for (int j = 0; j < lf2.nums.size(); j++)
                res.nums[i + j + 1] += lf1.nums[i] * lf2.nums[j];

        for (size_t i = len - 1; i > 0; i--) {
            res.nums[i - 1] += res.nums[i] / LongFloat::base;
            res.nums[i] %= LongFloat::base;
        }

        res._deleteZeros();

        return res;
    }

    LongFloat LongFloat::operator-() const {
        if (*this == 0_LF)
            return *this;
        LongFloat result;
        result.sign = -1 * sign;
        result.exponent = exponent;
        result.nums = std::vector<numType>(nums);
        return result;
    }

    LongFloat operator+(const LongFloat &lf1, const LongFloat &lf2) {
        if (lf1.sign == lf2.sign) {
            long long exp1 = lf1.exponent;
            long long exp2 = lf2.exponent;
            int maxExp = MAX(exp1, exp2);

            std::vector<LongFloat::numType> nums1(lf1.nums);
            std::vector<LongFloat::numType> nums2(lf2.nums);

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
            result.nums = std::vector<LongFloat::numType>(len, 0);

            for (size_t iter = 0; iter < maxNumSize; iter++)
                result.nums[iter + 1] = nums1[iter] + nums2[iter];

            for (size_t iter = len - 1; iter > 0; iter--) {
                result.nums[iter - 1] += result.nums[iter] / LongFloat::base;
                result.nums[iter] %= LongFloat::base;
            }
            result.exponent = maxExp + 1;
            result._deleteZeros();
            return result;
        }
        if (lf1.sign == -1)
            return lf2 - (-lf1);
        return lf1 - (-lf2);
    }

    LongFloat operator-(const LongFloat &lf1, const LongFloat &lf2) {
        if (lf1.sign == 1 && lf2.sign == 1) {
            bool aBiggerB = lf1 > lf2;
            long long exp1 = aBiggerB ? lf1.exponent : lf2.exponent;
            long long exp2 = aBiggerB ? lf2.exponent : lf1.exponent;
            int maxExp = MAX(exp1, exp2);

            std::vector<LongFloat::numType> nums1(aBiggerB ? lf1.nums : lf2.nums);
            std::vector<LongFloat::numType> nums2(aBiggerB ? lf2.nums : lf1.nums);

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
            result.nums = std::vector<LongFloat::numType>(len, 0);

            for (size_t iter = 0; iter < maxNumSize; iter++)
                result.nums[iter + 1] = nums1[iter] - nums2[iter];

            for (size_t iter = len - 1; iter > 0; iter--) {
                if (result.nums[iter] < 0) {
                    result.nums[iter] += 10;
                    result.nums[iter - 1] -= 1;
                }
            }

            result.exponent = maxExp + 1;
            result._deleteZeros();

            return result;
        }
        if (lf1.sign == -1 && lf2.sign == -1)
            return (-lf2) - (-lf1);
        return lf1 + (-lf2);
    }

    LongFloat LongFloat::getReciprocal() {
        if (nums.size() == 1 && nums[0] == 0 || (nums.empty() && exponent == 0))
            throw std::invalid_argument("Division by zero!");

        LongFloat copy(*this);
        copy.sign = 1;
        LongFloat one(1);

        LongFloat result;
        result.sign = sign;
        result.exponent = 1;
        result.nums = std::vector<numType>();

        while (copy < 1) {
            copy.exponent++;
            result.exponent++;
        }

        while (one < copy) {
            one.exponent++;
        }

        result.exponent -= one.exponent - 1;

        size_t numSize = 0;
        size_t totalPrecision = (precision + 2) + MAX(0, result.exponent);

        do {
            numType div = 0;
            while (one >= copy) {
                div++;
                one = (one - copy);
            }
            one.exponent++;
            one._deleteZeros();
            result.nums.push_back(div);
            numSize++;
        } while (one != LongFloat() && numSize < totalPrecision);
        return result;
    }

    bool operator>(const LongFloat &lf1, const LongFloat &lf2) {
        if (lf1.sign != lf2.sign)
            return lf1.sign > lf2.sign;
        if (lf1.exponent != lf2.exponent)
            return (lf1.exponent > lf2.exponent) ^ (lf1.sign == -1);

        std::vector<LongFloat::numType> nums1(lf1.nums);
        std::vector<LongFloat::numType> nums2(lf2.nums);
        size_t maxNumSize = MAX(nums1.size(), nums2.size());

        while (nums1.size() != maxNumSize)
            nums1.push_back(0);

        while (nums2.size() != maxNumSize)
            nums2.push_back(0);

        for (size_t iter = 0; iter < maxNumSize; iter++) {
            if (nums1[iter] != nums2[iter]) {
                return (nums1[iter] > nums2[iter]) ^ (lf1.sign == -1);
            }
        }
        return false;
    }

    bool operator==(const LongFloat &lf1, const LongFloat &lf2) {
        if (lf1.nums.size() == lf2.nums.size() && lf1.nums.empty() && lf1.exponent == 0)
            return true;

        if (lf1.sign != lf2.sign || lf1.exponent != lf2.exponent)
            return false;

        LongFloat lf1Copy{lf1};
        LongFloat lf2Copy{lf2};
        while (lf1Copy.nums.size() > lf2Copy.nums.size()) {
            lf2Copy.nums.push_back(0);
        }

        while (lf1Copy.nums.size() < lf2Copy.nums.size()) {
            lf1Copy.nums.push_back(0);
        }

        for (int i = 0; i < std::min(LongFloat::getPrecision() + lf1.exponent, (long long) lf1.nums.size()); i++) {
            if (lf1Copy.nums[i] != lf2Copy.nums[i]) {
                return false;
            }
        }
        return true;
    }

    int operator<=>(const LongFloat &lf1, const LongFloat &lf2) {
        if (lf1 == lf2)
            return 0;
        if (lf1 > lf2)
            return 1;
        return -1;
    }

    LongFloat &LongFloat::operator=(const LongFloat &other) {
        if (&other != this) {
            sign = other.sign;
            exponent = other.exponent;
            nums = std::vector<numType>(other.nums);
        }
        return *this;
    }

    LongFloat operator/(const LongFloat &lf1, const LongFloat &lf2) {

        LongFloat lf2_inverse = LongFloat(lf2).getReciprocal();
        LongFloat result = lf1 * lf2_inverse;

        auto leaveDigits{(result.exponent > 0 ? result.exponent : 0) +
                         LongFloat::precision + 1};
        result.nums.resize(std::min(
                static_cast<int64_t>(result.nums.size()), leaveDigits));
        result._deleteZeros();
        return result;
    }

    std::string LongFloat::toString() const {
        LongFloat rounded = this->round();
        rounded._deleteZeros();

        std::string result;

        if (rounded.sign == -1)
            result += '-';

        if (rounded.exponent > 0) {
            int iter = 0;

            while (iter < rounded.nums.size() && iter < rounded.exponent)
                result += _intToChar(rounded.nums[iter++]);

            if (iter < rounded.nums.size()) {
                result += ".";
                while (iter < rounded.nums.size() && iter < precision + rounded.exponent)
                    result += _intToChar(rounded.nums[iter++]);
            }
        } else {
            result += "0.";
            for (int i = 0; i < -rounded.exponent; i++)
                result += "0";
            for (int i = 0; i < MIN(precision + rounded.exponent, nums.size()); i++)
                result += _intToChar(rounded.nums[i]);
        }
        return result;
    }

    LongFloat operator ""_LF(const char *str) {
        return LongFloat(std::string(str));
    }

    int LongFloat::getPrecision() {
        return LongFloat::precision;
    }

    void LongFloat::setPrecision(int value) {
        if (value > 0)
            precision = value;
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
            result._deleteZeros();
            return result;
        }
        throw std::invalid_argument("Negative num in sqrt");
    }

    LongFloat LongFloat::round() const {
        LongFloat result{*this};
        long long lastNumIdx{(result.exponent - 1) + precision};
        if (!result.nums.empty() && lastNumIdx >= 0 && lastNumIdx < result.nums.size() - 1) {
            numType afterLast = result.nums[lastNumIdx + 1];
            if (afterLast >= 5)
                result = result + LongFloat("0." + std::string(precision - 1, '0') + "1");
            result.nums.erase(result.nums.begin() + lastNumIdx + 1, result.nums.end());
        }
        result._deleteZeros();
        return result;
    }

    void LongFloat::setDefaultPrecision() {
        precision = 1000;
    }

    bool LongFloat::isEqual(const LongFloat &other) {
        return this->toString() == other.toString();
    }

}


