#ifndef CSVPARSER_CSVPARSER_H
#define CSVPARSER_CSVPARSER_H

#include <tuple>
#include <vector>
#include <fstream>
#include <typeinfo>
#include <regex>
#include "Utils.h"
#include "TupleUtils.h"

template<class ... Args>
class CSVParser {
private:
    std::ifstream &input;
    size_t skip_lines;
    int fileLength = -1;
    char escape_char;
    char col_separator;
    char row_separator;

    enum class ParsingState { simpleRead, delimiterReading };

    template<typename _CharT, typename _Traits, typename _Alloc>
    void getLine(std::basic_istream<_CharT, _Traits> &is, std::basic_string<_CharT, _Traits, _Alloc> &str) {
        str.clear();

        char c;
        while(is.get(c)) {
            if(c == row_separator) break;
            str.push_back(c);
        }
    }

    bool emptyTailToDelimiter(std::string a, int pos) {
        for(int i = pos; i < a.size(); ++i)
            if(a[i] == col_separator)
                break;
            else
            if(a[i] != ' ')
                return false;

        return true;
    }

    int getLength() {
        if(fileLength == -1) {
            input.clear();
            input.seekg(0, std::ios::beg);

            std::string line;
            for(fileLength = 0; getline(input, line); fileLength++);

            input.clear();
            input.seekg(0, std::ios::beg);
        }
        return fileLength;
    }


    class CSVIterator {
    private:
        std::string strBuffer;
        std::ifstream &input;
        size_t index;
        CSVParser<Args...> &parent;
        bool last = false;

        friend class CSVParser;

    public:
        CSVIterator(std::ifstream &file, size_t index, CSVParser<Args...> &parent) : index(index), parent(parent), input(file) {
            for(int i = 0; i < index - 1; i++, parent.getLine(input, strBuffer));

            parent.getLine(input, strBuffer);
            if(!input) throw std::logic_error("Bad file!");
        }

        CSVIterator& operator++() {
            if(index < parent.fileLength) {
                index++;
                input.clear();
                input.seekg(0, std::ios::beg);
                for(int i = 0; i < index - 1; ++i, parent.getLine(input, strBuffer));

                parent.getLine(input, strBuffer);
            }
            else {
                strBuffer = "";
                last = true;
            }

            return *this;
        }

        bool operator==(const CSVIterator &other) const {
            return this->last == other.last && this->index == other.index && this->strBuffer == other.strBuffer;
        }

        bool operator!=(const CSVIterator &other) {
            return !(*this == other);
        }

        std::tuple<Args...> operator*() {
            return parent.parseLine(strBuffer, index);
        }
    };

public:
    CSVParser(std::ifstream& file, size_t skip_lines,
              char row_separator = '\n', char col_separator = ',', char escape_char = '\"')
              : input(file), skip_lines(skip_lines), row_separator(row_separator), col_separator(col_separator), escape_char(escape_char) {
        if(!file.is_open())
            throw std::invalid_argument("Can't open file");
        if(skip_lines >= getLength())
            throw std::logic_error("Amount of lines to skip is greater than lines in the file");
        if(skip_lines < 0)
            throw std::logic_error("Bad number of lines to skip");
    }

    ~CSVParser() = default;

    CSVIterator begin() {
        CSVIterator a(input, skip_lines + 1, *this);
        return a;
    }

    CSVIterator end() {
        int t = getLength();

        CSVIterator a(input, 1, *this);
        a.last = true;
        a.strBuffer = "";
        a.index = getLength();
        return a;
    }

    std::vector<std::string> splitLine(std::string& line, size_t lineNumber) {
        std::vector<std::string> fields {""};
        ParsingState state = ParsingState::simpleRead;
        size_t fcounter = 0;
        size_t linePos = 0;
        bool filled = false;
        bool accessWriteDelim = false;
        line = trimString(line);
        for(char c : line) {
            if(state == ParsingState::simpleRead) {
                if(c == col_separator) {
                    fields[fcounter] = trimString(fields[fcounter]);
                    fields.emplace_back("");
                    fcounter++;
                    filled = false;
                }
                else if(c == escape_char) {
                    if(linePos > 0 && filled)
                        throw std::invalid_argument("Bad " + std::to_string(fcounter) + "th field at line " + std::to_string(lineNumber) +
                                               ": field delimiter not first!");

                    fields[fcounter] = trimString(fields[fcounter]);
                    state = ParsingState::delimiterReading;
                    accessWriteDelim = false;
                }
                else {
                    if(c != ' ')
                        filled = true;

                    fields[fcounter].push_back(c);
                }
            }
            else { //TODO DELIMITER READING
                if(c == escape_char) {
                    if(!accessWriteDelim && line.size() > linePos + 1 && line[linePos + 1] != escape_char) {
                        if(!emptyTailToDelimiter(line, linePos + 1))
                            throw std::invalid_argument(
                                    "Bad " + std::to_string(fcounter) + "th field at line " + std::to_string(lineNumber) +
                                    ": symbols after delimiter in field!");
                        state = ParsingState::simpleRead;
                    }
                    else if(!accessWriteDelim && linePos == line.size() - 1) {
                        state = ParsingState::simpleRead;
                    }
                    else if(!accessWriteDelim) accessWriteDelim = true;
                    else {
                        fields[fcounter].push_back(c);
                        accessWriteDelim = false;
                    }
                }
                else fields[fcounter].push_back(c);
            }
            linePos++;
        }
        if(state != ParsingState::simpleRead)
            throw std::invalid_argument(
                    "Bad " + std::to_string(fcounter) + "th field at line " + std::to_string(lineNumber) + ": not closed field!");
        return fields;
    }

    std::tuple<Args...> parseLine(std::string &line, size_t lineNumber) {
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
};

#endif