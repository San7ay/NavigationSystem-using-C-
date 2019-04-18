/*
 * CWpDatabase.cpp
 *
 *  Created on: 20-Nov-2018
 *      Author: Sanjay
 */

#include "CWpDatabase.h"
#include <stdio.h>
#include <string.h>


//Method Implementations

CWpDatabase::CWpDatabase()
{

}

void CWpDatabase::addWaypointDB(CWaypoint const& wp)
{
	CDBTemplate::addElement(wp);
}

CWaypoint* CWpDatabase::getPointerToWaypoint(std::string name)
{
	return CDBTemplate::getPointerToElement(name);
}

void CWpDatabase::print()
{
	CDBTemplate::print();
}

void CWpDatabase::getWaypointMap(map<string,CWaypoint> & waypointmap) const
{
	CDBTemplate::getElementMap(waypointmap);
}

void CWpDatabase::clearWpMap()
{
	CDBTemplate::clearElementMap();
}

string CWpDatabase::uppertolower(string name)
{
	return CDBTemplate::uppertolower(name);
}
