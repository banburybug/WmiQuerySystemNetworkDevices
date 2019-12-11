
#include <Windows.h>
#include "SystemDevices.h"
#include "Device.h"
#include <iostream>

int main()
{
	SystemDevices systemInfo;
	systemInfo.initialiseKnownAdapters();

	DEVICE networkDevice;
	bool Installed = false;

	//Get adapter;
	networkDevice = systemInfo.getNetworkAdapterFromPnPDevices();

	auto pnpDevices = systemInfo.getAllPnPDeviceNames();
	
	for (auto& i : pnpDevices)
	{
		printf("%s \n", i);
	}

	//Make sure we have a valid adapter
	if(networkDevice.AdapterType == NETWORK_ADAPTER_TYPE_GPRS)
	{
		
		switch(networkDevice.AdapterModel)
		{
			case NETWORK_ADAPTER_MODEL_NONE:
				//Could be already installed
			break;
			case NETWORK_ADAPTER_MODEL_MC8790:
			case NETWORK_ADAPTER_MODEL_MC8790V:
				//Run MC8970/MC8790V Batch file
				system("C:\\Drivers\\NexcomVTC6200\\GPRS\\MC8790_MC8790V\\MC8790_MC8790V.bat");
			break;
			case NETWORK_ADAPTER_MODEL_MC8355:
				//Run MC8355 Batch file
				system("C:\\Drivers\\NexcomVTC6200\\GPRS\\GOBI_3000\\MC8355.bat");
			break;
		}
	}

	networkDevice = systemInfo.getNetworkAdapterFromNetworkAdapter();
	if(networkDevice.AdapterType == NETWORK_ADAPTER_TYPE_GPRS)
	{
		Installed = true;
	}
}