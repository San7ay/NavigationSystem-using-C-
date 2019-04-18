/*
 * CDBTemplate.h
 *
 *  Created on: 05-Jan-2019
 *      Author: Sanjay
 */

#ifndef CDBTEMPLATE_H_
#define CDBTEMPLATE_H_

#include <map>
#include <cstring>
#include <iostream>

template<class T>
class CDBTemplate
{
private:
	std::map<std::string,T> m_DBmap;

public:

	CDBTemplate()
	{

	}

	void addElement(T const& element)
	{
		std::string name = element.getName();
		if(name != "")								//check for NULL value of name
		{
			m_DBmap[uppertolower(name)] = element;
		}
	}

	T* getPointerToElement(std::string name)
	{
		name = uppertolower(name);
		if(m_DBmap.empty())
		{
			std::cout<<"POI database empty"<<std::endl;
		}
		else
		{
			typename std::map<std::string,T>::const_iterator it;

			it = m_DBmap.find(name);
			if(it != m_DBmap.end())
			{
				return &m_DBmap[name];
			}
		}
		return NULL;
	}

	void getElementMap(std::map<std::string,T> & dbMap) const
	{
		dbMap = m_DBmap;
	}

	void print()
	{
		for( typename std::map<std::string,T>::iterator it=m_DBmap.begin();it!=m_DBmap.end();++it)
		{
			it->second.print();
		}
	}

	void clearElementMap()
	{
		m_DBmap.clear();
	}

	std::string uppertolower(std::string name)
	{
		int size = name.size();
		char char_array[size+1];
		strcpy(char_array,name.c_str());
		char c;
		int i= 0;
		while (char_array[i])
		{
			c=char_array[i];
		    char_array[i] = tolower(c);
		    i++;
		}
		name = char_array;
		return name;
	}

};

#endif /* CDBTEMPLATE_H_ */
