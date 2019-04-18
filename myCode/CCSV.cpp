/*
 * CCSV.cpp
 *
 *  Created on: 01-Dec-2018
 *      Author: Sanjay
 */

#include "CCSV.h"
#include <sstream>
#include <cctype>

void CCSV::setMediaName(std::string name)
{
	m_WpFilename = name+"-wp.txt";
	m_PoiFilename = name+"-poi.txt";
}

bool CCSV::writeData (const CWpDatabase& waypointDb,const CPoiDatabase& poiDb)
{
	map<string,CWaypoint> waypointmap;
	map<string,CPOI> poimap;

	/*
	 * get the map of the database
	 */
	poiDb.getPoiMap(poimap);
	waypointDb.getWaypointMap(waypointmap);

	ofstream wp_out(m_WpFilename.c_str());
	ofstream poi_out(m_PoiFilename.c_str());

	if(wp_out.is_open() && poi_out.is_open())
	{
		//writing the file from waypoint map
		map<string,CWaypoint>::const_iterator wp_it;
		for(wp_it=waypointmap.begin();wp_it!=waypointmap.end();++wp_it)
		{
			wp_out << (*wp_it).second.getName() << ",";
			wp_out<< (*wp_it).second.getLatitude()<<",";
			wp_out<< (*wp_it).second.getLongitude()<<endl;
		}

		//writing the file from POI map
		map<string,CPOI>::const_iterator poi_it;
		for(poi_it=poimap.begin();poi_it!=poimap.end();++poi_it)
		{
			poi_out << (*poi_it).second.getType() << ",";
			poi_out << (*poi_it).second.getName() << ",";
			poi_out << (*poi_it).second.getDescription()<<",";
			poi_out<< (*poi_it).second.getLatitude()<<",";
			poi_out<< (*poi_it).second.getLongitude()<<endl;
		}
		return true;
	}
	cout<<"File failed to open"<<endl;
	return false;
}

bool CCSV::readData(CWpDatabase& waypointDb,CPoiDatabase& poiDb,MergeMode mode)
{
	if(mode == REPLACE)
	{
		waypointDb.clearWpMap();
		poiDb.clearPoiMap();
	}

	ifstream wp_in(m_WpFilename.c_str());
	ifstream poi_in(m_PoiFilename.c_str());

	if(!wp_in.is_open()||!poi_in.is_open())
	{
		cout<<"File failed to open"<<endl;
		return false;
	}

	string name;
	string description;
	double latitude = 0;
	double longitude = 0;
	string line ;
	t_poi type;
	string tempstr;
	unsigned int linecount = 1;

	while(getline(wp_in,line) && line!="")    	//checking for blank lines
	{
		if(validateline(line,3))				//field number 3 for waypoint
		{
			stringstream ss(line);
			getline(ss,name,',');
			if(name == "")
				cout<<"ERROR: name of Waypoint is NULL in line "<<linecount<<"("<<m_WpFilename<<")"<<endl;
			getline(ss,tempstr,',');
			stringstream substr1(tempstr);
			if(is_number(tempstr) && tempstr!= "")
			{
				substr1 >> latitude;
				getline(ss,tempstr,',');
				stringstream substr2(tempstr);
				if(is_number(tempstr) && tempstr!= "")
				{
					substr2 >> longitude;
					CWaypoint tempwp(name,latitude,longitude);
					if(tempwp.getName()== "NULL")				//checking for NULL value of name
					{
						cout<<"ERROR: invalid value of latitude/longitude in line "<<linecount<<"("<<m_WpFilename<<")"<<endl;
					}
					else
					{
						waypointDb.addWaypointDB(tempwp); 		//adding waypoint after validating
					}
					++linecount;
				}
				else
				{
					cout<<"ERROR: invalid format of longitude in line "<<linecount<<"("<<m_WpFilename<<")"<<endl;
					++linecount;
				}
			}
			else
			{
				cout<<"ERROR: invalid format of latitude in line "<<linecount<<"("<<m_WpFilename<<")"<<endl;
				++linecount;
			}
		}
		else
		{
			cout<<"ERROR: invalid number of fields in line "<<linecount<<"("<<m_WpFilename<<")"<<endl;
			++linecount;
		}
	}

	linecount = 1;
	while(getline(poi_in,line) )
	{
		if(validateline(line,5) && line!="")
		{
			stringstream ss(line);
			getline(ss,tempstr,',');

			if(tempstr == "RESTAURANT"){ type = RESTAURANT;}
			else if(tempstr == "TOURISTIC"){ type = TOURISTIC;}
			else if(tempstr == "GASSTATION"){ type = GASSTATION;}
			else if(tempstr == "UNIVERSITY"){ type = UNIVERSITY;}
			else{type = NONE;}
			getline(ss,name,',');
			if(name == "")
				cout<<"ERROR: name of POI is NULL in line "<<linecount<<"("<<m_PoiFilename<<")"<<endl;
			getline(ss,description,',');
			if(description == "")
				cout<<"WARNING: description of POI is NULL in line "<<linecount<<"("<<m_PoiFilename<<")"<<endl;
			getline(ss,tempstr,',');
			stringstream str1(tempstr);
			if(is_number(tempstr) && tempstr!= "")
			{
				str1 >> latitude;
				getline(ss,tempstr,',');
				stringstream str2(tempstr);
				if(is_number(tempstr) && tempstr!= "")
				{
					str2 >> longitude;

					CPOI temppoi(type,name,description,latitude,longitude);
					if(type == NONE)
					{
						cout<<"ERROR: invalid value of ENUM in line "<<linecount<<"("<<m_PoiFilename<<")"<<endl;
					}
					else if(temppoi.getName()=="NULL")
					{
						cout<<"ERROR: invalid value of latitude/longitude in line "<<linecount<<"("<<m_PoiFilename<<")"<<endl;
					}
					else
					{
						poiDb.addPoi(temppoi);
					}
					++linecount;
				}
				else
				{
					cout<<"ERROR: invalid format of longitude in line "<<linecount<<"("<<m_PoiFilename<<")"<<endl;
					++linecount;
				}
			}
			else
			{
				cout<<"ERROR: invalid format of latitude in line "<<linecount<<"("<<m_PoiFilename<<")"<<endl;
				++linecount;
			}

		}
		else
		{
			cout<<"ERROR: invalid number of fields in line "<<linecount<<"("<<m_PoiFilename<<")"<<endl;
			++linecount;
		}
	}

	wp_in.close();
	poi_in.close();

	return true;
}

inline bool CCSV::validateline(string& str, unsigned int field)
{
	unsigned int count = 0;
	unsigned int size = str.length();
	for(unsigned int i =0;i<size;++i)
	{
		if(str[i] == ';' || str[i]==',')				// converting ';' to ','
		{
			str[i] = ',';
			++count;									//counting number of ','
		}
		if(str[i]== ',' && str[i+1] == ' ')				//checking for NULL values
		{
			str.erase(i+1,1);
			--i;
			--count;
		}
	}
	if(count == (field-1))
	{
		return true;
	}
	else
		return false;
}

inline bool CCSV::is_number(string str)
{
	unsigned int flag = 0;
	for(unsigned int i = 0;i < str.length();++i)
	{
		if(str[i] == '.')										//counting number of decimal point present
		{
			++flag;
		}
		if((!(isdigit(str[i])) && str[i]!='.') || flag>=2)		//checking for digit and for right number of decimal point
		{
			return false;
		}
	}
	return true;
}
