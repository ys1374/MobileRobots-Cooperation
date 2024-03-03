#include <iostream>
#include "Autostore.h"
#include "AStar.h"
#include <vector>
#include <fstream>



const unsigned int filledPercentOfWarehouse{ 80 }; //in %
double shiftHours{ 8 };
bool useSecondRobot{ 0 };

// ************** if changed these 3 delete files************************
const unsigned int xLenghOfWarehouse{ 30 }; //max x size of gird
const unsigned int yLenghOfWarehouse{ 30 }; //max y size of gird
const unsigned int zLenghOfWarehouse{ 20 }; //max num of bins in a column
const unsigned int numOfFirstRobots{ 2 };
const unsigned int numOfSecondRobots{ 3 };
const unsigned int secondRobotCapacity{ 5 };
const unsigned int numOfPorts{ 3 };

//***********************************************************************







long long int locationId{ 0 }, binId{ 0 };
long long int retrivalTaskId{ 0 };

unsigned int maxNumOfBins{ xLenghOfWarehouse * yLenghOfWarehouse * zLenghOfWarehouse * filledPercentOfWarehouse / 100 };


//functions-----------------------
int generateRandomNumber(int max);
void fillQueueOfBinRetrival(std::vector<Autostore::bin>& queueOfBinRetrival, const std::string& filename, std::vector<Autostore::bin> binsVector_);
void fillFirstRobotLocation(std::vector<Autostore::firstRobot>& firstRobotsVector_, const std::string& filename_);
void fillSecondRobotLocation(std::vector<Autostore::secondRobot>& secondRobotsVector_, const std::string& filename_);
//bool fileExists(const std::string& filename);
//void fillExcelFileCycleTime(lxw_worksheet* worksheet, double cycleTime_, const int column_, const int row_);
//--------------------------------
int PortLocations[3][3] = {
{xLenghOfWarehouse / 2 , 0, 0},
{0 , yLenghOfWarehouse / 2 , 1},
{xLenghOfWarehouse - 1, yLenghOfWarehouse / 2, 2}
};


