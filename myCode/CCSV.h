/*
 * CCSV.h
 *
 *  Created on: 01-Dec-2018
 *      Author: Sanjay
 */

#ifndef CCSV_H_
#define CCSV_H_

#include "CWpDatabase.h"
#include "CPoiDatabase.h"
#include "CPersistentStorage.h"

class CPersistentStorage;

class CCSV : public CPersistentStorage
{
public:

	/**
	 * set the filename
	 * @param string name(IN)
	 * @return void
	 */
	void setMediaName(std::string name);

	/**
	 * write the data from database to file
	 * @param const CWpDatabase& (IN)
	 * @param const CPoiDatabase& (IN)
	 * @return bool
	 */
	bool writeData (const CWpDatabase& waypointDb,const CPoiDatabase& poiDb);

	/**
	 * read the data from file to database
	 * @param CWpDatabase& (IN)
	 * @param CPoiDatabase& (IN)
	 * @return bool
	 */
	bool readData( CWpDatabase& waypointDb, CPoiDatabase& poiDb,MergeMode mode);

private:

	/**
	 * validate the single file for invalid number of fields
	 * @param string & line (IN)
	 * @param unsigned int number_of_fields (IN)
	 * @return bool
	 */
	bool validateline(string& is,unsigned int);

	/**
	 * validate wheather the string is number or not
	 */
	bool is_number(string str);

	/**
	 * for storing file name of waypoint database
	 */
	string m_WpFilename;

	/**
	 * for storing file name of POI database
	 */
	string m_PoiFilename;
};

#endif /* CCSV_H_ */
