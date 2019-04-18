/*
 * printTest.h
 *
 *  Created on: 08-Jan-2019
 *      Author: Sanjay
 */

#ifndef CPRINTTEST_H_
#define CPRINTTEST_H_

class CPrintTest: public CppUnit::TestFixture
{
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

	void printTest() //printing the route
	{
		m_pJson->setMediaName("database");
		m_pJson->readData(*m_pWp,*m_pPoi,REPLACE);
		m_pRoute->connectToPoiDatabase(m_pPoi);
		m_pRoute->connectToWpDatabase(m_pWp);
		m_pRoute->addWaypoint("amsterdam");
		m_pRoute->addPoi("Mensa_HDA","amsterdam");
		m_pRoute->print();
		CPPUNIT_ASSERT(m_pRoute->getRoute().size()==2);


	}

	void emptyPrintTest()  //printing the route without any waypoints or route addition
	{
		m_pRoute->connectToPoiDatabase(m_pPoi);
		m_pRoute->connectToWpDatabase(m_pWp);

		m_pRoute->print();
		CPPUNIT_ASSERT(m_pRoute->getRoute().size()==0);
    }

	void printFailTest()  //printing the without database connection
	{
		m_pJson->setMediaName("database");
		m_pJson->readData(*m_pWp,*m_pPoi,REPLACE);
		m_pRoute->connectToPoiDatabase(NULL);
		m_pRoute->connectToWpDatabase(NULL);
		m_pRoute->addWaypoint("amsterdam");
		m_pRoute->addPoi("Mensa_HDA","amsterdam");
		m_pRoute->print();

		CPPUNIT_ASSERT(m_pRoute->getRoute().size()== 0);
	}




	static CppUnit::TestSuite* suite()
	{
		CppUnit::TestSuite* suite = new CppUnit::TestSuite("print test");
		suite->addTest(new CppUnit::TestCaller<CPrintTest>
				 ("valid print", &CPrintTest::printTest));
		suite->addTest(new CppUnit::TestCaller<CPrintTest>
				("print without any elements in route", &CPrintTest::emptyPrintTest));
		suite->addTest(new CppUnit::TestCaller<CPrintTest>
				("print without database connection", &CPrintTest::printFailTest));

        return suite;
	}
};




#endif /* CPRINTTEST_H_ */
