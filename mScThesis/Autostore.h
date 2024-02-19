#pragma once

#include <string>
#include <iostream>
#include <set>
//#include <algorithm> // For std::shuffle
#include <random> // For std::default_random_engine
#include <chrono> // For std::chrono::system_clock
#include "AStar.h"
#include <vector>

#include <optional>



namespace Autostore {

	

	struct constantsAutostore {

		//Division x (meter)
		const double deltaX{ 0.7 };
		//Division y (meter)
		const double deltaY{ 0.5 };
		//Division z (meter)
		const double deltaZ{ 0.33 };
		//Exchange time( seconds )
		const double timeExchange{ 5 };
		//Locking and unlocking time( seconds )
		const double lockUnlockTime{ 1 };
		//Robot velocity(m/s)
		const double robotVelocity{ 2 };
		//Robot pick / deposit velocity(m/s)
		const double robotPickOrDepositeVelocity{ 1.6 };
		//Wheel exchange time( seconds )
		const double wheelExchangeTime{ 1 };
		//toward x time
		const double towardXCellTime{ deltaX / robotVelocity };
		//toward y time
		const double towardYCellTime{ deltaY / robotVelocity };
		//toward z time
		const double towardZCellTime{ deltaZ / robotPickOrDepositeVelocity };

		//
		int xLenghOfWarehouse{ -1 };
		int yLenghOfWarehouse{ -1 };
		int zLenghOfWarehouse{ -1 };

		//double hightOfBin{ 0 };

	};
	
	struct port {
		int xLocation{ -1 }; //tol	
		int yLocation{ -1 }; //arz 
		
		int id{ -1 };
	};

	class gridLocation
	{
	public:
		int xLocation{ -1 }; //tol	
		int yLocation{ -1 }; //arz 
		int zLocation{ -1 }; //depth

		long long int locationId{ -1 };
		long long int binId{ -1 };

		bool isFilledWithBin{ false };
		std::string locationName{ "namenotassigned!" };



		void gridFillerWithBin(int i_, int j_, int k_, long long int loacationId_)
		{
			
			
			locationId = loacationId_;
			locationName = "x[" + std::to_string(i_) + "]" + "y[" + std::to_string(j_) + "]" + "z[" + std::to_string(k_) + "]";
			xLocation = i_;//filling grid vector features
			yLocation = j_;
			zLocation = k_;

		}

		void gridReset()
		{

			int binId{ -1 };
			bool isFilledWithBin{ false };

		}



	};

	class bin {
	public:

		int xLocation{ -1 }; //tol	
		int yLocation{ -1 }; //arz 
		int zLocation{ -1 }; //depth

		long long int locationId{ -1 };

		long long int binId{ -1 };

		std::string binName{ "namenotassigned!" };
		std::string locationName{ "namenotassigned!" };

		void binFillerWithdata(int i_, int j_, int k_, long long int binid_)
		{
			binId = binid_;
			binName = "BinNO." + std::to_string(binid_);
			xLocation = i_;
			yLocation = j_;
			zLocation = k_;
		}

		void binReset()
		{
			xLocation = -1;	
			yLocation = -1; 
			zLocation = -1;

			locationId = -1;
			locationName = "namenotassigned!";
		}

	};

	class firstRobot{

	public:

		int xLocation{0}; //tol	
		int yLocation{0}; //arz 

		int id{ 0 };
		int binId{ 0 };
		bool isBusy{ false };

		double time{ 0 };

		std::string name{ "Name Not Assigned!" };

		void nameFillerFirstRobot(int id_)
		{
			id = id_;
			name = "FirstRobotNO" + std::to_string(id_);
		}

	};

	class secondRobot
	{


	public:
		int xLocation{0}; //tol	
		int yLocation{0}; //arz 

		int id{0};
		std::vector<int> binId{};
		bool isBusy{ false };

		std::string name{ "namenotassigned!" };




		void nameFillerSecondRobot(int id_)
		{
			id = id_ ;
			name = "SecondRobotNO"+std::to_string(id_);
		}


	};

