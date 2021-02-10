#include <iostream>
#include <vector>
#include "../src/string.h"
#include "../src/vector.h"
#include "../src/collection.h"

int main() {

    sextl::collection<int> collection;
    collection.append(15);
    std::cout << "collection: " << collection[0] << std::endl;

    sextl::vector<float> vec = {10.1f, 20.2f};
    vec.clone().for_each([&](auto &e) {
        e += 1.f;
        std::cout << "Element: " << e << std::endl;
    });

    sextl::string b = "TEST";
    sextl::string str = "te";

    sextl::string c = b + str;
    std::cout << c.length() << std::endl;
    std::cout << c.data() << std::endl;
    std::cout << c[0] << std::endl;
    return 0;
}
