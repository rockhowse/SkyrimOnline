#include <EnetServer.h>
#include <Engine\Game.h>

namespace Logic
{ 
	namespace Engine
	{
		void InitializeGame()
		{
			EnetServer::Initialize();

			IDirect3D9* pDevice;
			g_pIDirect3DDevice9->GetDirect3D(&pDevice);

			Logic::Engine::Input::TheInputManager = new Logic::Engine::Input::InputManager;
			TheIInputHook->SetListener(Logic::Engine::Input::TheInputManager); // Set listener.

			Logic::Overlay::TheGUI = new Logic::Overlay::GUI(); // Initialize the GUI.

			Signal<void(IDirect3DDevice9*)>* onPresent = &g_pIDirect3DDevice9->OnPresent; 
			Signal<void(IDirect3DDevice9*)>* onReset = &g_pIDirect3DDevice9->OnReset;
			
			onPresent->Add(std::bind(&Logic::Overlay::GUI::OnRender, Logic::Overlay::TheGUI, std::placeholders::_1));
			onReset->Add(std::bind(&Logic::Overlay::GUI::OnLostDevice, Logic::Overlay::TheGUI, std::placeholders::_1));

			Logic::Overlay::TheChat = new Logic::Overlay::Chat(Logic::Overlay::TheGUI->getGUI()); // Initialize the chat.

			if (GameType == 1)
				TheController = new Logic::Engine::Controllers::SkyrimController();
			else
				TheController = new Logic::Engine::Controllers::OblivionController();
		}

		void Update()
		{

		}
	}
}


