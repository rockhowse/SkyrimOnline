#pragma once

class SkyrimWalker
{
public:

	SkyrimWalker();
	~SkyrimWalker();

	std::string WalkRTTI();
	

protected:

	size_t Find(const std::string& pPattern);
	size_t FindDyncast();

private:

	uint32_t mOffset;
	uint32_t mDataBaseAddr;
	uint32_t mTextBaseAddr;
	std::string mDataContent;
	std::string mTextContent;
};