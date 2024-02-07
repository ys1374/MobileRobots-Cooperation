#include "D:\Projects\MSc\Thesis\Simulation\Learn\Astar\as2\a-star-master\source\AStar.hpp"
#include <iostream>
#include "Autostore.h"
#include <vector>





const unsigned int xLenghOfWarehouse{ 30 }; //max x size of gird
const unsigned int yLenghOfWarehouse{ 30 }; //max y size of gird
const unsigned int zLenghOfWarehouse{ 20 }; //max num of bins in a column

const unsigned int numOfFirstRobots{ 10 };
int numOfAvailableFirstRobots{ numOfFirstRobots };

const unsigned int numOfSecondRobots{ 3 };
int numOfAvailableSecondRobots{ numOfSecondRobots };

//std::vector<int> queueOfBinRetrival{};
std::vector<int> binsOnRetrival{};
std::vector<int> queueOfBinStorage{};


const unsigned int filledPercentOfWarehouse{ 50 }; //in %

long long int locationId{ 0 };
long long int retrivalTaskId{ 0 };

unsigned int maxNumOfBins{ xLenghOfWarehouse * yLenghOfWarehouse * zLenghOfWarehouse * filledPercentOfWarehouse / 100 };


//functions-----------------------
int generateRandomNumber(int max);
//--------------------------------



