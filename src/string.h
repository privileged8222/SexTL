#pragma once
#include <cstdlib>
#include <cstring>

namespace sextl
{
    struct string
    {
    private:
        size_t m_size;
        char* m_string;
        bool raii;
    public:
        string(bool raii = true)
        {
            this->m_size = 0;
            this->m_string = reinterpret_cast<char*>(malloc(sizeof(char)));
            this->raii = raii;
        }

        string(char* string, bool raii = true)
        {
            this->m_size = strlen(string) + 1;
            this->m_string = reinterpret_cast<char*>(malloc(this->m_size));
            strcpy_s(this->m_string, this->m_size, string);
            this->raii = raii;
        }

        constexpr char* raw()
        {
            return this->m_string;
        }

        void append(const char* string)
        {
            char* cur_string = reinterpret_cast<char*>(malloc(this->m_size));
            strcpy_s(cur_string, this->m_size, this->m_string);
            size_t cur_size = this->m_size;
            this->m_size = this->m_size + strlen(string);
            this->m_string = reinterpret_cast<char*>(realloc(this->m_string, this->m_size));
            strcpy_s(this->m_string, cur_size, cur_string);
            memmove(this->m_string + (this->m_size - strlen(string) - 1), string, strlen(string) +1);
            ::free(cur_string);
        }

        constexpr size_t length()
        {
            return this->m_size - 1;
        }

        void free()
        {
            ::free(this->m_string);
        }

        ~string()
        {
            if (this->raii)
            {
                this->free();
            }
        }
    };
}