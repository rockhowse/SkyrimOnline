#ifndef CORE_ID_GENERATOR_H
#define CORE_ID_GENERATOR_H

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <cstdint>
#include <list>

/*!
 * \class IdGenerator
 *
 * \brief Makes dealing with IDs easier. Thread safe.
 *
 */
class IdGenerator
{
public:
    /**
     * @brief Constructs and IdGenerator.
     *
     * Constructs and IdGenerator.
     *
     * @param aMaxId Maximum id value before looping.
     */
    IdGenerator(uint32_t aMaxId);
    ~IdGenerator();
    
    /**
     * @brief Get an Id.
     *
     * Get an Id, this method ensures that the Id is unique.
     *
     * @return The id.
     */
    uint32_t GetId();


    /**
     * @brief Free an Id.
     *
     * When done using an Id make it available to the Id Generator.
     *
     * @param aId The Id to free.
     */
    void FreeId(uint32_t aId);

private:

    uint32_t m_current;
    uint32_t m_max;
    std::list<uint32_t> m_freeIds;
};

#endif // CORE_ID_GENERATOR_H