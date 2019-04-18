/*
 * CWaypoint.cpp
 *
 *  Created on: 22-Oct-2018
 *  Author: Sanjay
 */

#include "CWaypoint.h"
#include <math.h>

CWaypoint::CWaypoint(std::string name,double latitude,double longitude)
{
	set(name,latitude,longitude);
}

void CWaypoint::set(std::string name,double latitude,double longitude)
{
	/*
	 * Validating the range of latitude and longitude
	 */
	if((latitude>=(-90))&&(latitude<=90)&&(longitude>=(-180))&&(longitude<=180))
	{
		m_latitude = latitude;
		m_longitude = longitude;
		m_name = name;
	}
	/*
	 * In case of invalid parameters
	 * setting 0 to the attributes
	 */
	else
	{
		m_latitude = 0;
		m_longitude = 0;
		m_name = "NULL";
	}
}

void CWaypoint::print()
{
	int deg = 0;
	int mm = 0;
	double ss = 0;
	std::cout<<m_name<<" on ";

		transformLatitude2degmmss(deg,mm,ss);
		std::cout<<"latitude : "<<deg<<" deg "<<mm<<" min "<<ss<<" sec ";
		transformLongitude2degmmss(deg,mm,ss);
		std::cout<<"longitude : "<<deg<<" deg "<<mm<<" min "<<ss<<" sec "<<std::endl;

}

std::ostream& operator <<(std::ostream& out,  CWaypoint& waypoint)
{
	int deg = 0;
	int mm = 0;
	double ss = 0;

	out<<waypoint.getName()<<" on ";
	waypoint.transformLatitude2degmmss(deg,mm,ss);
	out<<"latitude : "<<deg<<" deg "<<mm<<" min "<<ss<<" sec ";
	waypoint.transformLongitude2degmmss(deg,mm,ss);
	out<<"longitude : "<<deg<<" deg "<<mm<<" min "<<ss<<" sec "<<std::endl;

	return out;
}

void CWaypoint::transformLatitude2degmmss(int &deg,int &mm,double &ss)
{
	deg = m_latitude;
	double mtemp = (m_latitude-deg)*60;
	mm = mtemp;
	ss = (mtemp-mm)*60;
}

void CWaypoint::transformLongitude2degmmss(int &deg,int &mm,double &ss)
{
	deg = m_longitude;
	double mtemp = (m_longitude-deg)*60;
	mm = mtemp;
	ss = (mtemp-mm)*60;
}

double CWaypoint::getLatitude() const
{
	return m_latitude;
}


double CWaypoint::getLongitude() const
{
	return m_longitude;
}


std::string CWaypoint::getName() const
{
	return m_name;
}

CWaypoint::~CWaypoint()
{

}
























