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