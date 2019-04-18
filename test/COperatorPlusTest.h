/*
 * operatorPlusTest.h
 *
 *  Created on: 08-Jan-2019
 *      Author: Sanjay
 */

#ifndef COPERATORPLUSTEST_H_
#define COPERATORPLUSTEST_H_


class COperatorPlusTest: public CppUnit::TestFixture{

private:

	CWpDatabase* m_pWp;
	CPoiDatabase * m_pPoi;
	CRoute* m_pRoute1;
	CRoute* m_pRoute2;
	CJasonPersistence* m_pJson;

public:

	void setUp()
	{
		m_pWp = new CWpDatabase;
		m_pPoi = new CPoiDatabase;
		m_pRoute1 = new CRoute;
		m_pRoute2 = new CRoute;
		m_pJson = new CJasonPersistence;
	}

	void tearDown()
	{
		delete m_pWp;
		delete m_pPoi;
		delete m_pRoute1;
		delete m_pRoute2;
		delete m_pJson;

	}

	void operatorPlusTest()
	{
		m_pJson->setMediaName("database");
		m_pJson->readData(*m_pWp,*m_pPoi,REPLACE);
		m_pRoute1->connectToPoiDatabase(m_pPoi);
		m_pRoute1->connectToWpDatabase(m_pWp);
		m_pRoute2->connectToPoiDatabase(m_pPoi);
		m_pRoute2->connectToWpDatabase(m_pWp);


		m_pRoute1->addWaypoint("amsterdam");
		m_pRoute1->addPoi("Mensa_HDA","amsterdam");

		m_pRoute2->addWaypoint("Darmstadt");
		m_pRoute2->addPoi("Sitte","Darmstadt");

		CRoute routeptr = *m_pRoute1 + *m_pRoute2;

		CPPUNIT_ASSERT(routeptr.getRoute().size() == 4);

	}

	void operatorPlusTestFail()
	{
		m_pJson->setMediaName("database");
		m_pJson->readData(*m_pWp,*m_pPoi,REPLACE);
		m_pRoute1->connectToPoiDatabase(m_pPoi);
		m_pRoute1->connectToWpDatabase(NULL);
		m_pRoute2->connectToPoiDatabase(m_pPoi);
		m_pRoute2->connectToWpDatabase(m_pWp);

		m_pRoute1->addWaypoint("amsterdam");
		m_pRoute1->addPoi("Mensa_HDA","amsterdam");

		m_pRoute2->addWaypoint("Darmstadt");
		m_pRoute2->addPoi("Sitte","Darmstadt");

		CRoute routeptr = *m_pRoute1 + *m_pRoute2;

		CPPUNIT_ASSERT(routeptr.getRoute().size() == 0);

	}

	static CppUnit::TestSuite* suite() {
		CppUnit::TestSuite* suite = new CppUnit::TestSuite("Operator plus Tests");
		suite->addTest(new CppUnit::TestCaller<COperatorPlusTest>
				 ("Operator plus Tests", &COperatorPlusTest::operatorPlusTest));
		suite->addTest(new CppUnit::TestCaller<COperatorPlusTest>
				 ("Operator plus Tests", &COperatorPlusTest::operatorPlusTestFail));
		return suite;
	}

};


#endif /* COPERATORPLUSTEST_H_ */
