
#include "SystemDevices.h"



SystemDevices::SystemDevices():

	_querySystem()
{
		_AvailableGPRSDevices = std::vector<DEVICE>();
}

SystemDevices::~SystemDevices()
{}

DEVICE SystemDevices::getNetworkAdapterFromNetworkAdapter()
{

	DEVICE installedDevice;
	installedDevice.AdapterType = NETWORK_ADAPTER_TYPE_NONE;

	//Build the query
	std::string AdapterQuery = "SELECT * FROM Win32_NetworkAdapter WHERE PNPDeviceID LIKE ";
	//AdapterQuery = "SELECT * FROM Win32_NetworkAdapter";
								
	//Add all model names
	for(std::vector<DEVICE>::iterator it = _AvailableGPRSDevices.begin(); it != _AvailableGPRSDevices.end(); ++it)
	{
		std::vector<DEVICE>:: iterator next = it;

		AdapterQuery += "\"%";
		AdapterQuery += it->InstalledDeviceID.c_str();
		AdapterQuery += "%\"";
		AdapterQuery += " AND Name LIKE ";
		AdapterQuery += "\"%";
		AdapterQuery += it->InstalledName;
		AdapterQuery += "%\"";

		if(++next != _AvailableGPRSDevices.end())
			AdapterQuery += " OR PNPDeviceID LIKE ";

	}

	//Run the query
	std::string deviceName = _querySystem.runQuery(AdapterQuery);

	//Find which device we have fitted into the system
	for(std::vector<DEVICE>::iterator it = _AvailableGPRSDevices.begin(); it != _AvailableGPRSDevices.end(); ++it)
	{
		if( deviceName.find(it->InstalledName) == 0 )
			{
				installedDevice = *it;
				break;
			}
	}
	
	return installedDevice;




}


DEVICE SystemDevices::getNetworkAdapterFromPnPDevices()
{
	DEVICE installedDevice;
	installedDevice.AdapterType = NETWORK_ADAPTER_TYPE_NONE;

	//Build the query
	std::string PnpModelQuery = "SELECT * FROM Win32_PnPEntity WHERE Name = ";
	//PnpModelQuery = "SELECT * FROM Win32_PnPEntity WHERE Name LIKE \"%Sierra Wireless%\"";
	//PnpModelQuery = "SELECT * FROM Win32_PnPEntity";


	//Add all model names
	for(std::vector<DEVICE>::iterator it = _AvailableGPRSDevices.begin(); it != _AvailableGPRSDevices.end(); ++it)
	{
		std::vector<DEVICE>:: iterator next = it;

		PnpModelQuery += "\"";
		PnpModelQuery += it->Name.c_str();
		PnpModelQuery += "\"";
		PnpModelQuery += " AND DeviceID LIKE ";
		PnpModelQuery += "\"%";
		PnpModelQuery += it->DeviceID;
		PnpModelQuery += "%\"";

		if(++next != _AvailableGPRSDevices.end())
			PnpModelQuery += " OR Name = ";

	}

	//Run the query
	std::string deviceName = _querySystem.runQuery(PnpModelQuery);

	//Find which device we have fitted into the system
	for(std::vector<DEVICE>::iterator it = _AvailableGPRSDevices.begin(); it != _AvailableGPRSDevices.end(); ++it)
	{
		if( deviceName.compare(it->Name) == 0 )
			{
				installedDevice = *it;
				break;
			}
	}
	
	return installedDevice;


}

void SystemDevices::initialiseKnownAdapters()
{
	/*
		NOTE: Have witnessed GUID can change on install of drivers.
		CANNOT use to search once installed.
	*/

	//GOBI3000
	DEVICE devGOBI3000;
	devGOBI3000.Desc = "Gobi3000";
	devGOBI3000.Name  = "MC8355";
	devGOBI3000.CompatibleID = "";
	devGOBI3000.DeviceID = "USB\\\\VID_1199&PID_9011&MI_0";
	devGOBI3000.Manufacturer = "Sierra Wireless";
	devGOBI3000.AdapterType = NETWORK_ADAPTER_TYPE_GPRS;
	devGOBI3000.AdapterModel = NETWORK_ADAPTER_MODEL_MC8355;
	devGOBI3000.GUID = "{6748E5B1-8D7E-47CE-BCB9-F1659D22DBAC}";
	devGOBI3000.InstalledName = "Sierra Wireless Mobile Broadband Network Adapter";
	devGOBI3000.InstalledDeviceID = "";
	
	//MC8790
	DEVICE devMC8790;
	devMC8790.Desc = "MC8790";
	devMC8790.Name  = "MC8790";
	devMC8790.CompatibleID = "USB\\\\Class_ff&SubClass_ff&Prot_ff\", \"USB\\\\Class_ff&SubClass_ff\"", "USB\\\\Class_ff";
	devMC8790.DeviceID = "USB\\\\VID_1199&PID_683C&MI";
	devMC8790.Manufacturer = "Sierra Wireless";
	devMC8790.AdapterType = NETWORK_ADAPTER_TYPE_GPRS;
	devMC8790.AdapterModel = NETWORK_ADAPTER_MODEL_MC8790;
	devMC8790.GUID = "";
	devMC8790.InstalledName = "Sierra Wireless HSPA Network Adapter";
	devMC8790.InstalledDeviceID = "";


	//MC8790V
	DEVICE devMC8790V;
	devMC8790V.Desc = "MC8790V";
	devMC8790V.Name  = "MC8790V";
	devMC8790V.CompatibleID = "USB\\\\Class_ff&SubClass_ff&Prot_ff\", \"USB\\\\Class_ff&SubClass_ff\"", "USB\\\\Class_ff";
	devMC8790V.DeviceID = "USB\\\\VID_1199&PID_683C&MI";
	devMC8790V.Manufacturer = "Sierra Wireless";
	devMC8790V.AdapterType = NETWORK_ADAPTER_TYPE_GPRS;
	devMC8790V.AdapterModel = NETWORK_ADAPTER_MODEL_MC8790V;
	devMC8790V.GUID = "";
	devMC8790V.InstalledName = "Sierra Wireless HSPA Network Adapter";
	devMC8790V.InstalledDeviceID = "SWMUXBUS\\\\SW_NET";

	_AvailableGPRSDevices.push_back(devMC8790);
	_AvailableGPRSDevices.push_back(devMC8790V);
	_AvailableGPRSDevices.push_back(devGOBI3000);

}




