#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "RNA.h"

using namespace std;

int main(int argc, char* argv[]) {
    /*RNA rna(C, 0);
    for (size_t i = 0; i < 100; i++)
        rna += (Nucleotide) (i % 4);
    rna.print_rna();
    rna.trim(10);
    rna.print_rna();*/

    testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();
    return 0;
}
