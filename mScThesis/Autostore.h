#ifndef __Autostore_neo__8F637DB91972F6C878D41D63F7E7214F__
#define __Autostore_neo__8F637DB91972F6C878D41D63F7E7214F__

#include <string>
#include <iostream>
#include <random>
#include <set>
#include <algorithm> // For std::shuffle
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
		const int timeExchange{ 5 };
		//Locking and unlocking time( seconds )
		const int lockUnlockTime{ 5 };
		//Robot velocity(m/s)
		const int robotVelocity{ 2 };
		//Robot pick / deposit velocity(m/s)
		const int robotPickOrDepositeVelocity{ 2 };
		//Wheel exchange time( seconds )
		const int wheelExchangeTime{ 1 };
		//toward x time
		const double towardXCellTime{ deltaX / robotVelocity };
		//toward y time
		const double towardYCellTime{ deltaY / robotVelocity };

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

	class firstRobot
	{


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
		
		const int movementCostTimeForOneCell = 2;//in seconds
		const int changeDirectionCostTime = 10;//in seconds

		///////////////////////////
		long long int id{ -1 };

		int portXLocation{ -1 };
		int portYLocation{ -1 };

		int firstRobotXLocation{ -1 };
		int firstRobotYLocation{ -1 };

		int binXLocation{ -1 };
		int binYLocation{ -1 };
		int binZLocation{ -1 };

		int selectedPortId{ -1 };
		int selectedfirstRobotId{ -1 };

		
		int minCostRobotToBin{ 1000000000 };
		int minCostBinToPort{ 100000000 };

		//int movementBeforeDirection

		
		void firstRobotSelection( Autostore::bin bin_, std::vector<Autostore::firstRobot> firstRobotVector_) {
			
			int Cost_{ 0 };

			for (auto& robot : firstRobotVector_) {

				Cost_ = manhattanCostRobot(bin_, robot);
				//std::cout << "robot location:" << robot.xLocation <<" "<< robot.yLocation << "\t" << bin_.locationName << "\tCost:" << Cost_ << "\n";
				if (Cost_ < minCostRobotToBin) {
					//std::cout << "iam in\n";
					minCostRobotToBin = Cost_;
					firstRobotXLocation = robot.xLocation;
					firstRobotYLocation = robot.yLocation;

					selectedfirstRobotId = robot.id;
				}

				
			}
			//return minCostRobotToBin;
			//std::cout << "selectedRobotId:" << selectedPortId << "\n\n";
			//std::cout << "firstRobotXLocation:" << firstRobotXLocation << "\tfirstRobotYLocation:" << firstRobotYLocation << "\n";

		}

		void portSelection(Autostore::bin bin_, std::vector<Autostore::port> portVector_) {
			
			//int Cost_{ 0 };

			for (auto port : portVector_) {

				int Cost_ = manhattanCostPort(bin_, port);
				//std::cout << "port location:" << port.xLocation << " " << port.yLocation << "\t" << bin_.locationName << "\tCost:" << Cost_ << "\n";
				if (Cost_ < minCostBinToPort) {
					//std::cout << "iam in\n";
					minCostBinToPort = Cost_;

					portXLocation = port.xLocation;
					//std::cout << port.xLocation;

					portYLocation = port.yLocation;
					//std::cout << port.yLocation;

					selectedPortId = port.id;
				}


			}

		}

		int manhattanCostRobot(Autostore::bin bin_, Autostore::firstRobot robot_) {
			return{ abs(bin_.xLocation - robot_.xLocation) + abs(bin_.yLocation - robot_.yLocation) };
		}

		int manhattanCostPort(Autostore::bin bin_, Autostore::port port_) {
			return{ abs(bin_.xLocation - port_.xLocation) + abs(bin_.yLocation - port_.yLocation) };
		}

		double calculateStrightCost(int movement_) {

		}

		double detectDirectionChangesAndCount(const AStar::CoordinateList path_) {
			
			Autostore::constantsAutostore constants;
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
				

				// Determine current direction
				if (path_[i].x != path_[i - 1].x) {
					currentDirection = Direction::towardX;
					//std::cout << "towardX";
				}
				else if (path_[i].y != path_[i - 1].y) {
					currentDirection = Direction::towardY;
					//std::cout << "towardY";
				}

				// Check if direction has changed
				if (currentDirection != previousDirection && previousDirection != Direction::None) {

					//std::cout << "\nDirection changed at (" << path_[i - 1].x << ", " << path_[i - 1].y << ")";
					//std::cout << " after " << movesCount << " moves." << std::endl;
					
					
					
					if (previousDirection == Direction::towardX) {

						if (movesCount >= 6) {

							beforeCost = 4 + ((movesCount - 6) * constants.towardXCellTime);

						}
						else if (movesCount <= 3) {beforeCost = 2;}
						else if (movesCount < 6 && movesCount > 3) {beforeCost = 3;}
						//std::cout << "beforeCost is towardX and cost is:" << beforeCost <<std::endl;

					}
					else if(previousDirection == Direction::towardY) {

						if (movesCount >= 8) {

							beforeCost = 4 + ((movesCount - 8) * constants.towardYCellTime);

						}
						else if (movesCount <= 4) { beforeCost = 2; }
						else if (movesCount < 8 && movesCount > 4) { beforeCost = 3; }
						//std::cout << "beforeCost is towardYYYYYY and cost is:" << beforeCost << std::endl;
	
					}
																				
					movesCount = 0; // Reset count after a direction change
				}

				// Increment moves count if there was movement
				if (currentDirection != Direction::None) {movesCount++;}

				previousDirection = currentDirection;
			}

			// Print the number of moves after the last direction change (or if there was no change)
			if (movesCount > 0) {

				//std::cout << "\nMoved " << movesCount << " locations in the final direction." << std::endl;

				
				if (currentDirection == Direction::towardX) {

					//std::cout << "towardX" << std::endl;
					if (movesCount >= 6) {

						aftereCost = 4 + ((movesCount - 6) * constants.towardXCellTime);

					}
					else if (movesCount <= 3) { aftereCost = 2; }
					else if (movesCount < 6 && movesCount > 3) { aftereCost = 3; }
					//std::cout << "aftereCost is towardX and cost is:" << aftereCost << std::endl;

				}
				else if (currentDirection == Direction::towardY) {

					//std::cout << "towardY" << std::endl;
					if (movesCount >= 8) {

						aftereCost = 4 + ((movesCount - 8) * constants.towardYCellTime);

					}

					else if (movesCount <= 4) { aftereCost = 2; }
					else if (movesCount < 8 && movesCount > 4) { aftereCost = 3; }
					//std::cout << "aftereCost is towardY and cost is:" << aftereCost << std::endl;

				}

			}

			totalCost = beforeCost + aftereCost;
			//std::cout << "\nCost of RobotToBin \t"<< totalCost<<"\n";
			return totalCost;
		}

		int cycleTime(Autostore::bin& bin_, std::vector<Autostore::port> portVector_, std::vector<Autostore::firstRobot>& robot_, int xLenghOfWarehouse, int yLenghOfWarehouse)
		{
			AStar::Generator pathObject;
			pathObject.setWorldSize({ xLenghOfWarehouse, yLenghOfWarehouse });

			Autostore::constantsAutostore constants;


			auto pathRobotToBin = pathObject.findPath({ robot_[selectedfirstRobotId].xLocation, robot_[selectedfirstRobotId].yLocation }, { bin_.xLocation, bin_.yLocation });
			auto pathBinToPort = pathObject.findPath({ bin_.xLocation, bin_.yLocation }, { portVector_[selectedPortId].xLocation, portVector_[selectedPortId].yLocation });
			
			std::cout << "Generate path robot to bin ... \n";
			for (auto& coordinate : pathRobotToBin) {
				std::cout << coordinate.x <<  "\t"  ;
			}

			std::cout << "\n";
			for (auto& coordinate : pathRobotToBin) {
				std::cout << coordinate.y << "\t";
			}


			std::cout << "\nCost of total \t";

			std::cout << detectDirectionChangesAndCount(pathRobotToBin)+ detectDirectionChangesAndCount(pathBinToPort) <<"\n";

			//path print

			//std::cout << "\n";
			////////////////////////////////////////////
			//std::cout << "Generate path bin to port... \n";
			//for (auto& coordinate : pathBinToPort) {
			//	std::cout << coordinate.x << "\t";
			//}
			//std::cout << "\n";
			//for (auto& coordinate : pathBinToPort) {
			//	std::cout << coordinate.y << "\t";
			//}
			//std::cout << "\n";
			///////////////////////////////////////////

			//std::cout << "Robot location is:" << robot_.xLocation << " " << robot_.yLocation;
			//std::cout << "\tBin xlocation is:" << bin_.xLocation;
			//std::cout << "\tmanhatan cost is:" << manhattanCostRobot(bin_, robot_) << "\n";

			//int mcost = manhattanCostRobot(bin_, robot_);
			//robot_.xLocation = bin_.xLocation;
			//robot_.yLocation = bin_.yLocation;


			//constants.deltaX
			//movement first robot
			int movementCycleTime = (minCostRobotToBin + minCostBinToPort) * movementCostTimeForOneCell;

			//change direction
			int changeDirectionCycleTime = 2 * changeDirectionCostTime;

			//Total CycleTime
			int cycleTime = changeDirectionCycleTime + movementCycleTime;

			return cycleTime;
		}







		
	};

}
#endif 


