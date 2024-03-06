#include <iostream>
#include "Autostore.h"
#include "AStar.h"
#include <vector>
#include <fstream>
#include <string>
#include <filesystem>
#include <algorithm>
#include <functional>

bool useSecondRobot{ 0 };
bool useBoth{ 0 };
#if 1
const unsigned int filledPercentOfWarehouse{ 80 }; //in %
double shiftHours{ 8 };


// ************** if changed these 3 delete files************************
const unsigned int xLenghOfWarehouse{ 30 }; //max x size of gird
const unsigned int yLenghOfWarehouse{ 30 }; //max y size of gird
const unsigned int zLenghOfWarehouse{ 20 }; //max num of bins in a column
const unsigned int numOfFirstRobots{ 3 };
const unsigned int numOfSecondRobots{ 2 };
const unsigned int secondRobotCapacity{ 5 };
const unsigned int numOfPorts{ 3 };

//***********************************************************************

long long int locationId{ 0 }, binId{ 0 };
long long int retrivalTaskId{ 0 };

unsigned int numOfGridLocations{ xLenghOfWarehouse * yLenghOfWarehouse * zLenghOfWarehouse };
unsigned int maxNumOfBins{ xLenghOfWarehouse * yLenghOfWarehouse * zLenghOfWarehouse * filledPercentOfWarehouse / 100 };


#endif

//functions
#if 1
int generateRandomNumber(int max);
void fillQueueOfBinRetrival(std::vector<Autostore::bin>& queueOfBinRetrival, const std::string& filename, std::vector<Autostore::bin> binsVector_);
void fillFirstRobotLocation(std::vector<Autostore::firstRobot>& firstRobotsVector_, const std::string& filename_);
void fillSecondRobotLocation(std::vector<Autostore::secondRobot>& secondRobotsVector_, const std::string& filename_);
bool fileExists(const std::string& filename);

//--------------------------------



int PortLocations[3][3] = {
{xLenghOfWarehouse / 2 , 0, 0},
{0 , yLenghOfWarehouse / 2 , 1},
{xLenghOfWarehouse - 1, yLenghOfWarehouse / 2, 2}
};

#endif


