#include "Buffer.h"
#include <fstream>
#include <cstring>
#include <cstdlib>

ReadBuffer::ReadBuffer(const uint8_t* acpData, uint32_t aSize)
	: m_position(0)
{
	m_buffer.append((char*)acpData, aSize);
}

ReadBuffer::ReadBuffer(const WriteBuffer& aBuffer)
	: m_position(0)
{
	m_buffer.append((char*)aBuffer.GetBuffer(), aBuffer.Size());
}

uint32_t ReadBuffer::Size() const
{
    return (uint32_t)m_buffer.size();
}

uint32_t ReadBuffer::Read_char(char& aNumber)
{
	return ReadRaw((uint8_t*)&aNumber, 1);
}

uint32_t ReadBuffer::Read_uint8(uint8_t& aNumber)
{
	return ReadRaw((uint8_t*)&aNumber, 1);
}

uint32_t ReadBuffer::Read_int16(int16_t& aNumber)
{
	return ReadRaw((uint8_t*)&aNumber, 2);
}

uint32_t ReadBuffer::Read_uint16(uint16_t& aNumber)
{
    return ReadRaw((uint8_t*)&aNumber, 2);
}

uint32_t ReadBuffer::Read_int32(int32_t& aNumber)
{
	return ReadRaw((uint8_t*)&aNumber, 4);
}

uint32_t ReadBuffer::Read_uint32(uint32_t& aNumber)
{
	return ReadRaw((uint8_t*)&aNumber, 4);
}

uint32_t ReadBuffer::Read_int64(int64_t& aNumber)
{
	return ReadRaw((uint8_t*)&aNumber, 8);
}

uint32_t ReadBuffer::Read_uint64(uint64_t& aNumber)
{
	return ReadRaw((uint8_t*)&aNumber, 8);
}


uint32_t ReadBuffer::Read_string(std::string& aString)
{
    uint16_t len = 0;
	Read_uint16(len);
    aString.resize(len);
    ReadRaw((uint8_t*)&aString[0], (uint32_t)len);

    return len + 2;
}

uint32_t ReadBuffer::Read_float(float& aNumber)
{
	return ReadRaw((uint8_t*)&aNumber, 4);
}

uint32_t ReadBuffer::Read_double(double& aNumber)
{
	return ReadRaw((uint8_t*)&aNumber, 8);
}

uint32_t ReadBuffer::ReadRaw(uint8_t* apData, uint32_t aLength)
{
	if (Size() - m_position < aLength)
		return 0;

	memcpy(apData, &m_buffer[m_position], aLength);

	m_position += aLength;

	return aLength;
}

WriteBuffer::WriteBuffer(uint32_t aSize)
{
	if (aSize == 0)
		aSize = 64;

	m_buffer.reserve(aSize);
}

WriteBuffer::WriteBuffer(const uint8_t* acpData, uint32_t aSize)
{
	WriteRaw(acpData, aSize);
}

uint32_t WriteBuffer::Size() const
{
    return (uint32_t)m_buffer.size();
}

const uint8_t* WriteBuffer::GetBuffer() const
{
    return (const uint8_t*)&m_buffer[0];
}

uint32_t WriteBuffer::Write_char(char aNumber)
{
	return WriteRaw((const uint8_t*)&aNumber, 1);
}

uint32_t WriteBuffer::Write_uint8(uint8_t aNumber)
{
	return WriteRaw((const uint8_t*)&aNumber, 1);
}

uint32_t WriteBuffer::Write_int16(int16_t aNumber)
{
	return WriteRaw((const uint8_t*)&aNumber, 2);
}

uint32_t WriteBuffer::Write_uint16(uint16_t aNumber)
{
	return WriteRaw((const uint8_t*)&aNumber, 2);
}

uint32_t WriteBuffer::Write_int32(int32_t aNumber)
{
	return WriteRaw((const uint8_t*)&aNumber, 4);
}

uint32_t WriteBuffer::Write_uint32(uint32_t aNumber)
{
	return WriteRaw((const uint8_t*)&aNumber, 4);
}

uint32_t WriteBuffer::Write_int64(int64_t aNumber)
{
	return WriteRaw((const uint8_t*)&aNumber, 8);
}

uint32_t WriteBuffer::Write_uint64(uint64_t aNumber)
{
	return WriteRaw((const uint8_t*)&aNumber, 8);
}

uint32_t WriteBuffer::Write_string(const std::string& aString)
{
    Write_uint16((uint16_t)aString.size());
    return 2 + WriteRaw((uint8_t*)&aString[0], (uint32_t)aString.size());
}

uint32_t WriteBuffer::Write_float(float aNumber)
{
	return WriteRaw((const uint8_t*)&aNumber, 4);
}

uint32_t WriteBuffer::Write_double(double aNumber)
{
	return WriteRaw((const uint8_t*)&aNumber, 8);
}

uint32_t WriteBuffer::WriteRaw(const uint8_t* acpData, uint32_t aLength)
{
	m_buffer.append((char*)acpData, aLength);

	return aLength;
}
