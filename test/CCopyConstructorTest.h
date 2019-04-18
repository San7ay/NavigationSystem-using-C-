/*
 * copyConstructorTest.h
 *
 *  Created on: 08-Jan-2019
 *      Author: Sanjay
 */

#ifndef CCOPYCONSTRUCTORTEST_H_
#define CCOPYCONSTRUCTORTEST_H_


#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>

#include "../myCode/CRoute.h"

class CCopyConstructorTest: public CppUnit::TestFixture{
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

	void copyconstructor()
	{
		m_pJson->setMediaName("database");
		m_pJson->readData(*m_pWp,*m_pPoi,REPLACE);
		m_pRoute->connectToPoiDatabase(m_pPoi);
		m_pRoute->connectToWpDatabase(m_pWp);
		m_pRoute->addWaypoint("Darmstadt");
		m_pRoute->addPoi("Mensa_HDA","Darmstadt");

		CRoute m_route(*m_pRoute);

		CPPUNIT_ASSERT(m_route.getRoute().size() == 2);
	}

	static CppUnit::TestSuite* suite() {
		CppUnit::TestSuite* suite = new CppUnit::TestSuite("Copy constructor test");
		suite->addTest(new CppUnit::TestCaller<CCopyConstructorTest>
				 ("Copy constructor test", &CCopyConstructorTest::copyconstructor));
		return suite;
	}
};




#endif /* CCOPYCONSTRUCTORTEST_H_ */
