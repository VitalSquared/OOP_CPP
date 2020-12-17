#ifndef CSVPARSER_UTILS_H
#define CSVPARSER_UTILS_H

#include <regex>

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

//trim strings

std::string& ltrimString(std::string &str, const std::string &chars = " \n\t\r\f") {
    str.erase(0, str.find_first_not_of(chars));
    return str;
}

std::string& rtrimString(std::string &str, const std::string &chars = " \n\t\r\f") {
    str.erase(str.find_last_not_of(chars) + 1);
    return str;
}

std::string& trimString(std::string &str, const std::string &chars = " \n\t\r\f") {
    return ltrimString(rtrimString(str, chars), chars);
}

#endif
