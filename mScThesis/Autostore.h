#ifndef __Autostore_neo_yasinsalehi_ir_8F637DB91972F6C878D41D63F7E7214F__
#define __Autostore_neo_yasinsalehi_ir_8F637DB91972F6C878D41D63F7E7214F__

namespace Autostore {
	struct bin
	{
		int xLocation; //tol	
		int yLocation; //arz 
		int zLocation; //depth

		int id;
		int inventory;

	};

	struct robot
	{
		int xLocation; //tol	
		int yLocation; //arz 
		int zLocation; //depth

		int id;
		int bin_id;
		bool isBusy;
		bool isSecondType;

		auto path;

	};





}
#endif


