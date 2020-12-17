#ifndef CSVPARSER_TUPLEUTILS_H
#define CSVPARSER_TUPLEUTILS_H

#include <tuple>
#include <vector>
#include <iostream>
#include <sstream>
#include "Utils.h"

//tuple print

template <size_t N, typename... Args>
typename std::enable_if<(N >= sizeof...(Args))>::type
print_tuple(std::ostream& os, const std::tuple<Args...>&) {}

template <size_t N, typename... T>
typename std::enable_if<(N < sizeof...(T))>::type
print_tuple(std::ostream& os, const std::tuple<T...>& tuple) {
    if (N != 0) os << ", ";
    os << "[" << std::get<N>(tuple) << "]";
    print_tuple<N+1>(os, tuple);
}

template <typename... Args>
std::ostream& operator<<(std::ostream& os, const std::tuple<Args...>& tuple) {
    os << "(";
    print_tuple<0>(os, tuple);
    os << ")";
    return os;
}

//vector of strings to tuple

template<size_t N, typename T>
struct StringsToTuple {
    static void convert(T& tuple, const std::vector<std::string>& strings) {
        try {
            std::get<N - 1>(tuple) = from_string<typename std::tuple_element<N - 1, T>::type>(strings[N - 1]);
        }
        catch (std::exception&) {
            throw std::invalid_argument(std::to_string(N));
        }
        StringsToTuple<N - 1, T>::convert(tuple, strings);
    }
};

template<typename T>
struct StringsToTuple<0, T> {
    static void convert(T&, const std::vector<std::string>&) {}
};

template<typename... Args>
std::tuple<Args...> parseToTuple(const std::vector<std::string>& strings) {
    std::tuple<Args...> tuple;
    StringsToTuple<sizeof...(Args), std::tuple<Args...>>::convert(tuple, strings);
    return tuple;
}

#endif
