
//System Include Files
#include <iostream>
#include <stdlib.h>
#include <string>
#include <sstream>

//Own Include Files
#include "CWaypoint.h"
#include "CNavigationSystem.h"
#include "CGPSSensor.h"
#include "CPOI.h"
#include "CPoiDatabase.h"
#include "CRoute.h"
#include "CCSV.h"
#include "CJasonPersistence.h"

/*
 * Selecting between two format for printing coordinates.
 * 1. Decimal degree format
 * 2. DEG MM SS format
 */
#define DEGREE 1
#define MMSS 2

#define TEST 7		// for selecting between test cases

int main (void)
{
/*
 * Testcase for CWaypoint class
 */
#if TEST == 0
	CWaypoint amsterdam("amsterdam",52.368,4.9036);
	CWaypoint darmstadt("darmstadt",49.8728,8.6512);
	CWaypoint berlin("berlin",52.52,13.4050);
	CWaypoint tokio("tokio",35.6895,139.6917);

	amsterdam.print(DEGREE);
	berlin.print(MMSS);
	darmstadt.print(MMSS);
	tokio.print(MMSS);

	std::cout<<"Distance btw amsterdam and berlin "<<amsterdam.calculateDistance(berlin)<<std::endl;
	std::cout<<"Distance btw tokio and berlin "<<tokio.calculateDistance(darmstadt)<<std::endl;
#endif

/*
 * Test case for CGPSSensor class
 */
#if TEST == 1
	CGPSSensor s1;
	s1.getCurrentPosition().print(1);
#endif

/*
 * Test case for CPOI class
 */
#if TEST == 2
	CPOI c1(RESTAURANT,"Paradise","best restaurant in the world",50,30);
	c1.print();
#endif

/*
 * Test case for CPoiDatabase class
 */
#if TEST == 3
	CPoiDatabase c1;
	c1.addPoi(UNIVERSITY,"HDA","Best university in Germany",50,20);
	c1.addPoi(RESTAURANT,"Spice of India","only Indian restaurant",40,30);
	c1.getPointerToPoi("Mousami");
#endif

/*
 * Test case for CRoute class
 */
#if TEST == 4
	CRoute c1(4,5);
	CWaypoint wp("amsterdam",52.368,4.9036);

	c1.addPoi("HD_A");
	c1.print();

#endif

/*
 * Test case for Navigation class
 */
#if TEST == 5

	CNavigationSystem myNav;
	myNav.run();

#endif

#if TEST == 6

	CWpDatabase temp;
	CPoiDatabase temp1;
	CRoute r;
	CWaypoint amsterdam("amsterdam",52.368,4.9036);
	CWaypoint darmstadt("darmstadt",49.8728,8.6512);
	CWaypoint berlin("berlin",52.52,13.4050);
	CWaypoint tokio("tokio",35.6895,139.6917);

	temp.addWaypointDB(amsterdam);
	temp.addWaypointDB(darmstadt);
	temp.addWaypointDB(berlin);
	temp.addWaypointDB(tokio);

	r.connectToWpDatabase(&temp);

	r.addWaypoint("amsterdam");
	r.addWaypoint("berlin");
	r.addWaypoint("darmstadt");
	r.addWaypoint("tokio");
	r.addWaypoint("amsterdam");

	//r.print();

	//adding POI for our database
	CPOI Mensa_HDA(RESTAURANT,"Mensa_HDA","The best mensa in the world",10,20);
	CPOI Sitte(RESTAURANT,"Sitte","Most expensive but also good",11,22);
	CPOI Stadt_zentrum(TOURISTIC,"Stadt_zentrum","Beautiful and clean",20,30);
	CPOI H_DA(UNIVERSITY,"H_DA","The best university in the world",20,30);

	temp1.addPoi(Mensa_HDA);
	temp1.addPoi(Sitte);
	temp1.addPoi(Stadt_zentrum);
	temp1.addPoi(H_DA);



	//Connecting to the database(array) in CPoiDatabase class
	r.connectToPoiDatabase(&temp1);

	//adding POI for our route
	r.addPoi("H_DA","amsterdam");
	r.addPoi("Sitte","berlin");
	r.addPoi("Mensa_HDA","darmstadt");

	r.print();
	cout<<endl<<endl;

	CRoute f = r;

	r = r+f;
	r.print();
	cout<<endl<<endl;
	r += "Sitte";
	cout<<endl<<endl;
	r.print();

#endif


#if TEST == 7

	CJasonPersistence j1;
	CWpDatabase temp;
	CPoiDatabase temp1;
	CRoute r;

	CWaypoint amsterdam("amsterdam",52.368,4.9036);
	CWaypoint darmstadt("darmstadt",49.8728,8.6512);

	//temp.addWaypointDB(amsterdam);
	//temp.addWaypointDB(darmstadt);

	//r.connectToWpDatabase(&temp);

	//r.addWaypoint("amsterdam");
	//r.addWaypoint("darmstadt");

	//temp.print();

	CPOI Mensa_HDA(RESTAURANT,"Mensa_HDA","The best mensa in the world",10,20);
	CPOI Sitte(RESTAURANT,"Sitte","Most expensive but also good",11,22);

	//temp1.addPoi(Mensa_HDA);
	//temp1.addPoi(Sitte);

	//r.connectToPoiDatabase(&temp1);

	//r.addPoi("Mensa_HDA","amsterdam");
	//r.addPoi("Sitte","darmstadt");

	//temp1.print();

	j1.setMediaName("database");
	//j1.writeData(temp,temp1);
	j1.readData(temp,temp1,REPLACE);

	temp.print();
	temp1.print();

#endif

#if TEST == 8

	CRoute r;
	CWpDatabase temp;
	CPoiDatabase temp1;

	CWaypoint amsterdam("amsterdam",52.368,4.9036);
	CWaypoint darmstadt("darmstadt",49.8728,8.6512);
	CWaypoint tokio("tokio",35.6895,139.6917);

	temp.addWaypointDB(amsterdam);
	temp.addWaypointDB(darmstadt);
	temp.addWaypointDB(tokio);

	r.connectToWpDatabase(&temp);

	r.addWaypoint("amsterdam");
	r.addWaypoint("darmstadt");

	CPOI Mensa_HDA(RESTAURANT,"Mensa_HDA","The best mensa in the world",10,20);
	CPOI Sitte(RESTAURANT,"Sitte","Most expensive but also good",11,22);
	CPOI H_DA(UNIVERSITY,"H_DA","The best university in the world",20,30);

	temp1.addPoi(Mensa_HDA);
	temp1.addPoi(Sitte);
	temp1.addPoi(H_DA);

	r.connectToPoiDatabase(&temp1);

	r.addPoi("Mensa_HDA","amsterdam");
	r.addPoi("Sitte","darmstadt");

	r.print();

	r+="H_DA";

	//temp.print();
	r.print();



#endif


return 0;
}
