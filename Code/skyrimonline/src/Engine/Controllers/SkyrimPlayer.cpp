#pragma once

#include <stdafx.h>

#include <Engine/Controllers/SkyrimController.h>
#include <skyscript.h>

namespace Logic
{
	namespace Engine
	{
		namespace Controllers
		{
			SkyrimPlayer::SkyrimPlayer()
				: m_pPlayer((Actor*)ScriptDragon::Game::GetPlayer())
			{}

			SkyrimPlayer::~SkyrimPlayer()
			{}

			const std::string SkyrimPlayer::GetName()
			{
				return m_pPlayer->GetName();
			}
		}
	}
}