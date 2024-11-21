//
// Created by volta on 21/11/2024.
//
#include "gtest/gtest.h"
#include <iostream>


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    int result = RUN_ALL_TESTS();
    std::cout << "Risultato test: " << result << std::endl;
    return result;
}