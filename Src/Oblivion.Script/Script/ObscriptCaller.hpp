#pragma once

#include <vector>

struct ObscriptCaller
{
	ObscriptCaller(const char* pFunction);

	void Push(const std::string& pStr);
	void Push(const char pC);
	void Push(double pValue);

	double operator()(void * pThisObj = nullptr);

private:

	void PushSize(short pSize);

	std::vector<unsigned char> mData;
	const char* mFunction;
};