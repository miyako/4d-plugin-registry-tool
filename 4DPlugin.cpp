/* --------------------------------------------------------------------------------
 #
 #	4DPlugin.c
 #	source generated by 4D Plugin Wizard
 #	Project : Registry Tool
 #	author : miyako
 #	11/01/25
 #
 # --------------------------------------------------------------------------------*/


#include "4DPluginAPI.h"
#include "4DPlugin.h"

#if VERSIONWIN
#define TOTALBYTES    8192
#define BYTEINCREMENT 4096
#include <windows.h>
#include <malloc.h>
#include <stdio.h>
#endif

#if VERSIONWIN
HKEY _HKEY(unsigned int constant)
{
	HKEY hkey = HKEY_CLASSES_ROOT;
	
	switch (constant) 
	{
		case 0:
			hkey = HKEY_CLASSES_ROOT;
			break;
		case 1:
			hkey = HKEY_CURRENT_CONFIG;
			break;	
		case 2:
			hkey = HKEY_CURRENT_USER;
			break;	
		case 3:
			hkey = HKEY_LOCAL_MACHINE;
			break;		
		case 4:
			hkey = HKEY_PERFORMANCE_DATA;
			break;	
		case 5:
			hkey = HKEY_USERS;
			break;				
		case 6:
			hkey = HKEY_PERFORMANCE_TEXT;
			break;
		case 7:
			hkey = HKEY_PERFORMANCE_NLSTEXT;
			break;																		
		default:
			break;
	}
	return hkey;
}
#endif

void PluginMain( int32_t selector, PA_PluginParameters params )
{
	switch( selector )
	{
// --- Windows

		case 1 :
			RT_Set_binary_value( params );
			break;

		case 2 :
			RT_Set_long_value( params );
			break;

		case 3 :
			RT_Set_expand_string_value( params );
			break;

		case 4 :
			RT_Set_string_value( params );
			break;

		case 5 :
			RT_Get_string_value( params );
			break;

		case 6 :
			RT_Get_long_value( params );
			break;

		case 7 :
			RT_Get_binary_value( params );
			break;

		case 8 :
			RT_Get_expand_string_value( params );
			break;

	}
}

// ------------------------------------ Windows -----------------------------------


void RT_Set_binary_value( PA_PluginParameters params )
{
	int success = 0;
#if VERSIONWIN
	HKEY hkey = _HKEY(PA_GetLongParameter( params, 1 ));
	HKEY hk = NULL;
	PA_Unistring *key = PA_GetStringParameter( params, 2 );	
	PA_Unistring *name = PA_GetStringParameter( params, 3 );
	PA_Handle h = PA_GetBlobHandleParameter(params, 4);
	
	if (RegOpenKey(hkey, (LPCWSTR)key->fString, &hk)!=ERROR_SUCCESS) RegCreateKey(hkey, (LPCWSTR)key->fString, &hk);
	
	success = RegSetValueEx(hk, (LPCWSTR)name->fString, 0, REG_BINARY, (const BYTE *)PA_LockHandle(h), PA_GetHandleSize(h));
	PA_UnlockHandle(h);
#endif
	PA_ReturnLong( params, success );
}

void RT_Set_long_value( PA_PluginParameters params )
{
	int success = 0;
#if VERSIONWIN
	HKEY hkey = _HKEY(PA_GetLongParameter( params, 1 ));
	HKEY hk = NULL;
	PA_Unistring *key = PA_GetStringParameter( params, 2 );	
	PA_Unistring *name = PA_GetStringParameter( params, 3 );
	DWORD value = (DWORD)PA_GetLongParameter( params, 4 );	
	
	if (RegOpenKey(hkey, (LPCWSTR)key->fString, &hk)!=ERROR_SUCCESS) RegCreateKey(hkey, (LPCWSTR)key->fString, &hk);
	
	success = RegSetValueEx(hk, (LPCWSTR)name->fString, 0, REG_DWORD, (const BYTE *)&value, sizeof(DWORD));
#endif
	PA_ReturnLong( params, success );
}

