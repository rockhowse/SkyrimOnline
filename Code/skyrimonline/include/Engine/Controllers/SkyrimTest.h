#pragma once

#include <stdafx.h>

#include <skse/GameReferences.h>
#include <Engine/World.h>


class SkyrimTest
{
public:

	SkyrimTest();
	~SkyrimTest();

	void Update();

private:

	bool m_jumped;
	Actor* m_pActor;
};
