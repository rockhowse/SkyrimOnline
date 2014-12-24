#pragma once

#include <stdafx.h>

#include <Engine/Interfaces/IController.h>
#include <skse/GameReferences.h>
#include <Engine/World.h>

namespace Logic
{
	namespace Engine
	{
		namespace Controllers
		{
			class SkyrimTest
			{
			public:

				SkyrimTest();
				~SkyrimTest();
				
				void Update();

			private:

				Actor* m_pActor;
			};
		}
	}
}