int main()
{
	//we need to fill the warehouse with robots and bins objects*************************************

	//filling first robot-----------------------
	std::vector<Autostore::firstRobot> firstRobotsVector;// Vector of class objects
	Autostore::firstRobot firstRobotObject;

	for (int i = 0; i < numOfFirstRobots; i++) {
		firstRobotObject.nameFillerFirstRobot(i);
		firstRobotObject.xLocation = generateRandomNumber(xLenghOfWarehouse);
		firstRobotObject.yLocation = generateRandomNumber(yLenghOfWarehouse);
		// inserting objects to vector 
		firstRobotsVector.push_back(firstRobotObject);

		//std::cout << firstRobotsVector[i].id << "\t" << firstRobotsVector[i].name << "\n";
	}
	//------------------------------------------

	//second robot------------------------------
	std::vector<Autostore::secondRobot> secondRobotsVector;// Vector of class objects
	Autostore::secondRobot secondRobotObject;

	for (int i = 0; i < numOfSecondRobots; i++) {

		secondRobotObject.nameFillerSecondRobot(i);
		// inserting objects to vector 
		secondRobotsVector.push_back(secondRobotObject);

		//std::cout << secondRobotsVector[i].id << "\t" << secondRobotsVector[i].name << "\n";
	}
	//------------------------------------------

	//bins--------------------------------------
	std::vector<Autostore::bin> binsVector;// Vector of class objects
	Autostore::bin binsObject;

	//for (unsigned int i = 0; (i) < (maxNumOfBins); i++) {
	//	binsObject.binFillerWithdata(i);
	//	// inserting objects to vector 
	//	binsVector.push_back(binsObject);
	//	//std::cout << binsVector[i].id << "\t" << binsVector[i].binName << "\n";
	//}
	//------------------------------------------


	//creating gridbins location on grid--------
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


	//port objects---------------------------------
	std::vector<Autostore::port> portsVector;// Vector of class objects
	Autostore::port portObject;
	//---------------------------------------------


	for (int k = 0; k < zLenghOfWarehouse; k++) {
		for (int j = 0; j < yLenghOfWarehouse; j++) {
			for (int i = 0; i < xLenghOfWarehouse; i++) {



				gridLocationVector[i][j][k].gridFillerWithBin(i, j, k, locationId);//filling grid vector

				gridLocationVector[i][j][k].xLocation = i;//filling grid vector features
				gridLocationVector[i][j][k].yLocation = j;
				gridLocationVector[i][j][k].zLocation = k;


				//ports excluded top grid location for --------
				if (i== xLenghOfWarehouse/2 &&j== 0) {

					if (k == 0) {
						portObject.xLocation = i;
						portObject.yLocation = j;

						portObject.id = 0;

						portsVector.push_back(portObject);
					}


					continue;
				}
				if (i == 0 && j == yLenghOfWarehouse / 2)
				{
					if (k == 0) {
						portObject.xLocation = i;
						portObject.yLocation = j;

						portObject.id = 1;

						portsVector.push_back(portObject);
					}


					continue;
				}
				if (i == xLenghOfWarehouse && j == yLenghOfWarehouse)
				{
					if (k == 0) {
						portObject.xLocation = i;
						portObject.yLocation = j;

						portObject.id = 2;

						portsVector.push_back(portObject);
					}


					continue;
				}

				//----------------------------------------------

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

	//------------------------------------------


	//make a Queue for retrival from shufling the binsVector--------
	// 
	// Create an instance of VectorShuffler for Autostore::bin type
	Autostore::VectorShuffler<Autostore::bin> shuffler;

	// Shuffle the binsVector
	std::vector<Autostore::bin> queueOfBinRetrival = shuffler.shuffleVector(binsVector);
	//--------------------------------------------------------------


	//std::vector<Autostore::bin> binsVector;// Vector of class objects
	//Autostore::bin binsObject;





	/*size(firstRobotsVector);*/


	//for (auto& firstRobot : binsVector) {
	//	//firstRobot.time = firstRobot.time + cycleTime;

	//	std::cout << firstRobot.locationName <<  "\n";
	//}

	
	//double cycleTime(Autostore::bin, Autostore::firstRobot);


	std::vector<Autostore::retrivalTask> retrivalTaskVector;// Vector of class objects
	Autostore::retrivalTask retrivalTaskObject;

	//for (unsigned int i = 0; (i) < (maxNumOfBins); i++) {
	//	binsObject.binFillerWithdata(i);
	//	// inserting objects to vector 
	//	binsVector.push_back(binsObject);
	//	//std::cout << binsVector[i].id << "\t" << binsVector[i].binName << "\n";
	//}

	
	//the evaluation of warehouse throughput
	while (!queueOfBinRetrival.empty())//every time when all robots assigned comes back and checks
	{	
		retrivalTaskObject.id = retrivalTaskId;

		retrivalTaskObject.firstRobotSelection(queueOfBinRetrival[0], firstRobotsVector);

		retrivalTaskObject.portSelection(queueOfBinRetrival[0], portsVector);
		std::cout<< "robot id" << retrivalTaskObject.selectedfirstRobotId << "\tport id:" << retrivalTaskObject.selectedPortId <<"\n";

		retrivalTaskVector.push_back(retrivalTaskObject);
		
		
		//std::cout << "hii\n";
		//// for just first robot version of code
		//for (auto& firstRobot : firstRobotsVector) {
		//	if (queueOfBinRetrival.empty()) { break; }

		//	retrivalTaskObject.id = retrivalTaskId;
		//	retrivalTaskObject.robotSelection
		//	retrivalTaskVector.push_back(retrivalTaskObject);

		//	
		//	firstRobot.time = firstRobot.time + retrivalTaskObject.cycleTime(queueOfBinRetrival[0], firstRobot);


		//	std::cout << firstRobot.name << " " << "time:" << firstRobot.time << "\t" << "retrival task id:" << retrivalTaskObject.id << "\n";
		//	queueOfBinRetrival.erase(queueOfBinRetrival.begin());

		//	retrivalTaskId++;
		//}



		//if (queueOfBinRetrival.empty()) { break; }
		//std::cout << "Retrival On Board!\n";

		//queueOfBinRetrival[0];


		//std::cout << binsVector[0].binName << "\t" << queueOfBinRetrival[0].locationName << "\n";



		
		queueOfBinRetrival.erase(queueOfBinRetrival.begin());

		//break;
	}

	if (queueOfBinRetrival.empty()){std::cout << "Empty Retrival Queue!\n";}
	else{ std::cout << "Something Wrong!\n"; }
	


	//std::cout << queueOfBinRetrival[0].binName << "\t" << queueOfBinRetrival[0].locationName << "\n";
}

