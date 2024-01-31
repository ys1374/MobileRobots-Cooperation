#ifndef __Autostore_neo_yasinsalehi_ir_8F637DB91972F6C878D41D63F7E7214F__
#define __Autostore_neo_yasinsalehi_ir_8F637DB91972F6C878D41D63F7E7214F__

#include <string>
#include <iostream>

namespace Autostore {
	class bin
	{
	public:
		int xLocation; //tol	
		int yLocation; //arz 
		int zLocation; //depth

		int id;
		int inventory;

		std::string name{ "namenotassigned!" };



		void nameFillerBin(int x_, int y_, int z_, int id_)
		{
			xLocation = x_;
			yLocation = y_;
			zLocation = z_; 
			
			

			id = id_;
			name = "BinsNO:" + std::to_string(id_);
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





}
#endif


