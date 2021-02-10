#include <functional>
#include <algorithm>

#include "collection.h"

#ifndef SEXTL_VECTOR_H
#define SEXTL_VECTOR_H

namespace sextl {
    template<typename T>
    class vector : public collection<T> {
    public:
        vector()
            : collection<T>() { }

        vector(const std::initializer_list<T> defaults)
            : collection<T>(defaults) { }

        /**
         * Creates new vector with same objects
         * @return the new vector
         */
        constexpr auto clone() const noexcept -> vector<T> {
            return vector<T>(*this);
        }

        /**
         * Applies passed function to each object of vector
         * @param function to use
         */
        constexpr auto for_each(std::function<void(T&)> f) noexcept -> void {
            std::for_each(this->begin(), this->end(), f);
        }
    };
}

#endif //SEXTL_VECTOR_H
