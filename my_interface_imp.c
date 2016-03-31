#include "stdafx.h"

#include <malloc.h>
#include <string.h>
#include <assert.h>
#include "my_interface_imp.h"


static SML_FUNC_TABLE_DEFINE(MyNameObj, IMyProp) =
{
	//struct IMyProp
	//{
	SML_OBJ_FUNC_2(MyNameObj, IMyProp, SetName),//	HRESULT(*SetName)(struct IMyProp *_this, LPCTSTR name);

	{
		SML_OBJ_FUNC_3(MyNameObj, IMyProp, SML_IObject, CreateMember),//	//	HRESULT(*CreateMember)(struct IMyObject * _this);
		SML_OBJ_FUNC_3(MyNameObj, IMyProp, SML_IObject, DestroyMember),//	//	HRESULT(*DestroyMember)(struct IMyObject * _this);
		SML_OBJ_FUNC_3(MyNameObj, IMyProp, SML_IObject, AddRef),//	//	LONG(*AddRef)(struct IMyObject * _this);
		SML_OBJ_FUNC_3(MyNameObj, IMyProp, SML_IObject, Release),//	//	LONG(*Release)(struct IMyObject * _this);
		SML_OBJ_FUNC_3(MyNameObj, IMyProp, SML_IObject, QueryInterface)
	},

	SML_OBJ_FUNC_2(MyNameObj, IMyProp, GetName),//	LPCTSTR(*GetName)(struct IMyProp *_this);
};

static SML_FUNC_TABLE_DEFINE(MyNameObj, IMyMethod) = 
{
	SML_OBJ_FUNC_2(MyNameObj, IMyMethod, SayHi),

	{
		SML_OBJ_FUNC_3(MyNameObj, IMyMethod, SML_IObject, CreateMember),
		SML_OBJ_FUNC_3(MyNameObj, IMyMethod, SML_IObject, DestroyMember),
		SML_OBJ_FUNC_3(MyNameObj, IMyMethod, SML_IObject, AddRef),
		SML_OBJ_FUNC_3(MyNameObj, IMyMethod, SML_IObject, Release),
		SML_OBJ_FUNC_3(MyNameObj, IMyMethod, SML_IObject, QueryInterface)
	},

	SML_OBJ_FUNC_2(MyNameObj, IMyMethod, SayBye)
};

INT SML_OBJ_FUNC(MyNameObj, SizeOf)()
{
	return sizeof(struct MyNameObj);
}

struct SML_IObject * SML_OBJ_FUNC(MyNameObj, CreateInstanceStack_SAM_AUTO)(VOID * addr, INT size, INT bufferSize)
{
	if (size < SML_OBJ_FUNC(MyNameObj, SizeOf)())
	{
		return NULL;
	}

	struct MyNameObj * pObj = (struct MyNameObj *)(addr); //allocate memory
	SML_OBJ_FUNC(MyNameObj, InitObj)(pObj, SAM_AUTO, bufferSize); //init fields and interface table. from now on (after obj created and initialized) call interface method only 
	struct SML_IObject * pIMyObject = &(pObj->SML_INTERFACE(IMyProp).SML_INTERFACE(SML_IObject));
	SML_CALL_METHOD(AddRef, pIMyObject); //do not forget to increment reference count
	return pIMyObject;
}


struct SML_IObject * SML_OBJ_FUNC(MyNameObj, CreateInstance_SAM_MALLOC)(int bufferSize)
{
	struct MyNameObj * pObj = SML_ALLOC_OBJ(MyNameObj); //allocate memory
	SML_OBJ_FUNC(MyNameObj, InitObj)(pObj, SAM_MALLOC, bufferSize); //init fields and interface table. from now on (after obj created and initialized) call interface method only 
	struct SML_IObject * pIMyObject = &(pObj->SML_INTERFACE(IMyProp).SML_INTERFACE(SML_IObject));
	SML_CALL_METHOD(AddRef, pIMyObject); //do not forget to increment reference count
	return pIMyObject;
}


