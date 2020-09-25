#include <iostream>
#include <cmath>
#include "RNA.h"

//constructors and destructors//

RNA::RNA(Nucleotide nucleotide, size_t size) {
    _nucl = nucleotide;
    _size = size;
    update_capacity();
}

RNA::RNA(const RNA &rna) {
    _nucl = rna._nucl;
    _size = rna._size;
    _capacity = rna._capacity;
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
    return _capacity;
}

void RNA::trim(size_t from) {
    if (from >= _size) return;
    _size = from;
    update_capacity();
}

std::pair<RNA, RNA> RNA::split(size_t idx) {
    RNA rna1(_nucl, 0), rna2(_nucl, 0);
    for (size_t i = 0; i < std::min(idx, _size); i++)
        rna1 += get_nucleotide(i);
    for (size_t i = idx; i < _size; i++)
        rna2 += get_nucleotide(i);
    return std::pair<RNA, RNA>(rna1, rna2);
}

bool RNA::is_complementary(RNA &rna) {
    if (_size != rna._size) return false;

    for (size_t i = 0; i < _size; i++) {
        Nucleotide nucl1 = get_nucleotide(i);
        Nucleotide nucl2 = rna.get_nucleotide(i);
        if (nucl1 + nucl2 != 3) return false;
    }
    return true;
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
    for (size_t i = 0; i < _size; i++) {
        char nucl = 'A';
        switch(get_nucleotide(i)) {
            case A: nucl = 'A'; break;
            case G: nucl = 'G'; break;
            case C: nucl = 'C'; break;
            case T: nucl = 'T'; break;
        }
        cout << nucl;
    }
    cout << endl;
}

//operators

RNA& RNA::operator=(RNA const& rna) {
    _nucl = rna._nucl;
    _size = rna._size;
    _capacity = rna._capacity;
    delete [] _nucleotides;
    _nucleotides = rna._nucleotides;
    return *this;
}

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
        Nucleotide nucl1 = r1.get_nucleotide(i);
        Nucleotide nucl2 = r2.get_nucleotide(i);
        if (nucl1 != nucl2) return false;
    }
    return true;
}

bool operator!=(RNA &r1, RNA &r2) {
    return !(r1 == r2);
}

RNA RNA::operator!() {
    RNA rna(*this);
    for (size_t i = 0; i < _size; i++) {
        Nucleotide cur = get_nucleotide(i);
        rna.set_nucleotide((Nucleotide)(3 - cur), i);
    }
    return rna;
}

RNA::nucl_ref RNA::operator[](size_t index) {
    return nucl_ref(this, index);
}

//private functions//

void RNA::update_capacity() {
    if (ceil(1.0 * _size / PAIRS_IN_SIZE_T) <= _capacity) return;

    size_t old_capacity = _capacity;
    _capacity = ceil(2.0 * _size / PAIRS_IN_SIZE_T);
    auto *new_seq = new size_t[_capacity];
    for (size_t i = 0; i < old_capacity; i++)
        new_seq[i] = _nucleotides[i];
    for (size_t i = old_capacity; i < _capacity; i++)
        new_seq[i] = fill_nucleotides(_nucl);
    delete [] _nucleotides;
    _nucleotides = new_seq;
}

size_t RNA::fill_nucleotides(Nucleotide nucleotide) {
    size_t res = 0;
    for (size_t i = 0; i < PAIRS_IN_SIZE_T; i++) {
        res <<= 2u;
        res += nucleotide;
    }
    return res;
}

void RNA::add_nucleotide(Nucleotide nucleotide) {
    _size++;
    update_capacity();
    set_nucleotide(nucleotide, _size - 1);
}

Nucleotide RNA::get_nucleotide(size_t idx) {
    if (idx >= _size) _nucl;

    size_t block_idx = idx / PAIRS_IN_SIZE_T, pair_idx = idx % PAIRS_IN_SIZE_T;
    size_t block = _nucleotides[block_idx];
    return (Nucleotide)(((block >> (2u * (PAIRS_IN_SIZE_T - pair_idx - 1u)))) & 3u);
}

void RNA::set_nucleotide(Nucleotide nucleotide, size_t idx) {
    if (idx >= _size) {
        size_t from = _size;
        _size = idx + 1;
        update_capacity();
        for (size_t i = from; i < idx; i++)
            set_nucleotide(_nucl, i);
    }

    size_t block_idx = idx / PAIRS_IN_SIZE_T, pair_idx = idx % PAIRS_IN_SIZE_T;
    size_t block = _nucleotides[block_idx];
    size_t mask = ((size_t)3) << (2u * (PAIRS_IN_SIZE_T - pair_idx - 1));
    size_t nucl = fill_nucleotides(nucleotide) & mask;

    _nucleotides[block_idx] = (block & (~mask)) + nucl;
}
