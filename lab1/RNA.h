#ifndef LAB1_RNA_H
#define LAB1_RNA_H

#include <unordered_map>

using namespace std;

enum Nucleotide { A, G, C, T };

class RNA {
private:
    size_t _size;
    size_t *_nucleotides;

    size_t pairs_in_size_t();
    size_t fill_nucleotides(Nucleotide nucleotide);
    void add_nucleotide(Nucleotide);
    char nucleotide_to_char(Nucleotide nucleotide);

public:
    //constructors and destructors//
    RNA(Nucleotide nucleotide, size_t capacity);
    RNA(const RNA &rna);
    virtual ~RNA();

    //general
    size_t length();
    size_t capacity();

    void trim(size_t from);

    bool isComplementary (RNA & rna);

    Nucleotide get_nucleotide(size_t index);
    void set_nucleotide(Nucleotide nucleotide, size_t index);

    size_t cardinality(Nucleotide value);
    std::unordered_map<Nucleotide, int> cardinality();

    void print_rna();

    //operators
    void operator+=(Nucleotide nucleotide);
    friend RNA operator+(RNA &rna1, RNA &rna2);
    friend bool operator==(RNA &rna1, RNA &rna2);
    friend bool operator!=(RNA &rna1, RNA &rna2);
    RNA operator!();
};

#endif