struct SML_IObject * SML_OBJ_FUNC(MyNameObj, CreateInstance_SAM_HEAP_ALLOC)(INT bufferSize)
{
	struct MyNameObj * pObj = (struct MyNameObj *)HeapAlloc(GetProcessHeap(), 0, sizeof(struct MyNameObj)); //allocate memory
	SML_OBJ_FUNC(MyNameObj, InitObj)(pObj, SAM_HEAP_ALLOC, bufferSize); //init fields and interface table. from now on (after obj created and initialized) call interface method only 
	struct SML_IObject * pIMyObject = &(pObj->SML_INTERFACE(IMyProp).SML_INTERFACE(SML_IObject));
	SML_CALL_METHOD(AddRef, pIMyObject); //do not forget to increment reference count
	return pIMyObject;
}
struct SML_IObject * SML_OBJ_FUNC(MyNameObj, CreateInstance_SAM_VIRTUAL_ALLOC)(INT bufferSize)
{
	struct MyNameObj * pObj = (struct MyNameObj *)VirtualAlloc(NULL, sizeof(struct MyNameObj), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE); //allocate memory
	SML_OBJ_FUNC(MyNameObj, InitObj)(pObj, SAM_VIRTUAL_ALLOC, bufferSize); //init fields and interface table. from now on (after obj created and initialized) call interface method only 
	struct SML_IObject * pIMyObject = &(pObj->SML_INTERFACE(IMyProp).SML_INTERFACE(SML_IObject));
	SML_CALL_METHOD(AddRef, pIMyObject); //do not forget to increment reference count
	return pIMyObject;
}
struct SML_IObject * SML_OBJ_FUNC(MyNameObj, CreateInstance_SAM__MALLOCA)(INT bufferSize)
{
	struct MyNameObj * pObj = (struct MyNameObj *)_malloca(sizeof(struct MyNameObj)); //allocate memory
	SML_OBJ_FUNC(MyNameObj, InitObj)(pObj, SAM__MALLOCA, bufferSize); //init fields and interface table. from now on (after obj created and initialized) call interface method only 
	struct SML_IObject * pIMyObject = &(pObj->SML_INTERFACE(IMyProp).SML_INTERFACE(SML_IObject));
	SML_CALL_METHOD(AddRef, pIMyObject); //do not forget to increment reference count
	return pIMyObject;
}

//init interface table
HRESULT SML_OBJ_FUNC(MyNameObj, InitObj)(struct MyNameObj * pObj, enum SML_ALLOC_METHOD allocMethod, INT bufferSize)
{
	ZeroMemory(pObj, sizeof(struct MyNameObj));
	//pObj->m_refCount = 0;
	pObj->m_allocMethod = allocMethod;
	const INT MIN_BUFFER_SIZE = 4 * 1024 / sizeof(TCHAR);
	pObj->m_bufferSize = bufferSize >= MIN_BUFFER_SIZE ? bufferSize : MIN_BUFFER_SIZE; //some resource
																					   //pObj->m_name = NULL; //some resource
	pObj->SML_INTERFACE(IMyProp) = SML_FUNC_TABLE(MyNameObj, IMyProp);
	pObj->SML_INTERFACE(IMyMethod) = SML_FUNC_TABLE(MyNameObj, IMyMethod);
	return S_OK;
}

//struct IMyProp
//{
//	HRESULT(*SetName)(struct IMyProp *_this, LPCTSTR name);
//operation
HRESULT SML_OBJ_FUNC_2(MyNameObj, IMyProp, SetName)(struct IMyProp * _this, LPCTSTR name)
{
	struct MyNameObj * pObj = SML_GET_OBJECT_2(MyNameObj, IMyProp, _this);
	_tcscpy_s(pObj->m_name, pObj->m_bufferSize, name);
	return S_OK;
}

//	LPCTSTR(*GetName)(struct IMyProp *_this);
//operation
LPCTSTR SML_OBJ_FUNC_2(MyNameObj, IMyProp, GetName)(struct IMyProp *_this)
{
	struct MyNameObj * pObj = SML_GET_OBJECT_2(MyNameObj, IMyProp, _this);
	return pObj->m_name;
}
//	struct IMyObject m_IObject; //deliberately put at end

