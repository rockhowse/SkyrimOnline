#include "stdafx.h"
#include "SkyrimWalker.hpp"

using namespace pe_bliss;


SkyrimWalker::SkyrimWalker()
{
	std::ifstream file("TESV.exe", std::ios::binary);
	if(!file.is_open())
		throw std::runtime_error("Could not locate TESV.exe");

	pe_base image(pe_factory::create_pe(file));
	auto sections = image.get_image_sections();

	uint64_t imageBase = image.get_image_base_64();

	for(auto itor = sections.begin(), end = sections.end(); itor != end; ++itor)
	{
		if((*itor).get_name() == std::string(".data"))
		{
			mDataContent = itor->get_raw_data();
			mDataBaseAddr = itor->get_virtual_address() + imageBase;
		}
		else if((*itor).get_name() == std::string(".text"))
		{
			mTextContent = itor->get_raw_data();
			mTextBaseAddr = itor->get_virtual_address() + imageBase;
		}
	}

	FindDyncast();
}
	

SkyrimWalker::~SkyrimWalker()
{

}

std::string SkyrimWalker::WalkRTTI()
{
	uint32_t pat = *(uint32_t*)&mDataContent[0];
	std::string pattern;
	pattern.append((char*)&pat, 4);

	std::ostringstream os;

	os << std::hex << "static const dyncast_t dyncast_r  = (dyncast_t)0x" << FindDyncast() << ";" << std::endl << std::endl;

	size_t offset = 0;
	size_t rttiValue = Find(pattern);
	size_t symbol = Find(".?AV");
	while(symbol != std::string::npos)
	{
		size_t del = Find("@@");
		if(del > symbol)
		{
			std::string symbolName = mDataContent.substr(symbol + 4, del - symbol - 4);
			if(symbolName[0] != '?' && symbolName.find("@") == std::string::npos)
			{
				os <<  "rtti_offset(" << symbolName << ", 0x" << std::hex << rttiValue + offset + mDataBaseAddr << ");" << std::endl;
			}
		}
		
		offset += del + 3;
		mDataContent.erase(0 , del + 3);

		rttiValue = Find(pattern);
		symbol = Find(".?AV");
	}
	return os.str();
}

size_t SkyrimWalker::Find(const std::string& pPattern)
{
	return mDataContent.find(pPattern);
}

#define XCMP(offset, c) (*(uint8_t*)&mTextContent[i + offset] == c)

size_t SkyrimWalker::FindDyncast()
{
	for(auto i = 0; i < mTextContent.size() - 0xF; ++i)
	{
		if(XCMP(0, 0x6A) && XCMP(1, 0x18) && XCMP(2, 0x68) && XCMP(7, 0xE8)
			&& XCMP(0xC, 0x8B) && XCMP(0xD, 0x75)&& XCMP(0xE, 0x08))
		{
			return i + mTextBaseAddr;
		}
	}
	return -1;
}