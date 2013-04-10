#include "stdafx.h"
#include "Papyrus.hpp"
#include "Plugins.hpp"
#include <Hook/Function.hpp>


typedef long (__thiscall *tVMUpdate)(void* pthis, float a2);
typedef signed int (__thiscall *tInvoke)(void *, VMStack **, int , VMClassRegistry* , int );
typedef void (__cdecl *tsub_C395D0)(VMStack* stack, const char *Src, int a3, char *DstBuf, rsize_t SizeInBytes);
typedef char (__thiscall *tRegister)(VMClassRegistry**, IFunction* func);

tInvoke oInvoke;
tVMUpdate oVMUpdate;
tRegister oRegister;
tsub_C395D0 sub_C395D0 = (tsub_C395D0)0xC395D0;

uint32_t elapsed = 0;

int __fastcall Invoke(THISCALLVOID, VMStack **stack, int a3, VMClassRegistry* registry, int a5)
{
	char buff[0x400] = "Invoke : ";
	char dest[0x400] = {0};
	sub_C395D0(*stack, buff, 2, dest, 0x400);

	file << "Invoke " << (*stack)->state->numArgs << " " << (*stack)->ArgRun02 << " " << a3 << " " << a5 << "\n" << dest << std::endl;
	if((*stack)->state->baseValue)
	{
		file << "VMValue base : " << std::hex << (*stack)->state->baseValue->type << " " << *(uint32_t*)(*stack)->state->baseValue->data.p << std::endl;
	}

	for(uint32_t i = 0; i < 32/*(*stack)->state->numArgs*/; ++i)
	{
		file << "Arg #" << i << " : " << (*stack)->state->stack[i] << std::endl;
	}
	//(*stack)->ArgRun02 = 0; -> prevents game from closing... refcount ?
	return oInvoke(_this, stack, a3, registry, a5);
}

long __fastcall VMUpdate(THISCALLVOID, float a2)
{
	LONG ret = oVMUpdate(_this, a2);

	GetInstance()->Run();

	return ret;
}

char __fastcall Register(THISCALL(VMClassRegistry*), IFunction* f)
{
	file << "Register : " << f->GetClassName()->data << "::" << f->GetName()->data << std::endl;
	return oRegister(_this, f);
}

/*NAKED_JUMP(Invoke);
NAKED_JUMP(VMUpdate);
NAKED_JUMP(Register);*/

void __stdcall InstallPapyrusHook()
{
	/*oVMUpdate = (tVMUpdate)DetourFunction((PBYTE)0x8D40D0, (PBYTE)VMUpdate);
	oInvoke = (tInvoke)DetourFunction((PBYTE)0xC46CB0, (PBYTE)Invoke);
	oRegister = (tRegister)DetourFunction((PBYTE)0xC4D420 ,(PBYTE)Register);*/
}

void __stdcall UninstallPapyrusHook()
{
	//Delete();
}