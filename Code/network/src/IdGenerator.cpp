#include "IdGenerator.h"

IdGenerator::IdGenerator(uint32_t aMaxId)
	: m_current(0)
	, m_max(aMaxId)
{
}

IdGenerator::~IdGenerator()
{
}

uint32_t IdGenerator::GetId()
{
    if(m_current < m_max)
    {
        return m_current++;
    }

    uint32_t id = m_freeIds.front();
    m_freeIds.pop_front();
    return id;
}

void IdGenerator::FreeId(uint32_t aId)
{
    m_freeIds.push_back(aId);
}