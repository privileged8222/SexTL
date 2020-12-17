#include <initializer_list>
#include <cstdlib>

namespace sextl
{
    template<typename T>
    struct vector
    {
    private:
        size_t m_size;
        T* m_elements;
        bool raii;
    public:
        vector(bool raii = true)
        {
            this->m_elements = reinterpret_cast<T*>(malloc(sizeof(T)));
            this->m_size = 0;
            this->raii = raii;
        }

        vector(std::initializer_list<T> elements, bool raii = true)
        {
            this->m_size = elements.size() * sizeof(T);
            this->m_elements = reinterpret_cast<T*>(malloc(this->m_size));
            memmove(this->m_elements, elements.begin(), this->m_size);
            this->raii = raii;
        }

        constexpr void append(T element)
        {
            T* cur_elements = reinterpret_cast<T*>(malloc(this->m_size));
            memcpy(cur_elements, this->m_elements, this->m_size);
            size_t cur_size = this->m_size;
            this->m_size = this->m_size + sizeof(T);
            this->m_elements = reinterpret_cast<T*>(realloc(this->m_elements, this->m_size));
            memmove(this->m_elements, cur_elements, cur_size);
            this->m_elements[cur_size/sizeof(T)] = element;
            ::free(cur_elements);
        }

        constexpr T* begin()
        {
            return this->m_elements;
        }

        constexpr T* end()
        {
            return this->m_elements + (this->m_size/sizeof(T));
        }

        constexpr void clear()
        {
            memset(this->m_elements, NULL, this->m_size);
            realloc(this->m_elements, 0);
            this->m_size = 0;
        }

        constexpr void free()
        {
            ::free(this->m_elements);
        }

        ~vector()
        {
            if (this->raii)
            {
                this->free();
            }
        }
    };
}