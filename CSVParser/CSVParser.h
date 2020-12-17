#ifndef CSVPARSER_CSVPARSER_H
#define CSVPARSER_CSVPARSER_H

#include <tuple>
#include <vector>
#include <fstream>
#include "Utils.h"
#include "TupleUtils.h"

template<class ... Args>
class CSVParser {
private:
    std::ifstream &file;
    size_t skip_lines;
    int linesCount;
    char escape_char;
    char col_separator;
    char row_separator;

    std::string getLine(std::istream& is, size_t linesBefore) {
        std::string str;
        bool isEscapeChar = false;
        char c;
        while(is.get(c)) {
            if (c == escape_char) {
                isEscapeChar = !isEscapeChar;
            }
            if(c == row_separator && !isEscapeChar) break;
            str.push_back(c);
        }
        if (isEscapeChar) throw std::invalid_argument("Line " + std::to_string(linesBefore + 1) + ": escape character " + std::to_string(escape_char) + "did not have a closing equivalent");
        return str;
    }

    void updateLinesCount() {
        file.clear();
        file.seekg(0, std::ios::beg);
        for(linesCount = 0; getLine(file, linesCount) != ""; linesCount++);
        file.clear();
        file.seekg(0, std::ios::beg);
    }

    std::vector<std::string> splitLine(std::string& line, size_t lineNumber) {
        std::vector<std::string> fields;
        std::string cur_str, between_escape_chars;
        bool isEscapeChar = false;
        for (char c : line) {
            if (c == escape_char) {
                isEscapeChar = !isEscapeChar;
                if (!isEscapeChar) {
                    if (between_escape_chars.empty()) cur_str.push_back(escape_char);
                    else cur_str += between_escape_chars;
                    between_escape_chars.clear();
                }
                continue;
            }
            if (isEscapeChar) {
                between_escape_chars.push_back(c);
                continue;
            }
            if(c == col_separator) {
                fields.emplace_back(cur_str);
                cur_str.clear();
                continue;
            }
            cur_str.push_back(c);
        }
        if (isEscapeChar) throw std::invalid_argument("Line " + std::to_string(lineNumber) + ": escape character " + std::to_string(escape_char) + "did not have a closing equivalent");
        if (!cur_str.empty()) fields.emplace_back(cur_str);
        return fields;
    }

    std::tuple<Args...> parseLine(std::string& line, size_t lineNumber) {
        size_t size = sizeof...(Args);

        if(line.empty()) {
            throw std::invalid_argument("Line " + std::to_string(lineNumber) + ": empty line!");
        }

        std::vector<std::string> fields = splitLine(line, lineNumber);

        if(fields.size() != size) {
            throw std::invalid_argument("Line " + std::to_string(lineNumber) + ": wrong number of fields!");
        }

        std::tuple<Args...> lineTuple;
        try {
            lineTuple = parseToTuple<Args...>(fields);
        }
        catch(std::exception& e) {
            throw std::invalid_argument("Line " + std::to_string(lineNumber) + ", Field " + e.what() + ": bad type!");
        }

        return lineTuple;
    }

    class CSVIterator {
    private:
        std::ifstream &file;
        CSVParser<Args...>* parent;
        std::string content;
        size_t index;
        bool last;

        void updateContent() {
            if (last) content = "";
            else {
                file.clear();
                file.seekg(0, std::ios::beg);
                for (int i = 0; i < index; i++) parent->getLine(file, i);
                content = parent->getLine(file, index);
            }
        }

    public:
        CSVIterator(std::ifstream &file, size_t index, CSVParser<Args...>* parent) : index(index), parent(parent), file(file) {
            last = index >= parent->linesCount;
            updateContent();
        }

        CSVIterator& operator++() {
            if(index < parent->linesCount) index++;
            if (index >= parent->linesCount) last = true;
            updateContent();
            return *this;
        }

        CSVIterator& operator--() {
            if (index <= parent->skip_lines) {
                index = parent->skip_lines;
                last = false;
            }
            else {
                if (last) {
                    last = false;
                    index = parent->linesCount - 1;
                }
                else index--;
            }
            updateContent();
            return *this;
        }

        bool operator==(const CSVIterator &other) const {
            return this->last == other.last || (this->index == other.index && this->parent == other.parent);
        }

        bool operator!=(const CSVIterator &other) {
            return !(*this == other);
        }

        std::tuple<Args...> operator*() {
            return parent->parseLine(content, index + 1);
        }
    };

public:
    CSVParser(std::ifstream& file, size_t skip_lines,
              char row_separator = '\n', char col_separator = ',', char escape_char = '\"')
              : file(file), skip_lines(skip_lines), row_separator(row_separator), col_separator(col_separator), escape_char(escape_char) {
        if(!file.is_open())
            throw std::invalid_argument("File is not open");

        linesCount = 0;
        updateLinesCount();

        if(skip_lines >= linesCount)
            throw std::logic_error("Amount of lines to skip is greater than lines in the file");
        if(skip_lines < 0)
            throw std::logic_error("Bad number of lines to skip");
    }

    ~CSVParser() = default;

    CSVIterator begin() {
        return CSVIterator(file, skip_lines, this);
    }

    CSVIterator end() {
        return CSVIterator(file, linesCount, this);
    }
};

#endif