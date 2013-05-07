#include "Stdafx.h"
#include "ObscriptCaller.hpp"

typedef bool (*TCallOblivionFunction)(const char* fName, void* thisObj,std::vector<unsigned char>& parameterStack, std::vector<void*> forms, short count, double* result);
extern TCallOblivionFunction CallOblivionFunction;

union ShortToChar
{
	short s;
	char c[2];
};

ObscriptCaller::ObscriptCaller(const char* pFunction)
	:mFunction(pFunction), mCount(0)
{

}

void ObscriptCaller::Push(const std::string& pStr)
{
	short len = pStr.length();
	if(len < 0)
		return;

	PushSize(len);

	for(short i = 0; i < len; ++i)
	{
		Append(mData[i]);
	}
}

void ObscriptCaller::Push(const char pC)
{
	++mCount;

	Append(pC);
}

void ObscriptCaller::Push(double pValue)
{
	++mCount;

	mData.push_back(122);
	for(int i = 0; i < sizeof(double); ++i)
	{
		Append(((unsigned char*)&pValue)[i]);
	}
}

void ObscriptCaller::Push(int pValue)
{
	++mCount;

	mData.push_back(110);
	for(int i = 0; i < sizeof(int); ++i)
	{
		Append(((unsigned char*)&pValue)[i]);
	}
}

void ObscriptCaller::Push(short pValue)
{
	++mCount;

	for(int i = 0; i < sizeof(short); ++i)
	{
		Append(((unsigned char*)&pValue)[i]);
	}
}

void ObscriptCaller::PushForm(void* form)
{
	Append((unsigned char)114);
	Append((unsigned char)mForms.size() + 1);

	mForms.push_back(form);
}

void ObscriptCaller::Append(unsigned char byte)
{
	mData.push_back(byte);
}

void ObscriptCaller::PushSize(short pSize)
{
	ShortToChar s;
	s.s = pSize;

	Append(s.c[0]);
	Append(s.c[1]);
}

double ObscriptCaller::operator()(void* pThisObj)
{
	double res = 0.0;
	if(CallOblivionFunction)
		CallOblivionFunction(mFunction, pThisObj, mData, mForms, mCount, &res);
	else
	{
		MessageBoxA(0,"CallOblivionFunction is NULL", "Error", 0);
	}
	return res;
}

