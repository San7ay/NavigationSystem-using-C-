/*
 * operatorPlusEqualsTest.h
 *
 *  Created on: 08-Jan-2019
 *      Author: Sanjay
 */

#ifndef COPERATORPLUSEQUALSTEST_H_
#define COPERATORPLUSEQUALSTEST_H_


#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>

#include "../myCode/CRoute.h"

class COperatorPlusEqualTest: public CppUnit::TestFixture{
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

	void operatorplusequals()
	{
		m_pJson->setMediaName("database");
		m_pJson->readData(*m_pWp,*m_pPoi,REPLACE);
		m_pRoute->connectToPoiDatabase(m_pPoi);
		m_pRoute->connectToWpDatabase(m_pWp);

		*m_pRoute += "Amsterdam";
		*m_pRoute += "Mensa_HDA";
		*m_pRoute += "Sitte";
		*m_pRoute += "sumalya";

		CPPUNIT_ASSERT(m_pRoute->getRoute().size()==3);
	}

	static CppUnit::TestSuite* suite() {
		CppUnit::TestSuite* suite = new CppUnit::TestSuite("operator plus equals test");
		suite->addTest(new CppUnit::TestCaller<COperatorPlusEqualTest>
				 ("operator plus equals test", &COperatorPlusEqualTest::operatorplusequals));
		return suite;
	}
};


#endif /* COPERATORPLUSEQUALSTEST_H_ */
