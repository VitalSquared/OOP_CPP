#include <iostream>
#include <cstring>
#include <cmath>
#include <unordered_map>
#include "RNK.h"

//PUBLIC FUNCTIONS//

RNK::RNK(Nucleotide nucleotide, size_t capacity) {
    _capacity = capacity;
    _length = capacity;

    if (capacity == 0) {
        _nucleotides = nullptr;
    }
    else {
        _nucleotides = (char *) calloc(capacity_string_length(), sizeof(char));
        char value = (((((nucleotide << 2) + nucleotide) << 2) + nucleotide) << 2) + nucleotide;
        std::fill(_nucleotides, _nucleotides + capacity_string_length(), value);
    }
}

RNK::RNK(const RNK &rnk) {
    _capacity = rnk._capacity;
    _length = rnk._length;
    _nucleotides = (char *)calloc(capacity_string_length(), sizeof(char));
    memcpy((void *) _nucleotides, rnk._nucleotides, length_string_length());
}

RNK::~RNK() {
    free(_nucleotides);
}

size_t RNK::capacity() {
    return _capacity;
}

size_t RNK::length() {
    return _length;
}

size_t RNK::cardinality(Nucleotide nucleotide) {
    size_t cnt = 0;
    for (size_t i = 0; i < _length; i++) {
        Nucleotide cur = get_nucleotide(i);
        if (cur == nucleotide) cnt++;
    }
    return cnt;
}
unordered_map<Nucleotide, int> RNK::cardinality() {
    unordered_map<Nucleotide, int> map;

    int cnt[4] = { 0 };
    for (size_t i = 0; i < _length; i++) {
        Nucleotide cur = get_nucleotide(i);
        cnt[cur]++;
    }

    for (int i = 0; i < 4; i++) map.insert(make_pair((Nucleotide)i, cnt[i]));
    return map;
}

void RNK::trim(size_t idx) {
    if (idx >= _length) return;
    _length = idx;
}

//operators

RNK operator+ (RNK &r1, RNK &r2) {
    size_t len1 = r1.length(), len2 = r2.length();
    RNK new_rnk(A, r1.capacity() + r2.capacity());
    new_rnk._length = 0;
    for (size_t i = 0; i < len1; i++) new_rnk.add_nucleotide(r1.get_nucleotide(i));
    for (size_t i = 0; i < len2; i++) new_rnk.add_nucleotide(r2.get_nucleotide(i));
    return new_rnk;
}

bool operator== (RNK &r1, RNK &r2) {
    size_t len1 = r1.length(), len2 = r2.length();
    if (len1 != len2) return false;

    for (size_t i = 0; i < len1; i++) {
        Nucleotide n1 = r1.get_nucleotide(i), n2 = r2.get_nucleotide(i);
        if (n1 != n2) return false;
    }

    return true;
}

bool operator!= (RNK &r1, RNK &r2) {
    return !(r1 == r2);
}

Nucleotide RNK::operator[] (size_t idx) {
    return get_nucleotide(idx);
}

//helping functions

char RNK::get_char_representation(Nucleotide nucleotide) {
    char n = 'A';
    switch(nucleotide) {
        case A: n = 'A'; break;
        case G: n = 'G'; break;
        case C: n = 'C'; break;
        case T: n = 'T'; break;
    }
    return n;
}

void RNK::print_RNK() {
    for (size_t i = 0; i < _length; i++) {
        cout << get_char_representation(get_nucleotide(i));
    }
    cout << endl;
}

//PRIVATE FUNCTIONS//

size_t RNK::capacity_string_length() {
    return (size_t)ceil(_capacity / 4.0);
}

size_t RNK::length_string_length() {
    return (size_t)ceil(_length / 4.0);
}

Nucleotide RNK::get_nucleotide(size_t idx) {
    size_t block_idx = idx / 4, i = idx % 4;
    char block = _nucleotides[block_idx];
    return (Nucleotide)(((block >> (2 * (3 - i))) & 0b00000011));
}

void RNK::add_nucleotide(Nucleotide nucleotide) {
    if (_length >= _capacity) return;

    _length++;
    int i = (_length - 1) % 4;
    char last = _nucleotides[length_string_length() - 1];
    char mask = i == 0 ? 0 : i == 1 ? 0b11000000 : i == 2 ? 0b11110000 : 0b11111100;
    _nucleotides[length_string_length() - 1] = (last & mask) + ((nucleotide << (2 * (3 - i)) & (~mask)));
}