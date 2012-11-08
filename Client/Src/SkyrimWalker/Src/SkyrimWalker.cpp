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
	section dataSection;

	uint64_t imageBase = image.get_image_base_64();

	for(auto itor = sections.begin(), end = sections.end(); itor != end; ++itor)
	{
		if((*itor).get_name() == std::string(".data"))
		{
			dataSection = *itor;
			break;
		}
	}
	mContent = dataSection.get_raw_data();
	mBaseAddr = dataSection.get_virtual_address() + imageBase;
}

SkyrimWalker::~SkyrimWalker()
{

}

std::string SkyrimWalker::WalkRTTI()
{
	uint32_t pat = *(uint32_t*)&mContent[0];
	std::string pattern;
	pattern.append((char*)&pat, 4);

	std::ostringstream os;

	size_t offset = 0;
	size_t rttiValue = Find(pattern);
	size_t symbol = Find(".?AV");
	while(symbol != std::string::npos)
	{
		size_t del = Find("@@");
		if(del > symbol)
		{
			std::string symbolName = mContent.substr(symbol + 4, del - symbol - 4);
			if(symbolName[0] != '?' && symbolName.find("@") == std::string::npos)
			{
				os <<  "rtti_offset(" << symbolName << ", 0x" << std::hex << rttiValue + offset + mBaseAddr << ");" << std::endl;
			}
		}
		
		offset += del + 3;
		mContent.erase(0 , del + 3);

		rttiValue = Find(pattern);
		symbol = Find(".?AV");
	}
	return os.str();
}

size_t SkyrimWalker::Find(const std::string& pPattern)
{
	return mContent.find(pPattern);
}