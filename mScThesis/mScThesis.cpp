#include <iostream>
#include "Autostore.h"
#include "AStar.h"
#include <vector>
#include <fstream>
#include <string>
#include <filesystem>

bool useSecondRobot{ 0 };
bool useBoth{ 1 };
#if 1
const unsigned int filledPercentOfWarehouse{ 80 }; //in %
double shiftHours{ 8 };


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
std::vector<double> cycleTimeOneType;

#endif

//functions-----------------------
#if 1
int generateRandomNumber(int max);
void fillQueueOfBinRetrival(std::vector<Autostore::bin>& queueOfBinRetrival, const std::string& filename, std::vector<Autostore::bin> binsVector_);
void fillFirstRobotLocation(std::vector<Autostore::firstRobot>& firstRobotsVector_, const std::string& filename_);
void fillSecondRobotLocation(std::vector<Autostore::secondRobot>& secondRobotsVector_, const std::string& filename_);
bool fileExists(const std::string& filename);
//void fillExcelFileCycleTime(lxw_worksheet* worksheet, double cycleTime_, const int column_, const int row_);

//--------------------------------



int PortLocations[3][3] = {
{xLenghOfWarehouse / 2 , 0, 0},
{0 , yLenghOfWarehouse / 2 , 1},
{xLenghOfWarehouse - 1, yLenghOfWarehouse / 2, 2}
};

#endif











