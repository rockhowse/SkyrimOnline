#pragma once

#include "Types.hpp"

namespace FreeScript
{
	class TESNPC;
	class TESDataHandler
	{
	public:

		static TESDataHandler* GetInstance();

		char pad00to20c[0x20c];
		Vector<TESNPC*>	mNpcs;
	};

	typedef void* (__cdecl* factoryGetter)(uint8_t);

	class FormFactory
	{
	public:
		FormFactory();
		virtual ~FormFactory();

		virtual TESForm* Create() = 0;
		virtual const char*	GetName() = 0;
		virtual uint32_t	GetType() = 0;

		const char* name; // 04

		static FormFactory* GetFactory(uint8_t pType)
		{
			FormFactory** factories = (FormFactory**)0x012E49B0;
			return factories[pType];
		}

		template <class T>
		static T* Clone(T* from)
		{
			FormFactory* factory = GetFactory(from->formType)
			T* result = factory->Create();
			if(result)
			{
				result->Init();
				result->CopyFrom(from);
			}
			return result;
		}
	};
}