
/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CPOIDATABASE.CPP
* Author          : Sanjay prakash
* Description     :	Implements all CPoiDatabase class to maintain and manipulate
* 					the POI database
*
****************************************************************************/

//System Include Files


//Own Include Files

#include "CPoiDatabase.h"
#include <string.h>

using namespace std;

//Method Implementations

CPoiDatabase::CPoiDatabase()
{

}

void CPoiDatabase::addPoi(CPOI const& poi)
{
	CDBTemplate::addElement(poi);
}

CPOI* CPoiDatabase::getPointerToPoi(std::string name)
{
	return CDBTemplate::getPointerToElement(name);
}

void CPoiDatabase::getPoiMap(map<string,CPOI> & poimap) const
{
	CDBTemplate::getElementMap(poimap);
}

void CPoiDatabase::print()
{
	CDBTemplate::print();
}

void CPoiDatabase::clearPoiMap()
{
	CDBTemplate::clearElementMap();
}

string CPoiDatabase::uppertolower(string name)
{
	return CDBTemplate::uppertolower(name);
}
