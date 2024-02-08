#ifndef __Autostore_neo__8F637DB91972F6C878D41D63F7E7214F__
#define __Autostore_neo__8F637DB91972F6C878D41D63F7E7214F__

#include <string>
#include <iostream>
#include <random>
#include <set>
#include <algorithm> // For std::shuffle
#include <random> // For std::default_random_engine
#include <chrono> // For std::chrono::system_clock
//#include "D:\Projects\MSc\Thesis\Simulation\Learn\Astar\as2\a-star-master\source\AStar.hpp"
#include "AStar.h"


namespace Autostore {

	struct constantsAutostore {
		int y8b{ 9 };
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

		
		int minCostBinToPort{ 1000000000 };
		int minCostRobotToBin{ 100000000 };


		void firstRobotSelection( Autostore::bin bin_, std::vector<Autostore::firstRobot> firstRobotVector_) {
			int minCostRobot{ 100000000 };
			int Cost_{ 0 };

			for (auto& robot : firstRobotVector_) {

				Cost_ = manhattanCostRobot(bin_, robot);
				//std::cout << "robot location:" << robot.xLocation <<" "<< robot.yLocation << "\t" << bin_.locationName << "\tCost:" << Cost_ << "\n";
				if (Cost_ < minCostRobot) {
					//std::cout << "iam in\n";
					minCostRobot = Cost_;
					firstRobotXLocation = robot.xLocation;
					firstRobotYLocation = robot.yLocation;

					selectedfirstRobotId = robot.id;
				}


			}
			//std::cout << "selectedRobotId:" << selectedPortId << "\n\n";
			//std::cout << "firstRobotXLocation:" << firstRobotXLocation << "\tfirstRobotYLocation:" << firstRobotYLocation << "\n";

		}

		void portSelection(Autostore::bin bin_, std::vector<Autostore::port> portVector_) {
			
			int Cost_{ 0 };

			for (auto& port : portVector_) {

				Cost_ = manhattanCostPort(bin_, port);
				//std::cout << "port location:" << port.xLocation << " " << port.yLocation << "\t" << bin_.locationName << "\tCost:" << Cost_ << "\n";
				if (Cost_ < minCostRobotToBin) {
					//std::cout << "iam in\n";
					minCostRobotToBin = Cost_;
					portXLocation = port.xLocation;
					portYLocation = port.yLocation;

					selectedPortId = port.id;
				}


			}

		}

		void cycleTime(Autostore::bin& bin_, std::vector<Autostore::port> portVector_, std::vector<Autostore::firstRobot>& robot_,  int xLenghOfWarehouse, int yLenghOfWarehouse)
		{
			AStar::Generator pathObjectFirstRobotToBin;
			pathObjectFirstRobotToBin.setWorldSize({ xLenghOfWarehouse, yLenghOfWarehouse });
			pathObjectFirstRobotToBin.setHeuristic(AStar::Heuristic::manhattan);
			pathObjectFirstRobotToBin.setDiagonalMovement(false);

			std::cout << "Generate path ... \n";
			auto path = pathObjectFirstRobotToBin.findPath({ robot_[selectedfirstRobotId].xLocation, robot_[selectedfirstRobotId].yLocation}, {bin_.xLocation, bin_.yLocation});

			//path.

			for (auto& coordinate : path) {
				std::cout << coordinate.x << " " << coordinate.y << "\n";
			}

			//std::cout << "Robot location is:" << robot_.xLocation << " " << robot_.yLocation;
			//std::cout << "\tBin xlocation is:" << bin_.xLocation;
			//std::cout << "\tmanhatan cost is:" << manhattanCostRobot(bin_, robot_) << "\n";

			//int mcost = manhattanCostRobot(bin_, robot_);
			//robot_.xLocation = bin_.xLocation;
			//robot_.yLocation = bin_.yLocation;


			//return mcost;
		}

		int manhattanCostRobot(Autostore::bin bin_, Autostore::firstRobot robot_) {
			return{ abs(bin_.xLocation - robot_.xLocation) + abs(bin_.yLocation - robot_.yLocation) };
		}

		int manhattanCostPort(Autostore::bin bin_, Autostore::port port_) {
			return{ abs(bin_.xLocation - port_.xLocation) + abs(bin_.yLocation - port_.yLocation) };
		}





		
	};

}
#endif 


