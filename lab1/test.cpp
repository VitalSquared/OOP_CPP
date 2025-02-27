#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "RNA.h"

using testing::Eq;

namespace {
    class RNATest : public testing::Test {
    public:

    };
}

TEST_F(RNATest, basic_test_capacity) {
    for (int i = 0; i < 100; i++) {
        RNA rna(A, i);
        ASSERT_GE(rna.capacity(), ceil(1.0 * i / (sizeof(size_t) * 4)));
    }
}

TEST_F(RNATest, basic_test_length) {
    for (int i = 0; i < 100; i++) {
        RNA rna(A, i);
        ASSERT_EQ(rna.length(), i);
    }
}

TEST_F(RNATest, basic_test_get_set) {
    int cnt = 100;
    RNA rna(A, cnt);
    Nucleotide arr[cnt];
    for (int i = 0; i < cnt; i++) {
        arr[i] = (Nucleotide) (rand() % 4);
        rna[i] = arr[i];
    }
    for (int i = 0; i < cnt; i++) {
        ASSERT_EQ(rna[i], arr[i]);
    }
}

TEST_F(RNATest, basic_test_const_get) {
    int cnt = 100;
    const RNA rna(A, cnt);
    for (int i = 0; i < cnt; i++) {
        ASSERT_EQ(rna[i], A);
    }
}

TEST_F(RNATest, basic_test_add) {
    RNA rna(A, 0);
    rna += A;
    rna += G;
    rna += C;
    for (int i = 0; i < 3; i++)
        ASSERT_EQ(rna[i], (Nucleotide) i);
}

TEST_F(RNATest, basic_test_equality) {
    RNA rna(A, 100);
    RNA rna1(rna);
    ASSERT_EQ(true, rna == rna1);
}

TEST_F(RNATest, basic_test_unequality) {
    RNA rna(A, 100);
    RNA rna1(rna);
    rna1 += T;
    ASSERT_EQ(true, rna != rna1);
    rna1.trim(100);
    rna1[50] = T;
    ASSERT_EQ(true, rna != rna1);
}

TEST_F(RNATest, basic_test_set_outside) {
    RNA rna(A, 10);
    rna[19] = G;
    rna[21] = C;
    RNA check(A, 19);
    check += G;
    check += A;
    check += C;
    ASSERT_EQ(true, rna == check);
}

TEST_F(RNATest, basic_test_sum) {
    RNA rna1(A, 10), rna2(T, 10);
    RNA rna = rna1 + rna2;
    for (int i = 0; i < 10; i++)
        ASSERT_EQ(A, rna[i]);
    for (int i = 10; i < 20; i++)
        ASSERT_EQ(T, rna[i]);
}

TEST_F(RNATest, basic_test_trim) {
    RNA rna1(A, 10), rna2(T, 10);
    RNA rna = rna1 + rna2;
    RNA check(A, 5);
    rna.trim(5);
    ASSERT_EQ(true, rna == check);
}

TEST_F(RNATest, basic_test_split) {
    RNA rna1(A, 10), rna2(T, 10);
    RNA rna = rna1 + rna2;
    auto pair = rna.split(10);
    ASSERT_EQ(true, pair.first == rna1 && pair.second == rna2);
}

TEST_F(RNATest, basic_test_not) {
    RNA rna1(G, 10), rna2(T, 15), rna3(C, 5);
    RNA rna_ = rna1 + rna2;
    RNA rna = rna_ + rna3;
    RNA _rna = !rna;
    for (int i = 0; i < 10; i++)
        ASSERT_EQ(C, _rna[i]);
    for (int i = 10; i < 25; i++)
        ASSERT_EQ(A, _rna[i]);
    for (int i = 25; i < 30; i++)
        ASSERT_EQ(G, _rna[i]);
}

TEST_F(RNATest, basic_test_complementary) {
    RNA rna1(G, 10), rna2(C, 10);
    RNA _rna1 = !rna1;
    ASSERT_EQ(true, rna1.is_complementary(rna2));
    ASSERT_EQ(true, rna1.is_complementary(_rna1));
}

TEST_F(RNATest, basic_test_cardinality) {
    RNA rna1(A, 0);
    for (int i = 0; i < 5; i++)
        rna1 += A;
    for (int i = 0; i < 7; i++)
        rna1 += G;
    for (int i = 0; i < 4; i++)
        rna1 += C;
    for (int i = 0; i < 13; i++)
        rna1 += T;
    ASSERT_EQ(5, rna1.cardinality(A));
    ASSERT_EQ(7, rna1.cardinality(G));
    ASSERT_EQ(4, rna1.cardinality(C));
    ASSERT_EQ(13, rna1.cardinality(T));

    auto map = rna1.cardinality();
    for (auto elem : map) {
        Nucleotide nucl = elem.first;
        switch (nucl) {
            case A:
                ASSERT_EQ(5, elem.second);
                break;
            case G:
                ASSERT_EQ(7, elem.second);
                break;
            case C:
                ASSERT_EQ(4, elem.second);
                break;
            case T:
                ASSERT_EQ(13, elem.second);
                break;
        }
    }
}

TEST_F(RNATest, large_test) {
    RNA rna(A, 0);
    for (int i = 0; i < 1000000; i++) {
        rna += (Nucleotide) (i % 4);
    }
    rna.trim(0);
    rna.trim(0);
}