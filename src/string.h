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

        constexpr auto terminate(size_t size) noexcept -> void {
            this->m_data[size] = '\0';
        }

    public:
        string(const char *defaults)
                : collection(defaults, strlen(defaults) + 1) {
            this->terminate();
        };

        constexpr auto length() const noexcept -> size_t {
            return this->m_size - 1;
        }

        constexpr auto data() noexcept -> const char * {
            return this->begin();
        }

        auto concat(const string &a) noexcept -> string {
            string res = *this;
            res.resize(res.m_size + a.m_size - 1);
            std::copy(&a.m_data[0], &a.m_data[a.m_size], &res.m_data[res.m_size - 1]);
            res.m_size = res.m_size + a.m_size - 1;
            return res;
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
