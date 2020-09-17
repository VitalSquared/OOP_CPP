#include <cmath>
#include <iostream>
#include "RNA.h"

//constructors and destructors//

RNA::RNA(Nucleotide nucleotide, size_t capacity) {
    _capacity = capacity;
    _length = 0;
    _nucleotides = new size_t[array_length()];
    for (size_t i = 0; i < array_length(); i++)
        _nucleotides[i] = fill_nucleotides(nucleotide);
}

RNA::RNA(const RNA &rna) {
    _capacity = rna._capacity;
    _length = rna._length;
    _nucleotides = new size_t[_capacity];
    for (size_t i = 0; i < _capacity; i++)
        _nucleotides[i] = rna._nucleotides[i];
}

RNA::~RNA() {
    delete [] _nucleotides;
}

//public functions//

void RNA::print_rna() {
    for (size_t i = 0; i < _length; i++)
        cout << nucleotide_to_char(get_nucleotide(i));
    cout << endl;
}

void RNA::operator+=(Nucleotide nucleotide) {
    add_nucleotide(nucleotide);
}

//private functions//

size_t RNA::array_length() {
    return ceil(1.0 * _capacity / size_t_pairs_count());
}

size_t RNA::array_last_index() {
    return ceil(1.0 * _length / size_t_pairs_count()) - 1;
}

size_t RNA::fill_nucleotides(Nucleotide nucleotide) {
    size_t pairs = size_t_pairs_count();
    size_t res = 0;
    for (size_t i = 0; i < pairs; i++) {
        res <<= 2u;
        res += nucleotide;
    }
    return res;
}

char RNA::nucleotide_to_char(Nucleotide nucleotide) {
    char n = 'A';
    switch(nucleotide) {
        case A: n = 'A'; break;
        case G: n = 'G'; break;
        case C: n = 'C'; break;
        case T: n = 'T'; break;
    }
    return n;
}

size_t RNA::size_t_pairs_count() {
    return sizeof(size_t) * 4;
}

Nucleotide RNA::get_nucleotide(size_t idx) {
    size_t block_idx = idx / size_t_pairs_count(), i = idx % size_t_pairs_count();
    size_t block = _nucleotides[block_idx];
    return (Nucleotide)(((block >> (2u * (size_t_pairs_count() - i - 1u)))) & 3u);
}

void RNA::add_nucleotide(Nucleotide nucleotide) {
    if (_length >= _capacity) return;

    _length++;
    size_t i = (_length - 1) % size_t_pairs_count();
    size_t last = _nucleotides[array_last_index()];
    size_t mask = ((size_t)3) << (2u * (size_t_pairs_count() - i - 1));
    size_t nucl = fill_nucleotides(nucleotide) & mask;
    _nucleotides[array_last_index()] = (last & (~mask)) + nucl;
}