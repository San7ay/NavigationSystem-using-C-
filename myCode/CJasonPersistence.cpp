/*
 * CJasonPersistence.cpp
 *
 *  Created on: 17-Dec-2018
 *      Author: Sanjay
 */

#include "CJasonPersistence.h"
#include "CJsonScanner.h"
#include "CJsonToken.h"

#define  S  ' '
#define  Q  '"'

using namespace APT;


void CJasonPersistence::setMediaName(std::string name)
{
	m_jsFilename = name+"-JSON.txt";
}

bool CJasonPersistence::writeData(const CWpDatabase& waypointDb,const CPoiDatabase& poiDb)
{
	map<string,CWaypoint> waypointmap;
	map<string,CPOI> poimap;

	poiDb.getPoiMap(poimap);
	waypointDb.getWaypointMap(waypointmap);

	ofstream js_out(m_jsFilename.c_str());

	if(js_out.is_open())
	{
		js_out << "{"<<endl;
		if(!waypointmap.empty())
		{
			js_out <<S<<Q<<"waypoints"<<Q<<": ["<<endl;

			map<string,CWaypoint>::const_iterator wp_it;
			for(wp_it=waypointmap.begin();wp_it!=waypointmap.end();++wp_it)
			{
				js_out <<S<<S<<"{"<<endl;
				js_out<<S<<S<<S<<Q<<"name"<<Q<<": "<<Q<<(*wp_it).second.getName()<<Q<<","<<endl;
				js_out<<S<<S<<S<<Q<<"latitude"<<Q<<": "<<(*wp_it).second.getLatitude()<<","<<endl;
				js_out<<S<<S<<S<<Q<<"longitude"<<Q<<": "<<(*wp_it).second.getLongitude()<<endl;
				if(++wp_it==waypointmap.end())
				{
					js_out <<S<<S<<"}"<<endl;
					--wp_it;
				}
				else
				{
					js_out <<S<<S<<"},"<<endl;
					--wp_it;
				}
			}

			js_out<<" ]";

			if(!poimap.empty())
			{
				js_out<<","<<endl;
			}
		}
		if(!poimap.empty())
		{

			js_out <<S<<Q<<"pois"<<Q<<": ["<<endl;

			map<string,CPOI>::const_iterator poi_it;
			for(poi_it=poimap.begin();poi_it!=poimap.end();++poi_it)
			{
				js_out <<S<<S<<"{"<<endl;
				js_out<<S<<S<<S<<Q<<"name"<<Q<<": "<<Q<<(*poi_it).second.getName()<<Q<<","<<endl;
				js_out<<S<<S<<S<<Q<<"latitude"<<Q<<": "<<(*poi_it).second.getLatitude()<<","<<endl;
				js_out<<S<<S<<S<<Q<<"longitude"<<Q<<": "<<(*poi_it).second.getLongitude()<<","<<endl;
				js_out<<S<<S<<S<<Q<<"type"<<Q<<": "<<Q<<(*poi_it).second.getType()<<Q<<","<<endl;
				js_out<<S<<S<<S<<Q<<"description"<<Q<<": "<<Q<<(*poi_it).second.getDescription()<<Q<<endl;
				if(++poi_it==poimap.end())
				{
					js_out <<S<<S<<"}"<<endl;
					--poi_it;
				}
				else
				{
					js_out <<S<<S<<"},"<<endl;
					--poi_it;
				}
			}

			js_out<<" ]"<<endl;

		}
		js_out<<"}"<<endl;
		return true;
	}
	else
	{
		errorHandling(FAILED_TO_OPEN);
		return false;
	}
}

