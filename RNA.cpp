#include <iostream>
#include <cmath>
#include "RNA.h"

//constructors and destructors//

RNA::RNA(Nucleotide nucleotide, size_t size) {
    _size = size;
    _nucleotides = new size_t[capacity()];
    for (size_t i = 0; i < capacity(); i++)
        _nucleotides[i] = fill_nucleotides(nucleotide);
}

RNA::RNA(const RNA &rna) {
    _size = rna._size;
    _nucleotides = new size_t[capacity()];
    for (size_t i = 0; i < capacity(); i++)
        _nucleotides[i] = rna._nucleotides[i];
}
RNA::~RNA() {
    delete [] _nucleotides;
}

//public functions//

size_t RNA::length() {
    return _size;
}

size_t RNA::capacity() {
    return ceil(1.0 * _size / pairs_in_size_t());
}

void RNA::trim(size_t from) {
    _size = from;
    size_t *tmp = new size_t[capacity()];
    for (size_t i = 0; i < capacity(); i++)
        tmp[i] = _nucleotides[i];
    delete [] _nucleotides;
    _nucleotides = tmp;
}

bool RNA::isComplementary(RNA &rna) {
    if (_size != rna._size) return false;
    for (size_t i = 0; i < _size; i++) {
        Nucleotide nucl1 = get_nucleotide(i), nucl2 = rna.get_nucleotide(i);
        if (nucl1 + nucl2 != 3) return false;
    }
    return true;
}

Nucleotide RNA::get_nucleotide(size_t idx) {
    size_t block_idx = idx / pairs_in_size_t(), i = idx % pairs_in_size_t();
    size_t block = _nucleotides[block_idx];
    return (Nucleotide)(((block >> (2u * (pairs_in_size_t() - i - 1u)))) & 3u);
}

void RNA::set_nucleotide(Nucleotide nucleotide, size_t idx) {
    if (idx >= _size) return;

    size_t block_idx = idx / pairs_in_size_t(), i = idx % pairs_in_size_t();
    size_t block = _nucleotides[block_idx];
    size_t mask = ((size_t)3) << (2u * (pairs_in_size_t() - i - 1));
    size_t nucl = fill_nucleotides(nucleotide) & mask;

    _nucleotides[block_idx] = (block & (~mask)) + nucl;
}

size_t RNA::cardinality(Nucleotide nucleotide) {
    size_t cnt = 0;
    for (size_t i = 0; i < _size; i++) {
        Nucleotide cur = get_nucleotide(i);
        if (cur == nucleotide) cnt++;
    }
    return cnt;
}

std::unordered_map<Nucleotide, int> RNA::cardinality() {
    size_t *cnt = new size_t[4];
    unordered_map<Nucleotide, int> map(4);

    for (size_t i = 0; i < _size; i++)
        cnt[get_nucleotide(i)]++;
    for (size_t i = 0; i < 4; i++)
        map.insert(make_pair((Nucleotide)i, cnt[i]));

    delete [] cnt;
    return std::unordered_map<Nucleotide, int>();
}

void RNA::print_rna() {
    for (size_t i = 0; i < _size; i++)
        cout << nucleotide_to_char(get_nucleotide(i));
    cout << endl;
}

//operators

void RNA::operator+=(Nucleotide nucleotide) {
    add_nucleotide(nucleotide);
}

RNA operator+(RNA &r1, RNA &r2) {
    RNA rna(r1);
    for (size_t i = 0; i < r2._size; i++)
        rna.add_nucleotide(r2.get_nucleotide(i));
    return rna;
}

bool operator==(RNA &r1, RNA &r2) {
    if (r1._size != r2._size) return false;
    for (size_t i = 0; i < r1._size; i++) {
        Nucleotide n1 = r1.get_nucleotide(i), n2 = r2.get_nucleotide(i);
        if (n1 != n2) return false;
    }
    return true;
}

bool operator!=(RNA &r1, RNA &r2) {
    return !(r1 == r2);
}

RNA RNA::operator!() {
    RNA rna(A, 0);
    for (size_t i = 0; i < rna._size; i++) {
        Nucleotide cur = rna.get_nucleotide(i);
        rna.add_nucleotide((Nucleotide)(3 - cur));
    }
    return rna;
}

//private functions//

size_t RNA::pairs_in_size_t() {
    return sizeof(size_t) * 4;
}

size_t RNA::fill_nucleotides(Nucleotide nucleotide) {
    size_t pairs = pairs_in_size_t();
    size_t res = 0;
    for (size_t i = 0; i < pairs; i++) {
        res <<= 2u;
        res += nucleotide;
    }
    return res;
}

void RNA::add_nucleotide(Nucleotide nucleotide) {
    _size++;
    size_t i = (_size - 1) % pairs_in_size_t();
    if (i == 0) {
        size_t *tmp = new size_t[capacity()];
        for (size_t j = 0; j < capacity() - 1; j++)
            tmp[j] = _nucleotides[j];
        delete[] _nucleotides;
        _nucleotides = tmp;
    }
    set_nucleotide(nucleotide, _size - 1);
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
