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
        using iterator = T *;

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

        /**
         * Returns value of object at specific index
         * @param index of object
         * @return value of object at index
         */
        [[nodiscard]] constexpr auto get(const size_t index) const noexcept -> T {
            return this->m_data[index];
        }

        /**
         * Sets an object at a specific index to a value
         * @param index of object
         * @param new value of object
         * @return value of the new object
         */
        constexpr auto set(const size_t index, const T val) noexcept -> T {
            this->m_data[index] = std::move(val);
            return this->m_data[index];
        }

        /**
         * Returns size of collection
         * @return size of collection
         */
        [[nodiscard]] constexpr auto size() const noexcept -> size_t {
            return this->m_size;
        }

        /**
         * Changes size of collection (does not change objects)
         * @param new size of collection
         */
        constexpr auto resize(const size_t size) noexcept -> void {
            T *buf = new T[size];
            std::copy(&this->m_data[0], &this->m_data[size - 1], buf);
            this->m_data = new T[size];
            std::copy(&buf[0], &buf[size], this->m_data);
            delete[] buf;
        }

        /**
         * Clears the collection (does not resize)
         */
        constexpr auto clear() noexcept -> void {
            std::fill(&this->m_data[0], &this->m_data[this->m_size], 0);
            this->m_size = 0;
        }

        /**
         * Adds an object to the collection
         * @param new object
         * @return the collection with the new object
         */
        constexpr auto append(const T data) noexcept -> collection<T> {
            this->m_size++;
            this->resize(this->m_size);
            this->m_data[this->m_size - 1] = data;
            return *this;
        }

        /**
         * Removes an object from the collection by value
         * @param value to remove
         * @return the collection without the object
         */
        constexpr auto remove(const T data) noexcept -> collection<T> {
            T *buf = new T[this->m_size];
            size_t buf_counter = 0;
            for (auto i = 0; i < this->m_size; i++) {
                if (this->m_data[i] != data) {
                    buf[buf_counter] = this->m_data[i];
                    buf_counter++;
                }
            }
            std::copy(&buf[0], &buf[buf_counter + 1], this->m_data);
            delete[] buf;
            return *this;
        }

        /**
         * Removes an object from the collection by index
         * @param index to remove
         * @return the collection without the object
         */
        constexpr auto remove(size_t index) noexcept -> collection<T> {
            this->remove(this->m_data[index]);
        }

        /**
         * Beginning iterator of the collection (pointer to first object)
         * @return the beginning iterator
         */
        [[nodiscard]] constexpr auto begin() noexcept -> iterator {
            return &this->m_data[0];
        }

        /**
         * End iterator of the collection (pointer to last object)
         * @return the end iterator
         */
        [[nodiscard]] constexpr auto end() noexcept -> iterator {
            return &this->m_data[this->m_size];
        }

        virtual constexpr T &operator[](const size_t index) {
            return this->m_data[index];
        }

        virtual ~collection() {
            delete[] this->m_data;
        }
    };
}

#endif //SEXTL_COLLECTION_H
