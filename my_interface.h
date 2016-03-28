#pragma once


#include <tchar.h>
#include <windows.h>

#include "sml_interface_common.h"


//interface can only contain function pointer or interface 
struct IMyObject
{
	HRESULT(*CreateMember)(struct IMyObject * _this);
	HRESULT(*DestroyMember)(struct IMyObject * _this);
	LONG(*AddRef)(struct IMyObject * _this);
	LONG(*Release)(struct IMyObject * _this);
	void * (*QueryInterface)(struct IMyObject * _this, LPCSTR name);
};


struct IMyProp
{
	HRESULT(*SetName)(struct IMyProp *_this, LPCTSTR name);
	LPCTSTR(*GetName)(struct IMyProp *_this);
	SML_INTERFACE_DEFINE(IMyObject);
};


INT SML_OBJ_FUNC(MyName, SizeOf)();
struct IMyObject * SML_OBJ_FUNC(MyName, CreateInstanceStack_SAM_AUTO)(VOID * addr, INT size, INT bufferSize);

struct IMyObject * SML_OBJ_FUNC(MyName, CreateInstance_SAM_MALLOC)(INT bufferSize);
struct IMyObject * SML_OBJ_FUNC(MyName, CreateInstance_SAM_HEAP_ALLOC)(INT bufferSize);
struct IMyObject * SML_OBJ_FUNC(MyName, CreateInstance_SAM_VIRTUAL_ALLOC)(INT bufferSize);
struct IMyObject * SML_OBJ_FUNC(MyName, CreateInstance_SAM__MALLOCA)(INT bufferSize);

