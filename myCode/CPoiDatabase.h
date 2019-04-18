/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CPOIDATABASE.H
* Author          :	Sanjay Prakash
* Description     :	Class which provide database for POI and manipulate POI
*
****************************************************************************/

#ifndef CPOIDATABASE_H
#define CPOIDATABASE_H
#include "CPOI.h"
#include <fstream>
#include "CDBTemplate.h"

class CPoiDatabase : public CDBTemplate<CPOI>
{
private:
	// For storing POI
    std::map<std::string,CPOI> m_POI;

public:

    /*The constructor of the CPoidatabase,
     * which also allows you to set an initial value for number of POI for zero
     */
    CPoiDatabase();

    /*
     * Add POI into the database
     * @param t_poi type 			- 	the type value (IN)
     * @param string name			-	the name value (IN)
     * @param string description	-	the description value (IN)
     * @param double latitude		-	the latitude value (IN)
     * @param double longitude		-	the longitude value (IN)
     * @returnvalue none
     */
    void addPoi(CPOI const&);

    /*
     * With the name of the POI search for the required POI in the database(array)
     * and return the pointer pointing to the required POI.
     * @param string name	-	the name value (IN)
     * @returnvalue 		-	pointer to CPOI (CPOI*)
     */
    CPOI* getPointerToPoi(std::string name);

    /*
     * returns the map of the POI database
     */
    void getPoiMap(std::map<std::string,CPOI>&) const;

    /*
     * prints the content of POI database
     * used for debugging
     */
    void print();

    /*
     * clears the content of POI database
     */
    void clearPoiMap();

    /**
     *
     * @param string
     * @return string
     */
    std::string uppertolower(std::string);

};


/********************
**  CLASS END
*********************/
#endif /* CPOIDATABASE_H */