//	//	HRESULT(*CreateMember)(struct IMyObject * _this);
//create resources
HRESULT SML_OBJ_FUNC_3(MyNameObj, IMyProp, SML_IObject, CreateMember)(struct SML_IObject * _this)
{
	struct MyNameObj * pObj = SML_GET_OBJECT_3(MyNameObj, IMyProp, SML_IObject, _this);
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
HRESULT SML_OBJ_FUNC_3(MyNameObj, IMyProp, SML_IObject, DestroyMember)(struct SML_IObject * _this)
{
	struct MyNameObj * pObj = SML_GET_OBJECT_3(MyNameObj, IMyProp, SML_IObject, _this);
	VirtualFree(pObj->m_name, 0, MEM_RELEASE);
	pObj->m_name = NULL;
	return S_OK;
}
//	//	LONG(*AddRef)(struct IMyObject * _this)
//add reference count
LONG SML_OBJ_FUNC_3(MyNameObj, IMyProp, SML_IObject, AddRef)(struct SML_IObject * _this)
{
	struct MyNameObj * pObj = SML_GET_OBJECT_3(MyNameObj, IMyProp, SML_IObject, _this);
	return InterlockedIncrement(&pObj->m_refCount);
}
//	//	LONG(*Release)(struct IMyObject * _this);
//decrement reference count, destroy resources (again) by calling DestroyMember(...), and free object itself
LONG SML_OBJ_FUNC_3(MyNameObj, IMyProp, SML_IObject, Release)(struct SML_IObject * _this)
{
	struct MyNameObj * pObj = SML_GET_OBJECT_3(MyNameObj, IMyProp, SML_IObject, _this);
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
void * SML_OBJ_FUNC_3(MyNameObj, IMyProp, SML_IObject, QueryInterface)(struct SML_IObject * _this, LPCSTR name)
{
	struct MyNameObj * pObj = SML_GET_OBJECT_3(MyNameObj, IMyProp, SML_IObject, _this);
	void * pinterface = NULL;
	if (0 == strcmp(name, SML_NAME_OF(SML_IObject)))
	{
		pinterface = &(pObj->SML_INTERFACE(IMyProp).SML_INTERFACE(SML_IObject));
		assert(pinterface == _this);
	}
	else if (0 == strcmp(name, SML_NAME_OF(IMyProp)))
	{
		pinterface = &(pObj->SML_INTERFACE(IMyProp));
	}
	else if (0 == strcmp(name, SML_NAME_OF(IMyMethod)))
	{
		pinterface = &(pObj->SML_INTERFACE(IMyMethod));
	}

	if (NULL != pinterface)
	{
		SML_CALL_METHOD(AddRef, _this);
	}

	return pinterface;
}


HRESULT SML_OBJ_FUNC_3(MyNameObj, IMyMethod, SML_IObject, CreateMember)(struct SML_IObject * _this)
{
	struct MyNameObj * pOj = SML_GET_OBJECT_3(MyNameObj, IMyMethod, SML_IObject, _this);
	return SML_CALL_METHOD(CreateMember, &pOj->SML_INTERFACE(IMyProp).SML_INTERFACE(SML_IObject));
}
HRESULT SML_OBJ_FUNC_3(MyNameObj, IMyMethod, SML_IObject, DestroyMember)(struct SML_IObject * _this)
{
	struct MyNameObj * pOj = SML_GET_OBJECT_3(MyNameObj, IMyMethod, SML_IObject, _this);
	return SML_CALL_METHOD(DestroyMember, &pOj->SML_INTERFACE(IMyProp).SML_INTERFACE(SML_IObject));
}
LONG SML_OBJ_FUNC_3(MyNameObj, IMyMethod, SML_IObject, AddRef)(struct SML_IObject * _this)
{
	struct MyNameObj * pOj = SML_GET_OBJECT_3(MyNameObj, IMyMethod, SML_IObject, _this);
	return SML_CALL_METHOD(AddRef, &pOj->SML_INTERFACE(IMyProp).SML_INTERFACE(SML_IObject));
}
LONG SML_OBJ_FUNC_3(MyNameObj, IMyMethod, SML_IObject, Release)(struct SML_IObject * _this)
{
	struct MyNameObj * pOj = SML_GET_OBJECT_3(MyNameObj, IMyMethod, SML_IObject, _this);
	return SML_CALL_METHOD(Release, &pOj->SML_INTERFACE(IMyProp).SML_INTERFACE(SML_IObject));
}

void * SML_OBJ_FUNC_3(MyNameObj, IMyMethod, SML_IObject, QueryInterface)(struct SML_IObject * _this, LPCSTR name)
{
	struct MyNameObj * pOj = SML_GET_OBJECT_3(MyNameObj, IMyMethod, SML_IObject, _this);
	return SML_CALL_METHOD(QueryInterface, &pOj->SML_INTERFACE(IMyProp).SML_INTERFACE(SML_IObject), name);
}

HRESULT SML_OBJ_FUNC_2(MyNameObj, IMyMethod, SayHi)(struct IMyMethod * _this)
{
	struct MyNameObj * pOj = SML_GET_OBJECT_2(MyNameObj, IMyMethod, _this);
	_ftprintf_s(stdout, L"Hello, %s" L"\r\n", pOj->m_name);
	return S_OK;
}


HRESULT SML_OBJ_FUNC_2(MyNameObj, IMyMethod, SayBye)(struct IMyMethod * _this)
{
	struct MyNameObj * pOj = SML_GET_OBJECT_2(MyNameObj, IMyMethod, _this);
	_ftprintf_s(stdout, L"Byte bye, %s" L"\r\n", pOj->m_name);
	return S_OK;
}
//	//};
//};