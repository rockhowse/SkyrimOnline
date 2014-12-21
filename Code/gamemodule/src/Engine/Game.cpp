#include <Engine\Game.h>

namespace GameModule
{ 
	namespace Engine
	{
		GameModule::Engine::Interfaces::IController* iController;

		void Engine::InitializeGame()
		{
			IDirect3D9* pDevice;
			gl_pmyIDirect3DDevice9->GetDirect3D(&pDevice);

			GameModule::Engine::Input::TheInputListener = new GameModule::Engine::Input::UnmanagedInputListener;
			TheIInputHook->SetListener(GameModule::Engine::Input::TheInputListener); // Set listener.

			GameModule::Overlay::TheGUI = new GameModule::Overlay::GUI(); // Initialize the GUI.

			Signal<void(IDirect3DDevice9*)>* onPresent = &gl_pmyIDirect3DDevice9->OnPresent; 
			Signal<void(IDirect3DDevice9*)>* onReset = &gl_pmyIDirect3DDevice9->OnReset;
			
			onPresent->Add(std::bind(&GameModule::Overlay::GUI::OnRender, GameModule::Overlay::TheGUI, std::placeholders::_1));
			onReset->Add(std::bind(&GameModule::Overlay::GUI::OnLostDevice, GameModule::Overlay::TheGUI, std::placeholders::_1));

			GameModule::Overlay::TheChat = new GameModule::Overlay::Chat(GameModule::Overlay::TheGUI->getGUI()); // Initialize the chat.

			if (GameType == 1)
				iController = new GameModule::Engine::Controllers::SkyrimOnlineController();
			else
				iController = new GameModule::Engine::Controllers::OblivionOnlineController();
		}
	}
}


