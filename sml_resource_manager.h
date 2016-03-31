#pragma once

#include <tchar.h>
#include <windows.h>

#include "sml_interface_common.h"

typedef void(*SML_pfnCleanup)(void *);
typedef void(WINAPI *SML_pfnCleanupWinapi)(void *);
typedef void(WINAPI *SML_pfnCleanupNoParam)();

enum SML_RESOURCE_CLEANUP_METHOD
{
	SML_RCM_NULL = 0,
	SML_RCM_FUNC,
	SML_RCM_FUNC_STDCALL,
	SML_RCM_FUNC_NO_PARAM,
	SML_RCM_OBJECT,
	SML_RCM_HEAP_FREE,
	SML_RCM_VIRTUAL_FREE,
};

struct SML_Resource
{
	enum  SML_RESOURCE_CLEANUP_METHOD m_rcm;
	void * m_resource;
	void * m_func;
};

void SML_OBJ_FUNC(SML_Resource, Cleanup)(struct SML_Resource * res);

#define SML_INITIAL_RESOURCE_COUNT 8

struct SML_ResourceList
{
	struct SML_Resource * m_list;
	struct SML_Resource m_stack[SML_INITIAL_RESOURCE_COUNT];
	LONG m_count;
	LONG m_capacity;
};

void SML_OBJ_FUNC(SML_ResourceList, Init)(struct SML_ResourceList * resList);
void SML_OBJ_FUNC(SML_ResourceList, Add)(struct SML_ResourceList * resList, enum  SML_RESOURCE_CLEANUP_METHOD rcm, void * resource, void * func);
void SML_OBJ_FUNC(SML_ResourceList, Cleanup)(struct SML_ResourceList * resList);

#define  SML_RESOURCE_INIT 	\
struct SML_ResourceList sml_resourcelist; \
SML_OBJ_FUNC(SML_ResourceList, Init)(&sml_resourcelist);

#define  SML_RESOURCE_ADD(rcm, resource, func) \
SML_OBJ_FUNC(SML_ResourceList, Add)(&sml_resourcelist, rcm, (void*)(resource), (void*)(func))

#define SML_RESOURCE_CLEANUP \
SML_OBJ_FUNC(SML_ResourceList, Cleanup)(&sml_resourcelist)