int main()
{	//vectors
#if 1
	std::vector<Autostore::port> portsVector;
	std::vector<Autostore::firstRobot> firstRobotsVector;
	std::vector<Autostore::secondRobot> secondRobotsVector;
	std::vector<Autostore::bin> binsVector;
	std::vector<std::vector<std::vector<Autostore::gridLocation>>> gridLocationVector(xLenghOfWarehouse,std::vector<std::vector<Autostore::gridLocation>>(yLenghOfWarehouse,std::vector<Autostore::gridLocation>(zLenghOfWarehouse)));
	std::vector<Autostore::bin> queueOfBinRetrival;
	std::vector<Autostore::bin> oneRoundOfRetrivalTask;
	
#endif

	//reserve vectors
#if 1
	portsVector.reserve(numOfPorts);
	firstRobotsVector.reserve(numOfFirstRobots);
	secondRobotsVector.reserve(numOfSecondRobots);
	binsVector.reserve(maxNumOfBins);
	queueOfBinRetrival.reserve(maxNumOfBins);
	oneRoundOfRetrivalTask.reserve(numOfFirstRobots);
#endif
	//objects
#if 1
	Autostore::port portObject;
	Autostore::firstRobot firstRobotObject;
	Autostore::secondRobot secondRobotObject;
	Autostore::bin binsObject;
	Autostore::gridLocation gridLocationObject;
#endif

//filling Vectors----------------------------------------------------------------------
	
	//port
#if 0
	for (auto port : PortLocations) {
		portObject.xLocation = port[0];
		portObject.yLocation = port[1];

		portObject.id = port[2];

		portsVector.push_back(portObject);
	}
#endif
	//first robot
#if 0
	for (int i = 0; i < numOfFirstRobots; i++) {
		firstRobotObject.nameFillerFirstRobot(i);
		firstRobotObject.xLocation = generateRandomNumber(xLenghOfWarehouse-1);
		firstRobotObject.yLocation = generateRandomNumber(yLenghOfWarehouse-1);
		
		firstRobotsVector.push_back(firstRobotObject);
	}
#endif
	//second robot
#if 0
	for (int i = 0; i < numOfSecondRobots; i++) {
		secondRobotObject.nameFillerSecondRobot(i);
		secondRobotObject.xLocation = generateRandomNumber(xLenghOfWarehouse-1);
		secondRobotObject.yLocation = generateRandomNumber(yLenghOfWarehouse-1);
		secondRobotObject.id = i;
		secondRobotObject.bins.reserve(secondRobotCapacity);
		secondRobotsVector.push_back(secondRobotObject);
	}
#endif
	//locations and bins
#if 0
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
#if 1
	//Queue for retrival
	fillQueueOfBinRetrival(queueOfBinRetrival, "queueOfBinRetrival.txt", binsVector);
#endif

//EXCEL file ----------------------------------------------------------------------------

	//bothTypeExcel
#if 1	
	auto bothTypeExcelfileName{ "bothTypeExcelfile.xlsx" };
	lxw_workbook* bothTypeWorkbook = workbook_new(bothTypeExcelfileName);
	lxw_worksheet* bothTypeWorksheet = workbook_add_worksheet(bothTypeWorkbook, NULL);

	worksheet_write_string(bothTypeWorksheet, 0, 0, "LOCATION", NULL);

	worksheet_write_string(bothTypeWorksheet, 0, 1, "Bin X", NULL);
	worksheet_write_string(bothTypeWorksheet, 0, 2, "Bin Y", NULL);
	worksheet_write_string(bothTypeWorksheet, 0, 3, "Bin Z", NULL);

	worksheet_write_string(bothTypeWorksheet, 0, 4, "FR X", NULL);
	worksheet_write_string(bothTypeWorksheet, 0, 5, "FR Y", NULL);

	worksheet_write_string(bothTypeWorksheet, 0, 6, "SR X", NULL);
	worksheet_write_string(bothTypeWorksheet, 0, 7, "SR Y", NULL);

	worksheet_write_string(bothTypeWorksheet, 0, 8, "Port X", NULL);
	worksheet_write_string(bothTypeWorksheet, 0, 9, "Port Y", NULL);

	worksheet_write_string(bothTypeWorksheet, 0, 10, "FR ToB CT", NULL);
	worksheet_write_string(bothTypeWorksheet, 0, 11, "SR ToB CT", NULL);

	worksheet_write_string(bothTypeWorksheet, 0, 12, "1T E CT", NULL);
	worksheet_write_string(bothTypeWorksheet, 0, 13, "2T E CT", NULL);
		
	worksheet_write_string(bothTypeWorksheet, 0, 14, "B ToP CT", NULL);
	
	worksheet_write_string(bothTypeWorksheet, 0, 15, "1T L CT", NULL);
	worksheet_write_string(bothTypeWorksheet, 0, 16, "2T L CT", NULL);
	
	worksheet_write_string(bothTypeWorksheet, 0, 17, "1T CT", NULL);
	worksheet_write_string(bothTypeWorksheet, 0, 18, "2T CT", NULL);
	worksheet_write_string(bothTypeWorksheet, 0, 19, "CT", NULL);


#endif

	//twoTypeExcel
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


//filling retrivalTaskObject--------------------------------------------------------------
	//Vectors Copy	
#if 1
	auto oneTypePortsVector = portsVector;
	auto twoTypePortsVector = portsVector;
	auto bothTypePortsVector = portsVector;

	auto oneTypeFirstRobotsVector = firstRobotsVector;
	auto twoTypeFirstRobotsVector = firstRobotsVector;
	auto bothTypeFirstRobotsVector = firstRobotsVector;

	auto oneTypeSecondRobotsVector = secondRobotsVector;
	auto twoTypeSecondRobotsVector = secondRobotsVector;
	auto bothTypeSecondRobotsVector = secondRobotsVector;

	auto oneTypeBinsVector = binsVector;
	auto twoTypeBinsVector = binsVector;
	auto bothTypeBinsVector = binsVector;

	auto oneTypeGridLocationVector = gridLocationVector;
	auto twoTypeGridLocationVector = gridLocationVector;
	auto bothTypeGridLocationVector = gridLocationVector;

	auto oneTypeQueueOfBinRetrival = queueOfBinRetrival;
	auto twoTypeQueueOfBinRetrival = queueOfBinRetrival;
	auto bothTypeQueueOfBinRetrival = queueOfBinRetrival;

#endif

#if 0
	std::vector<Autostore::port> portsVector;
	std::vector<Autostore::firstRobot> firstRobotsVector;
	std::vector<Autostore::secondRobot> secondRobotsVector;
	std::vector<Autostore::bin> binsVector;
	std::vector<std::vector<std::vector<Autostore::gridLocation>>>
		gridLocationVector(
			xLenghOfWarehouse, std::vector<std::vector<Autostore::gridLocation>>(
				yLenghOfWarehouse, std::vector<Autostore::gridLocation>(
					zLenghOfWarehouse)));

#endif

	//One Type
#if 1
	Autostore::retrivalTask oneTypeRetrivalTaskObject(oneTypePortsVector, oneTypeFirstRobotsVector, oneTypeSecondRobotsVector, oneTypeBinsVector, oneTypeGridLocationVector);
	std::vector<Autostore::retrivalTask> oneTypeFinishedRetriveTaskVector;

	oneTypeRetrivalTaskObject.constants.xLenghOfWarehouse = xLenghOfWarehouse;
	oneTypeRetrivalTaskObject.constants.yLenghOfWarehouse = yLenghOfWarehouse;
	oneTypeRetrivalTaskObject.constants.zLenghOfWarehouse = zLenghOfWarehouse;

	oneTypeRetrivalTaskObject.constants.secondRobotCapacity = secondRobotCapacity;
#endif

	//Two type
#if 0
	Autostore::retrivalTask oneTypeRetrivalTaskObject(portsVector, firstRobotsVector, secondRobotsVector, binsVector, oneTypegridLocationVector);
	std::vector<Autostore::retrivalTask> finishedRetriveTaskVector;

	oneTypeRetrivalTaskObject.constants.xLenghOfWarehouse = xLenghOfWarehouse;
	oneTypeRetrivalTaskObject.constants.yLenghOfWarehouse = yLenghOfWarehouse;
	oneTypeRetrivalTaskObject.constants.zLenghOfWarehouse = zLenghOfWarehouse;

	oneTypeRetrivalTaskObject.constants.secondRobotCapacity = secondRobotCapacity;
#endif

	//Both type
#if 0
	Autostore::retrivalTask oneTypeRetrivalTaskObject(portsVector, firstRobotsVector, secondRobotsVector, binsVector, oneTypegridLocationVector);
	std::vector<Autostore::retrivalTask> finishedRetriveTaskVector;

	oneTypeRetrivalTaskObject.constants.xLenghOfWarehouse = xLenghOfWarehouse;
	oneTypeRetrivalTaskObject.constants.yLenghOfWarehouse = yLenghOfWarehouse;
	oneTypeRetrivalTaskObject.constants.zLenghOfWarehouse = zLenghOfWarehouse;

	oneTypeRetrivalTaskObject.constants.secondRobotCapacity = secondRobotCapacity;
#endif





	
	//one type
#if 1
	while ((!oneTypeQueueOfBinRetrival.empty()) && (!useSecondRobot) && (!useBoth))
	{	
		std::cout << "\nRetriving " << oneTypeQueueOfBinRetrival[0].locationName;
		//if (queueOfBinRetrival[0].xLocation == 0 && queueOfBinRetrival[0].yLocation == 0) {
		//	queueOfBinRetrival.erase(queueOfBinRetrival.begin());
		//}
		if (oneTypeQueueOfBinRetrival[0].xLocation == 0 && oneTypeQueueOfBinRetrival[0].yLocation == 0) {
			oneTypeQueueOfBinRetrival.erase(oneTypeQueueOfBinRetrival.begin());
			std::cout << "--------->This is deleted from queue!";
			continue;
		}
		if (oneTypeQueueOfBinRetrival[0].zLocation == 0) {
			oneTypeQueueOfBinRetrival.erase(oneTypeQueueOfBinRetrival.begin());
			std::cout << "--------->This is deleted from queue!";
			continue;
		}


		oneTypeRetrivalTaskObject.reset();
		oneTypeRetrivalTaskObject.id = retrivalTaskId;
		oneTypeRetrivalTaskObject.binToRetrive = oneTypeBinsVector[oneTypeQueueOfBinRetrival[0].binId];
		
		worksheet_write_string(oneTypeWorksheet, retrivalTaskId + 1, 0, oneTypeRetrivalTaskObject.binToRetrive.locationName.c_str(), NULL);
		worksheet_write_number(oneTypeWorksheet, retrivalTaskId + 1, 9, oneTypeRetrivalTaskObject.binToRetrive.xLocation, NULL);
		worksheet_write_number(oneTypeWorksheet, retrivalTaskId + 1, 10, oneTypeRetrivalTaskObject.binToRetrive.yLocation, NULL);
		worksheet_write_number(oneTypeWorksheet, retrivalTaskId + 1, 11, oneTypeRetrivalTaskObject.binToRetrive.zLocation, NULL);

		oneTypeRetrivalTaskObject.firstRobotSelection(oneTypeWorksheet);
		oneTypeRetrivalTaskObject.portSelection(oneTypeWorksheet);


		double cycleTime = oneTypeRetrivalTaskObject.oneTypeCycleTime(oneTypeWorksheet);
		//cycleTimeOneType.push_back(cycleTime);
		

		oneTypeFirstRobotsVector[oneTypeRetrivalTaskObject.selectedfirstRobot.id].time =
			oneTypeFirstRobotsVector[oneTypeRetrivalTaskObject.selectedfirstRobot.id].time + cycleTime; // change robot time
		
		oneTypeFirstRobotsVector[oneTypeRetrivalTaskObject.selectedfirstRobot.id].numOfTasks++;

		oneTypeQueueOfBinRetrival.erase(oneTypeQueueOfBinRetrival.begin());
		

		oneTypeFinishedRetriveTaskVector.push_back(oneTypeRetrivalTaskObject);
		
		//shift chech
#if 1
		if (oneTypeFirstRobotsVector[oneTypeRetrivalTaskObject.selectedfirstRobot.id].time >= (shiftHours * 60 * 60)) {
			std::cout << "\n\n\n************************Shift Hours is Passed**************************\n\n\n";

			std::cout << "Percentage of retrived Bins" << (oneTypeFinishedRetriveTaskVector.size() / maxNumOfBins) * 100 << "\n";

			for (auto robot : oneTypeFirstRobotsVector) {
				std::cout << "Robot Id:" << robot.id << " Robot time: " << robot.time << " Robot Tasks: " << robot.numOfTasks << "\n";
			}

			std::cout << "total num of retrived Bin: " << oneTypeFinishedRetriveTaskVector.size()
				<< " throughput/hour: " << oneTypeFinishedRetriveTaskVector.size()/shiftHours;

			break;
		}
		
#endif	
		if (retrivalTaskId % numOfFirstRobots == 1) {
			for (auto& robot : oneTypeFirstRobotsVector) {
				robot.isBusy = false;
			}
			//break;
		}
		retrivalTaskId++;
		//break;
		
		
	}
	
	
#endif


	//two type
#if 0
	retrivalTaskId{ 0 };
	while ((!twoTypeQueueOfBinRetrival.empty()) && (useSecondRobot) && (!useBoth) )
	{
		std::cout << "\nRetriving " << twoTypeQueueOfBinRetrival[0].locationName ;

		if (twoTypeQueueOfBinRetrival[0].xLocation == 0 && twoTypeQueueOfBinRetrival[0].yLocation == 0) {
			twoTypeQueueOfBinRetrival.erase(twoTypeQueueOfBinRetrival.begin());
			std::cout << "--------->This is deleted from queue!";
			continue;
		}
		if (twoTypeQueueOfBinRetrival[0].zLocation == 0) {
			twoTypeQueueOfBinRetrival.erase(twoTypeQueueOfBinRetrival.begin());
			std::cout << "--------->This is deleted from queue!";
			continue;
		}


		retrivalTaskObject.reset();
		retrivalTaskObject.id = retrivalTaskId;
		retrivalTaskObject.binToRetrive = binsVector[twoTypeQueueOfBinRetrival[0].binId];

		worksheet_write_string(twoTypeWorksheet, retrivalTaskId + 1, 0, retrivalTaskObject.binToRetrive.locationName.c_str(), NULL);
		worksheet_write_number(twoTypeWorksheet, retrivalTaskId + 1, 9, retrivalTaskObject.binToRetrive.xLocation, NULL);
		worksheet_write_number(twoTypeWorksheet, retrivalTaskId + 1, 10, retrivalTaskObject.binToRetrive.yLocation, NULL);
		worksheet_write_number(twoTypeWorksheet, retrivalTaskId + 1, 11, retrivalTaskObject.binToRetrive.zLocation, NULL);

		retrivalTaskObject.firstRobotSelection(twoTypeWorksheet);
		retrivalTaskObject.secondRobotSelection(twoTypeWorksheet);
		retrivalTaskObject.portSelection(twoTypeWorksheet);
		
		double cycleTime = retrivalTaskObject.twoTypeCycleTime(twoTypeWorksheet);


		twoTypeQueueOfBinRetrival.erase(twoTypeQueueOfBinRetrival.begin());
		finishedRetriveTaskVector.push_back(retrivalTaskObject);

		if (retrivalTaskId == 600) {
			break;
		}
		retrivalTaskId++;


	}

	

#endif

	
	//Both type
#if 0
	
	retrivalTaskId{ 0 };
	while ((!bothTypeQueueOfBinRetrival.empty()) && useBoth){

		if (oneRoundOfRetrivalTask.size() == 0) {

			if (retrivalTaskId != 0) {

				for (int i = 0; i < numOfFirstRobots; i++) {
					bothTypeQueueOfBinRetrival.erase(bothTypeQueueOfBinRetrival.begin());
				}

			}

			for (int i = 0; i < numOfFirstRobots; i++) {
				oneRoundOfRetrivalTask.push_back(bothTypeQueueOfBinRetrival[i]);
			}

			//std::sort(oneRoundOfRetrivalTask.begin(), oneRoundOfRetrivalTask.end(), compareByZLocation();
			std::sort(oneRoundOfRetrivalTask.begin(), oneRoundOfRetrivalTask.end(),
				[](const Autostore::bin& a, const Autostore::bin& b) {
					auto az = a.zLocation;
					auto bz = b.zLocation;

					return az < bz;
				});
		}

		std::cout << "\nRetriving " << oneRoundOfRetrivalTask[0].locationName;

		if (oneRoundOfRetrivalTask[0].xLocation == 0 && oneRoundOfRetrivalTask[0].yLocation == 0) {
			//queueOfBinRetrival.erase(queueOfBinRetrival.begin());
			oneRoundOfRetrivalTask.erase(oneRoundOfRetrivalTask.begin());
			std::cout << "--------->This is deleted from queue!";
			continue;
		}
		if (oneRoundOfRetrivalTask[0].zLocation == 0) {
			//queueOfBinRetrival.erase(queueOfBinRetrival.begin());
			oneRoundOfRetrivalTask.erase(oneRoundOfRetrivalTask.begin());
			std::cout << "--------->This is deleted from queue!";
			continue;
		}

		retrivalTaskObject.reset();
		retrivalTaskObject.id = retrivalTaskId;
		retrivalTaskObject.binToRetrive = binsVector[oneRoundOfRetrivalTask[0].binId];

		worksheet_write_string(bothTypeWorksheet, retrivalTaskId + 1, 0, retrivalTaskObject.binToRetrive.locationName.c_str(), NULL);
		worksheet_write_number(bothTypeWorksheet, retrivalTaskId + 1, 1, retrivalTaskObject.binToRetrive.xLocation, NULL);
		worksheet_write_number(bothTypeWorksheet, retrivalTaskId + 1, 2, retrivalTaskObject.binToRetrive.yLocation, NULL);
		worksheet_write_number(bothTypeWorksheet, retrivalTaskId + 1, 3, retrivalTaskObject.binToRetrive.zLocation, NULL);

		bool twoTypeCondition;
		if (oneRoundOfRetrivalTask.size() <= (numOfFirstRobots - numOfSecondRobots)) { twoTypeCondition = false; }
		else { twoTypeCondition = true; }



		if (twoTypeCondition) {
			retrivalTaskObject.firstRobotSelection(bothTypeWorksheet);
			retrivalTaskObject.secondRobotSelection(bothTypeWorksheet);
			retrivalTaskObject.portSelection(bothTypeWorksheet);

			double cycleTime = retrivalTaskObject.twoTypeCycleTime(bothTypeWorksheet);
		}
		else
		{
			retrivalTaskObject.firstRobotSelection(bothTypeWorksheet);
			retrivalTaskObject.portSelection(bothTypeWorksheet);
			double cycleTime = retrivalTaskObject.oneTypeCycleTime(bothTypeWorksheet);
		}


		oneRoundOfRetrivalTask.erase(oneRoundOfRetrivalTask.begin());
		finishedRetriveTaskVector.push_back(retrivalTaskObject);


		if (retrivalTaskId == 300) {break;}
		retrivalTaskId++;


	}




	

#endif




	if (!useSecondRobot) { workbook_close(oneTypeWorkbook); }
	if (useSecondRobot) { workbook_close(twoTypeWorkbook); }
	if (useBoth) { workbook_close(bothTypeWorkbook); }

	//error handeling
#if 0
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

