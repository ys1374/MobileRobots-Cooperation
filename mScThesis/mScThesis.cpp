#include <iostream>
#include "Autostore.h"
#include "AStar.h"
#include <vector>



const unsigned int filledPercentOfWarehouse{ 60 }; //in %


// ************** if changed these 3 delete files************************
const unsigned int xLenghOfWarehouse{ 30 }; //max x size of gird
const unsigned int yLenghOfWarehouse{ 30 }; //max y size of gird
const unsigned int zLenghOfWarehouse{ 20 }; //max num of bins in a column
const unsigned int numOfFirstRobots{ 3 };
const unsigned int numOfSecondRobots{ 3 };
//***********************************************************************




double hightOfBin{ 0.33 };


long long int locationId{ 0 };
long long int retrivalTaskId{ 0 };

unsigned int maxNumOfBins{ xLenghOfWarehouse * yLenghOfWarehouse * zLenghOfWarehouse * filledPercentOfWarehouse / 100 };


//functions-----------------------
int generateRandomNumber(int max);
void saveVectorToFile(const std::vector<Autostore::bin>& vec, const std::string& filename);
void fillQueueOfBinRetrival(std::vector<Autostore::bin>& queueOfBinRetrival, const std::string& filename, std::vector<Autostore::bin> binsVector_);
void fillFirstRobotLocation(std::vector<Autostore::firstRobot>& firstRobotsVector_, const std::string& filename_);
//--------------------------------



int main()
{	
	int excludedGridLocations[10][10] = {
	{xLenghOfWarehouse / 2 , 0, 0},
	{0 , yLenghOfWarehouse / 2 , 1},
	{xLenghOfWarehouse - 1, yLenghOfWarehouse / 2, 2}
	};
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
	//------------------------------------------

	//port objects---------------------------------
	std::vector<Autostore::port> portsVector;// Vector of class objects
	Autostore::port portObject;
	//---------------------------------------------
	
	//fill locations and bins--------------------------------------------------------------------------------
	for (int k = 0; k < zLenghOfWarehouse; k++) {
		for (int j = 0; j < yLenghOfWarehouse; j++) {
			for (int i = 0; i < xLenghOfWarehouse; i++) {

				gridLocationVector[i][j][k].gridFillerWithBin(i, j, k, locationId);//filling grid vector

				gridLocationVector[i][j][k].xLocation = i;//filling grid vector features
				gridLocationVector[i][j][k].yLocation = j;
				gridLocationVector[i][j][k].zLocation = k;


				//ports excluded top grid location for --------
				//for (auto excludedpoints : excludedGridLocations) {
				//	if (i == excludedpoints[0] && j == excludedpoints[1]) {


				//		if (k == 0) {
				//			//std::cout << "port is 0:" << i << " " << j << "\n";
				//			portObject.xLocation = i;
				//			portObject.yLocation = j;

				//			portObject.id = excludedpoints[2];

				//			portsVector.push_back(portObject);
				//		}


				//		goto label;
				//	}
				//}





				if (i== xLenghOfWarehouse/2 &&j== 0) {

					

					if (k == 0) {
						//std::cout << "port is 0:" << i << " " << j << "\n";
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
						//std::cout << "port is 1:" << i << " " << j << "\n";
						portObject.xLocation = i;
						portObject.yLocation = j;

						portObject.id = 1;

						portsVector.push_back(portObject);
					}


					continue;
				}
				if (i == xLenghOfWarehouse-1 && j == yLenghOfWarehouse/2)
				{
					
					if (k == 0) {
						//std::cout << "port is 2:" << i << " " << j << "\n";
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

	fillFirstRobotLocation(firstRobotsVector, "robots_locations.txt");

	std::cout << "Objects on Warehouse all set!\n";

	//-------------------------------------------------------------------------------------------------------


	//make a Queue for retrival from shufling the binsVector-----------------
	std::vector<Autostore::bin> queueOfBinRetrival;
	queueOfBinRetrival.reserve(maxNumOfBins);

	// read file if file exist fill the retrival queue with file if not it generate new from binsVector shuffle
	fillQueueOfBinRetrival(queueOfBinRetrival, "queueOfBinRetrival.txt", binsVector);
	//-----------------------------------------------------------------------

	//filling retrivalTaskObject--------------------------------------------------------------
	Autostore::retrivalTask retrivalTaskObject;
	std::vector<Autostore::retrivalTask> finishedRetriveTaskVector;

	retrivalTaskObject.portsVector = portsVector;
	retrivalTaskObject.firstRobotsVector = firstRobotsVector;
	retrivalTaskObject.secondRobotsVector = secondRobotsVector;
	retrivalTaskObject.binsVector = binsVector;
	retrivalTaskObject.gridLocationVector = gridLocationVector;

	retrivalTaskObject.mainPortsVector = &portsVector;
	retrivalTaskObject.mainFirstRobotsVector = &firstRobotsVector;
	retrivalTaskObject.mainSecondRobotsVector = &secondRobotsVector;
	retrivalTaskObject.mainBinsVector = &binsVector;
	retrivalTaskObject.mainGridLocationVector = &gridLocationVector;

	retrivalTaskObject.vectorsFiller();
	//---------------------------------------------------------------------------------------
	retrivalTaskObject.constants.xLenghOfWarehouse = xLenghOfWarehouse;
	retrivalTaskObject.constants.yLenghOfWarehouse = yLenghOfWarehouse;
	retrivalTaskObject.constants.zLenghOfWarehouse = zLenghOfWarehouse;
	retrivalTaskObject.constants.hightOfBin = hightOfBin;
	

	
	//the evaluation of warehouse throughput
	while (!queueOfBinRetrival.empty())
	{	
		std::cout << "\n\nRetriving " << queueOfBinRetrival[0].locationName << " is on Track\n";

		retrivalTaskObject.reset();
		retrivalTaskObject.id = retrivalTaskId;
		retrivalTaskObject.binToRetrive = queueOfBinRetrival[0];

		retrivalTaskObject.firstRobotSelection();
		retrivalTaskObject.portSelection();
		
		double cycleTime = retrivalTaskObject.cycleTime();

		firstRobotsVector[retrivalTaskObject.selectedfirstRobot.id].time = firstRobotsVector[retrivalTaskObject.selectedfirstRobot.id].time + cycleTime;

		std::cout << "Finished Retriving " << queueOfBinRetrival[0].locationName << 
			". CycleTime: " << cycleTime << " Robot Id: " << retrivalTaskObject.selectedfirstRobot.id
			<< " RobotTime: " << firstRobotsVector[retrivalTaskObject.selectedfirstRobot.id].time;
		
		
		finishedRetriveTaskVector.push_back(retrivalTaskObject);
		queueOfBinRetrival.erase(queueOfBinRetrival.begin());
		

#if 1
		if (firstRobotsVector[retrivalTaskObject.selectedfirstRobot.id].time >= (60 * 60)) {
			std::cout << "\n\n\n************************One Hour is Passed**************************\n\n\n";

			for (auto robot : firstRobotsVector) {
				std::cout << "Robot Id:" << robot.id << " Robot time: " << robot.time << "\n";
			}

			std::cout << finishedRetriveTaskVector.size();
			break;
		}
		
#endif
		
		
	}

	if (queueOfBinRetrival.empty()){std::cout << "\n\nEmpty Retrival Queue!\n";}
	else{ std::cout << "\n\nRetrival Queue Not Empty Or Something Wrong!\n"; }
	


	//std::cout << queueOfBinRetrival[0].binName << "\t" << queueOfBinRetrival[0].locationName << "\n";
	return 0;
}

