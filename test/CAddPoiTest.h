/*
 * addPoiTest.h
 *
 *  Created on: 08-Jan-2019
 *      Author: Sanjay
 */

#ifndef CADDPOITEST_H_
#define CADDPOITEST_H_

#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>

#include "../myCode/CRoute.h"

class CAddPoiTest: public CppUnit::TestFixture{
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

	void addTest()
	{
		m_pJson->setMediaName("database");
		m_pJson->readData(*m_pWp,*m_pPoi,REPLACE);
		m_pRoute->connectToPoiDatabase(m_pPoi);
		m_pRoute->connectToWpDatabase(m_pWp);
		m_pRoute->addWaypoint("Darmstadt");
		m_pRoute->addPoi("Mensa_HDA","Darmstadt");
		m_pRoute->addPoi("Sitte","berlin");

		CPPUNIT_ASSERT(m_pRoute->getRoute().size()==2);
	}

	void addTestFail()
	{
		m_pRoute->connectToWpDatabase(NULL);
		m_pRoute->addPoi("Darmstadt","Mensa_HDA");

		CPPUNIT_ASSERT(m_pRoute->getRoute().size()==0);
	}

	static CppUnit::TestSuite* suite() {
		CppUnit::TestSuite* suite = new CppUnit::TestSuite("Add POI Tests");
		suite->addTest(new CppUnit::TestCaller<CAddPoiTest>
				 ("Add POI Tests", &CAddPoiTest::addTest));
		suite->addTest(new CppUnit::TestCaller<CAddPoiTest>
				 ("Add POI Tests", &CAddPoiTest::addTestFail));
		return suite;
	}
};

#endif /* CADDPOITEST_H_ */
