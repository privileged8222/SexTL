#include <string>

#include "collection.h"

#ifndef SEXTL_STRING_H
#define SEXTL_STRING_H

namespace sextl {
    class string : public collection<char> {
    private:
        constexpr auto terminate() noexcept -> void {
            this->m_data[this->m_size - 1] = '\0';
        }

        constexpr auto terminate(const size_t size) noexcept -> void {
            this->m_data[size] = '\0';
        }

    public:
        string()
                : collection() {}

        string(const char *defaults)
                : collection(defaults, strlen(defaults) + 1) {
            this->terminate();
        };

        /**
         * Returns the number of characters in the string (not including terminator)
         * @return the length of the string
         */
        [[nodiscard]] constexpr auto length() const noexcept -> size_t {
            return this->m_size - 1;
        }

        /**
         * Returns this string as a C-string
         * @return beginning iterator (this as C-string)
         */
        [[nodiscard]] constexpr auto data() noexcept -> iterator {
            return this->begin();
        }

        /**
         * Concatenates two strings together
         * @param the other string to concat
         * @return the new string
         */
        [[nodiscard]] auto concat(const string &a) noexcept -> string {
            this->resize(this->m_size + a.m_size);
            std::copy(a.begin(), a.end(), &this->m_data[this->m_size - 1]);
            this->m_size = this->m_size + a.m_size;
            return *this;
        }

        string operator<<(const string &a) {
            return this->concat(a);
        }

        string operator+(const string &a) {
            return this->concat(a);
        }

        string operator+(const char *a) {
            return this->concat(string(a));
        }
    };
}

#endif //SEXTL_STRING_H
