#pragma once

class ClientInitialTransaction
	: public BasicSerializable<
		std::string,
		std::vector<uint32_t>,
		std::vector<float>,
		std::vector<uint32_t>,
		uint32_t,
		uint32_t,
		uint32_t,
		BasicArray<3, float>,
		BasicArray<3, float>
	>
{
public:

	ACCESSOR_1(0, Name);
	ACCESSOR_1(1, WornForms);
	ACCESSOR_1(2, FaceMorphs);
	ACCESSOR_1(3, FacePresets);
	ACCESSOR_1(4, Race);
	ACCESSOR_1(5, Gender);
	ACCESSOR_1(6, Level);
	ACCESSOR_1(7, Position);
	ACCESSOR_1(8, Rotation);

};

class PlayerMoveState: public
	BasicSerializable<
		SwitchedSerializable<uint32_t,
			SwitchedField<0x0001, float>,
			SwitchedField<0x0002, BasicArray<3, float>>,
			SwitchedField<0x0004, float>,
			SwitchedField<0x0008, uint64_t>
			>
		>
{
public:

	ACCESSOR_2(0, 0, Heading);
	ACCESSOR_2(0, 1, Position);
	ACCESSOR_2(0, 2, Speed);
	ACCESSOR_2(0, 3, Time);
};