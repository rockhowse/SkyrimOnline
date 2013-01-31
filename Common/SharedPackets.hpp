#pragma once

class ChatMessage : public
	BasicSerializable<std::string, std::string>
{
public:

	ACCESSOR_1(0, Channel);
	ACCESSOR_1(1, TheMessage);
};

class PlayerGOMTransaction
	: public BasicSerializable<
	SwitchedSerializable<uint32_t, 
		SwitchedField<0x0001, std::string>,
		SwitchedField<0x0002,std::vector<uint32_t>>,
		SwitchedField<0x0004,std::vector<float>>,
		SwitchedField<0x0008,std::vector<uint32_t>>,
		SwitchedField<0x0010,uint32_t>,
		SwitchedField<0x0020,uint32_t>,
		SwitchedField<0x0040,uint32_t>,
		SwitchedField<0x0080,BasicArray<3, float>>,
		SwitchedField<0x0100,BasicArray<3, float>>
		>
	>
{
public:

	ACCESSOR_2(0, 0, Name);
	ACCESSOR_2(0, 1, WornForms);
	ACCESSOR_2(0, 2, FaceMorphs);
	ACCESSOR_2(0, 3, FacePresets);
	ACCESSOR_2(0, 4, Race);
	ACCESSOR_2(0, 5, Gender);
	ACCESSOR_2(0, 6, Level);
	ACCESSOR_2(0, 7, Position);
	ACCESSOR_2(0, 8, Rotation);

};