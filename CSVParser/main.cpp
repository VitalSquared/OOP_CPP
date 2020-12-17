#include <iostream>
#include <fstream>
#include <tuple>
#include "TupleUtils.h"
#include "CSVParser.h"

int main() {
    {
        std::ifstream file("test2.csv");
        CSVParser<std::string, int, int, int, double, bool> parser(file, 2);
        try {
            for (const auto &tuple : parser) {
                std::cout << tuple << std::endl;
            }
        }
        catch (std::exception &e) {
            std::cout << e.what() << std::endl;
        }
        file.close();
    }
    std::cout << std::endl;
    {
        std::ifstream file("test3.csv");
        CSVParser<std::string, int, int, double, char> parser(file, 0);
        try {
            for (const auto &tuple : parser) {
                std::cout << tuple << std::endl;
            }
        }
        catch (std::exception &e) {
            std::cout << e.what() << std::endl;
        }
        file.close();
    }
    return 0;
}
