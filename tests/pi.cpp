#include <iostream>
#include <chrono>
#include <string>

#include <LongFloat.h>


namespace LongNums {

    LongFloat calculatePi(int precision) {
        LongFloat result{};
        LongFloat buffer{};

        int k = 0;
        LongFloat sixteenPower{1};
        LongFloat inverseSixteen = LongFloat((1.0/16));
        while (-buffer.getExponent() < precision + 1) {
            buffer = sixteenPower *
                     (LongFloat((8 * k + 1) / 4.0).getReciprocal() - LongFloat((8 * k + 4) / 2.0).getReciprocal() - LongFloat(8 * k + 5).getReciprocal() - LongFloat(8 * k + 6).getReciprocal());
            result = result + buffer;
            k++;
            sixteenPower = sixteenPower * inverseSixteen;
        }

        result.setPrecision(precision + 1);

        return result;
    }

}

using namespace LongNums;

int main(int argc, char *argv[]) {

    int current_precision = 100;

    auto start{std::chrono::high_resolution_clock::now()};

    LongFloat pi = calculatePi(current_precision);

    auto finish{std::chrono::high_resolution_clock::now()};

    auto delta{std::chrono::duration_cast<std::chrono::milliseconds>(
            finish - start)};

    std::cout << pi << std::endl;
    std::cout << delta << std::endl;

    return 0;
}