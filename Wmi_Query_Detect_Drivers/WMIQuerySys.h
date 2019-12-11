#ifndef WMIQUERY_H
#define WMIQUERY_H

#include <Windows.h>
#include <iostream>
#include <vector>

class WMIQuerySys
{
public:
	std::string WMIQuerySys::runQuery(const std::string &query);
	std::vector<std::string> WMIQuerySys::getDeviceNames(const std::string &query);

};

#endif