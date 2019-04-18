/*
 * operatorEqualTest.h
 *
 *  Created on: 08-Jan-2019
 *      Author: Sanjay
 */

#ifndef COPERATOREQUALTEST_H_
#define COPERATOREQUALTEST_H_


#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>

#include "../myCode/CRoute.h"

class COperatorEqualTest: public CppUnit::TestFixture{
private:

	CWpDatabase* m_pWp;
	CPoiDatabase * m_pPoi;
	CRoute* m_pRoute;
	CRoute* m_pRoute1;
	CJasonPersistence* m_pJson;

public:
	void setUp()
	{
		m_pWp = new CWpDatabase;
		m_pPoi = new CPoiDatabase;
		m_pRoute = new CRoute;
		m_pRoute1 = new CRoute;
		m_pJson = new CJasonPersistence;
	}

	void tearDown()
	{
		delete m_pWp;
		delete m_pPoi;
		delete m_pRoute;
		delete m_pRoute1;
		delete m_pJson;
	}

	void operatorequals()
	{
		m_pJson->setMediaName("database");
		m_pJson->readData(*m_pWp,*m_pPoi,REPLACE);
		m_pRoute->connectToPoiDatabase(m_pPoi);
		m_pRoute->connectToWpDatabase(m_pWp);
		m_pRoute->addWaypoint("Darmstadt");
		m_pRoute->addPoi("Mensa_HDA","Darmstadt");

		*m_pRoute1 = *m_pRoute;

		CPPUNIT_ASSERT(m_pRoute1->getRoute().size()==2);
	}

	static CppUnit::TestSuite* suite() {
		CppUnit::TestSuite* suite = new CppUnit::TestSuite("operator equals test");
		suite->addTest(new CppUnit::TestCaller<COperatorEqualTest>
				 ("operator equals test", &COperatorEqualTest::operatorequals));
		return suite;
	}
};



#endif /* COPERATOREQUALTEST_H_ */