	template <typename T>
	class VectorShuffler {
	public:
		// Function to shuffle a given vector
		std::vector<T> shuffleVector(const std::vector<T>& inputVector) {
			// Copy the input vector
			std::vector<T> outputVector = inputVector;

			// Obtain a time-based seed
			long long unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
	
			// Shuffle the copy randomly
			std::shuffle(outputVector.begin(), outputVector.end(), std::default_random_engine(seed));

			return outputVector;
		}
	};

	class retrivalTask {
	public:

		retrivalTask(std::vector<port>& portsVector, 
			std::vector<firstRobot>& firstRobotsVector, 
			std::vector<secondRobot>& secondRobotsVector, 
			std::vector<bin>& binsVector, 
			std::vector<std::vector<std::vector<Autostore::gridLocation>>>& gridLocationVector)
			:
			portsVector_(portsVector), 
			firstRobotsVector_(firstRobotsVector), 
			secondRobotsVector_(secondRobotsVector), 
			binsVector_(binsVector), 
			gridLocationVector_(gridLocationVector) {}

		///////////////////////////
		bin* binToRetrive_;
		bin binToRetrive;

		port selectedPort;
		firstRobot selectedfirstRobot;

		long long int id{ -1 };
		
		int minCostRobotToBin{ 1000000000 };
		int minCostBinToPort{ 100000000 };

		bool directAccessToBin{ false };

		int directionCost{ 0 };

		int numOfBinToRelocate{ 0 };

		
		///////////////////////////

		//std::vector<port>* mainPortsVector{};
		//std::vector<firstRobot>* mainFirstRobotsVector{};
		//std::vector<secondRobot>* mainSecondRobotsVector{};
		//std::vector<bin>* mainBinsVector{};
		//std::vector<std::vector<std::vector<Autostore::gridLocation>>>* mainGridLocationVector;

		std::vector<port> &portsVector_;
		std::vector<firstRobot> &firstRobotsVector_;
		std::vector<secondRobot> &secondRobotsVector_;
		std::vector<bin> &binsVector_;
		std::vector<std::vector<std::vector<Autostore::gridLocation>>> &gridLocationVector_;

		constantsAutostore constants;



	
		void reset() {

			id = -1;

			minCostRobotToBin = 1000000000 ;
			minCostBinToPort = 100000000 ;

			directAccessToBin = false ;

			directionCost = 0 ;

		};



		void firstRobotSelection() {

			int Cost_{ 0 };

			for (auto& robot : firstRobotsVector_) {

				Cost_ = manhattanCostRobot(robot);
				//std::cout << Cost_ << " ";

				if (Cost_ < minCostRobotToBin) {
					
					//std::cout << "inR ";
					minCostRobotToBin = Cost_;
					selectedfirstRobot = robot;

				}

			}

			std::cout << "Selected Robot:  " <<
				"Id:" << selectedfirstRobot.id <<
				" x:" << selectedfirstRobot.xLocation <<
				" y:" << selectedfirstRobot.yLocation <<"    ";

		}

		void portSelection() {
			
			int Cost_{ 0 };
			
			for (auto& port : portsVector_) {

				int Cost_ = manhattanCostPort(port);
				//std::cout << Cost_ << " ";

				if (Cost_ < minCostBinToPort) {
					//std::cout << "inP ";
					minCostBinToPort = Cost_;
					selectedPort = port;

				}
		
			}

			std::cout << "Selected Port:  " <<
				"Id:" << selectedPort.id <<
				" x:" << selectedPort.xLocation <<
				" y:" << selectedPort.yLocation << "\n";

		}

		int manhattanCostRobot(firstRobot robot_) {
			return{ abs(binToRetrive.xLocation - robot_.xLocation) + abs(binToRetrive.yLocation - robot_.yLocation) };
		};

		int manhattanCostPort(port port_) {
			return{ abs(binToRetrive.xLocation - port_.xLocation) + abs(binToRetrive.yLocation - port_.yLocation) };
		};






		









