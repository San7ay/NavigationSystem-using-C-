/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CPOI.H
* Author          :	Sanjay Prakash
* Description     :	Implement CPOI class, setting the details of POI
*
*
****************************************************************************/

#ifndef CPOI_H
#define CPOI_H

#include "CWaypoint.h"

/*
 *ENUM for type of POI
 */
enum point_of_intrest{
	RESTAURANT,
	TOURISTIC,
	GASSTATION,
	UNIVERSITY,
	NONE
}; typedef point_of_intrest t_poi;

class CPOI : public CWaypoint
{
private:

	//used for type of POI
    t_poi m_type;
    //used for description of POI
    std::string m_description;

public:
    /*
     * Constructor of class CPOI
     * Which is used to set the initial value
     * @param t_poi type 		-		initial value of POI type, default NONE(IN)
     * @param string name 		-		initial value of name , default NULL (IN)
     * @param string description-		initial value of description of POI, default NULL,(IN)
     * @param double latitude	-		intital value of latitude of POI, default 0,(IN)
     * @param double longitude	-		initial value of longitude of POI, default 0,(IN)
     */
    CPOI(t_poi type = NONE , std::string name = "NULL", std::string description = "NULL", double latitude = 0, double longitude = 0);

    /*
     * Prints the details of the POI
     * @param NONE
     * @returmvalue NONE
     */
    virtual void print();

    virtual ~CPOI();

    /*
     * overloading << operator for printing POI
     */
    friend std::ostream& operator <<(std::ostream& stream, CPOI& poi);

    /*
     * returns the type value of POI
     */
    std::string getType() const;

    /*
     * returns the description of the POI
     */
    std::string getDescription() const;

};
/********************
**  CLASS END
*********************/
#endif /* CPOI_H */
