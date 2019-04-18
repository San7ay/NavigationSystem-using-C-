/*
 * CJasonPersistence.h
 *
 *  Created on: 17-Dec-2018
 *      Author: Sanjay
 */

#ifndef CJASONPERSISTENCE_H_
#define CJASONPERSISTENCE_H_

#include "CWpDatabase.h"
#include "CPoiDatabase.h"
#include "CPersistentStorage.h"

class CPersistentStorage;

enum error_type
{
	FAILED_TO_OPEN,INVALID_FORMAT,INVALID_DB,WARNING,INVALID_ATTRIBUTE,
	INVALID_ATTRIBUTE_NAME,INVALID_VALUE
};

enum state_type
{
	waiting_for_object_begin, waiting_for_db_name, waiting_for_db_begin, waiting_for_attribute_name,
	waiting_for_name_seprator, waiting_for_value, waiting_for_value_seprator, waiting_for_db_end,
	waiting_for_object_end,stay_state
};

class CJasonPersistence : public CPersistentStorage
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

	void errorHandling(error_type error,int line=0);

private:
	/**
	 * for storing the name of the string
	 */
	 string m_jsFilename;

};

#endif /* CJASONPERSISTENCE_H_ */
