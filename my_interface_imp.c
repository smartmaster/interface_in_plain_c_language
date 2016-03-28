#include "stdafx.h"

#include <malloc.h>
#include <string.h>
#include <assert.h>
#include "my_interface_imp.h"


static SML_FUNC_TABLE_DEFINE(MyName, IMyProp) =
{
	//struct IMyProp
	//{
	SML_OBJ_FUNC(MyName, SetName),//	HRESULT(*SetName)(struct IMyProp *_this, LPCTSTR name);
	SML_OBJ_FUNC(MyName, GetName),//	LPCTSTR(*GetName)(struct IMyProp *_this);
								  //	struct IMyObject m_IObject; //deliberately put at end
								  //	//struct IMyObject
								  //	//{
	SML_OBJ_FUNC(MyName, CreateMember),//	//	HRESULT(*CreateMember)(struct IMyObject * _this);
	SML_OBJ_FUNC(MyName, DestroyMember),//	//	HRESULT(*DestroyMember)(struct IMyObject * _this);
	SML_OBJ_FUNC(MyName, AddRef),//	//	LONG(*AddRef)(struct IMyObject * _this);
	SML_OBJ_FUNC(MyName, Release),//	//	LONG(*Release)(struct IMyObject * _this);
	SML_OBJ_FUNC(MyName, QueryInterface)
	//	//};
	//};
};

INT SML_OBJ_FUNC(MyName, SizeOf)()
{
	return sizeof(struct MyName);
}

struct IMyObject * SML_OBJ_FUNC(MyName, CreateInstanceStack_SAM_AUTO)(VOID * addr, INT size, INT bufferSize)
{
	if (size < SML_OBJ_FUNC(MyName, SizeOf)())
	{
		return NULL;
	}

	struct MyName * pObj = (struct MyName *)(addr); //allocate memory
	SML_OBJ_FUNC(MyName, InitObj)(pObj, SAM_AUTO, bufferSize); //init fields and interface table. from now on (after obj created and initialized) call interface method only 
	struct IMyObject * pIMyObject = &(pObj->SML_INTERFACE(IMyProp).SML_INTERFACE(IMyObject));
	SML_CALL_METHOD(AddRef, pIMyObject); //do not forget to increment reference count
	return pIMyObject;
}


struct IMyObject * SML_OBJ_FUNC(MyName, CreateInstance_SAM_MALLOC)(int bufferSize)
{
	struct MyName * pObj = SML_ALLOC_OBJ(MyName); //allocate memory
	SML_OBJ_FUNC(MyName, InitObj)(pObj, SAM_MALLOC, bufferSize); //init fields and interface table. from now on (after obj created and initialized) call interface method only 
	struct IMyObject * pIMyObject = &(pObj->SML_INTERFACE(IMyProp).SML_INTERFACE(IMyObject));
	SML_CALL_METHOD(AddRef, pIMyObject); //do not forget to increment reference count
	return pIMyObject;
}


struct IMyObject * SML_OBJ_FUNC(MyName, CreateInstance_SAM_HEAP_ALLOC)(INT bufferSize)
{
	struct MyName * pObj = (struct MyName *)HeapAlloc(GetProcessHeap(), 0, sizeof(struct MyName)); //allocate memory
	SML_OBJ_FUNC(MyName, InitObj)(pObj, SAM_HEAP_ALLOC, bufferSize); //init fields and interface table. from now on (after obj created and initialized) call interface method only 
	struct IMyObject * pIMyObject = &(pObj->SML_INTERFACE(IMyProp).SML_INTERFACE(IMyObject));
	SML_CALL_METHOD(AddRef, pIMyObject); //do not forget to increment reference count
	return pIMyObject;
}
struct IMyObject * SML_OBJ_FUNC(MyName, CreateInstance_SAM_VIRTUAL_ALLOC)(INT bufferSize)
{
	struct MyName * pObj = (struct MyName *)VirtualAlloc(NULL, sizeof(struct MyName), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE); //allocate memory
	SML_OBJ_FUNC(MyName, InitObj)(pObj, SAM_VIRTUAL_ALLOC, bufferSize); //init fields and interface table. from now on (after obj created and initialized) call interface method only 
	struct IMyObject * pIMyObject = &(pObj->SML_INTERFACE(IMyProp).SML_INTERFACE(IMyObject));
	SML_CALL_METHOD(AddRef, pIMyObject); //do not forget to increment reference count
	return pIMyObject;
}
struct IMyObject * SML_OBJ_FUNC(MyName, CreateInstance_SAM__MALLOCA)(INT bufferSize)
{
	struct MyName * pObj = (struct MyName *)_malloca(sizeof(struct MyName)); //allocate memory
	SML_OBJ_FUNC(MyName, InitObj)(pObj, SAM__MALLOCA, bufferSize); //init fields and interface table. from now on (after obj created and initialized) call interface method only 
	struct IMyObject * pIMyObject = &(pObj->SML_INTERFACE(IMyProp).SML_INTERFACE(IMyObject));
	SML_CALL_METHOD(AddRef, pIMyObject); //do not forget to increment reference count
	return pIMyObject;
}

