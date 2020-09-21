#ifndef LAB1_RNA_H
#define LAB1_RNA_H

#include <unordered_map>

using namespace std;

enum Nucleotide { A, G, C, T };

class RNA {
private:
    size_t _capacity;
    size_t _length;
    size_t *_nucleotides;

    size_t array_length();
    size_t array_last_index();
    size_t fill_nucleotides(Nucleotide nucleotide);
    char nucleotide_to_char(Nucleotide nucleotide);
    size_t size_t_pairs_count();
    Nucleotide get_nucleotide(size_t idx);
    void add_nucleotide(Nucleotide);

public:
    RNA(Nucleotide nucleotide, size_t capacity);
    RNA(const RNA &rna);
    virtual ~RNA();

    void print_rna();

    //operators
    void operator+=(Nucleotide nucleotide);
};

#endif
