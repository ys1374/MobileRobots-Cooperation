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
		double zLenghOfWarehouse{ 0 };
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

		
		///////////////////////////

		std::vector<port>* mainPortsVector;
		std::vector<firstRobot>* mainFirstRobotsVector;
		std::vector<secondRobot>* mainSecondRobotsVector;
		std::vector<bin>* mainBinsVector;

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

		void binIsDirectAccess(std::vector<std::vector<std::vector<Autostore::gridLocation>>>& gridLV_) {
			auto x_ = binToRetrive.xLocation;
			auto y_ = binToRetrive.yLocation;
			auto z_ = binToRetrive.zLocation + 1;

			//directAccessToBin = !gridLV_[x_][y_][z_].isFilledWithBin;
			directAccessToBin = true;
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

		double elevatingCycleTime() {

			auto elevatingCells = constants.zLenghOfWarehouse - binToRetrive.zLocation;
			double cycleTime = (elevatingCells * constants.hightOfBin) / constants.robotPickOrDepositeVelocity;
			cycleTime = cycleTime + constants.lockUnlockTime;
			
			if (directAccessToBin) {
				return cycleTime;
			}
			else {
				return cycleTime + reLocationCycleTime();
			}
		}

		double reLocationCycleTime() {
			auto& portsVector_ = (*mainPortsVector);
			auto& firstRobotsVector_ = (*mainFirstRobotsVector);
			auto& secondRobotsVector_ = (*mainSecondRobotsVector);
			auto& binsVector_ = (*mainBinsVector);

			//std::cout << (*binsVector);
			//std::cout << "binid" << binToRetrive.binId;
			//std::cout << "before" << binsVector_[binToRetrive.binId].xLocation;
			//binsVector_[binToRetrive.binId].xLocation = 5;
			//std::cout << "after" << binsVector_[binToRetrive.binId].xLocation;

			return 0.0;
		};

		double cycleTime(int xLenghOfWarehouse, int yLenghOfWarehouse)
		{
			AStar::Generator pathObject;
			pathObject.setWorldSize({ xLenghOfWarehouse, yLenghOfWarehouse });

			

			auto binX_ = binToRetrive.xLocation;
			auto binY_ = binToRetrive.yLocation;

			auto robotX_ = selectedfirstRobot.xLocation;
			auto robotY_ = selectedfirstRobot.yLocation;

			auto portX_ = selectedPort.xLocation;
			auto portY_ = selectedPort.yLocation;

			//--------------------------------------------------------------------------------
			auto pathRobotToBin = pathObject.findPath({ robotX_, robotY_ }, { binX_, binY_ });
			auto pathBinToPort = pathObject.findPath({ binX_, binY_ }, { portX_, portY_ });
			//--------------------------------------------------------------------------------

			std::cout << "path robot to bin------------------------------------------------------------------ \n";
			for (auto& coordinate : pathRobotToBin) {
				std::cout << coordinate.x <<  "\t"  ;
			}

			std::cout << "\n";
			for (auto& coordinate : pathRobotToBin) {
				std::cout << coordinate.y << "\t";
			}
			auto robotToBinCost = onGridRobotMovementCycleTime(pathRobotToBin);


			
			std::cout << pathRobotToBin.size() << " " << pathRobotToBin.size() << "\t";


			std::cout << "\npathBinToPort----------------------------------------------------------------------\n";
			for (auto& coordinate : pathBinToPort) {
				std::cout << coordinate.x << "\t";
			}

			std::cout << "\n";
			for (auto& coordinate : pathBinToPort) {
				std::cout << coordinate.y << "\t";
			}

			auto binToPortCost = onGridRobotMovementCycleTime(pathBinToPort);
			//------------------------------------------------------------------------------------------------------
			std::cout << "\n";

			//Total CycleTime
			double totalCycleTime = robotToBinCost + binToPortCost ;
			totalCycleTime = elevatingCycleTime() + totalCycleTime;

			return totalCycleTime;
		};
		

	
	};


};
#endif 


