#include <iostream>

#include "include/LongFloat.h"

using namespace LongNums;

int main() {
    LongFloat a("1.15");
    LongFloat b("2.3");
    LongFloat c("1.1111");
    std::cout << -a << std::endl;
    std::cout << a * b << std::endl;
    std::cout << a + b << std::endl;
    std::cout << a - b << std::endl;
    std::cout << b - a << std::endl;
    std::cout << b / a << std::endl;
    std::cout << b / c << std::endl;
    std::cout << "123"_LF / "345"_LF << std::endl;
    return 0;
}
