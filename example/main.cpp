#include <iostream>
#include "../src/vector.h"

int main() {
    {
        sextl::vector<int> test = {10, 20}; // RAII
        test.append(30);
        test.append(100);
        for (auto x : test)
        {
            std::cout << x << std::endl;
        }
    }

    {
        sextl::vector<int> test = sextl::vector<int>({10, 20}, false); // NO RAII
        test.append(30);
        test.append(100);
        for (auto x : test)
        {
            std::cout << x << std::endl;
        }
        test.free();
    }

    return 0;
}
