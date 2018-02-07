#ifndef WMIQUERY_H
#define WMIQUERY_H

#include <Windows.h>
#include <iostream>

class WMIQuerySys
{
public:
	std::string WMIQuerySys::runQuery(const std::string &query);

};

#endif