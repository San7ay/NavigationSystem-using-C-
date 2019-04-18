
/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CPOI.CPP
* Author          :	Sanjay Prakash
* Description     :	Implement CPOI class, setting the details of POI
*
****************************************************************************/

//System Include Files


//Own Include Files

#include "CPOI.h"

//Method Implementations

CPOI::CPOI(t_poi type, std::string name, std::string description, double latitude, double longitude)
: CWaypoint(name,latitude,longitude)
/*
 * explicitly call base class constructor
 */
{
	m_type = type;
	m_description = description;
}

void CPOI::print()
{
	std::string temp[] = {"Restaurant","Tourist place","Gas station","University"};
	std::cout<<"Point of Interest"<<std::endl<<"============================"<<std::endl;
	std::cout<<"of type "<<temp[m_type]<<" : "<<m_description<<std::endl;
	CWaypoint::print();
	//explicitly call base class print
}

std::ostream& operator <<(std::ostream& cout,  CPOI& poi)
{
	std::string temp[] = {"Restaurant","Tourist place","Gas station","University"};
	std::cout<<"Point of Interest"<<std::endl<<"============================"<<std::endl;
	std::cout<<"of type "<<temp[poi.m_type]<<" : "<<poi.m_description<<std::endl;
	std::cout<<poi.getName()<<" on ";
	std::cout<<"latitude : "<<poi.getLatitude()<<std::endl;
	std::cout<<"longitude : "<<poi.getLongitude()<<std::endl;

	return cout;
}

std::string CPOI::getDescription() const
{
	return m_description;
}

std::string CPOI::getType() const
{
	std::string type;
	if(m_type == RESTAURANT){ type = "RESTAURANT";}
	if(m_type == TOURISTIC){ type = "TOURISTIC";}
	if(m_type == GASSTATION){ type = "GASSTATION";}
	if(m_type == UNIVERSITY){ type = "UNIVERSITY";}

	return type;
}

CPOI::~CPOI()
{

}

