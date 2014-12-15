#pragma once

namespace Skyrim
{
	template <class T>
	class BaseHelper
	{
	protected:
		T* mData;
	public:

		BaseHelper(T* pData) : mData(pData){}
	};
}