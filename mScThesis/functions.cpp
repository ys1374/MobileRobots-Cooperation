#include "Autostore.h"
#include <cmath>
#include <iostream>
using uint = unsigned int;
#include <random>


int generateRandomNumber(int max_) {
    // Static to initialize the seed and engine only once
    static std::random_device rd; // Obtain a random number from hardware
    static std::mt19937 eng(rd()); // Seed the generator

    std::uniform_int_distribution<> distr(0, max_); // Define the range

    return distr(eng); // Generate and return the random number
}



