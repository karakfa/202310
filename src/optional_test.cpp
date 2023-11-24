#include <iostream>
#include <optional>


std::optional<int> coalesce(std::optional<int> a, std::optional<int> b) {

    return a ?: b;    // elvis operator..

}

int main() {

    std::optional<int> a = {};
    std::optional<int> b = 10;

    std::cout << coalesce(a,b).value() << "\n";

    return 0;

}