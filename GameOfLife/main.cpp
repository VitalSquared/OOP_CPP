#include <iostream>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Interface.h"

using namespace std;

int main() {
    //testing::InitGoogleTest();
    //int res = RUN_ALL_TESTS();
    //return 0;

    Interface interface(10, 10);
    interface.run();
    return 0;
}
