#include <functional>
#include <algorithm>

#include "collection.h"

#ifndef SEXTL_VECTOR_H
#define SEXTL_VECTOR_H

namespace sextl {
    template<typename T>
    class vector : public collection<T> {
    private:
        class vec_stream {
        private:
            T * m_elements = nullptr;
            size_t m_size;

        public:
            vec_stream(const vector<T> &vec) {
                this->m_elements = new T[vec.size()];
                for (auto i = 0; i < vec.size(); i++) {
                    this->m_elements[i] = vec.get(i);
                }
                this->m_size = vec.size();
            }

            vec_stream(const std::initializer_list<T> elems) {
                this->m_elements = new T[elems.size()];
                for (auto i = 0; i < elems.size(); i++) {
                    this->elements[i] = *(&elems.begin() + i);
                }
                this->m_size = elems.size();
            }

            vec_stream(const vec_stream *stream) {
                this->m_elements = new T[stream->m_size];
                this->m_elements = std::move(this->m_elements);
                this->m_size = stream->m_size;
            }

            /**
             * The number of elements in the current stream
             * @return number of elements
             */
            constexpr auto count() const noexcept -> size_t {
                return this->m_size;
            }

            /**
             * Filters the vec_stream with the given predicate
             * @param predicate to filter with
             * @return a new vector the objects that matched the predicate
             */
            constexpr auto filter(const std::function<bool(const T &)> predicate) const noexcept -> vec_stream {
                auto vec = vector<T>();
                for (auto i = 0; i < this->m_size; i++) {
                    if (predicate(this->m_elements[i]))
                        vec.append(this->m_elements[i]);
                }
                return vec_stream(vec);
            }

            /**
             * Collects the given stream to a given collection
             * @tparam collection type (eg: vector)
             * @return the new collection
             */
            template<typename K>
            constexpr auto collect() const noexcept -> K {
                static_assert(std::is_base_of_v<sextl::collection<T>, K>, "Collect template parameter not derived from collection.");
                auto collection = K();
                for (auto i = 0; i < this->m_size; i++)
                    collection.append(this->m_elements[i]);
                return collection;
            }

            /**
             * Runs given function on element if the predicate returns true
             * @param predicate for each element
             * @param function to run on each element
             * @return a new stream with the current objects
             */
            constexpr auto compute_if(std::function<bool(T &)> predicate, std::function<void(T &)> f) noexcept -> vec_stream {
                for (auto i = 0; i < this->m_size; i++) {
                    if (predicate(this->m_elements[i]))
                        f(this->m_elements[i]);
                }
                return vec_stream(this);
            }

            ~vec_stream() {
                delete[] this->m_elements;
            }
        };

    public:
        vector()
                : collection<T>() {}

        vector(const std::initializer_list<T> defaults)
                : collection<T>(defaults) {}

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
        constexpr auto for_each(const std::function<void(T &)> f) noexcept -> void {
            for (auto it = this->begin(); it < this->end(); it++) {
                f(*it);
            }
        }

        /**
         * Returns a vec_stream for the current vector
         * @return vec_stream containing this vector objects
         */
        constexpr auto stream() const noexcept -> vec_stream {
            return vec_stream(*this);
        }
    };
}

#endif //SEXTL_VECTOR_H