		double cycleTime()
		{
			std::cout << "\nrobotToBin ... ";
			auto robotToBinCycleTime_ = robotToBinCycleTime();
			std::cout << "robotToBinCycleTime: " << robotToBinCycleTime_ << "\n\n";


			auto elevatingCycleTime_ = elevatingCycleTime();
			std::cout << "\nelevatingCycleTime: " << elevatingCycleTime_ << "\n";

			std::cout << "\nrobotAndBinToPort ... \n";
			auto binToPortCycleTime_ = binToPortCycleTime();
			std::cout << "robotAndBinToPortCycleTime: " << binToPortCycleTime_ << "\n\n";

			//****************************************************************
			auto binX{ binToRetrive.xLocation };//bin to relocate
			auto binY{ binToRetrive.yLocation };
			auto binZ{ binToRetrive.zLocation };

			auto binId = binToRetrive.binId;


			gridLocationVector_[binX][binY][binZ].binId = -1;
			gridLocationVector_[binX][binY][binZ].isFilledWithBin = false;

			binsVector_[binId].xLocation = -1;
			binsVector_[binId].yLocation = -1;
			binsVector_[binId].zLocation = -1;

			binsVector_[binId].locationId = -1;
			binsVector_[binId].locationName = "namenotassigned!";

			//*****************************************************************

			return robotToBinCycleTime_ + elevatingCycleTime_ + binToPortCycleTime_;
		};

		//***********************************************************************************
		double robotToBinCycleTime() {

			AStar::Generator pathObject;
			pathObject.setWorldSize({ constants.xLenghOfWarehouse, constants.yLenghOfWarehouse });

			auto binX_ = binToRetrive.xLocation;
			auto binY_ = binToRetrive.yLocation;

			auto robotX_ = selectedfirstRobot.xLocation;
			auto robotY_ = selectedfirstRobot.yLocation;

			auto pathRobotToBin = pathObject.findPath({ robotX_, robotY_ }, { binX_, binY_ });
#if 0
			std::cout << "path robot to bin------------------------------------------------------------------ \n";
			for (auto& coordinate : pathRobotToBin) {
				std::cout << coordinate.x << "\t";
			}

			std::cout << "\n";
			for (auto& coordinate : pathRobotToBin) {
				std::cout << coordinate.y << "\t";
		}

#endif
			auto robotToBinCost = onGridRobotMovementCycleTime(pathRobotToBin);


			//change location of robot---------------------------------------------
#if 0
			firstRobotsVector_[selectedfirstRobot.id].xLocation = binX_;
			firstRobotsVector_[selectedfirstRobot.id].yLocation = binY_;
 #endif
			//---------------------------------------------------------------------

			return robotToBinCost;
	};

		double binToPortCycleTime() {


			AStar::Generator pathObject;
			pathObject.setWorldSize({ constants.xLenghOfWarehouse, constants.yLenghOfWarehouse });

			auto binX_ = binToRetrive.xLocation;
			auto binY_ = binToRetrive.yLocation;

			auto portX_ = selectedPort.xLocation;
			auto portY_ = selectedPort.yLocation;

			auto pathBinToPort = pathObject.findPath({ binX_, binY_ }, { portX_, portY_ });

			//---------------------------------------------------------------------
#if 0
			std::cout << "\npathBinToPort----------------------------------------------------------------------\n";
			for (auto& coordinate : pathBinToPort) {
				std::cout << coordinate.x << "\t";
			}

			std::cout << "\n";
			for (auto& coordinate : pathBinToPort) {
				std::cout << coordinate.y << "\t";
			}
#endif
			auto binToPortCost = onGridRobotMovementCycleTime(pathBinToPort);


			//change location of robot and bin---------------------------------------------

#if 0
			firstRobotsVector_[selectedfirstRobot.id].xLocation = portX_;
			firstRobotsVector_[selectedfirstRobot.id].yLocation = portY_;

			gridLocationVector_[binToRetrive.xLocation][binToRetrive.yLocation][binToRetrive.zLocation].gridReset();
			binsVector_[binToRetrive.binId].binReset();
 #endif


			//---------------------------------------------------------------------
			//std::cout << "\n";

			return binToPortCost;
		}

