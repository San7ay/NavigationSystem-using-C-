
/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CROUTE.CPP
* Author          : Sanjay Prakash
* Description     :	Implementation of CRoute class, it create the required
* 					Route with waypoints and POI
*
****************************************************************************/


//System Include Files


//Own Include Files

#include "CRoute.h"
#include <iterator>
#include <algorithm>


//Method Implementations

#define MAXWP  100				//maximum number of waypoint allowed in the route
#define MAXPOI 100				//maximum number of POI allowed in the route

CRoute::CRoute()
{
	m_pPoiDatabase = NULL;
	m_pWpDatabase = NULL;
	m_noWp = 0;
	m_noPoi = 0;
}

CRoute::CRoute(CRoute const& origin)
{
	this->m_pPoiDatabase = origin.m_pPoiDatabase;
	this->m_pWpDatabase = origin.m_pWpDatabase;
	this->m_noPoi = origin.m_noPoi;
	this->m_noWp = origin.m_noWp;

	list<CWaypoint*>::const_iterator it;
	for(it = origin.m_pWaypoint.begin();it!=origin.m_pWaypoint.end();++it)
	{
		this->m_pWaypoint.push_back(*it);
	}
}

void CRoute::connectToPoiDatabase(CPoiDatabase* pPoiDB)
{
	if(pPoiDB != NULL)
	{
		m_pPoiDatabase = pPoiDB;
	}
	else
		cout<<"POI database not found"<<endl;
}

void CRoute::connectToWpDatabase(CWpDatabase* pWaypointDB)
{
	if(pWaypointDB == NULL)
	{
		cout<<"Waypoint databse not found"<<endl;
	}
	else
	{
		m_pWpDatabase = pWaypointDB;
	}

}

void CRoute::addWaypoint(std::string nameWp)
{
	if(m_pWpDatabase != NULL )
	{
		//check if waypoint is present in database or not
		if(m_pWpDatabase->getPointerToWaypoint(nameWp)==NULL && m_noWp<=MAXWP)
		{
			cout<<"ERROR: cannot find waypoint"<<endl;
		}
		else
		{
			m_pWaypoint.push_back(m_pWpDatabase->getPointerToWaypoint(nameWp));
			++m_noWp;
		}
	}
}

void CRoute::addPoi(std::string namePoi,std::string afterWp)
{
	if(m_pPoiDatabase != NULL && m_pWpDatabase!= NULL)
	{
		//check if POI is present in database or not
		if(m_pPoiDatabase->getPointerToPoi(namePoi)==NULL && m_noPoi<=MAXPOI)
		{
			cout<<"ERROR: cannot find POI"<<endl;
		}
		else
		{
			list<CWaypoint*>::reverse_iterator rit;
			unsigned int size = m_pWaypoint.size();
			for(rit = m_pWaypoint.rbegin();rit!=m_pWaypoint.rend();++rit)
			{
				if((*rit)->getName()==afterWp && size== m_pWaypoint.size())
				{
					//add POI if waypoint with name afterWp is found
					m_pWaypoint.insert(rit.base(),(m_pPoiDatabase->getPointerToPoi(namePoi)));
					++rit;
					++m_noPoi;
				}

			}
			if(size == m_pWaypoint.size())
			{
				cout<<"POI not added , waypoint not found"<<endl;
			}
		}
	}
}

void CRoute::print()
{
	if(m_pPoiDatabase != NULL && m_pWpDatabase!= NULL)
	{
		cout<<"Route has "<<m_noWp<<" waypoints and "<<m_noPoi<<" POI"<<endl;
		list<CWaypoint*>::iterator it;

		for(it = m_pWaypoint.begin();it!=m_pWaypoint.end();++it)		//check if the entry in list is POI or not
		{
			if(*it != NULL)												//check for NULL pointer
			{
				if((dynamic_cast<CPOI*>(*it)!=0))
				{
					cout<<*(dynamic_cast<CPOI*>(*it));
				}
				else
					cout<<**it;
			}
		}
		cout<<endl;
	}
}

CRoute& CRoute::operator=(const CRoute& route)
{
	this->m_pPoiDatabase = route.m_pPoiDatabase;
	this->m_pWpDatabase = route.m_pWpDatabase;
	this->m_noPoi = route.m_noPoi;
	this->m_noWp = route.m_noWp;

	list<CWaypoint*>::const_iterator it;
	for(it = route.m_pWaypoint.begin();it!=route.m_pWaypoint.end();++it)
	{
		this->m_pWaypoint.push_back(*it);
	}

	return *this;
}

CRoute& CRoute::operator+=(string name)
{
	this->addWaypoint(name);
	list<CWaypoint*>::const_iterator it;
	it = this->m_pWaypoint.end();
	--it;

	if((dynamic_cast<CPOI*>(*it)!=0))  //check if the entry in list is POI or not
	{
		if(this->m_pPoiDatabase->getPointerToPoi(name)==NULL && m_noPoi<=MAXPOI)
		{
			cout<<"ERROR: cannot find POI"<<endl;
		}
		else
		{
			this->m_pWaypoint.push_back(m_pPoiDatabase->getPointerToPoi(name));
			++m_noPoi;
			cout<<name<<" POI found and added at the end"<<endl;
		}
	}
	else
	{
		this->addPoi(name,(**it).getName());
	}
	return *this;
}

CRoute operator+(CRoute& route1, CRoute& route2)
{
	CRoute temp;
	//check whether both the routes are connected to same database
	if((route1.m_pPoiDatabase == route2.m_pPoiDatabase) && (route1.m_pWpDatabase == route2.m_pWpDatabase)&&
		route1.m_pPoiDatabase != NULL && route1.m_pWpDatabase!= NULL && route2.m_pPoiDatabase != 0 && route2.m_pWpDatabase != 0)
	{
		CRoute R(route1);
		list<CWaypoint*>::iterator it;
		temp.m_pWaypoint.assign(route2.m_pWaypoint.begin(),route2.m_pWaypoint.end());
		if(R.m_pWaypoint.size()!=0)
		{
			for(it = R.m_pWaypoint.begin();it!=R.m_pWaypoint.end();++it)
			{
				temp.m_pWaypoint.push_back(*it);
			}
		}
//		it = route.m_pWaypoint.end();
//		--it;
//		temp.m_pWaypoint = route.m_pWaypoint;
//		this->m_noPoi += route.m_noPoi;
//		this->m_noWp += route.m_noWp;
//		this->m_pWaypoint.splice(it,temp.m_pWaypoint);
//		return *this;
	}
	else
	{
		cout<<"Routes are not connected to the same database"<<endl;
	}
	return temp;
}

const vector<const CWaypoint*> CRoute::getRoute()
{
	vector<const CWaypoint*> vec_pointer;
	list<CWaypoint*>::iterator it;
	for(it=m_pWaypoint.begin();it!=m_pWaypoint.end();++it)
	{
		vec_pointer.push_back(*it);
	}
	return vec_pointer;
}

CRoute::~CRoute()
{

}

