
/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CGPSSENSOR.CPP
* Author          : Sanjay Prakash
* Description     :	Used to get the coordinate of the current place
*
****************************************************************************/


//System Include Files

//Own Include Files

#include "CGPSSensor.h"

//Method Implementations


CGPSSensor::CGPSSensor()
{
	//nothing to do here
}


CWaypoint CGPSSensor::getCurrentPosition()
{
	std::cout<<"GPS Sensor"<<std::endl;
	CWaypoint c;
	double latitude=0;
	double longitude =0;
	std::string name = "NULL";
	std::cout<<"enter the latitude"<<std::endl;
	std::cin>>latitude;
	while(!std::cin)											//validating for integer type input
	{
		std::cin.clear();
		std::cin.ignore(30,'\n');
		std::cout<<"Enter correct latitude"<<std::endl;
		std::cin>>latitude;
	}
	std::cout<<"enter the Longitude"<<std::endl;
	std::cin>>longitude;
	while(!std::cin)											//validating for integer type input
	{
		std::cin.clear();
		std::cin.ignore(30,'\n');
		std::cout<<"Enter correct longitude"<<std::endl;
		std::cin>>longitude;
	}

	/*
	 * If entered coordinates exceeds the range then set name to invalid
	 */
	if((latitude<(-90))||(latitude>90)||(longitude<(-180))||(longitude>180))
	{
		latitude = 0;
		longitude = 0;
		name = "Invalid";
	}
	c.set(name,latitude,longitude);
	return c;

}
