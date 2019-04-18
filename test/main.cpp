/*
 * main.cpp
 *
 *  Created on: 08-Jan-2019
 *      Author: Sanjay
 */
#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/ui/text/TestRunner.h>

#include "CAddPoiTest.h"
#include "CAddWaypointTest.h"
#include "CConnectToPoiDatabaseTest.h"
#include "CConnectToWpDatabaseTest.h"
#include "CCopyConstructorTest.h"
#include "CGetRouteTest.h"
#include "COperatorEqualTest.h"
#include "COperatorPlusEqualsTest.h"
#include "COperatorPlusTest.h"
#include "CPrintTest.h"

using namespace CppUnit;

int main (int argc, char* argv[]) {

	TextUi::TestRunner runner;
	std::cout<<"Test environment"<<std::endl;
	runner.addTest( CAddPoiTest::suite());
	runner.addTest(CAddWaypointTest::suite());
	runner.addTest(CConnectToPoiDatabaseTest::suite());
	runner.addTest(CConnectToWpDatabaseTest::suite());
	runner.addTest(CCopyConstructorTest::suite());
	runner.addTest(CGetRouteTest::suite());
	runner.addTest(COperatorEqualTest::suite());
	runner.addTest(COperatorPlusEqualTest::suite());
	runner.addTest(COperatorPlusTest::suite());
	runner.addTest(CPrintTest::suite());

	runner.run();

	return 0;
}




