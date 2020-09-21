#include <iostream>
#include "RNA.h"

using namespace std;

int main() {
    RNA rna(C, 0);
    for (size_t i = 0; i < 100; i++)
        rna += (Nucleotide)(i % 4);
    rna.print_rna();
    rna.trim(10);
    rna.print_rna();
    return 0;
}
