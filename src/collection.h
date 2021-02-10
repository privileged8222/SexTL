#include <initializer_list>
#include <cstdlib>
#include <cstring>
#include <utility>

#ifndef SEXTL_COLLECTION_H
#define SEXTL_COLLECTION_H

namespace sextl {
    template<typename T>
    class collection {
    protected:
        size_t m_size = 0;
        T *m_data = nullptr;

    public:
        collection(const std::initializer_list<T> defaults) {
            this->m_data = new T[defaults.size()];
            std::copy(defaults.begin(), defaults.end(), this->m_data);
            this->m_size = defaults.size();
        }

        collection(const T *defaults, const size_t defaults_size) {
            this->m_data = new T[defaults_size];
            std::copy(&defaults[0], &defaults[defaults_size - 1], this->m_data);
            this->m_size = defaults_size;
        }

        collection(const collection<T> &defaults) {
            this->m_data = new T[defaults.m_size];
            std::copy(&defaults.m_data[0], &defaults.m_data[defaults.m_size], this->m_data);
            this->m_size = defaults.m_size;
        }

        collection() {
            this->m_data = new T[0];
            this->m_size = 0;
        }

        constexpr auto get(const size_t index) const noexcept -> T {
            return this->m_data[index];
        }

        constexpr auto set(const size_t index, const T val) noexcept -> void {
            this->m_data[index] = std::move(val);
        }

        constexpr auto size() const noexcept -> size_t {
            return this->m_size;
        }

        constexpr auto resize(const size_t size) noexcept -> void {
            T *buf = new T[size];
            std::copy(&this->m_data[0], &this->m_data[size - 1], buf);
            this->m_data = new T[size];
            std::copy(&buf[0], &buf[size], this->m_data);
            delete[] buf;
        }

        constexpr auto clear(const size_t size) noexcept -> void {
            std::fill(&this->m_data[0], &this->m_data[this->m_size], 0);
            this->m_size = 0;
        }

        constexpr auto append(const T data) noexcept -> void {
            this->m_size++;
            this->resize(this->m_size);
            this->m_data[this->m_size - 1] = data;
        }

        constexpr auto begin() noexcept -> T * {
            return &this->m_data[0];
        }

        constexpr auto end() noexcept -> T * {
            return &this->m_data[this->m_size];
        }

        constexpr T &operator[](const size_t index) {
            return this->m_data[index];
        }

        virtual ~collection() {
            delete this->m_data;
        }
    };
}

#endif //SEXTL_COLLECTION_H
