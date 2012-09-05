#pragma once

typedef void *(*dyncast_t)(void* obj, uint32_t __idc0, const void* type, const void* target, uint32_t __idc1);
static const dyncast_t dyncast_r = (dyncast_t)0x00F06C5E;

#define rtti_offset(name, offset) static void* freeRTTI_ ## name = (void*)offset

rtti_offset(TESForm,0x011E3000);
rtti_offset(TESNPC,0x011E6A2C);
rtti_offset(BGSBipedObjectForm, 0x011E6E10);
rtti_offset(TESRace, 0x011E7C70);

#undef  rtti_offset

#define rtti_cast(obj,type,target) (::FreeScript::## target*)dyncast_r((void*)obj, 0, freeRTTI_ ## type, freeRTTI_ ## target, 0)

//#define DYNAMIC_CAST(obj, from, to) ( ## to *) Runtime_DynamicCast((void*)(obj), 0, RTTI_ ## from, RTTI_ ## to, 0)