		double onGridRobotMovementCycleTime(const AStar::CoordinateList path_) {

			double beforeCost{ 0 }, aftereCost{ 0 }, totalCost{ 0 };

			if (path_.size() < 3) { // Need at least 3 points to detect a direction change
				std::cout << "Not enough points to detect direction change." << std::endl;
			}

			enum class Direction { towardX, towardY, None };

			Direction previousDirection = Direction::None;
			Direction currentDirection = Direction::None;

			int movesCount{ 0 }; // Tracks the number of moves in the current direction

			int movementBeforeDirectionChange{ 0 };
			int movementAfterDirectionChange{ 0 };

			for (size_t i = 1; i < path_.size(); ++i) {


				// Determine current direction------------------------------------------
				if (path_[i].x != path_[i - 1].x) { currentDirection = Direction::towardX; }
				else if (path_[i].y != path_[i - 1].y) { currentDirection = Direction::towardY; }


				// Check if direction has changed------------------------------------------------------
				if (currentDirection != previousDirection && previousDirection != Direction::None) {

					if (previousDirection == Direction::towardX) {

						std::cout << "\nDirection changed at (" << path_[i - 1].x << ", " << path_[i - 1].y << ")";
						std::cout << " after " << movesCount << " moves towardX. ";

						if (movesCount >= 6) { beforeCost = 4 + ((movesCount - 6) * constants.towardXCellTime); }
						else if (movesCount <= 3) { beforeCost = 2; }//1, 2, 3
						else if (movesCount < 6 && movesCount > 3) { beforeCost = 3; }//4,5

					}
					else if (previousDirection == Direction::towardY) {

						std::cout << "\nDirection changed at (" << path_[i - 1].x << ", " << path_[i - 1].y << ")";
						std::cout << " after " << movesCount << " moves towardY. ";

						if (movesCount >= 8) { beforeCost = 4 + ((movesCount - 8) * constants.towardYCellTime); }
						else if (movesCount <= 4) { beforeCost = 2; }
						else if (movesCount < 8 && movesCount > 4) { beforeCost = 3; }

					}
					//-----------------------------------------------------------------------------------

					movesCount = 0; // Reset count after a direction change
				}

				// Increment moves count if there was movement
				if (currentDirection != Direction::None) { movesCount++; }

				previousDirection = currentDirection;
			}//for loop Finished

			// Print the number of moves after the last direction change (or if there was no change)
			if (movesCount > 0) {

				if (currentDirection == Direction::towardX) {

					std::cout << "Then Moved " << movesCount << " locations towardX." << "\n";

					if (movesCount >= 6) { aftereCost = 4 + ((movesCount - 6) * constants.towardXCellTime); }
					else if (movesCount <= 3) { aftereCost = 2; }
					else if (movesCount < 6 && movesCount > 3) { aftereCost = 3; }

				}
				else if (currentDirection == Direction::towardY) {

					std::cout << "Then Moved " << movesCount << " locations towardY." << "\n";

					if (movesCount >= 8) { aftereCost = 4 + ((movesCount - 8) * constants.towardYCellTime); }
					else if (movesCount <= 4) { aftereCost = 2; }
					else if (movesCount < 8 && movesCount > 4) { aftereCost = 3; }

				}

			}

			totalCost = beforeCost + constants.wheelExchangeTime + aftereCost;

			return totalCost;
		};
		//************************************************************************************


		
		
		double elevatingCycleTime() {

			auto elevatingCells = constants.zLenghOfWarehouse - binToRetrive.zLocation + 1;
			double cycleTime = elevatingCells * constants.towardZCellTime;
			cycleTime = cycleTime + constants.lockUnlockTime;
			
			goalBinIsDirectAccess();

			if (directAccessToBin) {
				std::cout << "\ndirectAccessToBin\n";
				return cycleTime;
			}
			else {
				return cycleTime + reLocationCycleTime();
			}
		}

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		void goalBinIsDirectAccess() {

			auto x_ = binToRetrive.xLocation;
			auto y_ = binToRetrive.yLocation;
			auto z_ = binToRetrive.zLocation + 1;// plus one

			directAccessToBin = ((gridLocationVector_[x_][y_][z_].isFilledWithBin == false) ? true : false);

		}

