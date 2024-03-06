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
#include "xlsxwriter.h"

 

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
		const double firstRobotPickOrDepositeVelocity{ 1.6 };
		//Wheel exchange time( seconds )
		const double wheelExchangeTime{ 1 };
		//toward x time
		const double towardXCellTime{ deltaX / robotVelocity };
		//toward y time
		const double towardYCellTime{ deltaY / robotVelocity };
		//toward z time
		const double firstRobotTowardZCellTime{ deltaZ / firstRobotPickOrDepositeVelocity };

		//
		int xLenghOfWarehouse{ -1 };
		int yLenghOfWarehouse{ -1 };
		int zLenghOfWarehouse{ -1 };

		int secondRobotCapacity{ 0 };

		const double secondRobotPickOrDepositeVelocityUnloaded{ 1.6 };
		const double secondRobotPickOrDepositeVelocityAfterLoaed{ 1.5 };
		const double secondRobotPickOrDepositeVelocityLoading{ 1.4 };



		const double secondRobotTowardZCellTimeUnloaded{ deltaZ / secondRobotPickOrDepositeVelocityUnloaded };
		const double secondRobotTowardZCellTimeAfterLoaed{ deltaZ / secondRobotPickOrDepositeVelocityAfterLoaed };
		const double secondRobotTowardZCellTimeLoading{ deltaZ / secondRobotPickOrDepositeVelocityLoading };
		const double changeLocationSecondRobotLoaded{ 3 };

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
		double numOfTasks{ 0 };
		std::string name{ "Name Not Assigned!" };
		std::vector<bin> bins{};


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
		std::vector<bin> bins{};

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
		//definitions
#if 1
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
		bin binToRetrive;
		port selectedPort;
		firstRobot selectedfirstRobot;
		std::vector<secondRobot> selectedsecondRobotsVector;
		constantsAutostore constants;

		int numOfSecondRobot{ 0 };
		long long int id{ -1 };
		int minCostRobotToBin{ 1000000000 };
		int minCostBinToPort{ 100000000 };
		bool directAccessToBin{ false };
		int directionCost{ 0 };
		int numOfBinToRelocate{ 0 };

		std::vector<port> &portsVector_;
		std::vector<firstRobot> &firstRobotsVector_;
		std::vector<secondRobot> &secondRobotsVector_;
		std::vector<bin> &binsVector_;
		std::vector<std::vector<std::vector<Autostore::gridLocation>>> &gridLocationVector_;

#endif


		//selection and find
#if 1
		void reset() {

			id = -1;

			minCostRobotToBin = 1000000000 ;
			minCostBinToPort = 100000000 ;

			directAccessToBin = false ;

			directionCost = 0 ;

			numOfSecondRobot = 0;

		};

		void firstRobotSelection() {

			int Cost_{ 0 };

			for (auto& robot : firstRobotsVector_ ) {

				Cost_ = manhattanCostFirstRobot(robot);

				if (Cost_ < minCostRobotToBin && robot.isBusy == false) {
					
					minCostRobotToBin = Cost_;
					selectedfirstRobot = robot;			

				}

			}

			firstRobotsVector_[selectedfirstRobot.id].isBusy = true;


			//std::cout << "FirstRobot:" <<
			//	"Id[" << selectedfirstRobot.id << "]" <<
			//	"x[" << selectedfirstRobot.xLocation << "]" <<
			//	"y[" << selectedfirstRobot.yLocation << "]";

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


			//std::cout << " Port:  " <<
			//	"Id[" << selectedPort.id << "]" <<
			//	"x[" << selectedPort.xLocation << "]" <<
			//	"y[" << selectedPort.yLocation << "]";

		}

		int manhattanCostFirstRobot(firstRobot robot_) {
			return{ abs(binToRetrive.xLocation - robot_.xLocation) + abs(binToRetrive.yLocation - robot_.yLocation) };
		};

		int manhattanCostPort(port port_) {
			return{ abs(binToRetrive.xLocation - port_.xLocation) + abs(binToRetrive.yLocation - port_.yLocation) };
		};

		void secondRobotSelection() {
			//std::cout << " SecondRobot:";
			int Cost_{ 0 };

			if (!directAccessToBin) {
				auto topbinZLocation = findTopBin(binToRetrive.xLocation, binToRetrive.yLocation).zLocation;
				auto numOfTopBins = topbinZLocation - binToRetrive.zLocation;

				for (int i = 0; i <= numOfTopBins / constants.secondRobotCapacity; i++) {

					if ((i * 5) < numOfTopBins &&
						numOfTopBins <= ((i * constants.secondRobotCapacity) + constants.secondRobotCapacity)) {

						//std::cout << "numOfTopBins" << numOfTopBins;
						if (size(secondRobotsVector_) >= (i + 1)) { numOfSecondRobot = (i + 1); }
						else if (size(secondRobotsVector_) < (i + 1)) { numOfSecondRobot = size(secondRobotsVector_); }
						else { "sth Wrong in secondRobotSelection"; }

					}

				}

			}
			else { numOfSecondRobot = 0; }



			for (int i = 0; i < numOfSecondRobot; i++) {
				int selectedSecondRobotId{ -1 };
				auto minCost_{ 10000000000000 };

				for (auto& robot : secondRobotsVector_) {

					Cost_ = manhattanCostSecondRobot(robot);

					if (Cost_ < minCost_ && robot.isBusy == false) {

						minCost_ = Cost_;
						selectedSecondRobotId = robot.id;

					}

				}



				secondRobotsVector_[selectedSecondRobotId].isBusy = true;
				selectedsecondRobotsVector.push_back(secondRobotsVector_[selectedSecondRobotId]);

				//std::cout <<
				//	"Id[" << secondRobotsVector_[selectedSecondRobotId].id << "]" <<
				//	"x[" << secondRobotsVector_[selectedSecondRobotId].xLocation << "]" <<
				//	"y[" << secondRobotsVector_[selectedSecondRobotId].yLocation << "] ";

				//worksheet_write_number(oneTypeWorksheet_, id + 1, 6, secondRobotsVector_[selectedSecondRobotId].xLocation, NULL);
				//worksheet_write_number(oneTypeWorksheet_, id + 1, 7, secondRobotsVector_[selectedSecondRobotId].yLocation, NULL);

			}

		}

		int manhattanCostSecondRobot(secondRobot robot_) {
			return{ abs(binToRetrive.xLocation - robot_.xLocation) + abs(binToRetrive.yLocation - robot_.yLocation) };
		};

		bin findTopBin(int x_, int y_) {

			for (auto& location : gridLocationVector_[x_][y_]) {


				if (location.isFilledWithBin == false) {
					auto binid = gridLocationVector_[x_][y_][(location.zLocation) - 1].binId;
					auto& bin = binsVector_[binid];

					return bin;
				}


				else if (location.isFilledWithBin == true && location.zLocation == constants.zLenghOfWarehouse - 1) {
					return binsVector_[gridLocationVector_[x_][y_][location.zLocation].binId];;
				}

			}

		};

		void goalBinIsDirectAccess() {

			auto x_ = binToRetrive.xLocation;
			auto y_ = binToRetrive.yLocation;
			auto z_ = binToRetrive.zLocation + 1;// plus one

			directAccessToBin = ((gridLocationVector_[x_][y_][z_].isFilledWithBin == false) ? true : false);

		}