bool CJasonPersistence::readData(CWpDatabase& waypointDb, CPoiDatabase& poiDb,MergeMode mode)
{
	if(mode == REPLACE)
	{
		waypointDb.clearWpMap();
		poiDb.clearPoiMap();
	}

	state_type previous_state = waiting_for_object_begin;
	state_type next_state = waiting_for_object_begin;

	ifstream inputfile(m_jsFilename.c_str());

	CJsonScanner scanner(inputfile);

	CJsonStringToken* StringToken_ptr = NULL;
	CJsonNumberToken* NumberToken_ptr = NULL;

	unsigned int value_cnt = 0;
	unsigned int temp_cnt = 0;
	string attribute_value = "NULL";
	string name = "NULL";
	string description = "NULL";
	double latitude = 0;
	double longitude = 0;
	t_poi type = NONE;

	if(!inputfile.is_open())
	{
		errorHandling(FAILED_TO_OPEN);
	}

	while(inputfile.is_open())
	{
		try
		{
			CJsonToken* TokenPtr = scanner.nextToken();

			switch(next_state)
			{
			case waiting_for_object_begin:
											{
												//cout<<"waiting_for_first_token"<<endl;
												if(TokenPtr->getType() == CJsonToken::BEGIN_OBJECT)
												{
													if(previous_state == waiting_for_db_begin)
													{
														next_state = waiting_for_attribute_name;
													}
													else if(previous_state == waiting_for_value_seprator)
													{
														next_state = waiting_for_attribute_name;
													}
													else
													{
														next_state = waiting_for_db_name;
													}
													previous_state = waiting_for_object_begin;
												}
												else
												{
													errorHandling(INVALID_FORMAT);
													inputfile.close();
												}
												break;
											}

			case waiting_for_db_name:
										{
											//cout<<"waiting_for_db_name"<<endl;
											if(TokenPtr->getType() == CJsonToken::STRING)
											{
												StringToken_ptr = static_cast<CJsonStringToken*>(TokenPtr);
												string temp = StringToken_ptr->getValue();
												if(temp == "waypoints" || temp == "pois")
												{
													value_cnt = (temp == "waypoints")?3:5;
													temp_cnt = value_cnt;

													next_state = waiting_for_name_seprator;
													previous_state = waiting_for_db_name;
												}
												else
												{
													errorHandling(INVALID_DB,scanner.scannedLine());
													next_state = stay_state;
													previous_state = waiting_for_db_name;
													break;
												}
											}
											else
											{
												errorHandling(INVALID_DB);
											}
											break;
										}

			case waiting_for_name_seprator:
											{
												//cout<<"waiting_for_name_seprator"<<endl;
												if(TokenPtr->getType() == CJsonToken::NAME_SEPARATOR)
												{
													if(previous_state == waiting_for_db_name)
													{
														next_state = waiting_for_db_begin;
													}
													else if(previous_state == waiting_for_attribute_name)
													{
														next_state = waiting_for_value;
													}
													previous_state = waiting_for_name_seprator;
												}
												else
												{
													errorHandling(INVALID_FORMAT,scanner.scannedLine());
													inputfile.close();
												}
												break;
											}

			case waiting_for_db_begin:
										{
											//cout<<"waiting_for_db_begin"<<endl;
											if(TokenPtr->getType() == CJsonToken::BEGIN_ARRAY)
											{
												next_state = waiting_for_object_begin;
												previous_state = waiting_for_db_begin;
											}
											else
											{
												errorHandling(INVALID_FORMAT,scanner.scannedLine());
												inputfile.close();
											}
											break;
										}

			case waiting_for_attribute_name:
											{
												//cout<<"waiting_for_attribute_name"<<endl;
												if(TokenPtr->getType() == CJsonToken::STRING)
												{
													StringToken_ptr = static_cast<CJsonStringToken*>(TokenPtr);
													attribute_value = StringToken_ptr->getValue();
													next_state = waiting_for_name_seprator;
													previous_state = waiting_for_attribute_name;
												}
												else
												{
													errorHandling(WARNING,scanner.scannedLine());
													next_state = stay_state;
													previous_state = waiting_for_attribute_name;
													value_cnt = temp_cnt;
												}
												break;
											}

			case stay_state:
							{
								//cout<<"stay state"<<endl;
								if(previous_state == waiting_for_db_name)
								{
									if(TokenPtr->getType() == CJsonToken::END_ARRAY)
									{
										next_state = waiting_for_value_seprator;
										previous_state = waiting_for_value_seprator;
									}
									else
									{
										next_state = stay_state;
										previous_state = waiting_for_db_name;
									}
								}
								else
								{
									if(TokenPtr->getType() == CJsonToken::BEGIN_OBJECT)
									{
										next_state = waiting_for_attribute_name;
										previous_state = waiting_for_value_seprator;
									}
									else if(TokenPtr->getType() == CJsonToken::END_ARRAY)
									{
										next_state = waiting_for_value_seprator;
										previous_state = waiting_for_value_seprator;
									}
									else
									{
										next_state = stay_state;
										previous_state = stay_state;
									}
								}
								break;
							}

			case waiting_for_value:
									{
										//cout<<"waiting_for_value"<<endl;
										if(TokenPtr->getType() == CJsonToken::NUMBER || TokenPtr->getType() == CJsonToken::STRING)
										{
											if(value_cnt!=0)
											{
												StringToken_ptr = static_cast<CJsonStringToken*>(TokenPtr);
												NumberToken_ptr = static_cast<CJsonNumberToken*>(TokenPtr);

												if(attribute_value=="name")
												{
													name = StringToken_ptr->getValue();
													if(name == "")
													{
														errorHandling(INVALID_ATTRIBUTE,scanner.scannedLine());
													}
												}

												else if(attribute_value == "latitude")
												{
													if(NumberToken_ptr == NULL)
													{
														errorHandling(INVALID_ATTRIBUTE,scanner.scannedLine());
													}
													else
													{
														latitude = NumberToken_ptr->getValue();
													}

												}
												else if(attribute_value == "longitude")
												{
													if(NumberToken_ptr == NULL)
													{
														errorHandling(INVALID_ATTRIBUTE,scanner.scannedLine());
													}
													else
													{
														longitude = NumberToken_ptr->getValue();
													}

												}

												else if(attribute_value == "description")
												{
													description = StringToken_ptr->getValue();

												}
												else if(attribute_value == "type")
												{
													string temp;
													temp = StringToken_ptr->getValue();
													if(temp=="RESTAURANT")
														type = RESTAURANT;
													if(temp=="TOURISTIC")
														type = TOURISTIC;
													if(temp=="GASSTATION")
														type = GASSTATION;
													if(temp=="UNIVERSITY")
														type = UNIVERSITY;
													if(type==NONE)
													{
														errorHandling(INVALID_ATTRIBUTE,scanner.scannedLine());
														next_state = stay_state;
														previous_state = waiting_for_value;
														value_cnt = temp_cnt;
														break;

													}

												}

												else
												{
													errorHandling(INVALID_ATTRIBUTE_NAME,scanner.scannedLine());
													next_state = stay_state;
													previous_state = waiting_for_value;
													value_cnt = temp_cnt;
													break;

												}
												--value_cnt;

											}
											if(value_cnt!=0)
											{
												next_state = waiting_for_value_seprator;
												previous_state = waiting_for_value;
											}
											if(value_cnt==0)
											{
												if((name!="NULL") && (latitude!=0) && (longitude!= 0) && (type==NONE) && (description=="NULL"))
												{
													waypointDb.addWaypointDB(CWaypoint(name,latitude,longitude));
													value_cnt = 3;
												}
												else
												{
													poiDb.addPoi(CPOI(type,name,description,latitude,longitude));
													value_cnt = 5;
												}
												name = "NULL";
												latitude = 0;
												longitude = 0;
												type = NONE;
												description = "NULL";

												next_state = waiting_for_object_end;
												previous_state = waiting_for_value;

											}
										}
										else
										{
											errorHandling(INVALID_ATTRIBUTE,scanner.scannedLine());
											next_state = stay_state;
											previous_state = waiting_for_value;
											value_cnt = temp_cnt;

										}
										break;

									}

			case waiting_for_value_seprator:
											{
												//cout<<"waiting_for_value_seprator"<<endl;
												if(TokenPtr == NULL)
												{
													errorHandling(INVALID_FORMAT,scanner.scannedLine());
													inputfile.close();
												}
												else if(TokenPtr->getType() == CJsonToken::VALUE_SEPARATOR)
												{
													if(previous_state == waiting_for_object_end)
													{
														next_state = waiting_for_object_begin;
													}
													else if(previous_state == waiting_for_value_seprator)
													{
														next_state = waiting_for_db_name;
													}
													else
													{
														next_state = waiting_for_attribute_name;
													}
													previous_state = waiting_for_value_seprator;
												}
												else if(TokenPtr->getType() == CJsonToken::END_ARRAY)
												{
													next_state = waiting_for_value_seprator;
													previous_state = waiting_for_value_seprator;

												}
												else if(TokenPtr->getType() == CJsonToken::END_OBJECT)
												{
													inputfile.close();
												}
												else if(TokenPtr->getType() == CJsonToken::BEGIN_OBJECT)
												{
													next_state = waiting_for_attribute_name;
													previous_state = waiting_for_value_seprator;
												}
												else
												{
													errorHandling(INVALID_VALUE,scanner.scannedLine());
												}
												break;
											}

			case waiting_for_db_end:
									{
										//cout<<"waiting_for_db_end"<<endl;

										if(TokenPtr->getType()== CJsonToken::END_ARRAY)
										{
											TokenPtr = scanner.nextToken();

											if(TokenPtr->getType() == CJsonToken::VALUE_SEPARATOR)
											{
												next_state = waiting_for_db_name;
												previous_state = waiting_for_db_end;
											}
											else if(TokenPtr->getType() == CJsonToken::END_OBJECT)
											{
												next_state = waiting_for_object_end;
												previous_state = waiting_for_db_end;
											}

										}
										else
										{
											errorHandling(INVALID_FORMAT,scanner.scannedLine());
											inputfile.close();
										}
										break;

									}

			case waiting_for_object_end:
										{
											//cout<<"waiting_for_last_token"<<endl;
											if(TokenPtr->getType() == CJsonToken::END_OBJECT)
											{
												if(previous_state == waiting_for_value)
												{
													next_state = waiting_for_value_seprator;
													previous_state = waiting_for_object_end;
												}

											}
											else
											{
												errorHandling(WARNING,scanner.scannedLine());
											}

											break;
										}

			}

		}
		catch(int error)
		{
			cerr<<"WARNING:Invalid character in line "<<scanner.scannedLine()<<endl;
		}

	}
	return true;
}