void RT_Set_expand_string_value( PA_PluginParameters params )
{
	int success = 0;
#if VERSIONWIN
	HKEY hkey = _HKEY(PA_GetLongParameter( params, 1 ));
	HKEY hk = NULL;
	PA_Unistring *key = PA_GetStringParameter( params, 2 );	
	PA_Unistring *name = PA_GetStringParameter( params, 3 );
	PA_Unistring *value = PA_GetStringParameter( params, 4 );	
	
	if (RegOpenKey(hkey, (LPCWSTR)key->fString, &hk)!=ERROR_SUCCESS) RegCreateKey(hkey, (LPCWSTR)key->fString, &hk);
	
	success = RegSetValueEx(hk, (LPCWSTR)name->fString, 0, REG_EXPAND_SZ, (const BYTE *)value->fString, (value->fLength*sizeof(wchar_t))+sizeof(wchar_t));
#endif
	PA_ReturnLong( params, success );
}

void RT_Set_string_value( PA_PluginParameters params )
{
	int success = 0;
#if VERSIONWIN
	HKEY hkey = _HKEY(PA_GetLongParameter( params, 1 ));
	HKEY hk = NULL;
	PA_Unistring *key = PA_GetStringParameter( params, 2 );	
	PA_Unistring *name = PA_GetStringParameter( params, 3 );
	PA_Unistring *value = PA_GetStringParameter( params, 4 );	
	
	if (RegOpenKey(hkey, (LPCWSTR)key->fString, &hk)!=ERROR_SUCCESS) RegCreateKey(hkey, (LPCWSTR)key->fString, &hk);
	
	success = RegSetValueEx(hk, (LPCWSTR)name->fString, 0, REG_SZ, (const BYTE *)value->fString, (value->fLength*sizeof(wchar_t))+sizeof(wchar_t));
#endif
	PA_ReturnLong( params, success );
}

void RT_Get_string_value( PA_PluginParameters params )
{
	int success = 0;
#if VERSIONWIN
	HKEY hkey = _HKEY(PA_GetLongParameter( params, 1 ));
	HKEY hk = NULL;
	PA_Unistring *key = PA_GetStringParameter( params, 2 );	
	PA_Unistring *name = PA_GetStringParameter( params, 3 );
	PA_Unistring *value = PA_GetStringParameter( params, 4 );	
	DWORD type = 0;
	DWORD size = TOTALBYTES;
	DWORD data = TOTALBYTES;
	
	if (RegOpenKey(hkey, (LPCWSTR)key->fString, &hk)==ERROR_SUCCESS)
	{	
		PPERF_DATA_BLOCK PerfData = (PPERF_DATA_BLOCK) malloc(size);
		
		if(PerfData)
		{
			success = RegQueryValueEx(hk, (LPCWSTR)name->fString, 0, &type, (LPBYTE)PerfData, &data);
			
			while(success==ERROR_MORE_DATA)
			{
				size += BYTEINCREMENT;
				PerfData = (PPERF_DATA_BLOCK) realloc( PerfData, size );
				data = size;
				
				success = RegQueryValueEx(hk, (LPCWSTR)name->fString, 0, &type, (LPBYTE)PerfData, &data);
			}						 
			
			if(success==ERROR_SUCCESS)
			{
				if(type==REG_SZ)
				{
					PA_SetUnistring(value, PA_CreateUnistring((PA_Unichar *)PerfData).fString);		
				}
			}		
			free(PerfData);
		}
	}
#endif
	PA_ReturnLong( params, success );
}