#endif



		double onGridRobotMovementCycleTime(const AStar::CoordinateList path_) {

			double beforeCost{ 0 }, aftereCost{ 0 }, totalCost{ 0 };

			if (path_.size() < 3) { // Need at least 3 points to detect a direction change
				std::cout << "---------> Not enough points to detect direction change.";
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

						//std::cout << "\nDirection changed at (" << path_[i - 1].x << ", " << path_[i - 1].y << ")";
						//std::cout << " after " << movesCount << " moves towardX. ";

						if (movesCount >= 6) { beforeCost = 4 + ((movesCount - 6) * constants.towardXCellTime); }
						else if (movesCount <= 3) { beforeCost = 2; }//1, 2, 3
						else if (movesCount < 6 && movesCount > 3) { beforeCost = 3; }//4,5

					}
					else if (previousDirection == Direction::towardY) {

						//std::cout << "\nDirection changed at (" << path_[i - 1].x << ", " << path_[i - 1].y << ")";
						//std::cout << " after " << movesCount << " moves towardY. ";

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

					//std::cout << "Then Moved " << movesCount << " locations towardX." << "\n";

					if (movesCount >= 6) { aftereCost = 4 + ((movesCount - 6) * constants.towardXCellTime); }
					else if (movesCount <= 3) { aftereCost = 2; }
					else if (movesCount < 6 && movesCount > 3) { aftereCost = 3; }

				}
				else if (currentDirection == Direction::towardY) {

					//std::cout << "Then Moved " << movesCount << " locations towardY." << "\n";

					if (movesCount >= 8) { aftereCost = 4 + ((movesCount - 8) * constants.towardYCellTime); }
					else if (movesCount <= 4) { aftereCost = 2; }
					else if (movesCount < 8 && movesCount > 4) { aftereCost = 3; }

				}

			}

			totalCost = beforeCost + constants.wheelExchangeTime + aftereCost;

			return totalCost;
		};

		double firstRobotToBinCycleTime() {

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

			auto binToPortCost = onGridRobotMovementCycleTime(pathBinToPort);

			return binToPortCost;
		}

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
					(gridLocationVector_[newX][newY][0].isFilledWithBin == true)) { //for excluded grid location)

					int newZ = findTopBin(newX, newY).zLocation + 1;
					if (newZ == constants.zLenghOfWarehouse) { continue; }

					auto degradingCells = constants.zLenghOfWarehouse - newZ;


					double cycleTime = 0;
					cycleTime = degradingCells * constants.firstRobotTowardZCellTime;
					cycleTime = cycleTime + constants.lockUnlockTime + dir[2]; // dir[2] is the cost of relocation on top grid

					cost_ = cycleTime;




					if (cost_ < lowestCost) {
						//std::cout << "\ninnnnn" << cost_ << " ";
						lowestCost = cost_;
						bestLocation = gridLocationVector_[newX][newY][newZ];
						directionCost = dir[2];
					}


				}
				else {
					continue;
				}



			}
			return bestLocation;
		}




		//One type CT