void CJasonPersistence::errorHandling(error_type error,int line)
{
	switch(error)
	{
	case FAILED_TO_OPEN:
	{
		cerr<<"ERROR: Failed to open file"<<endl;
		break;
	}
	case INVALID_FORMAT:
	{
		if(line == 0)
		{
			cerr<<"ERROR: Invalid format"<<endl;
		}
		else
		{
			cerr<<"ERROR: Invalid format in line "<<line<<endl;
		}
		break;
	}
	case INVALID_DB:
	{
		if(line == 0)
		{
			cerr<<"ERROR: Invalid format of database"<<endl;
		}
		else
		{
			cerr<<"ERROR: Invalid name of database in line "<<line<<endl;
		}
		break;
	}
	case WARNING:
	{
		cerr<<"WARNING: Expected behaviour not found in line "<<line<<endl;
		break;
	}
	case INVALID_ATTRIBUTE:
	{
		cerr<<"ERROR: Invalid value of attribute in line "<<line<<endl;
		break;
	}
	case INVALID_ATTRIBUTE_NAME:
	{
		cerr<<"ERROR: Invalid name of the attribute in line "<<line<<endl;
		break;
	}
	case INVALID_VALUE:
	{
		cerr<<"ERROR: Invalid value in line "<<line<<endl;
		break;
	}
	}
}
