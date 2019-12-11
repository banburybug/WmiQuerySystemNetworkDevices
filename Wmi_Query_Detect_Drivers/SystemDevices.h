#ifndef SYSTEMDEVICES_H
#define SYSTEMDEVICES_H

#include <iostream>

#include "Device.h"
#include "WMIQuerySys.h"
#include "vector"
#include <vector>
#include <vector>

class SystemDevices
{

private:
	std::vector<DEVICE> _AvailableGPRSDevices;
	WMIQuerySys _querySystem;
	
public:
	SystemDevices();
	~SystemDevices();

	DEVICE getNetworkAdapterFromPnPDevices();
	std::vector<std::string> getAllPnPDeviceNames();
	DEVICE getNetworkAdapterFromNetworkAdapter();
	void initialiseKnownAdapters();

};

#endif