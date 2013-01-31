#pragma once

class ChatMessage : public
	BasicSerializable<std::string, std::string>
{
public:

	ACCESSOR_1(0, Channel);
	ACCESSOR_1(1, TheMessage);
};