int main()
{	
	 
	//***we need to fill the warehouse with robots and bins objects*****
	// 	//port objects---------------------------------
	std::vector<Autostore::port> portsVector;// Vector of class objects
	Autostore::port portObject;

	for (auto port : PortLocations) {
		portObject.xLocation = port[0];
		portObject.yLocation = port[1];

		portObject.id = port[2];

		portsVector.push_back(portObject);
	}

	//filling first robot-----------------------
	std::vector<Autostore::firstRobot> firstRobotsVector;// Vector of class objects
	Autostore::firstRobot firstRobotObject;

	for (int i = 0; i < numOfFirstRobots; i++) {
		firstRobotObject.nameFillerFirstRobot(i);
		firstRobotObject.xLocation = generateRandomNumber(xLenghOfWarehouse-1);
		firstRobotObject.yLocation = generateRandomNumber(yLenghOfWarehouse-1);
		
		firstRobotsVector.push_back(firstRobotObject);
	}

	//second robot------------------------------
	std::vector<Autostore::secondRobot> secondRobotsVector;// Vector of class objects
	Autostore::secondRobot secondRobotObject;

	for (int i = 0; i < numOfSecondRobots; i++) {
		secondRobotObject.nameFillerSecondRobot(i);
		secondRobotObject.xLocation = generateRandomNumber(xLenghOfWarehouse-1);
		secondRobotObject.yLocation = generateRandomNumber(yLenghOfWarehouse-1);

		secondRobotObject.id = i;

		secondRobotObject.bins.reserve(secondRobotCapacity);
		//Autostore::bin bin;
		//for (int i = 0; i < secondRobotCapacity; i++) {
		//	secondRobotObject.bins.push_back(bin);
		//}

		secondRobotsVector.push_back(secondRobotObject);
	}

	//bins--------------------------------------
	std::vector<Autostore::bin> binsVector;// Vector of class objects
	Autostore::bin binsObject; // fins will fill with locations

	//creating gridbins location on grid--------
	std::vector<std::vector<std::vector<Autostore::gridLocation>>> gridLocationVector(
		xLenghOfWarehouse,
		std::vector<std::vector<Autostore::gridLocation>>(
		yLenghOfWarehouse,
		std::vector<Autostore::gridLocation>(
		zLenghOfWarehouse)));// Vector of class objects

	Autostore::gridLocation gridLocationObject;//creating object


	
	//fill locations and bins-------------------------------------------------
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

	
	//write robots location to file
	fillFirstRobotLocation(firstRobotsVector, "firstRobots_locations.txt");
	fillSecondRobotLocation(secondRobotsVector, "secondRobots_locations.txt");


	std::cout << "Objects on Warehouse all set!\n";


	//make a Queue for retrival from shufling the binsVector-----------------
	std::vector<Autostore::bin> queueOfBinRetrival;
	queueOfBinRetrival.reserve(maxNumOfBins);

	fillQueueOfBinRetrival(queueOfBinRetrival, "queueOfBinRetrival.txt", binsVector);


	//filling retrivalTaskObject--------------------------------------------------------------
	Autostore::retrivalTask retrivalTaskObject(portsVector, firstRobotsVector, secondRobotsVector, binsVector, gridLocationVector);
	std::vector<Autostore::retrivalTask> finishedRetriveTaskVector;

	retrivalTaskObject.constants.xLenghOfWarehouse = xLenghOfWarehouse;
	retrivalTaskObject.constants.yLenghOfWarehouse = yLenghOfWarehouse;
	retrivalTaskObject.constants.zLenghOfWarehouse = zLenghOfWarehouse;

	retrivalTaskObject.constants.secondRobotCapacity = secondRobotCapacity;
	

	//filling EXCEL file ------------------------------------------------------------------------
	
	
	auto excelfileName{ "cycletime.xlsx" };

	lxw_workbook* workbook = workbook_new(excelfileName);
	lxw_worksheet* worksheet = workbook_add_worksheet(workbook, NULL);
	//--------------
	auto excelfileName2{ "cycletime2.xlsx" };

	lxw_workbook* workbook2 = workbook_new(excelfileName2);
	lxw_worksheet* worksheet2 = workbook_add_worksheet(workbook2, NULL);









	
	//the evaluation throughput in one type ---------------------------------
	while ((!queueOfBinRetrival.empty()) && (!useSecondRobot))
	{	
		std::cout << "\n\nRetriving " << queueOfBinRetrival[0].locationName << " is on Track\n";
		if (queueOfBinRetrival[0].xLocation == 0 && queueOfBinRetrival[0].yLocation == 0) {
			queueOfBinRetrival.erase(queueOfBinRetrival.begin());
		}



		retrivalTaskObject.reset();
		retrivalTaskObject.id = retrivalTaskId;
		retrivalTaskObject.binToRetrive = binsVector[queueOfBinRetrival[0].binId];
		//retrivalTaskObject.binToRetrive_ = &binsVector[queueOfBinRetrival[0].binId];


		retrivalTaskObject.firstRobotSelection();
		retrivalTaskObject.portSelection();
		
		

		double cycleTime = retrivalTaskObject.oneTypeCycleTime();
		worksheet_write_number(worksheet, retrivalTaskId + 1, 0, cycleTime, NULL);







		firstRobotsVector[retrivalTaskObject.selectedfirstRobot.id].time =
			firstRobotsVector[retrivalTaskObject.selectedfirstRobot.id].time + cycleTime; // change robot time
		
		firstRobotsVector[retrivalTaskObject.selectedfirstRobot.id].numOfTasks++;



		//std::cout << "Finished Retriving " << queueOfBinRetrival[0].locationName << 
		//	". CycleTime: " << cycleTime << " Robot Id: " << retrivalTaskObject.selectedfirstRobot.id
		//	<< " RobotTime: " << firstRobotsVector[retrivalTaskObject.selectedfirstRobot.id].time<<
		//	"\n-----------------------------------------------------------";
		
		
		//finishedRetriveTaskVector.push_back(finishedRetriveTaskVector[retrivalTaskId]);
		queueOfBinRetrival.erase(queueOfBinRetrival.begin());
		


		finishedRetriveTaskVector.push_back(retrivalTaskObject);
		

#if 1
		if (firstRobotsVector[retrivalTaskObject.selectedfirstRobot.id].time >= (shiftHours * 60 * 60)) {
			std::cout << "\n\n\n************************Shift Hours is Passed**************************\n\n\n";

			std::cout << "Percentage of retrived Bins" << (finishedRetriveTaskVector.size() / maxNumOfBins) * 100 << "\n";

			for (auto robot : firstRobotsVector) {
				std::cout << "Robot Id:" << robot.id << " Robot time: " << robot.time << " Robot Tasks: " << robot.numOfTasks << "\n";
			}

			std::cout << "total num of retrived Bin: " << finishedRetriveTaskVector.size()
				<< " throughput/hour: " << finishedRetriveTaskVector.size()/shiftHours;
			break;
		}
		
#endif	
		if (retrivalTaskId % numOfFirstRobots == 1) {
			for (auto& robot : firstRobotsVector) {
				robot.isBusy = false;
			}
			//break;
		}
		retrivalTaskId++;
		//break;
		
		
	}
	
	if (!useSecondRobot) { workbook_close(workbook); }























#if 1
	//the evaluation throughput in two type -------------------------------------
	while ((!queueOfBinRetrival.empty()) && (useSecondRobot))
	{
		std::cout << "\n\nRetriving " << queueOfBinRetrival[0].locationName << " is on Track\n";

		if (queueOfBinRetrival[0].xLocation == 0 && queueOfBinRetrival[0].yLocation == 0) {
			queueOfBinRetrival.erase(queueOfBinRetrival.begin());
			continue;
		}
		if (queueOfBinRetrival[0].zLocation == 0) {
			queueOfBinRetrival.erase(queueOfBinRetrival.begin());
			continue;
		}



		retrivalTaskObject.reset();
		retrivalTaskObject.id = retrivalTaskId;
		retrivalTaskObject.binToRetrive = binsVector[queueOfBinRetrival[0].binId];
		//retrivalTaskObject.binToRetrive_ = &binsVector[queueOfBinRetrival[0].binId];


		retrivalTaskObject.firstRobotSelection();
		retrivalTaskObject.secondRobotSelection();
		retrivalTaskObject.portSelection();


		//double cycleTime = retrivalTaskObject.oneTypeCycleTime();
		double cycleTime = retrivalTaskObject.twoTypeCycleTime();
		worksheet_write_number(worksheet, retrivalTaskId + 1, 0, cycleTime, NULL);
		//break;






		firstRobotsVector[retrivalTaskObject.selectedfirstRobot.id].time =
			firstRobotsVector[retrivalTaskObject.selectedfirstRobot.id].time + cycleTime; // change robot time

		firstRobotsVector[retrivalTaskObject.selectedfirstRobot.id].numOfTasks++;



		//finishedRetriveTaskVector.push_back(finishedRetriveTaskVector[retrivalTaskId]);
		queueOfBinRetrival.erase(queueOfBinRetrival.begin());



		finishedRetriveTaskVector.push_back(retrivalTaskObject);


#if 1
		if (firstRobotsVector[retrivalTaskObject.selectedfirstRobot.id].time >= (shiftHours * 60 * 60)) {
			std::cout << "\n\n\n************************Shift Hours is Passed**************************\n\n\n";

			std::cout << "Percentage of retrived Bins" << (finishedRetriveTaskVector.size() / maxNumOfBins) * 100 << "\n";

			for (auto robot : firstRobotsVector) {
				std::cout << "Robot Id:" << robot.id << " Robot time: " << robot.time << " Robot Tasks: " << robot.numOfTasks << "\n";
			}

			std::cout << "total num of retrived Bin: " << finishedRetriveTaskVector.size()
				<< " throughput/hour: " << finishedRetriveTaskVector.size() / shiftHours;
			break;
		}

#endif	


		if (retrivalTaskId % numOfFirstRobots == 1) {
			for (auto& robot : firstRobotsVector) {
				robot.isBusy = false;
			}
			//break;
		}
		retrivalTaskId++;


	}
	if (useSecondRobot) { workbook_close(workbook2); }
	
#endif




























	if (queueOfBinRetrival.empty()){
		for (auto &robot : firstRobotsVector) {
			std::cout << "Robot Id:" << robot.id << " Robot time: " << robot.time << "\n";
		}
		std::cout << "\n\nEmpty Retrival Queue!\n";
	}
	else{ std::cout << "\n\nRetrival Queue Not Empty Or Something Wrong!\n"; }








	return 0;
}

