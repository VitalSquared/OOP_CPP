#ifndef LAB1_RNK_H
#define LAB1_RNK_H

#include <unordered_map>

using namespace std;

enum Nucleotide { A, G, C, T };

class RNK {
private:
    char *_nucleotides;
    size_t _capacity;
    size_t _length;

    //helping functions
    size_t capacity_string_length();
    size_t length_string_length();
    Nucleotide get_nucleotide(size_t);
    void add_nucleotide(Nucleotide);

public:
    RNK(Nucleotide nucleotide, size_t capacity);
    RNK(const RNK &rnk);
    ~RNK();

    size_t capacity();
    size_t length();
    size_t cardinality(Nucleotide nucleotide);
    unordered_map<Nucleotide, int> cardinality();
    void trim(size_t trimStartIdx);

    //operators
    friend RNK operator+(RNK &rnk1, RNK &rnk2);
    friend bool operator==(RNK &rnk1, RNK &rnk2);
    friend bool operator!=(RNK &rnk1, RNK &rnk2);
    Nucleotide operator[](size_t idx);

    //helping functions
    static char get_char_representation(Nucleotide nucleotide);
    void print_RNK();
};

#endif
