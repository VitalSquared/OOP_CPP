#include <iostream>
#include "RNA.h"

using namespace std;

int main() {
    RNA rna(A, 10000000);
    for (size_t i = 0; i < 1000; i++)
        rna += C;
    rna.print_rna();
    return 0;
}
