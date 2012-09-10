#pragma once

#define DECLARE_ENTITY(name, data) static const unsigned int name = 0x##data;

namespace Skyrim
{
	static const unsigned int Version = 6;

	DECLARE_ENTITY(Bear, B70F7)
	DECLARE_ENTITY(DarkElf, 45800)
	DECLARE_ENTITY(DragonBlood, F77F8)
	DECLARE_ENTITY(Dragon, EAFB4)
	DECLARE_ENTITY(DragonElder, F811A)
	DECLARE_ENTITY(DragonForst, 0010FEEC)
	DECLARE_ENTITY(Giant, 936D3)
	DECLARE_ENTITY(Alduin, 8E4F1)
	DECLARE_ENTITY(Mirmulnir, 1CA05)
	DECLARE_ENTITY(Nahagliiv, FE431)
	DECLARE_ENTITY(Odahviing, F6850)
	DECLARE_ENTITY(Paarthurnax, 3C57C)
	DECLARE_ENTITY(Viinturuth, FE432)
	DECLARE_ENTITY(Vuljotnaak, FE430)
	DECLARE_ENTITY(Bandit, 1068FE)
	DECLARE_ENTITY(BanditChief, E1646)
	DECLARE_ENTITY(SabreCat, C96BF)
	DECLARE_ENTITY(Wolf, 753CE)
	DECLARE_ENTITY(Troll, f077a)
}