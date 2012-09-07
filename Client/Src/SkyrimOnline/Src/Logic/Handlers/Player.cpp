
#include "stdafx.h"
#include <Logic/Session.h>
#include <Game/data.h>
#include <Overlay/Chat.h>
#include <Overlay/Interface.h>
#include <SkyrimOnline.h>

namespace Skyrim
{
	namespace Logic
	{
		//--------------------------------------------------------------------------------
		void Session::HandleChatMessage(Packet& data)
		{
			try{
				std::string msg;
				data >> msg;
				OnChatMessage(msg);
			}
			catch(std::exception& e)
			{
				System::Log::Error(e.what());
			}
		}
		//--------------------------------------------------------------------------------
		void Session::HandlePlayerSpawn(Packet& data)
		{
			try
			{
				uint32_t race;
				uint32_t level;
				uint32_t gender;
				std::vector<float> faceMorph;
				std::vector<uint32_t> wornForms;
				std::string name;

				data >> race 
					 >> gender 
					 >> level 
					 >> faceMorph 
					 >> wornForms
					 >> name;

				Game::ActorController* player = new Game::ActorController(data.ObjectId, race, gender);
				SkyrimOnline::GetInstance().GetControllerManager().Add(player);
				
				player->GetCharacter()->SetFaceMorph(faceMorph);
				player->GetCharacter()->EquipItems(wornForms);
				player->GetCharacter()->SetName(name);

				OnSpawn();
			}
			catch(std::exception& e)
			{
				System::Log::Error(e.what());
			}
		}
		//--------------------------------------------------------------------------------
		void Session::HandlePlayerMoveAndLook(Packet& data)
		{
			auto player = SkyrimOnline::GetInstance().GetControllerManager().Get(data.ObjectId);
			float px, py, pz, rx, ry, rz;
			uint32_t relapsed;
			data >> px >> py >> pz >> rx >> ry >> rz >> relapsed;

			if(player)
				player->InterpolateTo(px, py, pz, rx, ry, rz, relapsed);
		}
		//--------------------------------------------------------------------------------
		void Session::HandlePlayerRemove(Packet& data)
		{
			try{
				auto player = SkyrimOnline::GetInstance().GetControllerManager().Get(data.ObjectId);
				if(player)
					delete SkyrimOnline::GetInstance().GetControllerManager().Remove(player);
			}
			catch(std::exception& e)
			{
				System::Log::Error(e.what());
			}
		}
		//--------------------------------------------------------------------------------
		void Session::HandleMount(Packet& data)
		{
			try{
				auto remote = SkyrimOnline::GetInstance().GetControllerManager().Get(data.ObjectId);
				if(remote)
				{
					uint32_t mountId;
					data >> mountId;
					remote->SetMount(mountId);
				}
			}
			catch(std::exception& e)
			{
				System::Log::Error(e.what());
			}
		}
		//--------------------------------------------------------------------------------
		void Session::HandleUnmount(Packet& data)
		{
			try{
				auto remote = SkyrimOnline::GetInstance().GetControllerManager().Get(data.ObjectId);
				if(remote)
				{
					remote->SetMount(0);
				}
			}
			catch(std::exception& e)
			{
				System::Log::Error(e.what());
			}
		}
		//--------------------------------------------------------------------------------
	}
}