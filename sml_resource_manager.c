#include "stdafx.h"


#include "my_interface.h"
#include "sml_resource_manager.h"

void SML_OBJ_FUNC(SML_Resource, Cleanup)(struct SML_Resource * res)
{
	switch (res->m_rcm)
	{
	case SML_RCM_FUNC:
	{
		SML_pfnCleanup func = (SML_pfnCleanup)(res->m_func);
		func(res->m_resource);
	}
	break;

	case SML_RCM_FUNC_STDCALL:
	{
		SML_pfnCleanupWinapi func = (SML_pfnCleanupWinapi)(res->m_func);
		func(res->m_resource);
	}
	break;

	case SML_RCM_FUNC_NO_PARAM:
	{
		SML_pfnCleanupNoParam func = (SML_pfnCleanupNoParam)(res->m_func);
		func();
	}
	break;

	case SML_RCM_OBJECT:
	{
		struct SML_IObject * pObj = (struct SML_IObject *)(res->m_resource);
		SML_CALL_METHOD(Release, pObj);
	}
	break;

	case SML_RCM_HEAP_FREE:
	{
		HeapFree(GetProcessHeap(), 0, res->m_resource);
	}
	break;

	case SML_RCM_VIRTUAL_FREE:
	{
		VirtualFree(res->m_resource, 0, MEM_RELEASE);
	}
	break;

	}

	ZeroMemory(res, sizeof(struct SML_Resource));
}




//void Init();
void SML_OBJ_FUNC(SML_ResourceList, Init)(struct SML_ResourceList * resList)
{
	ZeroMemory(resList, sizeof(struct SML_ResourceList));
	resList->m_list = resList->m_stack;
	resList->m_count = 0;
	resList->m_capacity = SML_INITIAL_RESOURCE_COUNT;
}
//void Add();
void SML_OBJ_FUNC(SML_ResourceList, Add)(struct SML_ResourceList * resList, enum  SML_RESOURCE_CLEANUP_METHOD rcm, void * resource, void * func)
{
	if (resList->m_count >= resList->m_capacity)
	{
		resList->m_capacity += SML_INITIAL_RESOURCE_COUNT;

		if (resList->m_list == resList->m_stack)
		{
			resList->m_list = (struct SML_Resource *)HeapAlloc(
				GetProcessHeap(),//_In_ HANDLE hHeap,
				HEAP_ZERO_MEMORY,//_In_ DWORD  dwFlags,
				resList->m_capacity * sizeof(struct SML_Resource)//,//_In_ SIZE_T dwBytes
				);
			CopyMemory(resList->m_list, resList->m_stack, resList->m_count * sizeof(struct SML_Resource));
			ZeroMemory(resList->m_stack, resList->m_count * sizeof(struct SML_Resource));
		}
		else
		{
			resList->m_list = (struct SML_Resource *)HeapReAlloc(
				GetProcessHeap(),//_In_ HANDLE hHeap,
				HEAP_ZERO_MEMORY,//_In_ DWORD  dwFlags,
				resList->m_list,//_In_ LPVOID lpMem,
				resList->m_capacity * sizeof(struct SML_Resource)//,//_In_ SIZE_T dwBytes
				);
		}
	}

	resList->m_list[resList->m_count].m_rcm = rcm;
	resList->m_list[resList->m_count].m_resource = resource;
	resList->m_list[resList->m_count].m_func = func;

	++resList->m_count;
}
//void Cleanup()
void SML_OBJ_FUNC(SML_ResourceList, Cleanup)(struct SML_ResourceList * resList)
{
	for (LONG ii = resList->m_count - 1; ii >= 0; --ii)
	{
		SML_OBJ_FUNC(SML_Resource, Cleanup)(resList->m_list + ii);
	}

	if (resList->m_list != resList->m_stack)
	{
		HeapFree(GetProcessHeap(), 0, resList->m_list);
	}

	ZeroMemory(resList, sizeof(struct SML_ResourceList));
}