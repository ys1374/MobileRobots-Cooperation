#include "Autostore.h"
#include <cmath>
#include <iostream>
using uint = unsigned int;
#include <random>
#include <fstream>
#include <vector>
#include <sstream>




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
        //fileOut << robot.id << " " << robot.xLocation << " " << robot.yLocation << "\n";
        fileOut << item.binId << "\n";
    }
}

void loadVectorFromFile(std::vector<Autostore::bin>& queueOfBinRetrival_, const std::string& filename_, std::vector<Autostore::bin> binsVector_) {
    std::ifstream fileIn(filename_, std::ios::binary);
    if (!fileIn) {
        throw std::runtime_error("Cannot open file for reading");
    }

    int binId;
    while (fileIn >> binId) {
        
        queueOfBinRetrival_.push_back(binsVector_[binId]);
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
        std::cout << "Loaded Queue from file." << std::endl;
    }
    else {
        Autostore::VectorShuffler<Autostore::bin> shuffler;
        queueOfBinRetrival = shuffler.shuffleVector(binsVector_);
        //std::cout << "Test line\n";
        // Optionally, save the newly filled vector to file
        saveVectorToFile(queueOfBinRetrival, filename_);
        std::cout << "Queue Filled regularly and saved to file." << std::endl;
    }
}


///////for first robot-----------------------------------

void saveFirstRobotLocations(const std::vector<Autostore::firstRobot>& firstRobotsVector_, const std::string& filename_) {
    std::ofstream fileOut(filename_);
    if (!fileOut) {
        throw std::runtime_error("Cannot open file for writing");
    }

    for (auto& robot : firstRobotsVector_) {
        fileOut << robot.id << " " << robot.xLocation << " " << robot.yLocation << "\n";
    }
}


void loadFirstRobotLocations(std::vector<Autostore::firstRobot>& firstRobotsVector_, const std::string& filename) {
    std::ifstream fileIn(filename);
    if (!fileIn) {
        throw std::runtime_error("Cannot open file for reading");
    }

    //robots.clear(); // Clear existing data
    int x, y, id;

    while (fileIn >> id >> x >> y) {
        firstRobotsVector_[id].xLocation = x;
        firstRobotsVector_[id].yLocation = y;
        //robots.emplace_back(x, y, id);
        //std::cout << id;
    }
}


void fillFirstRobotLocation(std::vector<Autostore::firstRobot>& firstRobotsVector_, const std::string& filename_) {
    if (fileExists(filename_)) {
        // File exists, load vector from file
        loadFirstRobotLocations(firstRobotsVector_, filename_);
        std::cout << "Loaded robots location from file." << std::endl;
    }
    else {
        // Optionally, save the newly filled vector to file
        saveFirstRobotLocations(firstRobotsVector_, filename_);
        std::cout << "Filled robots regularly and saved to file." << std::endl;
    }
}


//second robot ----------------------------------------------------------------------------------------------------
void saveSecondRobotLocations(const std::vector<Autostore::secondRobot>& secondRobotsVector_, const std::string& filename_) {
    std::ofstream fileOut(filename_);
    if (!fileOut) {
        throw std::runtime_error("Cannot open file for writing");
    }

    for (auto& robot : secondRobotsVector_) {
        fileOut << robot.id << " " << robot.xLocation << " " << robot.yLocation << "\n";
    }
}


void loadSecondRobotLocations(std::vector<Autostore::secondRobot>& secondRobotsVector_, const std::string& filename_) {
    std::ifstream fileIn(filename_);
    if (!fileIn) {
        throw std::runtime_error("Cannot open file for reading");
    }

    //robots.clear(); // Clear existing data
    int x, y, id;

    while (fileIn >> id >> x >> y) {
        secondRobotsVector_[id].xLocation = x;
        secondRobotsVector_[id].yLocation = y;
        //robots.emplace_back(x, y, id);
        //std::cout << id;
    }
}


void fillSecondRobotLocation(std::vector<Autostore::secondRobot>& secondRobotsVector_, const std::string& filename_) {
    if (fileExists(filename_)) {
        // File exists, load vector from file
        loadSecondRobotLocations(secondRobotsVector_, filename_);
        std::cout << "Loaded 2nd robots location from file." << std::endl;
    }
    else {
        // Optionally, save the newly filled vector to file
        saveSecondRobotLocations(secondRobotsVector_, filename_);
        std::cout << "Filled 2nd robots regularly and saved to file." << std::endl;
    }
}


void fillExcelFileCycleTime(lxw_worksheet* worksheet, double cycleTime_, const int column_, const int row_) {
    worksheet_write_number(worksheet, row_, column_, cycleTime_, NULL);
}
