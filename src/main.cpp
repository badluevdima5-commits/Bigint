#include "../include/Bigint.h"
#include <iostream>

int main() {
    Bigint a("-0");
    Bigint b("2");
    std::cout << a << std::endl;
    return 0;
}