int main()
{	
	 
	//***we need to fill the warehouse with robots and bins objects*****
	//port objects---------------------------------
#if 1
	std::vector<Autostore::port> portsVector;// Vector of class objects
	Autostore::port portObject;

	for (auto port : PortLocations) {
		portObject.xLocation = port[0];
		portObject.yLocation = port[1];

		portObject.id = port[2];

		portsVector.push_back(portObject);
	}
#endif
	//filling first robot-----------------------
#if 1
	std::vector<Autostore::firstRobot> firstRobotsVector;// Vector of class objects
	Autostore::firstRobot firstRobotObject;

	for (int i = 0; i < numOfFirstRobots; i++) {
		firstRobotObject.nameFillerFirstRobot(i);
		firstRobotObject.xLocation = generateRandomNumber(xLenghOfWarehouse-1);
		firstRobotObject.yLocation = generateRandomNumber(yLenghOfWarehouse-1);
		
		firstRobotsVector.push_back(firstRobotObject);
	}
#endif
	//second robot------------------------------
#if 1
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
#endif
	//bins--------------------------------------
#if 1
	std::vector<Autostore::bin> binsVector;// Vector of class objects
	Autostore::bin binsObject; // fins will fill with locations
#endif

	//creating gridbins location on grid--------
#if 1
	std::vector<std::vector<std::vector<Autostore::gridLocation>>> gridLocationVector(
		xLenghOfWarehouse,
		std::vector<std::vector<Autostore::gridLocation>>(
		yLenghOfWarehouse,
		std::vector<Autostore::gridLocation>(
		zLenghOfWarehouse)));// Vector of class objects

	Autostore::gridLocation gridLocationObject;//creating object
#endif

	
	//fill locations and bins-------------------------------------------------
#if 1
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
#endif

	//make a Queue for retrival from shufling the binsVector-----------------
#if 1
	std::vector<Autostore::bin> queueOfBinRetrival;
	queueOfBinRetrival.reserve(maxNumOfBins);

	fillQueueOfBinRetrival(queueOfBinRetrival, "queueOfBinRetrival.txt", binsVector);
#endif

	//filling retrivalTaskObject--------------------------------------------------------------
#if 1
	Autostore::retrivalTask retrivalTaskObject(portsVector, firstRobotsVector, secondRobotsVector, binsVector, gridLocationVector);
	std::vector<Autostore::retrivalTask> finishedRetriveTaskVector;

	retrivalTaskObject.constants.xLenghOfWarehouse = xLenghOfWarehouse;
	retrivalTaskObject.constants.yLenghOfWarehouse = yLenghOfWarehouse;
	retrivalTaskObject.constants.zLenghOfWarehouse = zLenghOfWarehouse;

	retrivalTaskObject.constants.secondRobotCapacity = secondRobotCapacity;
#endif

	//filling EXCEL file ------------------------------------------------------------------------
	
#if 1	
	auto twoTypeExcelfileName{ "twoTypeExcelfile.xlsx" };
	lxw_workbook* twoTypeWorkbook = workbook_new(twoTypeExcelfileName);
	lxw_worksheet* twoTypeWorksheet = workbook_add_worksheet(twoTypeWorkbook, NULL);
	worksheet_write_string(twoTypeWorksheet, 0, 0, "LOCATION", NULL);

	worksheet_write_string(twoTypeWorksheet, 0, 9, "Bin X", NULL);
	worksheet_write_string(twoTypeWorksheet, 0, 10, "Bin Y", NULL);
	worksheet_write_string(twoTypeWorksheet, 0, 11, "Bin Z", NULL);

	worksheet_write_string(twoTypeWorksheet, 0, 1, "FR X", NULL);
	worksheet_write_string(twoTypeWorksheet, 0, 2, "FR Y", NULL);

	worksheet_write_string(twoTypeWorksheet, 0, 3, "Port X", NULL);
	worksheet_write_string(twoTypeWorksheet, 0, 4, "Port Y", NULL);

	worksheet_write_string(twoTypeWorksheet, 0, 5, "SR ToB CT", NULL);
	worksheet_write_string(twoTypeWorksheet, 0, 6, "twoT E CT", NULL);

	worksheet_write_string(twoTypeWorksheet, 0, 7, "FR ToB CT", NULL);
	worksheet_write_string(twoTypeWorksheet, 0, 8, "B ToP CT", NULL);

	worksheet_write_string(twoTypeWorksheet, 0, 12, "twoT L CT", NULL);
	worksheet_write_string(twoTypeWorksheet, 0, 13, "CT", NULL);

	//worksheet_write_string(twoTypeWorksheet, 0, 14, "#BTo Relocate", NULL);

	worksheet_write_string(twoTypeWorksheet, 0, 14, "2ndR id", NULL);
	worksheet_write_string(twoTypeWorksheet, 0, 15, "2ndR X", NULL);
	worksheet_write_string(twoTypeWorksheet, 0, 16, "2ndR Y", NULL);
#endif
	//----------------------------------------------------------
	//oneTypeExcel
#if 1
	auto oneTypeExcelfileName{ "oneTypeExcelfile.xlsx" };
	lxw_workbook* oneTypeWorkbook = workbook_new(oneTypeExcelfileName);
	lxw_worksheet* oneTypeWorksheet = workbook_add_worksheet(oneTypeWorkbook, NULL);
	worksheet_write_string(oneTypeWorksheet, 0, 0, "LOCATION", NULL);

	worksheet_write_string(oneTypeWorksheet, 0, 9, "Bin X", NULL);
	worksheet_write_string(oneTypeWorksheet, 0, 10, "Bin Y", NULL);
	worksheet_write_string(oneTypeWorksheet, 0, 11, "Bin Z", NULL);

	worksheet_write_string(oneTypeWorksheet, 0, 1, "FR X", NULL);
	worksheet_write_string(oneTypeWorksheet, 0, 2, "FR Y", NULL);

	worksheet_write_string(oneTypeWorksheet, 0, 3, "Port X", NULL);
	worksheet_write_string(oneTypeWorksheet, 0, 4, "Port Y", NULL);

	worksheet_write_string(oneTypeWorksheet, 0, 5, "FR ToB CT", NULL);
	worksheet_write_string(oneTypeWorksheet, 0, 6, "E CT", NULL); 

	worksheet_write_string(oneTypeWorksheet, 0, 7, "2*BToP CT", NULL); 
	worksheet_write_string(oneTypeWorksheet, 0, 8, "CT", NULL);

	worksheet_write_string(oneTypeWorksheet, 0, 12, "E goal CT", NULL);
	worksheet_write_string(oneTypeWorksheet, 0, 13, "relocationCT", NULL);

	worksheet_write_string(oneTypeWorksheet, 0, 14, "#BTo Relocate", NULL);
#endif











	
	//the evaluation throughput in one type 11111111111111111111111111111111
#if 1
	while ((!queueOfBinRetrival.empty()) && (!useSecondRobot))
	{	
		std::cout << "\nRetriving " << queueOfBinRetrival[0].locationName;
		//if (queueOfBinRetrival[0].xLocation == 0 && queueOfBinRetrival[0].yLocation == 0) {
		//	queueOfBinRetrival.erase(queueOfBinRetrival.begin());
		//}
		if (queueOfBinRetrival[0].xLocation == 0 && queueOfBinRetrival[0].yLocation == 0) {
			queueOfBinRetrival.erase(queueOfBinRetrival.begin());
			std::cout << "--------->This is deleted from queue!";
			continue;
		}
		if (queueOfBinRetrival[0].zLocation == 0) {
			queueOfBinRetrival.erase(queueOfBinRetrival.begin());
			std::cout << "--------->This is deleted from queue!";
			continue;
		}


		retrivalTaskObject.reset();
		retrivalTaskObject.id = retrivalTaskId;
		retrivalTaskObject.binToRetrive = binsVector[queueOfBinRetrival[0].binId];
		
		worksheet_write_string(oneTypeWorksheet, retrivalTaskId + 1, 0, retrivalTaskObject.binToRetrive.locationName.c_str(), NULL);
		worksheet_write_number(oneTypeWorksheet, retrivalTaskId + 1, 9, retrivalTaskObject.binToRetrive.xLocation, NULL);
		worksheet_write_number(oneTypeWorksheet, retrivalTaskId + 1, 10, retrivalTaskObject.binToRetrive.yLocation, NULL);
		worksheet_write_number(oneTypeWorksheet, retrivalTaskId + 1, 11, retrivalTaskObject.binToRetrive.zLocation, NULL);

		retrivalTaskObject.firstRobotSelection(oneTypeWorksheet);
		retrivalTaskObject.portSelection(oneTypeWorksheet);


		double cycleTime = retrivalTaskObject.oneTypeCycleTime(oneTypeWorksheet);
		cycleTimeOneType.push_back(cycleTime);
		

		firstRobotsVector[retrivalTaskObject.selectedfirstRobot.id].time =
			firstRobotsVector[retrivalTaskObject.selectedfirstRobot.id].time + cycleTime; // change robot time
		
		firstRobotsVector[retrivalTaskObject.selectedfirstRobot.id].numOfTasks++;

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
	
	if (!useSecondRobot) { workbook_close(oneTypeWorkbook); }
#endif


	//two type evaluation throughput
#if 1

	while ((!queueOfBinRetrival.empty()) && (useSecondRobot))
	{
		std::cout << "\nRetriving " << queueOfBinRetrival[0].locationName ;

		if (queueOfBinRetrival[0].xLocation == 0 && queueOfBinRetrival[0].yLocation == 0) {
			queueOfBinRetrival.erase(queueOfBinRetrival.begin());
			std::cout << "--------->This is deleted from queue!";
			continue;
		}
		if (queueOfBinRetrival[0].zLocation == 0) {
			queueOfBinRetrival.erase(queueOfBinRetrival.begin());
			std::cout << "--------->This is deleted from queue!";
			continue;
		}


		retrivalTaskObject.reset();
		retrivalTaskObject.id = retrivalTaskId;
		retrivalTaskObject.binToRetrive = binsVector[queueOfBinRetrival[0].binId];

		worksheet_write_string(twoTypeWorksheet, retrivalTaskId + 1, 0, retrivalTaskObject.binToRetrive.locationName.c_str(), NULL);
		worksheet_write_number(twoTypeWorksheet, retrivalTaskId + 1, 9, retrivalTaskObject.binToRetrive.xLocation, NULL);
		worksheet_write_number(twoTypeWorksheet, retrivalTaskId + 1, 10, retrivalTaskObject.binToRetrive.yLocation, NULL);
		worksheet_write_number(twoTypeWorksheet, retrivalTaskId + 1, 11, retrivalTaskObject.binToRetrive.zLocation, NULL);

		retrivalTaskObject.firstRobotSelection(twoTypeWorksheet);
		retrivalTaskObject.secondRobotSelection(twoTypeWorksheet);
		retrivalTaskObject.portSelection(twoTypeWorksheet);
		
		double cycleTime = retrivalTaskObject.twoTypeCycleTime(twoTypeWorksheet);

		//worksheet_write_number(twoTypeWorksheet, retrivalTaskId + 1, 0, cycleTimeOneType[retrivalTaskId], NULL);
		//worksheet_write_number(twoTypeWorksheet, retrivalTaskId + 1, 1, cycleTime, NULL);
		//worksheet_write_number(twoTypeWorksheet, retrivalTaskId + 1, 2, ((cycleTime / cycleTimeOneType[retrivalTaskId]) - 1)*100, NULL);
		//worksheet_write_number(twoTypeWorksheet, retrivalTaskId + 1, 3, retrivalTaskObject.binToRetrive.zLocation, NULL);
		//break;



		queueOfBinRetrival.erase(queueOfBinRetrival.begin());
		finishedRetriveTaskVector.push_back(retrivalTaskObject);


#if 0
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


		if (retrivalTaskId % numOfFirstRobots == 1) {
			for (auto& robot : firstRobotsVector) {
				robot.isBusy = false;
			}
			//break;
		}


#endif
		if (retrivalTaskId == 600) {
			break;
		}
		retrivalTaskId++;


	}

	if (useSecondRobot) { workbook_close(twoTypeWorkbook); }

#endif


	//Both type
#if 1

	while ((!queueOfBinRetrival.empty()) && useBoth){

		std::cout << "\nRetriving " << queueOfBinRetrival[0].locationName;

		if (queueOfBinRetrival[0].xLocation == 0 && queueOfBinRetrival[0].yLocation == 0) {
			queueOfBinRetrival.erase(queueOfBinRetrival.begin());
			std::cout << "--------->This is deleted from queue!";
			continue;
		}
		if (queueOfBinRetrival[0].zLocation == 0) {
			queueOfBinRetrival.erase(queueOfBinRetrival.begin());
			std::cout << "--------->This is deleted from queue!";
			continue;
		}


		retrivalTaskObject.reset();
		retrivalTaskObject.id = retrivalTaskId;
		retrivalTaskObject.binToRetrive = binsVector[queueOfBinRetrival[0].binId];

		//worksheet_write_string(twoTypeWorksheet, retrivalTaskId + 1, 0, retrivalTaskObject.binToRetrive.locationName.c_str(), NULL);
		//worksheet_write_number(twoTypeWorksheet, retrivalTaskId + 1, 9, retrivalTaskObject.binToRetrive.xLocation, NULL);
		//worksheet_write_number(twoTypeWorksheet, retrivalTaskId + 1, 10, retrivalTaskObject.binToRetrive.yLocation, NULL);
		//worksheet_write_number(twoTypeWorksheet, retrivalTaskId + 1, 11, retrivalTaskObject.binToRetrive.zLocation, NULL);

		auto numOfTopBin = retrivalTaskObject.findTopBin(queueOfBinRetrival[0].xLocation, queueOfBinRetrival[0].yLocation).zLocation;

		retrivalTaskObject.firstRobotSelection(twoTypeWorksheet);
		retrivalTaskObject.secondRobotSelection(twoTypeWorksheet);
		retrivalTaskObject.portSelection(twoTypeWorksheet);

		double cycleTime = retrivalTaskObject.twoTypeCycleTime(twoTypeWorksheet);



		queueOfBinRetrival.erase(queueOfBinRetrival.begin());
		finishedRetriveTaskVector.push_back(retrivalTaskObject);

		if (retrivalTaskId == 600) {break;}
		retrivalTaskId++;


	}

	if (useSecondRobot) { workbook_close(twoTypeWorkbook); }

#endif


	//error handeling
#if 1
	if (queueOfBinRetrival.empty()){
		for (auto &robot : firstRobotsVector) {
			std::cout << "Robot Id:" << robot.id << " Robot time: " << robot.time << "\n";
		}
		std::cout << "\n\nEmpty Retrival Queue!\n";
	}
	else{ std::cout << "\n\nRetrival Queue Not Empty Or Something Wrong!\n"; }
#endif







	return 0;
}