//init interface table
HRESULT SML_OBJ_FUNC(MyName, InitObj)(struct MyName * pObj, enum SML_ALLOC_METHOD allocMethod, INT bufferSize)
{
	ZeroMemory(pObj, sizeof(struct MyName));
	//pObj->m_refCount = 0;
	pObj->m_allocMethod = allocMethod;
	const INT MIN_BUFFER_SIZE = 4 * 1024 / sizeof(TCHAR);
	pObj->m_bufferSize = bufferSize >= MIN_BUFFER_SIZE ? bufferSize : MIN_BUFFER_SIZE; //some resource
																					   //pObj->m_name = NULL; //some resource
	pObj->SML_INTERFACE(IMyProp) = SML_FUNC_TABLE(MyName, IMyProp);
	return S_OK;
}

//struct IMyProp
//{
//	HRESULT(*SetName)(struct IMyProp *_this, LPCTSTR name);
//operation
HRESULT SML_OBJ_FUNC(MyName, SetName)(struct IMyProp * _this, LPCTSTR name)
{
	struct MyName * pObj = SML_GET_OBJECT_1(MyName, IMyProp, _this);
	_tcscpy_s(pObj->m_name, pObj->m_bufferSize, name);
	return S_OK;
}

//	LPCTSTR(*GetName)(struct IMyProp *_this);
//operation
LPCTSTR SML_OBJ_FUNC(MyName, GetName)(struct IMyProp *_this)
{
	struct MyName * pObj = SML_GET_OBJECT_1(MyName, IMyProp, _this);
	return pObj->m_name;
}
//	struct IMyObject m_IObject; //deliberately put at end

//	//	HRESULT(*CreateMember)(struct IMyObject * _this);
//create resources
HRESULT SML_OBJ_FUNC(MyName, CreateMember)(struct IMyObject * _this)
{
	struct MyName * pObj = SML_GET_OBJECT_2(MyName, IMyProp, IMyObject, _this);
	pObj->m_name = (LPTSTR)VirtualAlloc(
		NULL,//_In_opt_ LPVOID lpAddress,
		pObj->m_bufferSize * sizeof(TCHAR),//_In_     SIZE_T dwSize,
		MEM_RESERVE | MEM_COMMIT,//_In_     DWORD  flAllocationType,
		PAGE_READWRITE//,//_In_     DWORD  flProtect
		);; //some resource
	pObj->m_name[0] = 0;
	return S_OK;
}
//	//	HRESULT(*DestroyMember)(struct IMyObject * _this);
//destroy resources
HRESULT SML_OBJ_FUNC(MyName, DestroyMember)(struct IMyObject * _this)
{
	struct MyName * pObj = SML_GET_OBJECT_2(MyName, IMyProp, IMyObject, _this);
	VirtualFree(pObj->m_name, 0, MEM_RELEASE);
	pObj->m_name = NULL;
	return S_OK;
}
//	//	LONG(*AddRef)(struct IMyObject * _this)
//add reference count
LONG SML_OBJ_FUNC(MyName, AddRef)(struct IMyObject * _this)
{
	struct MyName * pObj = SML_GET_OBJECT_2(MyName, IMyProp, IMyObject, _this);
	return InterlockedIncrement(&pObj->m_refCount);
}
//	//	LONG(*Release)(struct IMyObject * _this);
//decrement reference count, destroy resources (again) by calling DestroyMember(...), and free object itself
LONG SML_OBJ_FUNC(MyName, Release)(struct IMyObject * _this)
{
	struct MyName * pObj = SML_GET_OBJECT_2(MyName, IMyProp, IMyObject, _this);
	LONG refCount = InterlockedDecrement(&pObj->m_refCount);
	if (0 == refCount)
	{
		SML_CALL_METHOD(DestroyMember, _this);
		switch (pObj->m_allocMethod)
		{
		case SAM_AUTO:
		{
			//do nothing because i am not the owner of memory
		}
		break;
		case SAM_MALLOC:
			free(pObj);
			break;
		case SAM_HEAP_ALLOC:
			HeapFree(GetProcessHeap(), 0, pObj);
			break;
		case SAM_VIRTUAL_ALLOC:
			VirtualFree(pObj, 0, MEM_RELEASE);
			break;
		case SAM__MALLOCA:
			_freea(pObj);
			break;
		}
	}
	return S_OK;
}

//QueryInterface
//reference count is incremented on successful query
void * SML_OBJ_FUNC(MyName, QueryInterface)(struct IMyObject * _this, LPCSTR name)
{
	struct MyName * pObj = SML_GET_OBJECT_2(MyName, IMyProp, IMyObject, _this);
	void * pinterface = NULL;
	if (0 == strcmp(name, SML_NAME_OF(IMyObject)))
	{
		pinterface = &(pObj->SML_INTERFACE(IMyProp).SML_INTERFACE(IMyObject));
		assert(pinterface == _this);
	}
	else if (0 == strcmp(name, SML_NAME_OF(IMyProp)))
	{
		pinterface = &(pObj->SML_INTERFACE(IMyProp));
	}

	if (NULL != pinterface)
	{
		SML_CALL_METHOD(AddRef, _this);
	}

	return pinterface;
}
//	//};
//};