#if 1

		double oneTypeCycleTime(lxw_worksheet* worksheet_ )
		{
			auto firstRobotToBinCycleTime_ = firstRobotToBinCycleTime();
			worksheet_write_number(worksheet_, id + 1, 9, firstRobotToBinCycleTime_, NULL);

			auto elevatingCycleTime_ = oneTypeElevatingCycleTime(worksheet_);//14 15 8
			worksheet_write_number(worksheet_, id + 1, 10, elevatingCycleTime_, NULL);
			

			auto binToPortCycleTime_ = 2 * binToPortCycleTime();
			worksheet_write_number(worksheet_, id + 1, 12, binToPortCycleTime_, NULL);
			worksheet_write_number(worksheet_, id + 1, 13, binToPortCycleTime_, NULL);//port to bin

			//change Location
#if 1
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
			binsVector_[binId].locationName = "Retrived!";


			firstRobotsVector_[selectedfirstRobot.id].xLocation = selectedPort.xLocation;
			firstRobotsVector_[selectedfirstRobot.id].yLocation = selectedPort.yLocation;
#endif
			
			auto oneTypeLoweringCycleTime_ = oneTypeLoweringCycleTime(elevatingCycleTime_);
			worksheet_write_number(worksheet_, id + 1, 11, oneTypeLoweringCycleTime_, NULL);
			//*****************************************************************

			auto totalCycleTime{ 
				firstRobotToBinCycleTime_ + 
				elevatingCycleTime_ +
				oneTypeLoweringCycleTime_ +
				binToPortCycleTime_ };


			return totalCycleTime;
		};

		//***********************************************************************************

		double oneTypeElevatingCycleTime(lxw_worksheet* worksheet_) {

			auto elevatingCells = constants.zLenghOfWarehouse - binToRetrive.zLocation + 1;
			double elevatingGoalBinCycleTime = elevatingCells * constants.firstRobotTowardZCellTime;
			elevatingGoalBinCycleTime = elevatingGoalBinCycleTime + constants.lockUnlockTime;
			
			goalBinIsDirectAccess();
			auto elevatingRelocationCT = reLocationCycleTime(worksheet_);
			
			
			worksheet_write_number(worksheet_, id + 1, 14, elevatingGoalBinCycleTime, NULL);
			worksheet_write_number(worksheet_, id + 1, 15, elevatingRelocationCT, NULL);

			if (directAccessToBin) {
				return elevatingGoalBinCycleTime;
			}
			else {
				return elevatingGoalBinCycleTime + elevatingRelocationCT;
			}
		}

		double oneTypeLoweringCycleTime(double elevatingCycleTime_) {

			auto elevatingCells = constants.zLenghOfWarehouse - binToRetrive.zLocation + 1;
			double elevatingGoalBinCycleTime = elevatingCells * constants.firstRobotTowardZCellTime;
			elevatingGoalBinCycleTime = elevatingGoalBinCycleTime + constants.lockUnlockTime;

			auto loweringRelocationCT = elevatingCycleTime_ - elevatingGoalBinCycleTime;

			auto newX{ binToRetrive.xLocation };
			auto newY{ binToRetrive.yLocation };
			auto newZ{ binToRetrive.zLocation };

			for (auto it = selectedfirstRobot.bins.rbegin(); it != selectedfirstRobot.bins.rend(); ++it) {
				auto& binToRelocate_ = *it;
			

				auto binX{ binsVector_[binToRelocate_.binId].xLocation };
				auto binY{ binsVector_[binToRelocate_.binId].yLocation };
				auto binZ{ binsVector_[binToRelocate_.binId].zLocation };
				
				////**********************grid reset**************************************
				gridLocationVector_[binX][binY][binZ].binId = -1;
				gridLocationVector_[binX][binY][binZ].isFilledWithBin = false;

				////**********************grid reset**************************************
				gridLocationVector_[newX][newY][newZ].binId = binToRelocate_.binId;
				gridLocationVector_[newX][newY][newZ].isFilledWithBin = true;
				
				//*********************change location of bin*************************
				binsVector_[binToRelocate_.binId].xLocation = newX;
				binsVector_[binToRelocate_.binId].yLocation = newY;
				binsVector_[binToRelocate_.binId].zLocation = newZ;

				binsVector_[binToRelocate_.binId].locationId = gridLocationVector_[newX][newY][newZ].locationId;
				binsVector_[binToRelocate_.binId].locationName = gridLocationVector_[newX][newY][newZ].locationName;


				newZ = newZ + 1;
			}
			selectedfirstRobot.bins.clear();
			firstRobotsVector_[selectedfirstRobot.id].bins.clear();
			
			return loweringRelocationCT;
		}

		double reLocationCycleTime(lxw_worksheet* worksheet_) {

			//std::cout << "No direct Access\n" << "relocation in progress ...\n";


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
			worksheet_write_number(worksheet_, id + 1, 8, numOfBinToRelocate, NULL);




			for (int i = 0; i < numOfBinToRelocate; i++) {

				auto bestLocation = bestLocationForRelocation();

				int newX{ bestLocation.xLocation };
				int newY{ bestLocation.yLocation };
				int newZ{ bestLocation.zLocation };


				//elevating cycle time for top bin on goal x and y column
				auto binToRelocate = findTopBin(binX, binY);
				
				binZ = binToRelocate.zLocation;

				numOfElevatingCellsBinXBinY = constants.zLenghOfWarehouse - binZ + 1;
				cycleTime = cycleTime + (numOfElevatingCellsBinXBinY * constants.firstRobotTowardZCellTime);
				cycleTime = cycleTime + constants.lockUnlockTime;





				//direction change and coming back cycle time
				cycleTime = cycleTime + (2 * directionCost);




				// depositCells cycle time
				numOfDepositCellsNewXNewY = constants.zLenghOfWarehouse - newZ + 1;
				cycleTime = cycleTime + (numOfDepositCellsNewXNewY * constants.firstRobotTowardZCellTime);
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

				//**********************************************************************
				selectedfirstRobot.bins.push_back(binsVector_[binToRelocate.binId]);

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

#endif


		//two type CT
#if 1

		double twoTypeCycleTime(lxw_worksheet* oneTypeWorksheet_)
		{
			auto firstRobotToBinCycleTime_ = firstRobotToBinCycleTime();
			worksheet_write_number(oneTypeWorksheet_, id + 1, 9, firstRobotToBinCycleTime_, NULL);

			auto secondRobotToBinCycleTime_ = secondRobotToBinCycleTime();
			worksheet_write_number(oneTypeWorksheet_, id + 1, 10, secondRobotToBinCycleTime_, NULL);

			auto twoTypeElevatingCycleTime_ = twoTypeElevatingCycleTime();
			worksheet_write_number(oneTypeWorksheet_, id + 1, 12, twoTypeElevatingCycleTime_, NULL);

			auto binToPortCycleTime_ = binToPortCycleTime();
			worksheet_write_number(oneTypeWorksheet_, id + 1, 14, binToPortCycleTime_, NULL);



			//****************bin & grid & secondR & FR*****************************
#if 1
			auto binX{ binToRetrive.xLocation };//bin to relocate
			auto binY{ binToRetrive.yLocation };
			auto binZ{ binToRetrive.zLocation };

			auto binId = binToRetrive.binId;


			gridLocationVector_[binX][binY][binZ].binId = -3;
			gridLocationVector_[binX][binY][binZ].isFilledWithBin = false;

			binsVector_[binId].xLocation = -3;
			binsVector_[binId].yLocation = -3;
			binsVector_[binId].zLocation = -3;

			binsVector_[binId].locationId = -3;
			binsVector_[binId].locationName = "Retrived!-3";

			firstRobotsVector_[selectedfirstRobot.id].xLocation = selectedPort.xLocation;
			firstRobotsVector_[selectedfirstRobot.id].yLocation = selectedPort.yLocation;

			for (auto& selectedSecondRobot : selectedsecondRobotsVector) {
				secondRobotsVector_[selectedSecondRobot.id].xLocation = binX;
				secondRobotsVector_[selectedSecondRobot.id].yLocation = binY;
			}

			firstRobotsVector_[selectedfirstRobot.id].xLocation = selectedPort.xLocation;
			firstRobotsVector_[selectedfirstRobot.id].yLocation = selectedPort.yLocation;
#endif
			//*****************************************************************


			auto twoTypeLoweringCycleTime_ = twoTypeLoweringCycleTime();
			worksheet_write_number(oneTypeWorksheet_, id + 1, 13, twoTypeLoweringCycleTime_, NULL);

			auto robotToBinCycleTime_{ 0.0 };
			if (firstRobotToBinCycleTime_ > secondRobotToBinCycleTime_ + twoTypeElevatingCycleTime_) { robotToBinCycleTime_ = firstRobotToBinCycleTime_; }
			else { robotToBinCycleTime_ = secondRobotToBinCycleTime_; }
			worksheet_write_number(oneTypeWorksheet_, id + 1, 11, twoTypeLoweringCycleTime_, NULL);

			auto totalCycleTime = 
				
				robotToBinCycleTime_ +
				twoTypeElevatingCycleTime_ +
				binToPortCycleTime_ +
				twoTypeLoweringCycleTime_;
				

			return totalCycleTime;
		};
		//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

		double secondRobotToBinCycleTime() {
			AStar::Generator pathObject;
			pathObject.setWorldSize({ constants.xLenghOfWarehouse, constants.yLenghOfWarehouse });

			auto binX_ = binToRetrive.xLocation;
			auto binY_ = binToRetrive.yLocation;

			double robotToBinCost{ 0.0 };
			double maxRobotToBinTime{ 0.0 };

			for (auto& selectedSecondRobot : selectedsecondRobotsVector) {

				auto robotX_ = selectedSecondRobot.xLocation;
				auto robotY_ = selectedSecondRobot.yLocation;

				auto pathRobotToBin = pathObject.findPath({ robotX_, robotY_ }, { binX_, binY_ });

				robotToBinCost =  onGridRobotMovementCycleTime(pathRobotToBin);

				if (robotToBinCost > maxRobotToBinTime) {
					maxRobotToBinTime = robotToBinCost;
				}

				

			}


			return maxRobotToBinTime;
		}

		double twoTypeElevatingCycleTime() {
			//double secondRobotcost_{0.0};
			//double firstRobotcost_{0.0};

			auto topbinZLocation = findTopBin(binToRetrive.xLocation, binToRetrive.yLocation).zLocation;
			auto numOfTopBins = topbinZLocation - binToRetrive.zLocation;
			auto numOfSecondRobot = size(selectedsecondRobotsVector);
			int numOfTopBinsLeft{ numOfTopBins };

			//for goal bin
			auto elevatingCells = constants.zLenghOfWarehouse - binToRetrive.zLocation + 1;
			double cycleTime = elevatingCells * constants.firstRobotTowardZCellTime;
			cycleTime = cycleTime + constants.lockUnlockTime;




			//for relocation bins
			for (auto& robot : selectedsecondRobotsVector) {

				topbinZLocation = findTopBin(binToRetrive.xLocation, binToRetrive.yLocation).zLocation;

				auto loweringCellsUnloaded = constants.zLenghOfWarehouse - topbinZLocation;
				auto loweringTimeUnloaded = loweringCellsUnloaded * constants.secondRobotTowardZCellTimeUnloaded;



				int loweringCellsLoading{ 0 };
				if (numOfTopBinsLeft >= constants.secondRobotCapacity) {
					loweringCellsLoading = constants.secondRobotCapacity;
				}
				else if (numOfTopBinsLeft < constants.secondRobotCapacity) {
					loweringCellsLoading = numOfTopBinsLeft;
				}
				auto loweringTimeLoading = loweringCellsLoading * constants.secondRobotTowardZCellTimeLoading;



				auto elevatingCellsLoaded = loweringCellsUnloaded + loweringCellsLoading;
				auto elevatingTimeLoaded = elevatingCellsLoaded * constants.secondRobotTowardZCellTimeAfterLoaed;


				double cycleTime_ = 
					loweringTimeUnloaded + loweringTimeLoading +
					constants.lockUnlockTime + elevatingTimeLoaded +
					constants.changeLocationSecondRobotLoaded;


				cycleTime = cycleTime + cycleTime_;
				
				auto binX = binToRetrive.xLocation;
				auto binY = binToRetrive.yLocation;
				auto binZ = findTopBin(binX, binY).zLocation;

				for (int i = 0; i < loweringCellsLoading; i++) {
					auto binZ_ = binZ - i;

					auto binid = gridLocationVector_[binX][binY][binZ_].binId;
					auto& bin = binsVector_[binid];

					
					//*********************reset bin*************************
					binsVector_[binid].xLocation = -2;
					binsVector_[binid].yLocation = -2;
					binsVector_[binid].zLocation = -2;

					binsVector_[binid].locationId = -2;
					binsVector_[binid].locationName = "Retrived!";
					//**********************************************************
					secondRobotsVector_[robot.id].bins.push_back(binsVector_[binid]);
					robot.bins.push_back(binsVector_[binid]);
					//**********************grid reset**************************************
					gridLocationVector_[binX][binY][binZ_].binId = -2;
					gridLocationVector_[binX][binY][binZ_].isFilledWithBin = false;

				}
				numOfTopBinsLeft = numOfTopBinsLeft - loweringCellsLoading;

			}



			return cycleTime;
		}

		double twoTypeLoweringCycleTime() {

			int topbinZLocation_{ 0 };
			double cycleTime{ 0.0 };
			//for relocation bins
			for (auto it = selectedsecondRobotsVector.rbegin(); it != selectedsecondRobotsVector.rend(); ++it) {
				auto& robot = *it;
				
				auto binX = binToRetrive.xLocation;
				auto binY = binToRetrive.yLocation;
				auto binZ = findTopBin(binX, binY).zLocation;
				topbinZLocation_ = binZ;

				auto loweringCellsLoaded_ = constants.zLenghOfWarehouse - topbinZLocation_;
				auto loweringTimeLoaded_ = loweringCellsLoaded_ * constants.secondRobotTowardZCellTimeAfterLoaed;


				auto elevatingCellsUnoading_{ size(secondRobotsVector_[robot.id].bins) };
				auto elevatingTimeUnoading_ = elevatingCellsUnoading_ * constants.secondRobotTowardZCellTimeLoading;



				auto elevatingCellsUnloaded_ = loweringCellsLoaded_ - elevatingCellsUnoading_;
				auto elevatingTimeUnloaded_ = elevatingCellsUnloaded_ * constants.secondRobotTowardZCellTimeUnloaded;

				cycleTime =
					cycleTime +
					loweringTimeLoaded_ + 
					constants.lockUnlockTime + 
					elevatingTimeUnoading_ +
					elevatingTimeUnloaded_ +
					constants.changeLocationSecondRobotLoaded;




				for (int i = 0; i < size(secondRobotsVector_[robot.id].bins); i++) {
					auto binZ_ = binZ + i + 1;

					auto binid = robot.bins[size(secondRobotsVector_[robot.id].bins) - i - 1].binId;
					//auto binid2 = robot.bins.back().binId;
					//auto& bin = binsVector_[binid];


					//*********************reset bin*************************
					binsVector_[binid].xLocation = binX;
					binsVector_[binid].yLocation = binY;
					binsVector_[binid].zLocation = binZ_;

					binsVector_[binid].locationId = gridLocationVector_[binX][binY][binZ_].locationId;
					binsVector_[binid].locationName = gridLocationVector_[binX][binY][binZ_].locationName;
					//**********************************************************
					//secondRobotsVector_[robot.id].bins.erase(secondRobotsVector_[robot.id].bins.begin());
					//**********************grid reset**************************************
					gridLocationVector_[binX][binY][binZ_].binId = binsVector_[binid].binId;
					gridLocationVector_[binX][binY][binZ_].isFilledWithBin = true;

				}
				secondRobotsVector_[robot.id].bins.clear();
				secondRobotsVector_[robot.id].isBusy = false;
				robot.isBusy = false;

			}


			selectedsecondRobotsVector.clear();
			return cycleTime;
		}
#endif
	

		//Both Type CT
		
		

		//Both Type One type CT
#if 1
		double bothTypeOneTypeCycleTime(lxw_worksheet* worksheet_)
		{
			auto firstRobotToBinCycleTime_ = firstRobotToBinCycleTime();
			worksheet_write_number(worksheet_, id + 1, 9, firstRobotToBinCycleTime_, NULL);
			worksheet_write_number(worksheet_, id + 1, 11, firstRobotToBinCycleTime_, NULL);

			auto elevatingCycleTime_ = bothTypeOneTypeElevatingCycleTime(worksheet_);
			worksheet_write_number(worksheet_, id + 1, 12, elevatingCycleTime_, NULL);


			auto binToPortCycleTime_ = binToPortCycleTime();
			worksheet_write_number(worksheet_, id + 1, 14, binToPortCycleTime_, NULL);


			auto portToBinCycleTime_ = binToPortCycleTime_;
			worksheet_write_number(worksheet_, id + 1, 15, portToBinCycleTime_, NULL);//port to bin

			//change Location
#if 1
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
			binsVector_[binId].locationName = "Retrived!";


			firstRobotsVector_[selectedfirstRobot.id].xLocation = selectedPort.xLocation;
			firstRobotsVector_[selectedfirstRobot.id].yLocation = selectedPort.yLocation;
#endif

			auto oneTypeLoweringCycleTime_ = bothTypeOneTypeLoweringCycleTime(elevatingCycleTime_);
			worksheet_write_number(worksheet_, id + 1, 16, oneTypeLoweringCycleTime_, NULL);
			//*****************************************************************

			auto totalCycleTime{
				firstRobotToBinCycleTime_ +
				elevatingCycleTime_ +
				oneTypeLoweringCycleTime_ +
				binToPortCycleTime_ +
				portToBinCycleTime_ };


			return totalCycleTime;
		};

		//***********************************************************************************

		double bothTypeOneTypeElevatingCycleTime(lxw_worksheet* worksheet_) {

			auto elevatingCells = constants.zLenghOfWarehouse - binToRetrive.zLocation + 1;
			double elevatingGoalBinCycleTime = elevatingCells * constants.firstRobotTowardZCellTime;
			elevatingGoalBinCycleTime = elevatingGoalBinCycleTime + constants.lockUnlockTime;

			goalBinIsDirectAccess();
			auto elevatingRelocationCT = bothTypeReLocationCycleTime(worksheet_);


			worksheet_write_number(worksheet_, id + 1, 14, elevatingGoalBinCycleTime, NULL);
			worksheet_write_number(worksheet_, id + 1, 15, elevatingRelocationCT, NULL);

			if (directAccessToBin) {
				return elevatingGoalBinCycleTime;
			}
			else {
				return elevatingGoalBinCycleTime + elevatingRelocationCT;
			}
		}

		double bothTypeOneTypeLoweringCycleTime(double elevatingCycleTime_) {

			auto elevatingCells = constants.zLenghOfWarehouse - binToRetrive.zLocation + 1;
			double elevatingGoalBinCycleTime = elevatingCells * constants.firstRobotTowardZCellTime;
			elevatingGoalBinCycleTime = elevatingGoalBinCycleTime + constants.lockUnlockTime;

			auto loweringRelocationCT = elevatingCycleTime_ - elevatingGoalBinCycleTime;

			auto newX{ binToRetrive.xLocation };
			auto newY{ binToRetrive.yLocation };
			auto newZ{ binToRetrive.zLocation };

			for (auto it = selectedfirstRobot.bins.rbegin(); it != selectedfirstRobot.bins.rend(); ++it) {
				auto& binToRelocate_ = *it;


				auto binX{ binsVector_[binToRelocate_.binId].xLocation };
				auto binY{ binsVector_[binToRelocate_.binId].yLocation };
				auto binZ{ binsVector_[binToRelocate_.binId].zLocation };

				////**********************grid reset**************************************
				gridLocationVector_[binX][binY][binZ].binId = -1;
				gridLocationVector_[binX][binY][binZ].isFilledWithBin = false;

				////**********************grid reset**************************************
				gridLocationVector_[newX][newY][newZ].binId = binToRelocate_.binId;
				gridLocationVector_[newX][newY][newZ].isFilledWithBin = true;

				//*********************change location of bin*************************
				binsVector_[binToRelocate_.binId].xLocation = newX;
				binsVector_[binToRelocate_.binId].yLocation = newY;
				binsVector_[binToRelocate_.binId].zLocation = newZ;

				binsVector_[binToRelocate_.binId].locationId = gridLocationVector_[newX][newY][newZ].locationId;
				binsVector_[binToRelocate_.binId].locationName = gridLocationVector_[newX][newY][newZ].locationName;


				newZ = newZ + 1;
			}
			selectedfirstRobot.bins.clear();
			firstRobotsVector_[selectedfirstRobot.id].bins.clear();

			return loweringRelocationCT;
		}

		double bothTypeReLocationCycleTime(lxw_worksheet* worksheet_) {

			//std::cout << "No direct Access\n" << "relocation in progress ...\n";


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
			worksheet_write_number(worksheet_, id + 1, 8, numOfBinToRelocate, NULL);




			for (int i = 0; i < numOfBinToRelocate; i++) {

				auto bestLocation = bestLocationForRelocation();

				int newX{ bestLocation.xLocation };
				int newY{ bestLocation.yLocation };
				int newZ{ bestLocation.zLocation };


				//elevating cycle time for top bin on goal x and y column
				auto binToRelocate = findTopBin(binX, binY);

				binZ = binToRelocate.zLocation;

				numOfElevatingCellsBinXBinY = constants.zLenghOfWarehouse - binZ + 1;
				cycleTime = cycleTime + (numOfElevatingCellsBinXBinY * constants.firstRobotTowardZCellTime);
				cycleTime = cycleTime + constants.lockUnlockTime;


				//direction change and coming back cycle time
				cycleTime = cycleTime + (2 * directionCost);


				// depositCells cycle time
				numOfDepositCellsNewXNewY = constants.zLenghOfWarehouse - newZ + 1;
				cycleTime = cycleTime + (numOfDepositCellsNewXNewY * constants.firstRobotTowardZCellTime);
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

				//**********************************************************************
				selectedfirstRobot.bins.push_back(binsVector_[binToRelocate.binId]);

			}

			return cycleTime;
		};

#endif


		//Both Type two type
#if 1
		double bothTypeTwoTypeCycleTime(lxw_worksheet* oneTypeWorksheet_)
		{
			auto firstRobotToBinCycleTime_ = firstRobotToBinCycleTime();
			worksheet_write_number(oneTypeWorksheet_, id + 1, 9, firstRobotToBinCycleTime_, NULL);

			auto secondRobotToBinCycleTime_ = bothTypeSecondRobotToBinCycleTime();
			worksheet_write_number(oneTypeWorksheet_, id + 1, 10, secondRobotToBinCycleTime_, NULL);

			auto twoTypeElevatingCycleTime_ = bothTypeTwoTypeElevatingCycleTime();
			worksheet_write_number(oneTypeWorksheet_, id + 1, 13, twoTypeElevatingCycleTime_, NULL);

			auto binToPortCycleTime_ = binToPortCycleTime();
			worksheet_write_number(oneTypeWorksheet_, id + 1, 14, binToPortCycleTime_, NULL);


			auto robotToBinCycleTime_{ 0.0 };
			if (firstRobotToBinCycleTime_ > (secondRobotToBinCycleTime_ + twoTypeElevatingCycleTime_)) { robotToBinCycleTime_ = firstRobotToBinCycleTime_; }
			else { robotToBinCycleTime_ = secondRobotToBinCycleTime_; }
			worksheet_write_number(oneTypeWorksheet_, id + 1, 11, robotToBinCycleTime_, NULL);


			//****************bin & grid & secondR & FR*****************************
#if 1
			auto binX{ binToRetrive.xLocation };//bin to relocate
			auto binY{ binToRetrive.yLocation };
			auto binZ{ binToRetrive.zLocation };

			auto binId = binToRetrive.binId;


			gridLocationVector_[binX][binY][binZ].binId = -3;
			gridLocationVector_[binX][binY][binZ].isFilledWithBin = false;

			binsVector_[binId].xLocation = -3;
			binsVector_[binId].yLocation = -3;
			binsVector_[binId].zLocation = -3;

			binsVector_[binId].locationId = -3;
			binsVector_[binId].locationName = "Retrived!-3";

			firstRobotsVector_[selectedfirstRobot.id].xLocation = selectedPort.xLocation;
			firstRobotsVector_[selectedfirstRobot.id].yLocation = selectedPort.yLocation;

			for (auto& selectedSecondRobot : selectedsecondRobotsVector) {
				secondRobotsVector_[selectedSecondRobot.id].xLocation = binX;
				secondRobotsVector_[selectedSecondRobot.id].yLocation = binY;
			}

			firstRobotsVector_[selectedfirstRobot.id].xLocation = selectedPort.xLocation;
			firstRobotsVector_[selectedfirstRobot.id].yLocation = selectedPort.yLocation;
#endif
			//*****************************************************************


			auto twoTypeLoweringCycleTime_ = bothTypeTwoTypeLoweringCycleTime();
			worksheet_write_number(oneTypeWorksheet_, id + 1, 17, twoTypeLoweringCycleTime_, NULL);



			auto totalCycleTime =

				robotToBinCycleTime_ +
				twoTypeElevatingCycleTime_ +
				binToPortCycleTime_ +
				twoTypeLoweringCycleTime_;


			return totalCycleTime;
		};
		//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

		double bothTypeSecondRobotToBinCycleTime() {
			AStar::Generator pathObject;
			pathObject.setWorldSize({ constants.xLenghOfWarehouse, constants.yLenghOfWarehouse });

			auto binX_ = binToRetrive.xLocation;
			auto binY_ = binToRetrive.yLocation;

			double robotToBinCost{ 0.0 };
			double maxRobotToBinTime{ 0.0 };

			for (auto& selectedSecondRobot : selectedsecondRobotsVector) {

				auto robotX_ = selectedSecondRobot.xLocation;
				auto robotY_ = selectedSecondRobot.yLocation;

				auto pathRobotToBin = pathObject.findPath({ robotX_, robotY_ }, { binX_, binY_ });

				robotToBinCost = onGridRobotMovementCycleTime(pathRobotToBin);

				if (robotToBinCost > maxRobotToBinTime) {
					maxRobotToBinTime = robotToBinCost;
				}



			}


			return maxRobotToBinTime;
		}

		double bothTypeTwoTypeElevatingCycleTime() {
			//double secondRobotcost_{0.0};
			//double firstRobotcost_{0.0};

			auto topbinZLocation = findTopBin(binToRetrive.xLocation, binToRetrive.yLocation).zLocation;
			auto numOfTopBins = topbinZLocation - binToRetrive.zLocation;
			auto numOfSecondRobot = size(selectedsecondRobotsVector);
			int numOfTopBinsLeft{ numOfTopBins };

			//for goal bin
			auto elevatingCells = constants.zLenghOfWarehouse - binToRetrive.zLocation + 1;
			double cycleTime = elevatingCells * constants.firstRobotTowardZCellTime;
			cycleTime = cycleTime + constants.lockUnlockTime;




			//for relocation bins
			for (auto& robot : selectedsecondRobotsVector) {

				topbinZLocation = findTopBin(binToRetrive.xLocation, binToRetrive.yLocation).zLocation;

				auto loweringCellsUnloaded = constants.zLenghOfWarehouse - topbinZLocation;
				auto loweringTimeUnloaded = loweringCellsUnloaded * constants.secondRobotTowardZCellTimeUnloaded;



				int loweringCellsLoading{ 0 };
				if (numOfTopBinsLeft >= constants.secondRobotCapacity) {
					loweringCellsLoading = constants.secondRobotCapacity;
				}
				else if (numOfTopBinsLeft < constants.secondRobotCapacity) {
					loweringCellsLoading = numOfTopBinsLeft;
				}
				auto loweringTimeLoading = loweringCellsLoading * constants.secondRobotTowardZCellTimeLoading;



				auto elevatingCellsLoaded = loweringCellsUnloaded + loweringCellsLoading;
				auto elevatingTimeLoaded = elevatingCellsLoaded * constants.secondRobotTowardZCellTimeAfterLoaed;


				double cycleTime_ =
					loweringTimeUnloaded + loweringTimeLoading +
					constants.lockUnlockTime + elevatingTimeLoaded +
					constants.changeLocationSecondRobotLoaded;


				cycleTime = cycleTime + cycleTime_;

				auto binX = binToRetrive.xLocation;
				auto binY = binToRetrive.yLocation;
				auto binZ = findTopBin(binX, binY).zLocation;

				for (int i = 0; i < loweringCellsLoading; i++) {
					auto binZ_ = binZ - i;

					auto binid = gridLocationVector_[binX][binY][binZ_].binId;
					auto& bin = binsVector_[binid];


					//*********************reset bin*************************
					binsVector_[binid].xLocation = -2;
					binsVector_[binid].yLocation = -2;
					binsVector_[binid].zLocation = -2;

					binsVector_[binid].locationId = -2;
					binsVector_[binid].locationName = "Retrived!";
					//**********************************************************
					secondRobotsVector_[robot.id].bins.push_back(binsVector_[binid]);
					robot.bins.push_back(binsVector_[binid]);
					//**********************grid reset**************************************
					gridLocationVector_[binX][binY][binZ_].binId = -2;
					gridLocationVector_[binX][binY][binZ_].isFilledWithBin = false;

				}
				numOfTopBinsLeft = numOfTopBinsLeft - loweringCellsLoading;

			}



			return cycleTime;
		}

		double bothTypeTwoTypeLoweringCycleTime() {

			int topbinZLocation_{ 0 };
			double cycleTime{ 0.0 };
			//for relocation bins
			for (auto it = selectedsecondRobotsVector.rbegin(); it != selectedsecondRobotsVector.rend(); ++it) {
				auto& robot = *it;

				auto binX = binToRetrive.xLocation;
				auto binY = binToRetrive.yLocation;
				auto binZ = findTopBin(binX, binY).zLocation;
				topbinZLocation_ = binZ;

				auto loweringCellsLoaded_ = constants.zLenghOfWarehouse - topbinZLocation_;
				auto loweringTimeLoaded_ = loweringCellsLoaded_ * constants.secondRobotTowardZCellTimeAfterLoaed;


				auto elevatingCellsUnoading_{ size(secondRobotsVector_[robot.id].bins) };
				auto elevatingTimeUnoading_ = elevatingCellsUnoading_ * constants.secondRobotTowardZCellTimeLoading;



				auto elevatingCellsUnloaded_ = loweringCellsLoaded_ - elevatingCellsUnoading_;
				auto elevatingTimeUnloaded_ = elevatingCellsUnloaded_ * constants.secondRobotTowardZCellTimeUnloaded;

				cycleTime =
					cycleTime +
					loweringTimeLoaded_ +
					constants.lockUnlockTime +
					elevatingTimeUnoading_ +
					elevatingTimeUnloaded_ +
					constants.changeLocationSecondRobotLoaded;




				for (int i = 0; i < size(secondRobotsVector_[robot.id].bins); i++) {
					auto binZ_ = binZ + i + 1;

					auto binid = robot.bins[size(secondRobotsVector_[robot.id].bins) - i - 1].binId;
					//auto binid2 = robot.bins.back().binId;
					//auto& bin = binsVector_[binid];


					//*********************reset bin*************************
					binsVector_[binid].xLocation = binX;
					binsVector_[binid].yLocation = binY;
					binsVector_[binid].zLocation = binZ_;

					binsVector_[binid].locationId = gridLocationVector_[binX][binY][binZ_].locationId;
					binsVector_[binid].locationName = gridLocationVector_[binX][binY][binZ_].locationName;
					//**********************************************************
					//secondRobotsVector_[robot.id].bins.erase(secondRobotsVector_[robot.id].bins.begin());
					//**********************grid reset**************************************
					gridLocationVector_[binX][binY][binZ_].binId = binsVector_[binid].binId;
					gridLocationVector_[binX][binY][binZ_].isFilledWithBin = true;

				}
				secondRobotsVector_[robot.id].bins.clear();
				secondRobotsVector_[robot.id].isBusy = false;
				robot.isBusy = false;

			}


			selectedsecondRobotsVector.clear();
			return cycleTime;
		}
#endif


	};


};



