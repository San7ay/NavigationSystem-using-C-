/*
 * CWpDatabase.h
 *
 *  Created on: 20-Nov-2018
 *      Author: Sanjay
 */

#ifndef CWPDATABASE_H_
#define CWPDATABASE_H_
#include "CWaypoint.h"
#include "CDBTemplate.h"
#include <map>

using namespace std;

class CWpDatabase : public CDBTemplate<CWaypoint>
{

private:
	// For storing waypoints
    map<string,CWaypoint> m_Waypoint;

public:

    /*The constructor of the CWpdatabase,
     * which also allows you to set an initial value for number of Waypoints for zero
     */
    CWpDatabase();

    /*
     * Add waypoint into the database
     * @param string name			-	the name value (IN)
     * @param double latitude		-	the latitude value (IN)
     * @param double longitude		-	the longitude value (IN)
     * @returnvalue none
     */
    void addWaypointDB(CWaypoint const&);

    /*
     * With the name of the waypoint search for the required waypoint in the database
     * and return the pointer pointing to the required waypoint.
     * @param string name	-	the name value (IN)
     * @returnvalue 		-	pointer to CWaypoint (CWaypoint*)
     */
    CWaypoint* getPointerToWaypoint(std::string name);

    /*
     * prints the content of waypoint database
     * used for debugging
     */
    void print();

    /*
     * returns the map of the waypoint database
     */
    void getWaypointMap(map<string,CWaypoint> &) const;

    /*
     * clears the content of waypoint database
     */
    void clearWpMap();

    /*
     * converts all the character to lower case
     */
    string uppertolower(string);

};


#endif /* CWPDATABASE_H_ */
