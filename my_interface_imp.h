#pragma once

#include <tchar.h>
#include <windows.h>

#include "my_interface.h"



struct MyName
{
	volatile LONG m_refCount;
	INT m_allocMethod;
	INT m_bufferSize;
	LPTSTR m_name; //some resource
	SML_INTERFACE_DEFINE(IMyProp);
};

HRESULT SML_OBJ_FUNC(MyName, InitObj)(struct MyName * pObj, enum SML_ALLOC_METHOD allocMethod, INT bufferSize);

HRESULT SML_OBJ_FUNC(MyName, SetName)(struct IMyProp *_this, LPCTSTR name);
LPCTSTR SML_OBJ_FUNC(MyName, GetName)(struct IMyProp *_this);

HRESULT SML_OBJ_FUNC(MyName, CreateMember)(struct IMyObject * _this);
HRESULT SML_OBJ_FUNC(MyName, DestroyMember)(struct IMyObject * _this);
LONG SML_OBJ_FUNC(MyName, AddRef)(struct IMyObject * _this);
LONG SML_OBJ_FUNC(MyName, Release)(struct IMyObject * _this);
void * SML_OBJ_FUNC(MyName, QueryInterface)(struct IMyObject * _this, LPCSTR name);
