#include <iostream>
#include "Autostore.h"
#include "AStar.h"
#include <vector>



const unsigned int filledPercentOfWarehouse{ 80 }; //in %
double shiftHours{ 8 };

// ************** if changed these 3 delete files************************
const unsigned int xLenghOfWarehouse{ 30 }; //max x size of gird
const unsigned int yLenghOfWarehouse{ 30 }; //max y size of gird
const unsigned int zLenghOfWarehouse{ 20 }; //max num of bins in a column
const unsigned int numOfFirstRobots{ 2 };
const unsigned int numOfSecondRobots{ 3 };
const unsigned int numOfPorts{ 3 };
//***********************************************************************







long long int locationId{ 0 }, binId{ 0 };
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
	int PortLocations[3][3] = {
	{xLenghOfWarehouse / 2 , 0, 0},
	{0 , yLenghOfWarehouse / 2 , 1},
	{xLenghOfWarehouse - 1, yLenghOfWarehouse / 2, 2}
	};

	//port objects---------------------------------
	std::vector<Autostore::port> portsVector;// Vector of class objects
	Autostore::port portObject;

	for (auto port : PortLocations) {
		portObject.xLocation = port[0];
		portObject.yLocation = port[1];

		portObject.id = port[2];

		portsVector.push_back(portObject);
	}
	//---------------------------------------------


	 
	 
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


	
	//fill locations and bins--------------------------------------------------------------------------------
	for (int k = 0; k < zLenghOfWarehouse; k++) {
		for (int j = 0; j < yLenghOfWarehouse; j++) {
			for (int i = 0; i < xLenghOfWarehouse; i++) {

				//std::cout << "i" << i << "j" << j << "k" << k << "\n";

				gridLocationVector[i][j][k].gridFillerWithBin(i, j, k, locationId);//filling grid vector


				if (i == 15 && j ==2) {
					std::cout << "";
				}

				//ports excluded top grid location for --------
				for (auto port : PortLocations) {
					if (i == port[0] && j == port[1]) { goto skipFillingBins; }
				}

				//----------------------------------------------
				if (locationId < maxNumOfBins) { //just fill the locations which bins can take according to filledPercentOfWarehouse

					

					binsObject.binFillerWithdata(i, j, k, binId);
					binsObject.locationId = locationId;
					binsObject.locationName = gridLocationVector[i][j][k].locationName;

					binsVector.push_back(binsObject); //filling bins vector

					gridLocationVector[i][j][k].binId = binId;
					gridLocationVector[i][j][k].isFilledWithBin = true;





					binId++;

					//std::cout << "locid" << gridLocationVector[i][j][k].locationId << "\t" << "is assigned to binid" << binsVector[binid].binId << "\n";

				}




			
			skipFillingBins:

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
	Autostore::retrivalTask retrivalTaskObject(portsVector, firstRobotsVector, secondRobotsVector, binsVector, gridLocationVector);
	std::vector<Autostore::retrivalTask> finishedRetriveTaskVector;


	retrivalTaskObject.constants.xLenghOfWarehouse = xLenghOfWarehouse;
	retrivalTaskObject.constants.yLenghOfWarehouse = yLenghOfWarehouse;
	retrivalTaskObject.constants.zLenghOfWarehouse = zLenghOfWarehouse;
	//retrivalTaskObject.constants.hightOfBin = hightOfBin;
	//---------------------------------------------------------------------------------------

	

	
	//the evaluation of warehouse throughput
	while (!queueOfBinRetrival.empty())
	{	
		std::cout << "\n\nRetriving " << queueOfBinRetrival[0].locationName << " is on Track     ";
		if (queueOfBinRetrival[0].xLocation == 0 && queueOfBinRetrival[0].yLocation == 0) {
			queueOfBinRetrival.erase(queueOfBinRetrival.begin());
		}



		retrivalTaskObject.reset();
		retrivalTaskObject.id = retrivalTaskId;
		retrivalTaskObject.binToRetrive = binsVector[queueOfBinRetrival[0].binId];
		retrivalTaskObject.binToRetrive_ = &binsVector[queueOfBinRetrival[0].binId];


		retrivalTaskObject.firstRobotSelection();
		retrivalTaskObject.portSelection();
		
		

		double cycleTime = retrivalTaskObject.cycleTime();







		firstRobotsVector[retrivalTaskObject.selectedfirstRobot.id].time =
			firstRobotsVector[retrivalTaskObject.selectedfirstRobot.id].time + cycleTime; // change robot time




		std::cout << "Finished Retriving " << queueOfBinRetrival[0].locationName << 
			". CycleTime: " << cycleTime << " Robot Id: " << retrivalTaskObject.selectedfirstRobot.id
			<< " RobotTime: " << firstRobotsVector[retrivalTaskObject.selectedfirstRobot.id].time<<
			"-----------------------------------------------------------";
		
		
		//finishedRetriveTaskVector.push_back(finishedRetriveTaskVector[retrivalTaskId]);
		queueOfBinRetrival.erase(queueOfBinRetrival.begin());
		


		finishedRetriveTaskVector.push_back(retrivalTaskObject);
		

#if 1
		if (firstRobotsVector[retrivalTaskObject.selectedfirstRobot.id].time >= (shiftHours * 60 * 60)) {
			std::cout << "\n\n\n************************One Hour is Passed**************************\n\n\n";

			std::cout << "Percentage of retrived Bins" << (finishedRetriveTaskVector.size() / maxNumOfBins) * 100 << "\n";

			for (auto robot : firstRobotsVector) {
				std::cout << "Robot Id:" << robot.id << " Robot time: " << robot.time << "\n";
			}

			std::cout << "total num of retrived Bin: " << finishedRetriveTaskVector.size()
				<< " throughput/hour: " << finishedRetriveTaskVector.size()/shiftHours;
			break;
		}
		
#endif
		retrivalTaskId++;
		
	}










	if (queueOfBinRetrival.empty()){
		for (auto &robot : firstRobotsVector) {
			std::cout << "Robot Id:" << robot.id << " Robot time: " << robot.time << "\n";
		}
		std::cout << "\n\nEmpty Retrival Queue!\n";
	}
	else{ std::cout << "\n\nRetrival Queue Not Empty Or Something Wrong!\n"; }
	


	//std::cout << queueOfBinRetrival[0].binName << "\t" << queueOfBinRetrival[0].locationName << "\n";
	return 0;
}