		double reLocationCycleTime() {

			std::cout << "No direct Access\n" << "relocation in progress ...\n";


			int binX{ binToRetrive.xLocation };//bin to relocate
			int binY{ binToRetrive.yLocation };
			int binZ{};

			int newX{};
			int newY{};
			int newZ{};


			double cycleTime{ 0 };
			int numOfElevatingCellsBinXBinY{ 0 }, numOfDepositCellsNewXNewY{ 0 };
			bin topBinForRelocationNum, topBin;


			topBinForRelocationNum = findTopBin(binX, binY);
			numOfBinToRelocate = topBinForRelocationNum.zLocation - binToRetrive.zLocation;
			if (numOfBinToRelocate < 0) {
				std::cout << "";
				topBinForRelocationNum = findTopBin(binX, binY);
			}
			std::cout << "numOfBinToRelocate: " << numOfBinToRelocate << "";




			for (int i = 0; i < numOfBinToRelocate; i++) {

				auto bestLocation = bestLocationForRelocation();

				int newX{ bestLocation.xLocation };
				int newY{ bestLocation.yLocation };
				int newZ{ bestLocation.zLocation };


				//elevating cycle time for top bin on goal x and y column
				auto binToRelocate = findTopBin(binX, binY);
				binZ = binToRelocate.zLocation;

				numOfElevatingCellsBinXBinY = constants.zLenghOfWarehouse - binZ + 1;
				cycleTime = cycleTime + numOfElevatingCellsBinXBinY * constants.towardZCellTime;
				cycleTime = cycleTime + constants.lockUnlockTime;





				//direction change and coming back cycle time
				cycleTime = cycleTime + (2 * directionCost);





				// depositCells cycle time
				numOfDepositCellsNewXNewY = constants.zLenghOfWarehouse - newZ + 1;
				cycleTime = cycleTime + numOfDepositCellsNewXNewY * constants.towardZCellTime;
				cycleTime = cycleTime + constants.lockUnlockTime;




				//*********************change location of bin*************************
				binsVector_[binToRelocate.binId].xLocation = newX;
				binsVector_[binToRelocate.binId].yLocation = newY;
				binsVector_[binToRelocate.binId].zLocation = newZ;

				binsVector_[binToRelocate.binId].locationId = bestLocation.locationId;
				binsVector_[binToRelocate.binId].locationName = bestLocation.locationName;

				//**********************grid reset**************************************
				gridLocationVector_[binX][binY][binZ].binId = -1;
				gridLocationVector_[binX][binY][binZ].isFilledWithBin = false;

				gridLocationVector_[newX][newY][newZ].binId = binToRelocate.binId;
				gridLocationVector_[newX][newY][newZ].isFilledWithBin = true;

				//auto binid = topBin.binId;
								//gridLocationVector_[binX][binY][binZ].gridReset();
								//if (binToRetrive.xLocation == 8 && binToRetrive.yLocation == 22 && binToRetrive.xLocation == 9) {
				//	std::cout << "";
				//
								//binsVector_[binid].xLocation = -1;
				//binsVector_[binid].yLocation = -1;
				//binsVector_[binid].zLocation = -1;
								//binsVector_[binid].locationId = -1;
				//binsVector_[binid].locationName = "namenotassigned!";
								//gridLocationVector_[binX][binY][binZ].binId = -1;
				//gridLocationVector_[binX][binY][binZ].isFilledWithBin = false;
								//binsVector_[binid].xLocation = newX;
				//binsVector_[binid].yLocation = newY;
				//binsVector_[binid].zLocation = newZ;
								//binsVector_[binid].locationId = gridLocationVector_[newX][newY][newZ].locationId;
				//binsVector_[binid].locationName = gridLocationVector_[newX][newY][newZ].locationName;
								//gridLocationVector_[newX][newY][newZ].binId = binid;
				//gridLocationVector_[newX][newY][newZ].isFilledWithBin = true;
								//std::cout << "cycletime: " << cycleTime << "";

			}

			return cycleTime;
		};

