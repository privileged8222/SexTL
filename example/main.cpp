#include <iostream>
#include "../src/vector.h"
#include "../src/string.h"

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

    {
        sextl::string s = "1234567890";
        s.append(" test");
        std::cout << s.raw() << std::endl;
        std::cout << "String length: " << s.length() << std::endl;
    }

    return 0;
}
