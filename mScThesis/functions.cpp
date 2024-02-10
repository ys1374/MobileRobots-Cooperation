#include "Autostore.h"
#include <cmath>
#include <iostream>
using uint = unsigned int;
#include <random>
#include <fstream>
#include <vector>


int generateRandomNumber(int max_) {
    // Static to initialize the seed and engine only once
    static std::random_device rd; // Obtain a random number from hardware
    static std::mt19937 eng(rd()); // Seed the generator

    std::uniform_int_distribution<> distr(0, max_); // Define the range

    return distr(eng); // Generate and return the random number
}


void saveVectorToFile(const std::vector<Autostore::bin>& vec_, const std::string& filename) {
    std::ofstream fileOut(filename, std::ios::binary);
    if (!fileOut) {
        throw std::runtime_error("Cannot open file for writing");
    }

    for (const auto& item : vec_) {
        fileOut << item << "\n";
    }
}

void loadVectorFromFile(std::vector<Autostore::bin>& queueOfBinRetrival_, const std::string& filename_, std::vector<Autostore::bin> binsVector_) {
    std::ifstream fileIn(filename_, std::ios::binary);
    if (!fileIn) {
        throw std::runtime_error("Cannot open file for reading");
    }

    Autostore::bin item;
    while (fileIn >> item) {
        queueOfBinRetrival_.push_back(binsVector_[item.binId]);
        //std::cout << item.binId;
    }
}


bool fileExists(const std::string& filename) {
    std::ifstream file(filename);
    return file.good();
}

void fillQueueOfBinRetrival(std::vector<Autostore::bin>& queueOfBinRetrival, const std::string& filename_, std::vector<Autostore::bin> binsVector_) {
    if (fileExists(filename_)) {
        // File exists, load vector from file
        loadVectorFromFile(queueOfBinRetrival, filename_, binsVector_);
        std::cout << "Loaded from file." << std::endl;
    }
    else {
        Autostore::VectorShuffler<Autostore::bin> shuffler;
        queueOfBinRetrival = shuffler.shuffleVector(binsVector_);

        // Optionally, save the newly filled vector to file
        saveVectorToFile(queueOfBinRetrival, filename_);
        std::cout << "Filled regularly and saved to file." << std::endl;
    }
}



