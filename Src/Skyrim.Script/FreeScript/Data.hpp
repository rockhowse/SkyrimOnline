#pragma once

#include "Types.hpp"
#include "Forms.hpp"

#pragma unmanaged

namespace FreeScript
{
	bool GetGlobalSetting(int formIDSetting, float *fSetting);
	bool SetGlobalSetting(int formIDSetting, float fSetting);

	class TESNPC;
	class TESDataHandler
	{
	public:

		static TESDataHandler* GetInstance();

		char pad00to20c[0x20c];
		Vector<TESNPC*>	mNpcs;
	};

	typedef void* (__cdecl* factoryGetter)(uint8_t);

	class IFormFactory
	{
	public:
		IFormFactory();
		virtual ~IFormFactory();

		virtual TESForm* Create() = 0;
		virtual const char*	GetName() = 0;
		virtual uint32_t	GetType() = 0;

		//const char* name; // 04

		static IFormFactory* GetFactory(uint32_t pType)
		{
			IFormFactory** factories = (IFormFactory**)0x12e57b0;
			return factories[pType];
		}

		template <class T>
		static T* Clone(T* from)
		{
			IFormFactory* factory = GetFactory(from->formType);
			T* res = (T*)factory->Create();
			if(res)
			{
				res->Init();
				res->CopyFrom(from);
			}
			return res;
		}
	};
}