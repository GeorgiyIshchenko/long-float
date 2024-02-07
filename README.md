# LongFloat

LongFloat is a C++ library for dealing with arbitrary-precision float arithmetic.

## Installation

Use Git to install LongFloat.

```bash
git clone 'https://github.com/GeorgiyIshchenko/LongFloat'
```

## Usage

```c++
#include <iostream>

#include <LongFloat.h>

using namespace LongNums;

int main() {
    LongFloat a("1.15");
    LongFloat b("2.3");
    std::cout << -a << std::endl;
    std::cout << a * b << std::endl;
    std::cout << a + b << std::endl;
    std::cout << a - b << std::endl;
    std::cout << b / a << std::endl;
    std::cout << "123"_LF / "345"_LF << std::endl;
    return 0;
}
```

## Contributing

Pull requests are welcome. For major changes, please open an issue first
to discuss what you would like to change.
