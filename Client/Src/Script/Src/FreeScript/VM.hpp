#pragma once

class VMClassRegistry
{
public:

	VMClassRegistry();
	virtual ~VMClassRegistry();

	virtual void Unk01();
};

class SkyrimVM
{
public:

	SkyrimVM();
	~SkyrimVM();

	virtual void Unk01();

	char pad[0x100 - 0x4]; // 0x004 
	VMClassRegistry* registry;

	static SkyrimVM* instance;
};