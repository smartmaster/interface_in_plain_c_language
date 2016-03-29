#pragma once

#include <tchar.h>
#include <windows.h>

#include "my_interface.h"



struct MyNameObj
{
	volatile LONG m_refCount;
	SML_INTERFACE_DEFINE(IMyProp); //do not matter where the interface is put
	INT m_allocMethod;
	SML_INTERFACE_DEFINE(IMyMethod); //do not matter where the interface is put
	INT m_bufferSize;
	LPTSTR m_name; //some resource

};

HRESULT SML_OBJ_FUNC(MyNameObj, InitObj)(struct MyNameObj * pObj, enum SML_ALLOC_METHOD allocMethod, INT bufferSize);

HRESULT SML_OBJ_FUNC(MyNameObj, SetName)(struct IMyProp *_this, LPCTSTR name);
LPCTSTR SML_OBJ_FUNC(MyNameObj, GetName)(struct IMyProp *_this);

HRESULT SML_OBJ_FUNC(MyNameObj, CreateMember)(struct IMyObject * _this);
HRESULT SML_OBJ_FUNC(MyNameObj, DestroyMember)(struct IMyObject * _this);
LONG SML_OBJ_FUNC(MyNameObj, AddRef)(struct IMyObject * _this);
LONG SML_OBJ_FUNC(MyNameObj, Release)(struct IMyObject * _this);
void * SML_OBJ_FUNC(MyNameObj, QueryInterface)(struct IMyObject * _this, LPCSTR name);


//struct IMyMethod
//{

HRESULT SML_OBJ_FUNC_2(MyNameObj, IMyMethod, CreateMember)(struct IMyObject * _this);
HRESULT SML_OBJ_FUNC_2(MyNameObj, IMyMethod, DestroyMember)(struct IMyObject * _this);
LONG SML_OBJ_FUNC_2(MyNameObj, IMyMethod, AddRef)(struct IMyObject * _this);
LONG SML_OBJ_FUNC_2(MyNameObj, IMyMethod, Release)(struct IMyObject * _this);
void * SML_OBJ_FUNC_2(MyNameObj, IMyMethod, QueryInterface)(struct IMyObject * _this, LPCSTR name);
//	HRESULT(*SayHi)(struct IMyMethod * _this);
HRESULT SML_OBJ_FUNC(MyNameObj, SayHi)(struct IMyMethod * _this);
//	HRESULT(*SayBye)(struct IMyMethod * _this)
HRESULT SML_OBJ_FUNC(MyNameObj, SayBye)(struct IMyMethod * _this);
//};
