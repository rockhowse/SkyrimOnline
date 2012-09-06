#pragma once

template <class T>
struct Func
{
	typedef T* type;
};

#define decl(Type, Name) Func<Type>::type Name

typedef uint32_t (*_strFunc)(void*, const char*);


namespace SkyrimScript
{
	/*extern decl(TESForm*	(CActor*),								GetBaseForm);
	extern decl(uint32_t	(CActor*),								GetRace);
	extern decl(void		(TESNPC*,std::vector<float>*),			GetFaceMorph);
	extern decl(const char* (BGSLocation*),							GetLocationString);
	extern decl(uint32_t	(BGSLocation*),							GetLocationId);
	extern decl(void		(TESNPC*,const std::vector<float>*),	SetFaceMorph);
	extern decl(TESForm*	(CActor*,uint32_t),						GetWornForm);
	extern decl(void		(CActor*,const std::string&),			SetName);
	extern decl(TESNPC*		(uint32_t),								NpcListAt);
	extern decl(uint32_t	(),										NpcListCount);
	extern decl(std::string	(TESNPC*),								NpcGetName);
	extern decl(CActor*		(uint32_t),								ActorListAt);
	extern decl(uint32_t	(),										ActorListCount);
	extern decl(TESForm*	(TESForm*,TESForm*),					Duplicate);
	extern decl(void		(CActor*),								QueueNiNodeUpdate);
	extern decl(void		(_strFunc, const char* name, const char* dest),		RegisterPapyrusFunctionString);*/
}

void Imports();
void FreeImports();