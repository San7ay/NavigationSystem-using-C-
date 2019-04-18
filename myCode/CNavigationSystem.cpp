
/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CNAVIGATIONSYSTEM.CPP
* Author          :	Sanjay Prakash
* Description     :	Basic navigation system with number of waypoints and POI
*
****************************************************************************/


//System Include Files


//Own Include Files
#include "CNavigationSystem.h"

//Method Implementations

CNavigationSystem::CNavigationSystem()
{
	//nothing to do so far
}

void CNavigationSystem::run()
{
	unsigned int c;

	createDatabase();
	enterRoute();

	cout<<"select the required index of operation :"<<endl
			<<"1. Write to file"<<endl
			<<"2. Read from file"<<endl
			<<"3. Print route"<<endl;
	cin>>c;
	switch(c)
	{
	case 1:
		writeToFile();
		cout<<"WAYPOINT DATABASE"<<endl;
		m_WpDatabase.print();
		cout<<endl<<"POI DATABASE"<<endl;
		m_PoiDatabase.print();
		break;
	case 2:
		readFromFile(REPLACE);
		cout<<"WAYPOINT DATABASE"<<endl;
		m_WpDatabase.print();
		cout<<endl<<"POI DATABASE"<<endl;
		m_PoiDatabase.print();
		break;
	case 3:
		cout<<"ROUTE "<<endl;
		printRoute();
		cout<<"WAYPOINT DATABASE"<<endl;
		m_WpDatabase.print();
		cout<<endl<<"POI DATABASE"<<endl;
		m_PoiDatabase.print();
		break;
	}
}

void CNavigationSystem::enterRoute()
{
	m_route.connectToWpDatabase(&m_WpDatabase);

	m_route.addWaypoint("amsterdam");
	m_route.addWaypoint("berlin");
	m_route.addWaypoint("darmstadt");
	m_route.addWaypoint("tokio");

	//Connecting to the database(array) in CPoiDatabase class
	m_route.connectToPoiDatabase(&m_PoiDatabase);

	//adding POI for our route
	m_route.addPoi("H_DA","amsterdam");
	m_route.addPoi("Sitte","berlin");
	m_route.addPoi("Mensa_HDA","darmstadt");

}

void CNavigationSystem::printRoute()
{
	m_route.print();
}

void CNavigationSystem::createDatabase()
{
	CWaypoint amsterdam("amsterdam",52.368,4.9036);
	CWaypoint darmstadt("darmstadt",49.8728,8.6512);
	CWaypoint berlin("berlin",52.52,13.4050);
	CWaypoint tokio("tokio",35.6895,139.6917);
	CWaypoint mysore("mysore",64.4,45.6);
	CWaypoint manglore("manglore",53.5,68.5);
	CWaypoint paris("paris",48.5,56.8);
	CWaypoint frankfurt("frankfurt",64.6,74.8);

	m_WpDatabase.addWaypointDB(amsterdam);
	m_WpDatabase.addWaypointDB(darmstadt);
	m_WpDatabase.addWaypointDB(berlin);
	m_WpDatabase.addWaypointDB(tokio);
	m_WpDatabase.addWaypointDB(mysore);
	m_WpDatabase.addWaypointDB(manglore);
	m_WpDatabase.addWaypointDB(paris);
	m_WpDatabase.addWaypointDB(frankfurt);

	//adding POI for our database
	CPOI Mensa_HDA(RESTAURANT,"Mensa_HDA","The best mensa in the world",10,20);
	CPOI Sitte(RESTAURANT,"Sitte","Most expensive but also good",11,22);
	CPOI Stadt_zentrum(TOURISTIC,"Stadt_zentrum","Beautiful and clean",20,30);
	CPOI H_DA(UNIVERSITY,"H_DA","The best university in the world",20,30);
	CPOI sumalya(RESTAURANT,"sumalya","best indian resturant ",64,33);
	CPOI TUD(UNIVERSITY,"TUD","one of the oldest university",68,54);
	CPOI lusenplatz(TOURISTIC,"city center","place for winter market",69,39);

	m_PoiDatabase.addPoi(Mensa_HDA);
	m_PoiDatabase.addPoi(Sitte);
	m_PoiDatabase.addPoi(Stadt_zentrum);
	m_PoiDatabase.addPoi(H_DA);
	m_PoiDatabase.addPoi(sumalya);
	m_PoiDatabase.addPoi(TUD);
	m_PoiDatabase.addPoi(lusenplatz);

}

void CNavigationSystem::writeToFile()
{
	CPersistentStorage *c1;
	CCSV temp;
	c1 = &temp;

	c1->setMediaName("CSV");
	c1->writeData(m_WpDatabase,m_PoiDatabase);
}

void CNavigationSystem::readFromFile(MergeMode mode)
{
	CPersistentStorage *c1;
	CCSV temp;
	c1 = &temp;

	c1->setMediaName("CSV");
	c1->readData(m_WpDatabase,m_PoiDatabase,mode);
}
