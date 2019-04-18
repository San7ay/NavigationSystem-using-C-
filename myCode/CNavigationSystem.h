/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CNAVIGATIONSYSTEM.H
* Author          :	Sanjay Prakash
* Description     :	Basic navigation system with number of waypoints and POI
*
****************************************************************************/

#ifndef CNAVIGATIONSYSTEM_H
#define CNAVIGATIONSYSTEM_H
#include "CGPSSensor.h"
#include "CRoute.h"
#include "CPoiDatabase.h"
#include "CWpDatabase.h"
#include "CPersistentStorage.h"
#include "CCSV.h"

class CNavigationSystem {

private:
    /**
     * Prints the route of our navigation system
     * @param 		none
     * @returnvalue none
     */
    void printRoute();
    /**
     * For entering our route with required Waypoint and POI
     * @param 		none
     * @returnvalue none
     */
    void enterRoute();

    /**
     * @link aggregationByValue
     */
    CGPSSensor m_GPSSensor;

    /**
     * @link aggregationByValue
     */
    CRoute m_route;

    /**
     * @link aggregationByValue
     */
    CPoiDatabase m_PoiDatabase;

    /**
     * @link aggregationByValue
     */
    CWpDatabase m_WpDatabase;

    /**
     * testcase of creating the database
     */
    void createDatabase();

    /**
     * testcase for writing database into a file
     */
    void writeToFile();

    /**
     * testcase for reading data from file to database
     */
    void readFromFile(MergeMode);

public:

    /**
     * Constructor of CNavigation
     */
    CNavigationSystem();
    /**
     * Method to enter the required route and getting distance between nearest POI
     * @param 		none
     * @returnvalue none
     */
    void run();

};
/********************
**  CLASS END
*********************/
#endif /* CNAVIGATIONSYSTEM_H */
