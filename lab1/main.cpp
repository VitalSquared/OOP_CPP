#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "RNA.h"

using namespace std;

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    int res = RUN_ALL_TESTS();
    return 0;
}
