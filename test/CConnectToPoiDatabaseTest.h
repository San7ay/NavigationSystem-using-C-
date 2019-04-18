/*
 * connectToPoiDatabaseTest.h
 *
 *  Created on: 08-Jan-2019
 *      Author: Sanjay
 */

#ifndef CCONNECTTOPOIDATABASETEST_H_
#define CCONNECTTOPOIDATABASETEST_H_


#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>

#include "../myCode/CRoute.h"

class CConnectToPoiDatabaseTest: public CppUnit::TestFixture{
private:

	CWpDatabase* m_pWp;
	CPoiDatabase * m_pPoi;
	CRoute* m_pRoute;
	CJasonPersistence* m_pJson;

public:
	void setUp()
	{
		m_pWp = new CWpDatabase;
		m_pPoi = new CPoiDatabase;
		m_pRoute = new CRoute;
		m_pJson = new CJasonPersistence;
	}

	void tearDown()
	{
		delete m_pWp;
		delete m_pPoi;
		delete m_pRoute;
		delete m_pJson;
	}

	void connectTest()
	{
		m_pJson->setMediaName("database");
		m_pJson->readData(*m_pWp,*m_pPoi,REPLACE);
		m_pRoute->connectToPoiDatabase(m_pPoi);
		m_pRoute->connectToWpDatabase(m_pWp);
		m_pRoute->addWaypoint("Darmstadt");
		m_pRoute->addPoi("Mensa_HDA","Darmstadt");

		CPPUNIT_ASSERT(m_pRoute->getRoute().size()==2);
	}

	void connectTestFail()
	{
		m_pRoute->connectToWpDatabase(NULL);
		m_pRoute->addPoi("Darmstadt","Mensa_HDA");

		CPPUNIT_ASSERT(m_pRoute->getRoute().size()==0);
	}

	static CppUnit::TestSuite* suite() {
		CppUnit::TestSuite* suite = new CppUnit::TestSuite("Connect POI DB Tests");
		suite->addTest(new CppUnit::TestCaller<CConnectToPoiDatabaseTest>
				 ("Connect POI DB Tests", &CConnectToPoiDatabaseTest::connectTest));
		suite->addTest(new CppUnit::TestCaller<CConnectToPoiDatabaseTest>
				 ("Connect POI DB Tests", &CConnectToPoiDatabaseTest::connectTestFail));
		return suite;
	}
};


#endif /* CCONNECTTOPOIDATABASETEST_H_ */
