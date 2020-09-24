#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <ctime>
#include "RNA.h"

using testing::Eq;

namespace {
    class RNATest : public testing::Test {
    public:

    };
}

TEST_F(RNATest, basic_test_1) {
    for (int i = 0; i < 100; i++) {
        RNA rna(A, i);
        ASSERT_EQ(rna.capacity(), ceil(1.0 * i / (sizeof(size_t) * 4)));
    }
}

TEST_F(RNATest, basic_test_2) {
    for (int i = 0; i < 100; i++) {
        RNA rna(A, i);
        ASSERT_EQ(rna.length(), i);
    }
}

TEST_F(RNATest, basic_test_3) {
    RNA rna(A, 0);
    for (int i = 0; i < 100; i++) {
        rna += (Nucleotide) (i % 4);
    }
    for (int i = 0; i < 100; i++) {
        ASSERT_EQ(rna.get_nucleotide(i), (Nucleotide) (i % 4));
    }
}

TEST_F(RNATest, large_test_1) {
    timespec start, end;
    RNA rna(A, 0);
    clock_gettime(CLOCK_MONOTONIC, &start);
    for (int i = 0; i < 500000; i++) {
        rna += (Nucleotide) (i % 4);
        clock_gettime(CLOCK_MONOTONIC, &end);
        auto time = (end.tv_sec - start.tv_sec) + 0.000000001 * (end.tv_nsec - start.tv_nsec);
        ASSERT_LE(time, 60);
    }
}
