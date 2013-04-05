#pragma once

class IFunction
{
	IFunction();
	virtual ~IFunction();

	virtual void Unk01();
	virtual void Unk02();
	virtual void Unk03();
	virtual void Unk04();
	virtual void Unk05();
	virtual void Unk06();
	virtual void Unk07();
	virtual bool IsNative();
	virtual void Unk08();
	virtual void Unk09();
};

class VMClassRegistry
{
public:

	VMClassRegistry();
	virtual ~VMClassRegistry();

	virtual void Unk01();
	virtual void Unk02();
	virtual void Unk03();
	virtual void Unk04();
	virtual void Unk05();
	virtual void Unk06();
	virtual void Unk07();
	virtual void Unk08();
	virtual void Unk09();
	virtual void Unk0A();
	virtual void Unk0B();
	virtual void Unk0C();
	virtual void Unk0D();
	virtual void Unk0E();
	virtual void Unk0F();
	virtual void Unk10();
	virtual void Unk11();
	virtual void Unk12();
	virtual void Unk13();
	virtual void Unk14();
	virtual void Unk15();
	virtual void Unk16();
	virtual void RegisterFunction(void*);

	// void ** vtbl; 04
	char pad04to68[0x68 - 0x04];
	char pad68toB8[0xB8 - 0x68];
	uint32_t registrationMap; // bc
	char padBCtoD0[0xD0 - 0xBC];
	uint32_t handle; // d0
};

class SkyrimVM
{
public:

	SkyrimVM();
	~SkyrimVM();

	virtual void Unk01();

	static SkyrimVM* GetInstance()
	{
		return *instance;
	}

	char pad[0x100 - 0x4]; // 0x004 
	VMClassRegistry* registry;


private:
	static SkyrimVM** instance;
};