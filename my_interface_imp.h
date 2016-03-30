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

HRESULT SML_OBJ_FUNC_2(MyNameObj, IMyProp, SetName)(struct IMyProp *_this, LPCTSTR name);
LPCTSTR SML_OBJ_FUNC_2(MyNameObj, IMyProp, GetName)(struct IMyProp *_this);

HRESULT SML_OBJ_FUNC_3(MyNameObj, IMyProp, IMyObject, CreateMember)(struct IMyObject * _this);
HRESULT SML_OBJ_FUNC_3(MyNameObj, IMyProp, IMyObject, DestroyMember)(struct IMyObject * _this);
LONG SML_OBJ_FUNC_3(MyNameObj, IMyProp, IMyObject, AddRef)(struct IMyObject * _this);
LONG SML_OBJ_FUNC_3(MyNameObj, IMyProp, IMyObject, Release)(struct IMyObject * _this);
void * SML_OBJ_FUNC_3(MyNameObj, IMyProp, IMyObject, QueryInterface)(struct IMyObject * _this, LPCSTR name);


//struct IMyMethod
//{

//HRESULT SML_OBJ_FUNC_3(MyNameObj, IMyMethod, IMyObject, CreateMember)(struct IMyObject * _this);
HRESULT SML_OBJ_FUNC_3(MyNameObj, IMyMethod, IMyObject, CreateMember)(struct IMyObject * _this);
HRESULT SML_OBJ_FUNC_3(MyNameObj, IMyMethod, IMyObject, DestroyMember)(struct IMyObject * _this);
LONG SML_OBJ_FUNC_3(MyNameObj, IMyMethod, IMyObject, AddRef)(struct IMyObject * _this);
LONG SML_OBJ_FUNC_3(MyNameObj, IMyMethod, IMyObject, Release)(struct IMyObject * _this);
void * SML_OBJ_FUNC_3(MyNameObj, IMyMethod, IMyObject, QueryInterface)(struct IMyObject * _this, LPCSTR name);
//	HRESULT(*SayHi)(struct IMyMethod * _this);
HRESULT SML_OBJ_FUNC_2(MyNameObj, IMyMethod, SayHi)(struct IMyMethod * _this);
//	HRESULT(*SayBye)(struct IMyMethod * _this)
HRESULT SML_OBJ_FUNC_2(MyNameObj, IMyMethod, SayBye)(struct IMyMethod * _this);
//};
