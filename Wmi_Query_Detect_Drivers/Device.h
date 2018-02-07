#pragma once
#ifndef DEVICE_H
#define DEVICE_H

enum NETWORK_ADAPTER_TYPES
{
	NETWORK_ADAPTER_TYPE_NONE = 0,
	NETWORK_ADAPTER_TYPE_GPRS
};

enum NETWORK_ADAPTER_MODELS
{
	NETWORK_ADAPTER_MODEL_NONE = 0,
	NETWORK_ADAPTER_MODEL_MC8790,
	NETWORK_ADAPTER_MODEL_MC8790V,
	NETWORK_ADAPTER_MODEL_MC8355
};

struct DEVICE
{
	std::string DeviceID;
	std::string Name;
	std::string CompatibleID;
	std::string Manufacturer;
	std::string Desc;
	std::string GUID;
	std::string InstalledName;
	std::string InstalledDeviceID;
	NETWORK_ADAPTER_TYPES AdapterType;
	NETWORK_ADAPTER_MODELS AdapterModel;
};

#endif