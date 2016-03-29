#pragma once

#include <tchar.h>
#include <windows.h>

#define  SML_NAME_OF(x)																# x

#define  SML_OBJ_FUNC(obj, func)													SmartLib_ ## obj ## _ ## func
#define  SML_OBJ_FUNC_2(obj, type2, func)											SmartLib_ ## obj ## _ ## type2 ## _ ## func
#define  SML_OBJ_FUNC_3(obj, type2, type3, func)									SmartLib_ ## obj ## _ ## type2 ## _ ## type3 ## _ ## func
#define  SML_OBJ_FUNC_4(obj, type2, type3, type4, func)								SmartLib_ ## obj ## _ ## type2 ## _ ## type3 ## _ ## type4 ## func
#define  SML_OBJ_FUNC_5(obj, type2, type3, type4, type5, func)						SmartLib_ ## obj ## _ ## type2 ## _ ## type3 ## _ ## type4 ## _ ## type5 ## func
#define  SML_OBJ_FUNC_6(obj, type2, type3, type4, type5, type6, func)				SmartLib_ ## obj ## _ ## type2 ## _ ## type3 ## _ ## type4 ## _ ## type5 ## _ ## type6 ## func
//add more if needed


#define  SML_FUNC_TABLE(type_name, interface_name)									SmartLib_ ## type_name ## _ ## interface_name ## _ ## Table
#define  SML_FUNC_TABLE_DEFINE(type_name, interface_name)							const struct interface_name SML_FUNC_TABLE(type_name, interface_name)

#define  SML_INTERFACE(interface_type)												m_smart_lib_interface_ ## interface_type
#define  SML_INTERFACE_DEFINE(interface_type)										struct interface_type SML_INTERFACE(interface_type)

#define SML_CALL_METHOD(method, interface_ptr, ...)									(interface_ptr) -> method ((interface_ptr), __VA_ARGS__)

#define SML_GET_OBJECT_1(type0, type1, ptr)											(struct type0 *)((CHAR*)(ptr) - (FIELD_OFFSET(struct type0, SML_INTERFACE(type1))))
#define SML_GET_OBJECT_2(type0, type1, type2, ptr)									(struct type0 *)((CHAR*)(ptr) - (FIELD_OFFSET(struct type0, SML_INTERFACE(type1)) + FIELD_OFFSET(struct type1, SML_INTERFACE(type2))))
#define SML_GET_OBJECT_3(type0, type1, type2, type3, ptr)							(struct type0 *)((CHAR*)(ptr) - (FIELD_OFFSET(struct type0, SML_INTERFACE(type1)) + FIELD_OFFSET(struct type1, SML_INTERFACE(type2)) + FIELD_OFFSET(struct type2, SML_INTERFACE(type3))))
#define SML_GET_OBJECT_4(type0, type1, type2, type3, type4, ptr)					(struct type0 *)((CHAR*)(ptr) - (FIELD_OFFSET(struct type0, SML_INTERFACE(type1)) + FIELD_OFFSET(struct type1, SML_INTERFACE(type2)) + FIELD_OFFSET(struct type2, SML_INTERFACE(type3)) + FIELD_OFFSET(struct type3, SML_INTERFACE(type4))))
#define SML_GET_OBJECT_5(type0, type1, type2, type3, type4, type5, ptr)				(struct type0 *)((CHAR*)(ptr) - (FIELD_OFFSET(struct type0, SML_INTERFACE(type1)) + FIELD_OFFSET(struct type1, SML_INTERFACE(type2)) + FIELD_OFFSET(struct type2, SML_INTERFACE(type3)) + FIELD_OFFSET(struct type3, SML_INTERFACE(type4)) + FIELD_OFFSET(struct type4, SML_INTERFACE(type5))))
#define SML_GET_OBJECT_6(type0, type1, type2, type3, type4, type5, type6, ptr)		(struct type0 *)((CHAR*)(ptr) - (FIELD_OFFSET(struct type0, SML_INTERFACE(type1)) + FIELD_OFFSET(struct type1, SML_INTERFACE(type2)) + FIELD_OFFSET(struct type2, SML_INTERFACE(type3)) + FIELD_OFFSET(struct type3, SML_INTERFACE(type4)) + FIELD_OFFSET(struct type4, SML_INTERFACE(type5))+ FIELD_OFFSET(struct type5, SML_INTERFACE(type6))))
//add more if needed

#define  SML_ALLOC_OBJ(obj_type)													(struct obj_type *)malloc(sizeof(struct obj_type))

enum SML_ALLOC_METHOD
{
	SAM_AUTO,
	SAM_MALLOC,
	SAM_HEAP_ALLOC,
	SAM_VIRTUAL_ALLOC,
	SAM__MALLOCA
};

