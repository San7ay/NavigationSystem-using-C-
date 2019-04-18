/*
 * CPersistentStorage.h
 *
 *  Created on: 26-Nov-2018
 *      Author: Sanjay
 */

#ifndef CPERSISTENTSTORAGE_H_
#define CPERSISTENTSTORAGE_H_

#include <string>

class CPoiDatabase;
class CWpDatabase;

enum MergeMode{ MERGE, REPLACE };		//MERGE merge the content of database and file in database
										//REPLACE replace the content of database with that of file

class CPersistentStorage
{
public:

	/*
	 * constructor
	 */
	CPersistentStorage();

	/**
	 * set the filename
	 * @param string name(IN)
	 * @return void
	 */
	virtual void setMediaName(std::string name)=0;

	/*
	 * write the data from database to file
	 * @param const CWpDatabase& (IN)
	 * @param const CPoiDatabase& (IN)
	 * @return bool
	 */
	virtual bool writeData (const CWpDatabase& waypointDb,const CPoiDatabase& poiDb)=0;

	/*
	 * read the data from file to database
	 * @param CWpDatabase& (IN)
	 * @param CPoiDatabase& (IN)
	 * @return bool
	 */
	virtual bool readData( CWpDatabase& waypointDb,CPoiDatabase& poiDb,MergeMode mode)=0;

	/*
	 * destructor
	 */
	virtual ~CPersistentStorage();

};

#endif /* CPERSISTENTSTORAGE_H_ */