		bin findTopBin(int x_, int y_) {

			//std::cout<<"findTopBin: " << x_ << " " << y_ << "\n";
			//if (x_ >= 0 && y_ >= 0 && 
			//	x_ <= constants.xLenghOfWarehouse -1 && 
			//	y_ <= constants.yLenghOfWarehouse - 1 &&
			//	gridLocationVector_[x_][y_][0].isFilledWithBin == true
						//	) {

			for (auto& location : gridLocationVector_[x_][y_]) {


				if (location.isFilledWithBin == false) {
					auto binid = gridLocationVector_[x_][y_][(location.zLocation) - 1].binId;
					auto& bin = binsVector_[binid];
					//std::cout << "\n";
					return bin;
				}


				else if (location.isFilledWithBin == true && location.zLocation == constants.zLenghOfWarehouse - 1) {
					return binsVector_[gridLocationVector_[x_][y_][location.zLocation].binId];;
				}

				//else if (bin.binId == -1 || bin.zLocation == constants.zLenghOfWarehouse - 1) {
				//	return binsVector_[gridLocationVector_[x_][y_][bin.zLocation].binId];;
				//}
			}
			//}
			//throw std::runtime_error("Not In Range");

		};

		gridLocation bestLocationForRelocation() {
			
			// Define the search pattern for the 8 surrounding cells and their cost
			int directions[8][3] = { 
				{-1, 0, 1}, {1, 0, 1}, 
				{0, -1, 1}, {0, 1, 1}, 
				{-1, -1, 3},{-1, 1, 3}, 
				{1, -1, 3}, {1, 1, 3} 
			};

			
			int binX = binToRetrive.xLocation;
			int binY = binToRetrive.yLocation;

			bin newTopbin_;
			double cost_{};

				
			double lowestCost = 1000000000000000.0;
			auto& bestLocation = gridLocationVector_[0][0][0];

			//std::cout << "binX " << binX << " binY" << binY << "\n";

			for (auto& dir : directions) {


				int newX = binX + dir[0];
				int newY = binY + dir[1];



				if (newX >= 0 && newX <= constants.xLenghOfWarehouse - 1 &&
					newY >= 0 && newY <= constants.yLenghOfWarehouse - 1 &&
					(gridLocationVector_[newX][newY][0].isFilledWithBin == true)){ //for excluded grid location)

					//(newX < 0 || newY < 0 ||
					//newX > constants.xLenghOfWarehouse - 1 ||
					//newY >= constants.yLenghOfWarehouse - 1 ||
					//gridLocationVector_[newX][newY][0].binId == -1
					//(newX == constants.xLenghOfWarehouse / 2 && newY == 0) ||
					//(newX == 0 && newY == constants.yLenghOfWarehouse / 2) ||
					//(newX == constants.xLenghOfWarehouse -1  && newY == constants.yLenghOfWarehouse / 2)){

					int newZ = findTopBin(newX, newY).zLocation + 1;
					if (newZ == constants.zLenghOfWarehouse - 1) { continue; }

					auto degradingCells = constants.zLenghOfWarehouse - newZ;


					double cycleTime = 0;
					cycleTime = degradingCells * constants.towardZCellTime;
					cycleTime = cycleTime + constants.lockUnlockTime + dir[2]; // dir[2] is the cost of relocation on top grid

					cost_ = cycleTime;




					if (cost_ < lowestCost) {
						//std::cout << "\ninnnnn" << cost_ << " ";
						lowestCost = cost_;
						bestLocation = gridLocationVector_[newX][newY][newZ];
						directionCost = dir[2];
					}

					//if (newX > 0 && newX < constants.xLenghOfWarehouse - 1 &&
					//	newY > 0 && newY < constants.yLenghOfWarehouse - 1 &&
					//	(gridLocationVector_[newX][newY][0].binId != -1) && //for excluded grid location
					//	(gridLocationVector_[newX][newY][newZ].binId == -1)) {
											//std::cout << "innnnnnnnnnnnnnnnnnn\n";
						//std::cout << "newX " << newX << " newy" << newY << " newz" << newZ <<"\n";

				}
				else {
					//std::cout << "direction excluded\n";
					continue;

				}

				//std::cout << "top bin z" << findTopBin(bestLocation.xLocation, bestLocation.yLocation).zLocation ;
				//std::cout << "\nBestLocation: " << bestLocation.locationName;
				

			}
			return bestLocation;
		}






		

	
	};


};



