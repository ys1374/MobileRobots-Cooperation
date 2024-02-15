#ifndef __Autostore_neo__8F637DB91972F6C878D41D63F7E7214F__
#define __Autostore_neo__8F637DB91972F6C878D41D63F7E7214F__

#include <string>
#include <iostream>
#include <set>
//#include <algorithm> // For std::shuffle
#include <random> // For std::default_random_engine
#include <chrono> // For std::chrono::system_clock
#include "AStar.h"
#include <vector>


namespace Autostore {

	

	struct constantsAutostore {

		//Division x (meter)
		const double deltaX{ 0.7 };
		//Division y (meter)
		const double deltaY{ 0.5 };
		//Exchange time( seconds )
		const double timeExchange{ 5 };
		//Locking and unlocking time( seconds )
		const double lockUnlockTime{ 5 };
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
		//
		int xLenghOfWarehouse{ -1 };
		int yLenghOfWarehouse{ -1 };
		int zLenghOfWarehouse{ -1 };

		double hightOfBin{ 0 };

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
			
			isFilledWithBin =  true;
			locationId = loacationId_;
			locationName = "x[" + std::to_string(i_) + "]" + "y[" + std::to_string(j_) + "]" + "z[" + std::to_string(k_) + "]";


		}

		void gridRemoverOfBin()
		{

			int id{ -1 };
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

		void binFillerWithdata(long long int binid_)
		{
			binId = binid_;
			binName = "BinNO." + std::to_string(binid_);
		}

		friend std::ostream& operator<<(std::ostream& os, const bin& b) {
			os << b.binId; // Serialize xLocation
			// Serialize other fields
			return os;
		}

		// Deserialize the bin object
		friend std::istream& operator>>(std::istream& is, bin& b) {
			is >> b.binId; // Deserialize xLocation
			// Deserialize other fields
			return is;
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

		///////////////////////////
		long long int id{ -1 };
		
		int minCostRobotToBin{ 1000000000 };
		int minCostBinToPort{ 100000000 };

		bool directAccessToBin{ false };

		int directionCost{ 0 };

		
		///////////////////////////

		std::vector<port>* mainPortsVector{};
		std::vector<firstRobot>* mainFirstRobotsVector{};
		std::vector<secondRobot>* mainSecondRobotsVector{};
		std::vector<bin>* mainBinsVector{};
		std::vector<std::vector<std::vector<Autostore::gridLocation>>>* mainGridLocationVector;

		std::vector<port> portsVector;
		std::vector<firstRobot> firstRobotsVector;
		std::vector<secondRobot> secondRobotsVector;
		std::vector<bin> binsVector;

		constantsAutostore constants;

		bin binToRetrive;
		port selectedPort;
		firstRobot selectedfirstRobot;
		
		void reset() {
			int minCostRobotToBin{ 1000000000 };
			int minCostBinToPort{ 100000000 };

			directAccessToBin = false;
		};

		void binIsDirectAccess() {

			auto& gridLocationVector_ = (*mainGridLocationVector);

			auto x_ = binToRetrive.xLocation;
			auto y_ = binToRetrive.yLocation;
			auto z_ = binToRetrive.zLocation + 1;

			directAccessToBin = ((gridLocationVector_[x_][y_][z_].binId == -1) ? true : false);
			

		}

		void firstRobotSelection() {

			int Cost_{ 0 };

			for (auto& robot : firstRobotsVector) {

				Cost_ = manhattanCostRobot(robot);
				std::cout << Cost_ << " ";

				if (Cost_ < minCostRobotToBin) {
					
					std::cout << "inR ";
					minCostRobotToBin = Cost_;
					selectedfirstRobot = robot;

				}

			}

			std::cout << "  Selected Robot:  " <<
				"Id:" << selectedfirstRobot.id <<
				" x:" << selectedfirstRobot.xLocation <<
				" y:" << selectedfirstRobot.yLocation <<"\n";

		}

		void portSelection() {
			
			int Cost_{ 0 };
			
			for (auto& port : portsVector) {

				int Cost_ = manhattanCostPort(port);
				std::cout << Cost_ << " ";

				if (Cost_ < minCostBinToPort) {
					std::cout << "inP ";
					minCostBinToPort = Cost_;
					selectedPort = port;

				}
		
			}

			std::cout << "  Selected Port:  " <<
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

		double onGridRobotMovementCycleTime(const AStar::CoordinateList path_) {
			
			double beforeCost{ 0 },aftereCost{ 0 }, totalCost{ 0 };

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
				if (path_[i].x != path_[i - 1].x) {currentDirection = Direction::towardX;}
				else if (path_[i].y != path_[i - 1].y) {currentDirection = Direction::towardY;}


				// Check if direction has changed------------------------------------------------------
				if (currentDirection != previousDirection && previousDirection != Direction::None) {
																		
					if (previousDirection == Direction::towardX) {

						std::cout << "\nDirection changed at (" << path_[i - 1].x << ", " << path_[i - 1].y << ")";
						std::cout << " after " << movesCount << " moves towardX. ";

						if (movesCount >= 6) {beforeCost = 4 + ((movesCount - 6) * constants.towardXCellTime);}
						else if (movesCount <= 3) {beforeCost = 2;}//1, 2, 3
						else if (movesCount < 6 && movesCount > 3) {beforeCost = 3;}//4,5

					}
					else if(previousDirection == Direction::towardY) {

						std::cout << "\nDirection changed at (" << path_[i - 1].x << ", " << path_[i - 1].y << ")";
						std::cout << " after " << movesCount << " moves towardY. ";

						if (movesCount >= 8) {beforeCost = 4 + ((movesCount - 8) * constants.towardYCellTime);}
						else if (movesCount <= 4) { beforeCost = 2; }
						else if (movesCount < 8 && movesCount > 4) { beforeCost = 3; }
	
					}
					//-----------------------------------------------------------------------------------
																				
					movesCount = 0; // Reset count after a direction change
				}

				// Increment moves count if there was movement
				if (currentDirection != Direction::None) {movesCount++;}

				previousDirection = currentDirection;
			}//for loop Finished

			// Print the number of moves after the last direction change (or if there was no change)
			if (movesCount > 0) {
		
				if (currentDirection == Direction::towardX) {

					std::cout << "Then Moved " << movesCount << " locations towardX." << std::endl;

					if (movesCount >= 6) {aftereCost = 4 + ((movesCount - 6) * constants.towardXCellTime);}
					else if (movesCount <= 3) { aftereCost = 2; }
					else if (movesCount < 6 && movesCount > 3) { aftereCost = 3; }

				}
				else if (currentDirection == Direction::towardY) {

					std::cout << "Then Moved " << movesCount << " locations towardY." << std::endl;

					if (movesCount >= 8) {aftereCost = 4 + ((movesCount - 8) * constants.towardYCellTime);}
					else if (movesCount <= 4) { aftereCost = 2; }
					else if (movesCount < 8 && movesCount > 4) { aftereCost = 3; }

				}

			}

			totalCost = beforeCost + constants.wheelExchangeTime + aftereCost;

			return totalCost;
		};

		bin findTopBin(int x_, int y_) {
			auto& gridLocationVector_ = (*mainGridLocationVector);
			auto& binsVector_ = (*mainBinsVector);

			for (auto& bin : gridLocationVector_[x_][y_]) {
	
				if (bin.binId == -1) {
					return binsVector_[gridLocationVector_[x_][y_][bin.zLocation - 1].binId];
				}

			}
		}

		gridLocation bestLocationForRelocation() {
			
			auto& portsVector_ = (*mainPortsVector);
			auto& firstRobotsVector_ = (*mainFirstRobotsVector);
			auto& secondRobotsVector_ = (*mainSecondRobotsVector);
			auto& binsVector_ = (*mainBinsVector);
			auto& gridLocationVector_ = (*mainGridLocationVector);

			// Define the search pattern for the 8 surrounding cells and their cost
			int directions[8][3] = { {-1, 0, 1}, {1, 0, 1}, {0, -1, 1}, {0, 1, 1}, {-1, -1, 3},
				{-1, 1, 3}, {1, -1, 3}, {1, 1, 3} };

			
			int binX = binToRetrive.xLocation;
			int binY = binToRetrive.yLocation;

			bin topbin_;
			int cost_{};
			double cycleTime;
				
			double lowestCost = 1000000000000000.0;
			auto& bestLocation = gridLocationVector_[0][0][0];

			//std::cout << "binX " << binX << " binY" << binY << "\n";

			for (auto& dir : directions) {
				int newX = binX + dir[0];
				int newY = binY + dir[1];
				if (newX > 0 && newX < constants.xLenghOfWarehouse - 1 && newY > 0 && newY < constants.yLenghOfWarehouse - 1 && (gridLocationVector_[newX][newY][0].isFilledWithBin = true)) {
					//std::cout << "newX " << newX << " newY" << newY << "\n";

					topbin_ = findTopBin(newX, newY);

					cost_ = constants.zLenghOfWarehouse - (topbin_.zLocation + 1) + dir[2];

					//std::cout << "not in" << cost_ << " ";

					if (cost_ < lowestCost) {
						//std::cout << "\ninnnnn" << cost_ << " ";
						lowestCost = cost_;
						bestLocation = gridLocationVector_[newX][newY][topbin_.zLocation + 1];
						directionCost = dir[2];
					}
				}


			}
			std::cout << "\nhiiiiiiiiiiiii " << bestLocation.locationName;
			return bestLocation;
		}

		double reLocationCycleTime() {

			std::cout << "relocation in progress ...\n";

			auto& portsVector_ = (*mainPortsVector);
			auto& firstRobotsVector_ = (*mainFirstRobotsVector);
			auto& secondRobotsVector_ = (*mainSecondRobotsVector);
			auto& binsVector_ = (*mainBinsVector);
			auto& gridLocationVector_ = (*mainGridLocationVector);

			// Define the search pattern for the 8 surrounding cells and their cost
			int directions[8][3] = { {-1, 0, 1}, {1, 0, 1}, {0, -1, 1}, {0, 1, 1}, {-1, -1, 3}, 
				{-1, 1, 3}, {1, -1, 3}, {1, 1, 3} };

			// Example grid coordinates for the cell you're starting from
			int binX = binToRetrive.xLocation;
			int binY = binToRetrive.yLocation;
			int binZ = binToRetrive.zLocation;

			bin topBin, depositTopBin;
			bin topbin_;
			int cost_{0};
			double cycleTime{0};

			int numOfBinToRelocate =  binZ - topBin.zLocation;

			std::cout << "numOfBinToRelocate " << numOfBinToRelocate;

			auto bestLocation = bestLocationForRelocation();
			int elevatingCells{0}, depositCells{0}; 

			for (int i = 0; i < numOfBinToRelocate; i++) {

				//elevating
				topBin = findTopBin(binX, binY);
				elevatingCells = constants.zLenghOfWarehouse - topBin.zLocation;
				cycleTime = cycleTime + (elevatingCells * constants.hightOfBin) / constants.robotPickOrDepositeVelocity;
				cycleTime = cycleTime + constants.lockUnlockTime;


				//direction cost
				cycleTime = cycleTime + directionCost;


				// depositCells
				depositTopBin = findTopBin(bestLocation.xLocation, bestLocation.yLocation);
				depositCells = constants.zLenghOfWarehouse - depositTopBin.zLocation;
				cycleTime = cycleTime + (elevatingCells * constants.hightOfBin) / constants.robotPickOrDepositeVelocity;
				cycleTime = cycleTime + constants.lockUnlockTime;

				std::cout << "\ncycletime: " << cycleTime;

			}
			
			




			return 0.0;
		};

		double elevatingCycleTime() {

			auto elevatingCells = constants.zLenghOfWarehouse - binToRetrive.zLocation;
			double cycleTime = (elevatingCells * constants.hightOfBin) / constants.robotPickOrDepositeVelocity;
			cycleTime = cycleTime + constants.lockUnlockTime;
			
			binIsDirectAccess();

			if (directAccessToBin) {
				std::cout << "\ndirectAccessToBin\n";
				return cycleTime;
			}
			else {
				return cycleTime + reLocationCycleTime();
			}
		}

		double robotToBinCycleTime() {

			auto& firstRobotsVector_ = (*mainFirstRobotsVector);

			AStar::Generator pathObject;
			pathObject.setWorldSize({ constants.xLenghOfWarehouse, constants.yLenghOfWarehouse });

			auto binX_ = binToRetrive.xLocation;
			auto binY_ = binToRetrive.yLocation;

			auto robotX_ = selectedfirstRobot.xLocation;
			auto robotY_ = selectedfirstRobot.yLocation;

			auto pathRobotToBin = pathObject.findPath({ robotX_, robotY_ }, { binX_, binY_ });

			std::cout << "path robot to bin------------------------------------------------------------------ \n";
			for (auto& coordinate : pathRobotToBin) {
				std::cout << coordinate.x << "\t";
			}

			std::cout << "\n";
			for (auto& coordinate : pathRobotToBin) {
				std::cout << coordinate.y << "\t";
			}
			auto robotToBinCost = onGridRobotMovementCycleTime(pathRobotToBin);


			//change location of robot---------------------------------------------
			firstRobotsVector_[selectedfirstRobot.id].xLocation = binX_;
			firstRobotsVector_[selectedfirstRobot.id].yLocation = binY_;
			//---------------------------------------------------------------------

			return robotToBinCost;
		}

		double binToPortCycleTime() {

			auto& firstRobotsVector_ = (*mainFirstRobotsVector);
			auto& binsVector_ = (*mainBinsVector);

			AStar::Generator pathObject;
			pathObject.setWorldSize({ constants.xLenghOfWarehouse, constants.yLenghOfWarehouse });

			auto binX_ = binToRetrive.xLocation;
			auto binY_ = binToRetrive.yLocation;

			auto robotX_ = selectedfirstRobot.xLocation;
			auto robotY_ = selectedfirstRobot.yLocation;

			auto portX_ = selectedPort.xLocation;
			auto portY_ = selectedPort.yLocation;

			auto pathBinToPort = pathObject.findPath({ binX_, binY_ }, { portX_, portY_ });

			//---------------------------------------------------------------------
			std::cout << "\npathBinToPort----------------------------------------------------------------------\n";
			for (auto& coordinate : pathBinToPort) {
				std::cout << coordinate.x << "\t";
			}

			std::cout << "\n";
			for (auto& coordinate : pathBinToPort) {
				std::cout << coordinate.y << "\t";
			}

			auto binToPortCost = onGridRobotMovementCycleTime(pathBinToPort);


			//change location of robot and bin---------------------------------------------
			firstRobotsVector_[selectedfirstRobot.id].xLocation = portX_;
			firstRobotsVector_[selectedfirstRobot.id].yLocation = portY_;

			binsVector_[binToRetrive.binId].xLocation = portX_;
			binsVector_[binToRetrive.binId].yLocation = portY_;
			binsVector_[binToRetrive.binId].zLocation = -1;

			//---------------------------------------------------------------------
			std::cout << "\n";

			return binToPortCost;
		}

		double cycleTime()
		{
			auto& portsVector_ = (*mainPortsVector);
			auto& firstRobotsVector_ = (*mainFirstRobotsVector);
			auto& secondRobotsVector_ = (*mainSecondRobotsVector);
			auto& binsVector_ = (*mainBinsVector);


			auto robotToBinCycleTime_ = robotToBinCycleTime();
			auto elevatingCycleTime_ = elevatingCycleTime();
			auto binToPortCycleTime_ = binToPortCycleTime();

			return robotToBinCycleTime_ + elevatingCycleTime_ + binToPortCycleTime_;
		};
		

	
	};


};
#endif 