void RT_Get_long_value( PA_PluginParameters params )
{
	int success = 0;
#if VERSIONWIN
	HKEY hkey = _HKEY(PA_GetLongParameter( params, 1 ));
	HKEY hk = NULL;
	PA_Unistring *key = PA_GetStringParameter( params, 2 );	
	PA_Unistring *name = PA_GetStringParameter( params, 3 );
	DWORD type = 0;
	DWORD size = TOTALBYTES;
	DWORD data = TOTALBYTES;
	
	if (RegOpenKey(hkey, (LPCWSTR)key->fString, &hk)==ERROR_SUCCESS)
	{	
		PPERF_DATA_BLOCK PerfData = (PPERF_DATA_BLOCK) malloc(size);
		
		if(PerfData)
		{
			success = RegQueryValueEx(hk, (LPCWSTR)name->fString, 0, &type, (LPBYTE)PerfData, &data);
			
			while(success==ERROR_MORE_DATA)
			{
				size += BYTEINCREMENT;
				PerfData = (PPERF_DATA_BLOCK) realloc( PerfData, size );
				data = size;
				
				success = RegQueryValueEx(hk, (LPCWSTR)name->fString, 0, &type, (LPBYTE)PerfData, &data);
			}						 
			
			if(success==ERROR_SUCCESS)
			{
				if(type==REG_DWORD)
				{
					DWORD value = 0;	
					data = sizeof(value);
					success = RegQueryValueEx(hk, (LPCWSTR)name->fString, 0, &type, (LPBYTE)&value, &data);													   
					PA_SetLongParameter(params, 4, value);		
				}
			}		
			free(PerfData);
		}
	}
#endif
	PA_ReturnLong( params, success );
	
}

void RT_Get_binary_value( PA_PluginParameters params )
{
	int success = 0;
#if VERSIONWIN
	HKEY hkey = _HKEY(PA_GetLongParameter( params, 1 ));
	HKEY hk = NULL;
	PA_Unistring *key = PA_GetStringParameter( params, 2 );	
	PA_Unistring *name = PA_GetStringParameter( params, 3 );	
	DWORD type = 0;
	DWORD size = TOTALBYTES;
	DWORD data = TOTALBYTES;
	
	if (RegOpenKey(hkey, (LPCWSTR)key->fString, &hk)==ERROR_SUCCESS)
	{	
		PPERF_DATA_BLOCK PerfData = (PPERF_DATA_BLOCK) malloc(size);
		
		if(PerfData)
		{
			success = RegQueryValueEx(hk, (LPCWSTR)name->fString, 0, &type, (LPBYTE)PerfData, &data);
			
			while(success==ERROR_MORE_DATA)
			{
				size += BYTEINCREMENT;
				PerfData = (PPERF_DATA_BLOCK) realloc( PerfData, size );
				data = size;
				
				success = RegQueryValueEx(hk, (LPCWSTR)name->fString, 0, &type, (LPBYTE)PerfData, &data);
			}						 
			
			if(success==ERROR_SUCCESS)
			{
				if(type==REG_BINARY)
				{
					PA_SetBlobParameter(params, 4, PerfData, data);	
				}
			}		
			free(PerfData);
		}
	}
#endif
	PA_ReturnLong( params, success );
}

void RT_Get_expand_string_value( PA_PluginParameters params )
{
	int success = 0;
#if VERSIONWIN
	HKEY hkey = _HKEY(PA_GetLongParameter( params, 1 ));
	HKEY hk = NULL;
	PA_Unistring *key = PA_GetStringParameter( params, 2 );	
	PA_Unistring *name = PA_GetStringParameter( params, 3 );
	PA_Unistring *value = PA_GetStringParameter( params, 4 );	
	DWORD type = 0;
	DWORD size = TOTALBYTES;
	DWORD data = TOTALBYTES;
	
	if (RegOpenKey(hkey, (LPCWSTR)key->fString, &hk)==ERROR_SUCCESS)
	{	
		PPERF_DATA_BLOCK PerfData = (PPERF_DATA_BLOCK) malloc(size);
		
		if(PerfData)
		{
			success = RegQueryValueEx(hk, (LPCWSTR)name->fString, 0, &type, (LPBYTE)PerfData, &data);
			
			while(success==ERROR_MORE_DATA)
			{
				size += BYTEINCREMENT;
				PerfData = (PPERF_DATA_BLOCK) realloc( PerfData, size );
				data = size;
				
				success = RegQueryValueEx(hk, (LPCWSTR)name->fString, 0, &type, (LPBYTE)PerfData, &data);
			}						 
			
			if(success==ERROR_SUCCESS)
			{
				if(type==REG_EXPAND_SZ)
				{
					PA_SetUnistring(value, PA_CreateUnistring((PA_Unichar *)PerfData).fString);		
				}
			}		
			free(PerfData);
		}
	}
#endif
	PA_ReturnLong( params, success );
}

