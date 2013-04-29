#include "Stdafx.h"
#include "ObscriptCaller.hpp"

typedef bool (*TCallOblivionFunction)(const char* fName, void* thisObj,std::vector<unsigned char>& parameterStack, double* result);
extern TCallOblivionFunction CallOblivionFunction;

union ShortToChar
{
	short s;
	char c[2];
};

ObscriptCaller::ObscriptCaller(const char* pFunction)
	:mFunction(pFunction)
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
		mData.push_back(mData[i]);
	}
}

void ObscriptCaller::Push(const char pC)
{
	PushSize(2);
	mData.push_back(pC);
}

void ObscriptCaller::Push(double pValue)
{
	mData.push_back(122);
	for(int i = 0; i < sizeof(double); ++i)
	{
		mData.push_back(((unsigned char*)&pValue)[i]);
	}
}

void ObscriptCaller::PushSize(short pSize)
{
	ShortToChar s;
	s.s = pSize;

	mData.push_back(s.c[0]);
	mData.push_back(s.c[1]);
}

double ObscriptCaller::operator()(void* pThisObj)
{
	double res = 0.0;
	if(CallOblivionFunction)
		CallOblivionFunction(mFunction, pThisObj, mData, &res);
	else
	{
		MessageBoxA(0,"CallOblivionFunction is NULL", "Error", 0);
	}
	return res;
}

