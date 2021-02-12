#include <type_traits>
#include <cmath>

#include "array.h"

#ifndef SEXTL_AVEC_H
#define SEXTL_AVEC_H

namespace sextl {
    // Arithmetic vector (eg Vec2 alternative)
    template<typename T, size_t S, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    class avec : public array<T, S> {
    public:
        using precise_double = long double;

        avec()
                : array<T, S>() {}

        avec(const std::initializer_list<T> defaults)
                : array<T, S>(defaults) {}

        /**
         * Returns distance to given avec
         * @param avec to find distance to
         * @return distance to given avec
         */
        [[nodiscard]] constexpr auto distance(const avec<T, S> &a) -> precise_double {
            precise_double res = 0.f;
            for (auto i = 0; i < S; i++)
                res += (this->m_data[i] - a.m_data[i]) * (this->m_data[i] - a.m_data[i]);
            return std::sqrtl(res / (precise_double) S);
        }
    };
}

#endif //SEXTL_AVEC_H
