// test_c.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <tchar.h>
#include <windows.h>

#include "my_interface.h"


int _tmain_case0(INT argc, TCHAR ** argv);

int _tmain(INT argc, TCHAR ** argv)
{
	int testCase = 0;
	switch (testCase)
	{
	case 2:
	{

	}
	break;
	case 1:
	{

	}
	break;
	case  0:
	{
		_tmain_case0(argc, argv);
	}
	break;
	}
}




int _tmain_case0(INT argc, TCHAR ** argv)
{
	struct  IMyObject * pIMyObject = NULL; //create instance, ref count  ++

	int allocMehtod = SAM_AUTO;
	switch (allocMehtod)
	{
	case SAM_AUTO:
	{
		INT size = SML_OBJ_FUNC(MyName, SizeOf)();
		VOID * addr = _alloca(size);
		pIMyObject = SML_OBJ_FUNC(MyName, CreateInstanceStack_SAM_AUTO)(addr, size, 1024);
	}
	break;
	case SAM_MALLOC:
	{
		pIMyObject = SML_OBJ_FUNC(MyName, CreateInstance_SAM_MALLOC)(1024);
	}
	break;
	case SAM_HEAP_ALLOC:
	{
		pIMyObject = SML_OBJ_FUNC(MyName, CreateInstance_SAM_HEAP_ALLOC)(1024);
	}
	break;
	case SAM_VIRTUAL_ALLOC:
	{
		pIMyObject = SML_OBJ_FUNC(MyName, CreateInstance_SAM_VIRTUAL_ALLOC)(1024);
	}
	break;
	case SAM__MALLOCA:
	{
		pIMyObject = SML_OBJ_FUNC(MyName, CreateInstance_SAM__MALLOCA)(1024);
	}
	break;
	
	}

	

	struct IMyProp * pIMyProp = SML_CALL_METHOD(QueryInterface, pIMyObject, SML_NAME_OF(IMyProp)); //QueryInterface, ref count ++

	struct IMyObject * pIMyObject1 = SML_CALL_METHOD(QueryInterface, pIMyObject, SML_NAME_OF(IMyObject));//QueryInterface, ref count ++

	SML_CALL_METHOD(Release, pIMyObject); //ref count --
	pIMyObject = NULL;

	SML_CALL_METHOD(Release, pIMyObject1); //ref count --
	pIMyObject1 = NULL;


	SML_CALL_METHOD(CreateMember, &pIMyProp->SML_INTERFACE(IMyObject)); //create resources 

	SML_CALL_METHOD(SetName, pIMyProp, TEXT("Iron Mike Tyson")); //object operation

	WCHAR name[256] = { 0 };
	_tcscpy_s(name, _countof(name), SML_CALL_METHOD(GetName, pIMyProp)); //object operation N...

	SML_CALL_METHOD(DestroyMember, &pIMyProp->SML_INTERFACE(IMyObject)); //destroy resources

	SML_CALL_METHOD(Release, &pIMyProp->SML_INTERFACE(IMyObject)); //ref count --, destroy resources (again) by calling DestroyMember(...) and free object itself

	return 0;
}
