#ifndef CORE_BUFFER_H
#define CORE_BUFFER_H

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <cstdint>
#include <string>

class WriteBuffer;

/*!
* \class ReadBuffer
*
* \brief Let's you deserialize data from a binary format.
*
*/
class ReadBuffer
{
public:

    ReadBuffer(const uint8_t* acpData, uint32_t aSize);
    ReadBuffer(const WriteBuffer& aBuffer);

	uint32_t Read_char(char& aNumber);
	uint32_t Read_uint8(uint8_t& aNumber);
	uint32_t Read_int16(int16_t& aNumber);
	uint32_t Read_uint16(uint16_t& aNumber);
	uint32_t Read_int32(int32_t& aNumber);
	uint32_t Read_uint32(uint32_t& aNumber);
	uint32_t Read_int64(int64_t& aNumber);
	uint32_t Read_uint64(uint64_t& aNumber);
	uint32_t Read_string(std::string& aString);
	uint32_t Read_float(float& aNumber);
	uint32_t Read_double(double& aNumber);
    uint32_t ReadRaw(uint8_t* apData, uint32_t aLength);

    uint32_t Size() const;


private:

    std::string m_buffer;
	uint32_t m_position;
};

/*!
* \class WriteBuffer
*
* \brief Let's you serialize data to a binary format.
*
*/
class WriteBuffer
{
public:

    WriteBuffer(uint32_t aSize = 64);
    WriteBuffer(const uint8_t* acpData, uint32_t aSize);

	uint32_t Write_char(char aNumber);
	uint32_t Write_uint8(uint8_t aNumber);
	uint32_t Write_int16(int16_t aNumber);
	uint32_t Write_uint16(uint16_t aNumber);
	uint32_t Write_int32(int32_t aNumber);
	uint32_t Write_uint32(uint32_t aNumber);
	uint32_t Write_int64(int64_t aNumber);
	uint32_t Write_uint64(uint64_t aNumber);
	uint32_t Write_string(const std::string& acString);
	uint32_t Write_float(float aNumber);
	uint32_t Write_double(double aNumber);
	uint32_t WriteRaw(const uint8_t* acpData, uint32_t aLength);

    uint32_t Size() const;
    const uint8_t* GetBuffer() const;

private:

	std::string m_buffer;
};


#endif // CORE_BUFFER_H