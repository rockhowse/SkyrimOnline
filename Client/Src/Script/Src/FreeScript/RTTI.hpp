#pragma once

template <class T>
struct FuncWrapper
{
	typedef T* type;
};

//typedef void *(*dyncast_t)(void* obj, uint32_t __idc0, const void* type, const void* target, uint32_t __idc1);

typedef FuncWrapper<void* (void*, uint32_t, const void*, const void*, uint32_t)>::type dyncast_t;
static const dyncast_t dyncast_r  = (dyncast_t)0x00F510AE;

#define rtti_offset(name, offset) static void* freeRTTI_ ## name = (void*)offset

rtti_offset(TESForm,0x0123A000);
rtti_offset(TESNPC,0x0123DA40);
rtti_offset(BGSBipedObjectForm, 0x0123DE10);
rtti_offset(TESRace, 0x0123E1B0);
rtti_offset(ExtraContainerChanges, 0x0123CA64);
rtti_offset(BSExtraData, 0x0123B200);
rtti_offset(TESObjectREFR, 0x0123C0BC);
rtti_offset(Actor, 0x0123DA2C);

#undef  rtti_offset

#define rtti_cast(obj,type,target) (::FreeScript::## target*)dyncast_r((void*)obj, 0, freeRTTI_ ## type, freeRTTI_ ## target, 0)

//#define DYNAMIC_CAST(obj, from, to) ( ## to *) Runtime_DynamicCast((void*)(obj), 0, RTTI_ ## from, RTTI_ ## to, 0)