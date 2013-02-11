#pragma once

class PlayerGOMEntryReplication
	:public BasicSerializable<SwitchedSerializable<uint16_t,
		SwitchedField<1, BasicVector<float> >,
		SwitchedField<1<<1, BasicVector<uint32_t> >,
		SwitchedField<1<<2, uint32_t>,
		SwitchedField<1<<3, uint32_t>,
		SwitchedField<1<<4, BasicArray<3, float>>,
		SwitchedField<1<<5, BasicArray<3, float>>,
		SwitchedField<1<<6, bool>,
		SwitchedField<1<<7, std::string>
	>, uint32_t>
{
public:

	ACCESSOR_2(0, 0, FaceMorph);
	ACCESSOR_2(0, 1, WornForms);
	ACCESSOR_2(0, 2, Level);
	ACCESSOR_2(0, 3, Region);
	ACCESSOR_2(0, 4, Position);
	ACCESSOR_2(0, 5, Rotation);
	ACCESSOR_2(0, 6, Mount);
	ACCESSOR_2(0, 7, Name);
	ACCESSOR_1(1, Test);

};

class WorldState : public
	BasicSerializable<SwitchedSerializable<uint32_t,
		SwitchedField<0x00000001, uint32_t>,
		SwitchedField<0x00000002, BasicArray<4, float>>
	>>
{
public:

	ACCESSOR_2(0, 0, Weather);
	ACCESSOR_2(0, 1, Date);
};