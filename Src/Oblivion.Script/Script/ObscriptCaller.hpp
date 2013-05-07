#pragma once

#include <vector>

struct ObscriptCaller
{
	ObscriptCaller(const char* pFunction);

	void Push(const std::string& pStr);
	void Push(const char pC);
	void Push(double pValue);
	void Push(int pValue);
	void Push(short pValue);
	void PushForm(void* form);

	double operator()(void * pThisObj = nullptr);

private:

	void Append(unsigned char byte);

	void PushSize(short pSize);

	std::vector<unsigned char> mData;
	std::vector<void*> mForms;
	const char* mFunction;
	short mCount;
};