#ifndef CSVPARSER_TUPLEUTILS_H
#define CSVPARSER_TUPLEUTILS_H

#include <tuple>
#include <vector>
#include <iostream>
#include <sstream>

//convert string to Type

template<class Type>
class from_string {
private:
    Type value;

public:
    from_string(const std::string &src) {
        std::stringstream s;
        s << src;
        s >> value;
        if (!s) throw std::exception();
    }

    operator const Type &() const {
        return value;
    }

    operator Type &() {
        return value;
    }
};

template<>
class from_string<std::string> {
private:
    std::string value;

public:
    from_string(const std::string &src) : value(src) {}

    operator const std::string &() const {
        return value;
    }

    operator std::string &() {
        return value;
    }
};

//tuple print

template<size_t N, typename T>
struct PrintTuple {
    static void print(std::ostream& os, const T& tuple) {
        PrintTuple<N - 1, T>::print(os, tuple);
        if (N != 1) os << ", ";
        os << "[" << std::get<N - 1>(tuple) << "]";
    }
};

template<typename T>
struct PrintTuple<0, T> {
    static void print(std::ostream& os, const T& tuple) {}
};

template <typename... Args>
std::ostream& operator<<(std::ostream& os, const std::tuple<Args...>& tuple) {
    os << "(";
    PrintTuple<sizeof...(Args), std::tuple<Args...>>::print(os, tuple);
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
