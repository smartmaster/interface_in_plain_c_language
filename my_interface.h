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
	SML_INTERFACE_DEFINE(IMyObject); //do not matter where the interface is put
	LPCTSTR(*GetName)(struct IMyProp *_this);
};

struct IMyMethod
{
	HRESULT (*SayHi)(struct IMyMethod * _this);
	SML_INTERFACE_DEFINE(IMyObject); //do not matter where the interface is put
	HRESULT(*SayBye)(struct IMyMethod * _this);
};


INT SML_OBJ_FUNC(MyNameObj, SizeOf)();
struct IMyObject * SML_OBJ_FUNC(MyNameObj, CreateInstanceStack_SAM_AUTO)(VOID * addr, INT size, INT bufferSize);

struct IMyObject * SML_OBJ_FUNC(MyNameObj, CreateInstance_SAM_MALLOC)(INT bufferSize);
struct IMyObject * SML_OBJ_FUNC(MyNameObj, CreateInstance_SAM_HEAP_ALLOC)(INT bufferSize);
struct IMyObject * SML_OBJ_FUNC(MyNameObj, CreateInstance_SAM_VIRTUAL_ALLOC)(INT bufferSize);
struct IMyObject * SML_OBJ_FUNC(MyNameObj, CreateInstance_SAM__MALLOCA)(INT bufferSize);

