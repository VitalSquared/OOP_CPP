#include <iostream>
#include <fstream>
#include <tuple>
#include "TupleUtils.h"
#include "CSVParser.h"

int main() {
    {
        std::ifstream file("test.csv");
        try {
            CSVParser<int, std::string, std::string, std::string, double> parser(file, 0);
            for (const auto &tuple : parser) {
                std::cout << tuple << std::endl;
            }
            std::cout << std::endl;
            std::cout << *(parser.begin() + 1) << std::endl;
            auto it = parser.begin();
            std::cout << *it << std::endl;
            it++;
            std::cout << *it << std::endl;
            it--;
            std::cout << *it << std::endl;
            std::cout << *(it + 2) << std::endl;
        }
        catch (std::exception &e) {
            std::cout << e.what() << std::endl;
        }
        if (file.is_open()) file.close();
    }
    std::cout << std::endl;
    {
        std::ifstream file("test2.csv");
        try {
            CSVParser<int, std::string, std::string, std::string, std::string> parser(file, 0, '\n', ';', '\"');
            for (const auto &tuple : parser) {
                std::cout << tuple << std::endl;
            }
        }
        catch (std::exception &e) {
            std::cout << e.what() << std::endl;
        }
        if (file.is_open()) file.close();
    }
    return 0;
}
