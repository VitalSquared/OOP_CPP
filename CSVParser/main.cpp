#include <iostream>
#include <fstream>
#include <tuple>
#include "TupleUtils.h"
#include "CSVParser.h"

int main() {
    std::ifstream file("test.csv");
    try {
        CSVParser<std::string, int, double> parser(file, 1);
        for (const auto &tuple : parser) {
            std::cout << tuple << std::endl;
        }
    }
    catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
    if (file.is_open()) file.close();
    return 0;
}
