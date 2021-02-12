#include <type_traits>

#ifndef SEXTL_ARRAY_H
#define SEXTL_ARRAY_H

namespace sextl {
    template<typename T, size_t S>
    class array {
    protected:
        T m_data[S];

    public:
        using iterator = T *;

        array()
                : m_data({}) {}

        array(const std::initializer_list<T> defaults) {
            for (auto i = 0; i < S; i++)
                if (i < defaults.size() - 1)
                    this->m_data[i] = *(defaults.begin() + i);
                else
                    break;
        }

        /**
         * Returns the number of objects in the array
         * @return number of objects
         */
        [[nodiscard]] constexpr auto size() const noexcept -> size_t {
            return S;
        }

        /**
        * Beginning iterator of the array (pointer to first object)
        * @return the beginning iterator
        */
        [[nodiscard]] constexpr auto begin() noexcept -> iterator {
            return &this->m_data[0];
        }

        /**
         * End iterator of the array (pointer to last object)
         * @return the end iterator
         */
        [[nodiscard]] constexpr auto end() noexcept -> iterator {
            return &this->m_data[this->m_size];
        }

        virtual constexpr T &operator[](const size_t index) {
            return this->m_data[index];
        }
    };
}

#endif //SEXTL_ARRAY_H
