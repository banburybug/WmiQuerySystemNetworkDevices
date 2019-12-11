
#include "WMIQuerySys.h"
#include "stdio.h"
#include "wbemidl.h"
#include "comdef.h"



# pragma comment(lib, "wbemuuid.lib")

std::string WMIQuerySys::runQuery(const std::string &query)
{
	std::string strDeviceName = "";

	// Step 1: ---Initialize COM---.
	if (SUCCEEDED(CoInitializeEx(0, COINIT_MULTITHREADED)))
	{     
    // Step 3: ------ Obtain the initial locator to WMI --------
    	IWbemLocator *pLoc = NULL;
    	if (SUCCEEDED(CoCreateInstance(CLSID_WbemLocator, 0, CLSCTX_INPROC_SERVER, IID_IWbemLocator, (LPVOID *) &pLoc)))
    	{
    	// Step 4: ----- Connect to WMI through the IWbemLocator::ConnectServer method
    		IWbemServices *pSvc = NULL;
    		// Connect to the root\cimv2 namespace with the current user and obtain pointer pSvc to make IWbemServices calls.
    		// Object path of WMI namespace// User name. NULL = current user// User password. NULL = current// Locale. NULL indicates current// Security flags.// Authority (e.g. Kerberos)// Context object // pointer to IWbemServices proxy
    		if (SUCCEEDED(pLoc->ConnectServer(_bstr_t(L"ROOT\\CIMV2"), NULL, NULL, 0, NULL, 0, 0, &pSvc)))
    		{
    		// Step 5: ---- Set security levels on the proxy ------
    		// Indicates the proxy to set // RPC_C_AUTHN_xxx// RPC_C_AUTHZ_xxx// Server principal name // RPC_C_AUTHN_LEVEL_xxx// RPC_C_IMP_LEVEL_xxx// client identity// proxy capabilities
    			if(SUCCEEDED(CoSetProxyBlanket(pSvc,	RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, NULL, RPC_C_AUTHN_LEVEL_CALL, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE)))
    			{
    			// Step 6: ---/ Use the IWbemServices pointer to make requests of WMI ----
    			// For example, get the name of the operating system
    				IEnumWbemClassObject* pEnumerator = NULL;                                                  
    				// If an argument is not passed by default the query will selct all PnP devices.
    				// 0 = Device is working properly
    				//if(SUCCEEDED(pSvc->ExecQuery(bstr_t("WQL"), bstr_t("SELECT * FROM Win32_PnPEntity WHERE ConfigManagerErrorCode IS NOT 0"), WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, NULL, &pEnumerator)))
					//if(SUCCEEDED(pSvc->ExecQuery(bstr_t("WQL"), bstr_t("SELECT * FROM Win32_POTSModem WHERE ConfigManagerErrorCode IS 0"), WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, NULL, &pEnumerator)))
					//if(SUCCEEDED(pSvc->ExecQuery(bstr_t("WQL"), bstr_t("SELECT * FROM Win32_POTSModem"), WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, NULL, &pEnumerator)))
    				//if(SUCCEEDED(pSvc->ExecQuery(bstr_t("WQL"), bstr_t("SELECT * FROM "+Win32Class+" WHERE Name LIKE '" +DeviceName+"%'"), WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, NULL, &pEnumerator)))
					//if(SUCCEEDED(pSvc->ExecQuery(bstr_t("WQL"), bstr_t("SELECT * FROM Win32_PnPEntity"), WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, NULL, &pEnumerator)))
					//if(SUCCEEDED(pSvc->ExecQuery(bstr_t("WQL"), bstr_t("SELECT * FROM Win32_PnPEntity  WHERE ConfigManagerErrorCode = 28"), WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, NULL, &pEnumerator)))
					//if(SUCCEEDED(pSvc->ExecQuery(bstr_t("WQL"), bstr_t("SELECT * FROM Win32_PnPEntity  WHERE ConfigManagerErrorCode <> 0"), WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, NULL, &pEnumerator)))
					//if(SUCCEEDED(pSvc->ExecQuery(bstr_t("WQL"), bstr_t("SELECT * FROM Win32_PnPEntity WHERE Name = ") + "\"" + devGOBI3000.Name.c_str() + "\"", WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, NULL, &pEnumerator)))
					//if(SUCCEEDED(pSvc->ExecQuery(bstr_t("WQL"), bstr_t("SELECT * FROM Win32_SystemDriver"), WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, NULL, &pEnumerator)))
					//if(SUCCEEDED(pSvc->ExecQuery(bstr_t("WQL"), bstr_t("SELECT * FROM Win32_NetworkAdapter WHERE GUID = ") + "\"" + devGOBI3000.GUID.c_str() + "\"", WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, NULL, &pEnumerator)))
					//if(SUCCEEDED(pSvc->ExecQuery(bstr_t("WQL"), bstr_t("SELECT * FROM Win32_NetworkAdapter "), WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, NULL, &pEnumerator)))
					//if(SUCCEEDED(pSvc->ExecQuery(bstr_t("WQL"), bstr_t("SELECT * FROM Win32_PnPEntity WHERE ClassGuid = ") + "\"" + devGOBI3000.GUID.c_str() + "\"", WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, NULL, &pEnumerator)))
					if(SUCCEEDED(pSvc->ExecQuery(bstr_t("WQL"), bstr_t(query.c_str()), WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, NULL, &pEnumerator)))
    				{
    				// Step 7: ---Get the data from the query in step 6 -----
    					IWbemClassObject *pclsObj;
    					ULONG uReturn = 0;
						std::string TotalObjTxt = "";

    					while (pEnumerator)
    					{
    						HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);
    
    						if(0 == uReturn)
    						{
    							break;
    						}

							#ifdef _DEBUG

								BSTR bstrObjTxt = SysAllocString(L"ObjectXmlText");;
								pclsObj->GetObjectText(0, &bstrObjTxt);

								//Got obj as xml txt, as we may need it
								std::string strObjTxt = _bstr_t(SysAllocString(bstrObjTxt));
								TotalObjTxt += strObjTxt;
								TotalObjTxt += "\n\n";
								SysFreeString(bstrObjTxt);
							#endif

							VARIANT v;
							BSTR strNameProp = SysAllocString(L"Name");
							BSTR strGUIDProp = SysAllocString(L"GUID");

							hr = pclsObj->Get(strNameProp, 0, &v, 0, 0);
							SysFreeString(strNameProp);

							// check the HRESULT to see if the action succeeded.
							if (SUCCEEDED(hr) && (V_VT(&v) == VT_BSTR))
							{
								#ifdef _DEBUG
									printf("%s%s\n\n", "bstrObjTxt		  : ", strObjTxt.c_str());
									
								#endif
								strDeviceName = _bstr_t(V_BSTR(&v));


								//printf("%s%s\n", "Name: ", strDeviceName.c_str());

								pclsObj->Get(strGUIDProp, 0, &v, 0, 0);
								std::string strGUID = _bstr_t(V_BSTR(&v));
								//printf("%s%s\n", "GUID: ", strGUID.c_str());
								SysFreeString(strGUIDProp);
							}
							else
							{
								wprintf(L"Error in getting specified object\n");
							}

							VariantClear(&v);
    						pclsObj->Release();
    					}
    				}
    				pEnumerator->Release();
    			}
    		}
    		pSvc->Release();
    	}
    	pLoc->Release();
    	CoUninitialize();
    }
	return strDeviceName;
}


