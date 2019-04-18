/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CROUTE.H
* Author          :	Sanjay Prakash
* Description     :	Used to maintain the route which include waypoints and POI
*
****************************************************************************/

#ifndef CROUTE_H
#define CROUTE_H
#include "CPOI.h"
#include "CPoiDatabase.h"
#include "CWpDatabase.h"
#include "CWaypoint.h"
#include "CJasonPersistence.h"
#include <list>
#include <vector>

class CRoute {
private:
    /*
     * pointer of CPoiDatabase
     */
    CPoiDatabase* m_pPoiDatabase;

    /*
     * pointer of CWpDatabase
     */
    CWpDatabase* m_pWpDatabase;

    /*
     * list for storing POI and Waypoint of route
     */
    list <CWaypoint*> m_pWaypoint;

    /*
     * number of waypoint in the route
     */
    unsigned int m_noWp;

    /*
     * number of POI in the route
     */
    unsigned int m_noPoi;

public:
    /**
     * constructor of CRoute class
     * which also allows you to set the initial value
     * @param unsigned int maxWp	-	 the initial maximum waypoint value, default value 2 (IN)
     * @param unsigned int maxPoi	-	 the initial maximun POI value , default value 0 (IN)
     */
    CRoute();

    /**
     * Copy constructor of class CRoute
     */
    CRoute(CRoute const& origin);

    /**
     * Destructor of the class CRoute
     */
    ~CRoute();

    /**
     * Used to connect to the database in class CPoiDatabase
     */
    void connectToPoiDatabase(CPoiDatabase* pPoiDB = NULL);

    /**
     * Used to connect to the database in class CWpDatabase
     */
    void connectToWpDatabase(CWpDatabase* pWpDB = NULL);

    /**
     * To add waypoints to the route
     */
    void addWaypoint(std::string nameWp);

    /**
     * Check for the POI in database and add the same to the route
     */
    void addPoi(std::string namePoi,std::string afterWp);

    /**
     * prints the Waypoints and POI in the route
     */
    void print();

    /**
     * copy the content of one route to other
     */
    CRoute& operator=(const CRoute& route);

    /**
     * add POI or/and Waypoint at the end
     */
    CRoute& operator+=(string name);

    /**
     * concatenate two route
     */
    friend CRoute operator+(CRoute& route1,CRoute& route2);

    /**
     * returns the list of pointers to the waypoints and poi in the route
     * @return list of pointer to the waypoints and poi in the route
     */
    const vector<const CWaypoint*> getRoute();


};
/********************
**  CLASS END
*********************/
#endif /* CROUTE_H */
