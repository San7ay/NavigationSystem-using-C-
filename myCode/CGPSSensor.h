/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CGPSSENSOR.H
* Author          :	Sanjay Prakash
* Description     :	Used to get the coordinate of the current place
*
****************************************************************************/

#ifndef CGPSSENSOR_H
#define CGPSSENSOR_H

#include "CWaypoint.h"

class CGPSSensor {
public:
	 /**
	  * Constructor of CGPSSensor
	  */
	 CGPSSensor();

	/**
	 * Returns the current position in terms of CWaypoint object
	 * @param none
	 * @returnvalue CWaypoint
	 */
    CWaypoint getCurrentPosition();
};
/********************
**  CLASS END
*********************/
#endif /* CGPSSENSOR_H */