std::vector<std::string> WMIQuerySys::getDeviceNames(const std::string& query)
{
	std::vector<std::string> deviceNames;

	// Step 1: ---Initialize COM---.
	if (SUCCEEDED(CoInitializeEx(0, COINIT_MULTITHREADED)))
	{
		// Step 3: ------ Obtain the initial locator to WMI --------
		IWbemLocator* pLoc = NULL;
		if (SUCCEEDED(CoCreateInstance(CLSID_WbemLocator, 0, CLSCTX_INPROC_SERVER, IID_IWbemLocator, (LPVOID*)&pLoc)))
		{
			// Step 4: ----- Connect to WMI through the IWbemLocator::ConnectServer method
			IWbemServices* pSvc = NULL;
			// Connect to the root\cimv2 namespace with the current user and obtain pointer pSvc to make IWbemServices calls.
			// Object path of WMI namespace// User name. NULL = current user// User password. NULL = current// Locale. NULL indicates current// Security flags.// Authority (e.g. Kerberos)// Context object // pointer to IWbemServices proxy
			if (SUCCEEDED(pLoc->ConnectServer(_bstr_t(L"ROOT\\CIMV2"), NULL, NULL, 0, NULL, 0, 0, &pSvc)))
			{
				// Step 5: ---- Set security levels on the proxy ------
				// Indicates the proxy to set // RPC_C_AUTHN_xxx// RPC_C_AUTHZ_xxx// Server principal name // RPC_C_AUTHN_LEVEL_xxx// RPC_C_IMP_LEVEL_xxx// client identity// proxy capabilities
				if (SUCCEEDED(CoSetProxyBlanket(pSvc, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, NULL, RPC_C_AUTHN_LEVEL_CALL, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE)))
				{
					// Step 6: ---/ Use the IWbemServices pointer to make requests of WMI ----
					// For example, get the name of the operating system
					IEnumWbemClassObject* pEnumerator = NULL;
					// If an argument is not passed by default the query will selct all PnP devices.
					// 0 = Device is working properly
					//if(SUCCEEDED(pSvc->ExecQuery(bstr_t("WQL"), bstr_t("SELECT * FROM Win32_PnPEntity WHERE ConfigManagerErrorCode IS NOT 0"), WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, NULL, &pEnumerator)))
					//if(SUCCEEDED(pSvc->ExecQuery(bstr_t("WQL"), bstr_t("SELECT * FROM Win32_POTSModem WHERE ConfigManagerErrorCode IS 0"), WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, NULL, &pEnumerator)))
					//if(SUCCEEDED(pSvc->ExecQuery(bstr_t("WQL"), bstr_t("SELECT * FROM Win32_POTSModem"), WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, NULL, &pEnumerator)))
					//if(SUCCEEDED(pSvc->ExecQuery(bstr_t("WQL"), bstr_t("SELECT * FROM "+Win32Class+" WHERE Name LIKE '" +DeviceName+"%'"), WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, NULL, &pEnumerator)))
					//if(SUCCEEDED(pSvc->ExecQuery(bstr_t("WQL"), bstr_t("SELECT * FROM Win32_PnPEntity"), WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, NULL, &pEnumerator)))
					//if(SUCCEEDED(pSvc->ExecQuery(bstr_t("WQL"), bstr_t("SELECT * FROM Win32_PnPEntity  WHERE ConfigManagerErrorCode = 28"), WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, NULL, &pEnumerator)))
					//if(SUCCEEDED(pSvc->ExecQuery(bstr_t("WQL"), bstr_t("SELECT * FROM Win32_PnPEntity  WHERE ConfigManagerErrorCode <> 0"), WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, NULL, &pEnumerator)))
					//if(SUCCEEDED(pSvc->ExecQuery(bstr_t("WQL"), bstr_t("SELECT * FROM Win32_PnPEntity WHERE Name = ") + "\"" + devGOBI3000.Name.c_str() + "\"", WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, NULL, &pEnumerator)))
					//if(SUCCEEDED(pSvc->ExecQuery(bstr_t("WQL"), bstr_t("SELECT * FROM Win32_SystemDriver"), WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, NULL, &pEnumerator)))
					//if(SUCCEEDED(pSvc->ExecQuery(bstr_t("WQL"), bstr_t("SELECT * FROM Win32_NetworkAdapter WHERE GUID = ") + "\"" + devGOBI3000.GUID.c_str() + "\"", WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, NULL, &pEnumerator)))
					//if(SUCCEEDED(pSvc->ExecQuery(bstr_t("WQL"), bstr_t("SELECT * FROM Win32_NetworkAdapter "), WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, NULL, &pEnumerator)))
					//if(SUCCEEDED(pSvc->ExecQuery(bstr_t("WQL"), bstr_t("SELECT * FROM Win32_PnPEntity WHERE ClassGuid = ") + "\"" + devGOBI3000.GUID.c_str() + "\"", WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, NULL, &pEnumerator)))
					if (SUCCEEDED(pSvc->ExecQuery(bstr_t("WQL"), bstr_t(query.c_str()), WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, NULL, &pEnumerator)))
					{
						// Step 7: ---Get the data from the query in step 6 -----
						IWbemClassObject* pclsObj;
						ULONG uReturn = 0;
						std::string TotalObjTxt = "";

						while (pEnumerator)
						{
							HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);

							if (0 == uReturn)
							{
								break;
							}

#ifdef _DEBUG

							BSTR bstrObjTxt = SysAllocString(L"ObjectXmlText");;
							pclsObj->GetObjectText(0, &bstrObjTxt);

							//Got obj as xml txt, as we may need it
							std::string strObjTxt = _bstr_t(SysAllocString(bstrObjTxt));
							TotalObjTxt += strObjTxt;
							TotalObjTxt += "\n\n";
							SysFreeString(bstrObjTxt);
#endif

							VARIANT v;
							BSTR strNameProp = SysAllocString(L"Name");
							BSTR strGUIDProp = SysAllocString(L"GUID");

							hr = pclsObj->Get(strNameProp, 0, &v, 0, 0);
							SysFreeString(strNameProp);

							// check the HRESULT to see if the action succeeded.
							if (SUCCEEDED(hr) && (V_VT(&v) == VT_BSTR))
							{
#ifdef _DEBUG
								printf("%s%s\n\n", "bstrObjTxt		  : ", strObjTxt.c_str());

#endif
								std::string tmp = _bstr_t(V_BSTR(&v));
								deviceNames.push_back(tmp);


								//printf("%s%s\n", "Name: ", strDeviceName.c_str());

								pclsObj->Get(strGUIDProp, 0, &v, 0, 0);
								std::string strGUID = _bstr_t(V_BSTR(&v));
								//printf("%s%s\n", "GUID: ", strGUID.c_str());
								SysFreeString(strGUIDProp);
							}
							else
							{
								wprintf(L"Error in getting specified object\n");
							}

							VariantClear(&v);
							pclsObj->Release();
						}
					}
					pEnumerator->Release();
				}
			}
			pSvc->Release();
		}
		pLoc->Release();
		CoUninitialize();
	}
	return deviceNames;
}