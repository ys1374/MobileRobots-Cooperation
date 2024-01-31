#include "D:\Projects\MSc\Thesis\Simulation\Learn\Astar\as2\a-star-master\source\AStar.hpp"
#include <iostream>
#include "Autostore.h"
#include <vector>

const unsigned int xLenghOfWarehouse{ 20 }; //x direction of gird
const unsigned int yLenghOfWarehouse{ 20 }; //y direction of gird
const unsigned int zLenghOfWarehouse{ 20 }; //max num of bins in a column

const unsigned int numOfFirstRobots{ 3 };
int numOfAvailableFirstRobots{ numOfFirstRobots };

const unsigned int numOfSecondRobots{ 3 };
int numOfAvailableSecondRobots{ numOfSecondRobots };

std::vector<int> queueOfBinRetrival{};
std::vector<int> binsOnRetrival{};
std::vector<int> queueOfBinStorage{};


const unsigned int filledPercentOfWarehouse{ 63 }; //in %

long long int binId{0};

unsigned int maxNumOfBins{ xLenghOfWarehouse * yLenghOfWarehouse * zLenghOfWarehouse * filledPercentOfWarehouse / 100 };

//std::string binNamesOnGrid[xLenghOfWarehouse][yLenghOfWarehouse][zLenghOfWarehouse]{};




int main()
{
	
	//we need to fill the warehouse with robots and bins objects
	
	
	//filling robots objects for robots

	//first robot-----------------------
	std::vector<Autostore::firstRobot> firstRobotsVector;// Vector of class objects
	Autostore::firstRobot firstRobotObject;

	for (int i = 0; i < numOfFirstRobots; i++) {
		// getting the random values from 
		// functions 
		firstRobotObject.nameFillerFirstRobot(i);
		// inserting objects to vector 
		firstRobotsVector.push_back(firstRobotObject);

		//std::cout << firstRobotsVector[i].id << "\t" << firstRobotsVector[i].name << "\n";
	}

	//second robot-----------------------
	std::vector<Autostore::secondRobot> secondRobotsVector;// Vector of class objects
	Autostore::secondRobot secondRobotObject;

	for (int i = 0; i < numOfSecondRobots; i++) {
		// getting the random values from 
		// functions 
		secondRobotObject.nameFillerSecondRobot(i);
		// inserting objects to vector 
		secondRobotsVector.push_back(secondRobotObject);

		//std::cout << secondRobotsVector[i].id << "\t" << secondRobotsVector[i].name << "\n";
	}

	//bins--------------------------------	
	std::vector<std::vector<std::vector<Autostore::bin>>> binsVector(
		xLenghOfWarehouse,
		std::vector<std::vector<Autostore::bin>>(
			yLenghOfWarehouse,
			std::vector<Autostore::bin>(
				zLenghOfWarehouse
				)
			)
	);// Vector of class objects
	
	Autostore::bin binsObject;

	for (int k = 0; k < zLenghOfWarehouse; k++) {
		for (int j = 0; j < yLenghOfWarehouse; j++) {
			for (int i = 0; i < xLenghOfWarehouse; i++) {
				
				binsVector[i][j][k].nameFillerBin(i, j, k, binId);
				binId++;
				//std::cout << "binsVector[" << i << "][" << j << "][" << k << "] = " << binsVector[i][j][k].id << "\t" << binsVector[i][j][k].name << "\n";
				if (binId == maxNumOfBins) { goto forward; }
				
			}
		}
	}

	


forward:
	std::cout << "Warehouse all set!";


	
	
	
	
	//the evaluation of warehouse throughput
	while (!queueOfBinRetrival.empty())
	{
		std::cout << "Retrival On Board!";
	}
	std::cout << "Empty Retrival Queue!";

}

