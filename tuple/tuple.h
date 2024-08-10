#ifndef __Tuple__
#define __Tuple__

#include <cstddef>
#include <optional>
#include <tuple>
#include <utility>
#include <algorithm>

namespace g3 {
    template<typename T, typename... Ts>
    struct tuple {
    private:
        T val;
        tuple<Ts...> rest;
    public:
        using value_type = T;
        using pointer = value_type*;
        using const_pointer = const value_type*;

        tuple() = default;

        T get_val() const {
            return val; 
        }

        const tuple<Ts...>& get_rest() const {
            return rest; 
        } 

        template<typename U, typename... Us>
        tuple(const U& ob, const Us&... args);

        template<typename... Us>
        tuple(const tuple<Us...>& rhv);

        template<typename... Us>
        tuple(tuple<Us...>&& rhv) noexcept;

        const tuple& operator=(const tuple& rhv);

        const tuple& operator=(tuple&& rhv) noexcept;

        void swap(tuple& other) noexcept;

};

    template<typename T>
    struct tuple<T> {
    private:
        T val;
    public:
        using value_type = T;
        using const_reference = const value_type&;
        using reference = value_type&;
        using pointer = value_type*;
        using const_pointer = const value_type*;

        tuple() = default;
        tuple(const_reference val);
        tuple(const tuple& rhv);
        tuple(tuple&& rhv) noexcept;

        T get_val() const {
            return val; 
        }

        const tuple& operator=(const tuple& rhv);
        const tuple& operator=(tuple&& rhv) noexcept;

        void swap(tuple& other) noexcept;
    };

    // Comparison operators for tuples
    template<typename... Ts, typename... Us>
    bool operator==(const tuple<Ts...>& lhv, const tuple<Us...>& rhv);

    template<typename... Ts, typename... Us>
    bool operator!=(const tuple<Ts...>& lhv, const tuple<Us...>& rhv);

    template<typename... Ts, typename... Us>
    bool operator>(const tuple<Ts...>& lhv, const tuple<Us...>& rhv);

    template<typename... Ts, typename... Us>
    bool operator>=(const tuple<Ts...>& lhv, const tuple<Us...>& rhv);

    template<typename... Ts, typename... Us>
    bool operator<(const tuple<Ts...>& lhv, const tuple<Us...>& rhv);

    template<typename... Ts, typename... Us>
    bool operator<=(const tuple<Ts...>& lhv, const tuple<Us...>& rhv);

    // Compare function for tuples
    template<typename T, typename U>
    std::optional<int> compare(const tuple<T>& lhv, const tuple<U>& rhv);

    template<typename... Ts, typename... Us>
    std::optional<int> compare(const tuple<Ts...>& lhv, const tuple<Us...>& rhv);

    
}

#include "tuple.hpp"

#endif // __Tuple__

