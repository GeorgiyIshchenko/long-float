#include <iostream>
#include <chrono>
#include <string>
#include <tuple>

#include <LongFloat.h>


namespace LongNums {

    std::tuple<LongFloat, LongFloat, LongFloat> binarySplit(long long a, long long b) {
        LongFloat Pab, Qab, Rab;
        if (a + 1 == b) {
            Pab = -(6_LF * a - 5) * (2_LF * a - 1) * (6_LF * a - 1);
            Qab = 10939058860032000_LF * a * a * a;
            Rab = Pab * (545140134_LF * a + 13591409_LF);
        } else {
            long long m = (a + b) / 2;
            auto [Pam, Qam, Ram] = binarySplit(a, m);
            auto [Pmb, Qmb, Rmb] = binarySplit(m, b);

            Pab = Pam * Pmb;
            Qab = Qam * Qmb;
            Rab = Qmb * Ram + Pam * Rmb;
        }
        return std::make_tuple(Pab, Qab, Rab);
    }

    LongFloat chudnovsky(long long n) {
        auto [P1n, Q1n, R1n] = binarySplit(1, n);
        return LongFloat(CHUDOVSKY_KOEF) * Q1n / (13591409_LF * Q1n + R1n);
    }

}

using namespace LongNums;

int main(int argc, char *argv[]) {
    if (argc >= 2) {
        LongFloat::setPrecision(atoi(argv[1]));
    }
    else
    {
        LongFloat::setPrecision(100);
    }

    auto start{std::chrono::high_resolution_clock::now()};

    LongFloat pi = chudnovsky(std::max(100ll, LongFloat::getPrecision() / 5ll));

    auto finish{std::chrono::high_resolution_clock::now()};

    auto delta{std::chrono::duration_cast<std::chrono::milliseconds>(
            finish - start)};

    std::cout << "Pi: " << pi << std::endl;
    std::cout << "Time spent: " << delta << std::endl;

    int cnt = 0;
    auto TruePi = std::string(PI_STR);
    auto ResultPiAsString = pi.toString();
    for(int i = 0; i < LongFloat::getPrecision() + 2; i++)
    {
        if (TruePi[i] == ResultPiAsString[i])
            cnt++;
        else
            break;
    }

    std::cout << "Total nums match: " << cnt << std::endl;

    return 0;
}