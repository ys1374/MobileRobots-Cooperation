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

//std::vector<int> queueOfBinRetrival{};
std::vector<int> binsOnRetrival{};
std::vector<int> queueOfBinStorage{};


const unsigned int filledPercentOfWarehouse{ 50 }; //in %

long long int locationId{ 0 };

unsigned int maxNumOfBins{ xLenghOfWarehouse * yLenghOfWarehouse * zLenghOfWarehouse * filledPercentOfWarehouse / 100 };




int main()
{
	//we need to fill the warehouse with robots and bins objects*************************************

	//filling first robot-----------------------
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

		secondRobotObject.nameFillerSecondRobot(i);
		// inserting objects to vector 
		secondRobotsVector.push_back(secondRobotObject);

		//std::cout << secondRobotsVector[i].id << "\t" << secondRobotsVector[i].name << "\n";
	}

	//bins--------------------------------
	std::vector<Autostore::bin> binsVector;// Vector of class objects
	Autostore::bin binsObject;

	//for (unsigned int i = 0; (i) < (maxNumOfBins); i++) {
	//	binsObject.binFillerWithdata(i);
	//	// inserting objects to vector 
	//	binsVector.push_back(binsObject);
	//	//std::cout << binsVector[i].id << "\t" << binsVector[i].binName << "\n";
	//}


	//creating gridbins location on grid---------------	
	std::vector<std::vector<std::vector<Autostore::gridLocation>>> gridLocationVector(
		xLenghOfWarehouse,
		std::vector<std::vector<Autostore::gridLocation>>(
			yLenghOfWarehouse,
			std::vector<Autostore::gridLocation>(
				zLenghOfWarehouse
				)
			)
	);// Vector of class objects

	Autostore::gridLocation gridLocationObject;//creating object


	for (int k = 0; k < zLenghOfWarehouse; k++) {
		for (int j = 0; j < yLenghOfWarehouse; j++) {
			for (int i = 0; i < xLenghOfWarehouse; i++) {

				gridLocationVector[i][j][k].gridFillerWithBin(i, j, k, locationId);//filling grid vector

				gridLocationVector[i][j][k].xLocation = i;//filling grid vector features
				gridLocationVector[i][j][k].yLocation = j;
				gridLocationVector[i][j][k].zLocation = k;

				if (locationId < maxNumOfBins) { //just fill the locations which bins can take according to filledPercentOfWarehouse
					auto binid = locationId;

					binsObject.binFillerWithdata(binid); 
					binsVector.push_back(binsObject); //filling bins vector




					gridLocationVector[i][j][k].binId = binsVector[binid].binId;
					binsVector[binid].locationId = gridLocationVector[i][j][k].locationId;

					binsVector[binid].locationName = gridLocationVector[i][j][k].locationName;

					binsVector[binid].xLocation = i;
					binsVector[binid].yLocation = j;
					binsVector[binid].zLocation = k;


					//std::cout << "locid" << gridLocationVector[i][j][k].locationId << "\t" << "is assigned to binid" << binsVector[binid].binId << "\n";

				}



				locationId++;
				//std::cout << "locid" << gridLocationVector[i][j][k].locationId << "\t" << gridLocationVector[i][j][k].locationName << "\n";


			}
		}
	}

	std::cout << "Objects on Warehouse all set!\n";


	//make a Queue for retrival from shufling the binsVector
	// 
	// Create an instance of VectorShuffler for Autostore::bin type
	Autostore::VectorShuffler<Autostore::bin> shuffler;

	// Shuffle the binsVector
	std::vector<Autostore::bin> queueOfBinRetrival = shuffler.shuffleVector(binsVector);


	//std::vector<Autostore::bin> binsVector;// Vector of class objects
	//Autostore::bin binsObject;






	//queueOfBinRetrival.erase(queueOfBinRetrival.begin()+2 );





	//the evaluation of warehouse throughput
	while (!queueOfBinRetrival.empty())
	{
		std::cout << "Retrival On Board!\n";
		//for (const auto& bin : queueOfBinRetrival) {
		//    std::cout << bin.binName << "\t" << bin.locationName << "\n";
		//}

		break;
	}
	std::cout << "Empty Retrival Queue!\n";
	std::cout << queueOfBinRetrival[0].binName << "\t" << queueOfBinRetrival[0].locationName << "\n";
}

