/*
 * CWaypoint.h
 *
 *  Created on: 22-Oct-2018
 *  Author: Sanjay Prakash
 */

#ifndef CWAYPOINT_H_
#define CWAYPOINT_H_

#include <iostream>

class CWaypoint
{
public:

	/*The constructor of the CWaypoint,
	 * which also allows you to set an initial value
	 * @param string name		- The initial name value, default NULL (IN)
	 * @param double latitude	- The initial latitude value, default 0 (IN)
	 * @param double longitude	- The initial longitude value, default 0 (IN)
	 */
	CWaypoint(std::string = "NULL", double = 0, double = 0);

	virtual ~CWaypoint();

	/**
	 * Sets the current coordinate value
	 * @param string name	    - the new name value (IN)
	 * @param double latitude	- the new latitude value (IN)
	 * @param double longitude	- the new longitude value (IN)
	 */
	void set(std::string, double, double);

	/**
	 * Returns the name
	 * @returnvalue string
	 */
	std::string getName() const;

	/**
	 * Returns the latitude value
	 * @returnvalue double
	 */
	double getLatitude() const;

	/**
	 * Returns the longitude value
	 * @returnvalue double
	 */
	double getLongitude() const;

	/* Print latitude and longitude of single place in two format
	 * 1. Decimal formant
	 * 2. Deg mm ss format
	 * @param 		int
	 * @returnvalue none
	 */
	virtual void print();

	/*
	 * operator overloading << for printing waypoints
	 */
	friend std::ostream& operator <<(std::ostream& stream, CWaypoint& waypoint);

private:
	/**
	 * Returns the longitude in deg mm ss format value by reference
	 * @param int & deg		- the current deg value (OUT)
	 * @param int & mm		- the current mm value (OUT)
	 * @param double & ss	- the current ss value (OUT)
	 */
	void transformLongitude2degmmss(int&, int&, double&);

	/**
	 * Returns the latitude in deg mm ss format value by reference
	 * @param int & deg		- the current deg value (OUT)
	 * @param int & mm		- the current mm value (OUT)
	 * @param double & ss	- the current ss value (OUT)
	 */
	void transformLatitude2degmmss(int&, int&, double&);

protected:
	/*
	 * For identification of waypoints by name
	 */
	std::string m_name;

	/*
	 * For storing latitude of waypoints
	 */
	double m_latitude;

	/*
	 * For storing longitude of waypoints
	 */
	double m_longitude;

};

#endif /* CWAYPOINT_H_ */
