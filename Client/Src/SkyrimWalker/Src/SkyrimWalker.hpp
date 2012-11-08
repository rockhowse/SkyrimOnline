#pragma once

class SkyrimWalker
{
public:

	SkyrimWalker();
	~SkyrimWalker();

	std::string WalkRTTI();

protected:

	size_t Find(const std::string& pPattern);

private:

	uint32_t mOffset;
	uint32_t mBaseAddr;
	std::string mContent;
};