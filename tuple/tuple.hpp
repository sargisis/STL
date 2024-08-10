
#ifndef TUPLE_HPP
#define TUPLE_HPP

#include "tuple.h"

namespace g3 {

    template<typename T, typename... Ts>
    template<typename U, typename... Us>
    tuple<T, Ts...>::tuple(const U& ob, const Us&... args)
        : val{ob}
        , rest{args...} 
    {}

    template<typename T, typename... Ts>
    template<typename... Us>
    tuple<T, Ts...>::tuple(const tuple<Us...>& rhv)
        : val{rhv.val}
        , rest{rhv.rest} 
    {}

    template<typename T, typename... Ts>
    template<typename... Us>
    tuple<T, Ts...>::tuple(tuple<Us...>&& rhv) noexcept
        : val{std::move(rhv.val)}
        , rest{std::move(rhv.rest)} 
    {}

    template<typename T, typename... Ts>
    const tuple<T, Ts...>& tuple<T, Ts...>::operator=(const tuple& rhv)
    {
        val = rhv.val;
        rest = rhv.rest;
        return *this;
    }

    template<typename T, typename... Ts>
    const tuple<T, Ts...>& tuple<T, Ts...>::operator=(tuple&& rhv) noexcept 
    {
        val = std::move(rhv.val);
        rest = std::move(rhv.rest);
        return *this;
    }

    template<typename T, typename... Ts>
    void tuple<T, Ts...>::swap(tuple& other) noexcept 
    {
        std::swap(val, other.val);
        rest.swap(other.rest);
    }

    template<typename T>
    tuple<T>::tuple(const_reference value) 
    : val{value} 
    {}

    template<typename T>
    tuple<T>::tuple(const tuple& rhv) 
    : val{rhv.val} 
    {}

    template<typename T>
    tuple<T>::tuple(tuple&& rhv) noexcept 
    : val{std::move(rhv.val)} 
    {
        rhv.val = T();
    }

    template<typename T>
    const tuple<T>& tuple<T>::operator=(const tuple& rhv) 
    {
        val = rhv.val;
        return *this;
    }

    template<typename T>
    const tuple<T>& tuple<T>::operator=(tuple&& rhv) noexcept 
    {
        val = std::move(rhv.val);
        rhv.val = T();
        return *this;
    }

    template<typename T>
    void tuple<T>::swap(tuple& other) noexcept 
    {
        std::swap(val, other.val);
    }

    template<typename T, typename U>
    std::optional<int> compare(const tuple<T>& lhv, const tuple<U>& rhv) 
    {
        if (lhv.val < rhv.val) return -1;
        if (lhv.val > rhv.val) return 1;
        return 0;
    }

    template<typename... Ts, typename... Us>
    std::optional<int> compare(const tuple<Ts...>& lhv, const tuple<Us...>& rhv) 
    {
        if (auto result = compare(lhv.val, rhv.val); result != 0) {
            return result;
        }
        return compare(lhv.rest, rhv.rest);
    }

    template<typename... Ts, typename... Us>
    bool operator==(const tuple<Ts...>& lhv, const tuple<Us...>& rhv) {
        return compare(lhv, rhv) == 0;
    }

    template<typename... Ts, typename... Us>
    bool operator!=(const tuple<Ts...>& lhv, const tuple<Us...>& rhv) {
        return !(lhv == rhv);
    }

    template<typename... Ts, typename... Us>
    bool operator>(const tuple<Ts...>& lhv, const tuple<Us...>& rhv) {
        return compare(lhv, rhv) > 0;
    }

    template<typename... Ts, typename... Us>
    bool operator>=(const tuple<Ts...>& lhv, const tuple<Us...>& rhv) {
        return compare(lhv, rhv) >= 0;
    }

    template<typename... Ts, typename... Us>
    bool operator<(const tuple<Ts...>& lhv, const tuple<Us...>& rhv) {
        return compare(lhv, rhv) < 0;
    }

    template<typename... Ts, typename... Us>
    bool operator<=(const tuple<Ts...>& lhv, const tuple<Us...>& rhv) {
        return compare(lhv, rhv) <= 0;
    }

}

#endif // TUPLE_HPP

