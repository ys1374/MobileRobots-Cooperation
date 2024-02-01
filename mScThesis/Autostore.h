#ifndef __Autostore_neo___yasinsalehi_ir_8F637DB91972F6C878D41D63F7E7214F__
#define __Autostore_neo___yasinsalehi_ir_8F637DB91972F6C878D41D63F7E7214F__

#include <string>
#include <iostream>
#include <random>
#include <set>
#include <algorithm> // For std::shuffle
#include <random> // For std::default_random_engine
#include <chrono> // For std::chrono::system_clock

namespace Autostore {
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

		std::string name{ "namenotassigned!" };




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

	class UniqueRandomNumberGenerator {
	private:
		std::set<int> generatedNumbers;
		std::random_device rd;
		std::mt19937 gen;
		std::uniform_int_distribution<> distrib;
		int maxNumber;

	public:
		UniqueRandomNumberGenerator(int maxNum) : maxNumber(maxNum), gen(rd()), distrib(0, maxNum) {}

		int generate() {
			if (generatedNumbers.size() == maxNumber) {
				throw std::runtime_error("All possible numbers have been generated.");
			}

			while (true) {
				int num = distrib(gen);
				if (generatedNumbers.insert(num).second) {
					return num;
				}
			}
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

}
#endif 


