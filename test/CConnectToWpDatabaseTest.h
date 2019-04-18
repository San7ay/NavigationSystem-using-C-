/*
 * connectToWpDatabaseTest.h
 *
 *  Created on: 08-Jan-2019
 *      Author: Sanjay
 */

#ifndef CCONNECTTOWPDATABASETEST_H_
#define CCONNECTTOWPDATABASETEST_H_

#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>

#include "../myCode/CRoute.h"

class CConnectToWpDatabaseTest: public CppUnit::TestFixture{
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

		CPPUNIT_ASSERT(m_pRoute->getRoute().size()==1);
	}

	void connectTestFail()
	{
		m_pRoute->connectToWpDatabase(NULL);
		m_pRoute->addWaypoint("Darmstadt");

		CPPUNIT_ASSERT(m_pRoute->getRoute().size()==0);
	}

	static CppUnit::TestSuite* suite() {
		CppUnit::TestSuite* suite = new CppUnit::TestSuite("Connect WP DB Tests");
		suite->addTest(new CppUnit::TestCaller<CConnectToWpDatabaseTest>
				 ("Connect WP DB Tests", &CConnectToWpDatabaseTest::connectTest));
		suite->addTest(new CppUnit::TestCaller<CConnectToWpDatabaseTest>
				 ("Connect WP DB Tests", &CConnectToWpDatabaseTest::connectTestFail));
		return suite;
	}
};




#endif /* CCONNECTTOWPDATABASETEST_H_ */
