#include <EnetServer.h>
#include <Engine\Game.h>


void InitializeGame()
{
	if (TheController)
	{
		return;
	}

	EnetServer::Initialize();

	IDirect3D9* pDevice;
	g_pIDirect3DDevice9->GetDirect3D(&pDevice);

	TheInputManager = new InputManager;
	TheIInputHook->SetListener(TheInputManager); // Set listener.

	TheGUI = new GUI(); // Initialize the GUI.

	Signal<void(IDirect3DDevice9*)>* onPresent = &g_pIDirect3DDevice9->OnPresent; 
	Signal<void(IDirect3DDevice9*)>* onReset = &g_pIDirect3DDevice9->OnReset;
			
	onPresent->Add(std::bind(&GUI::OnRender, TheGUI, std::placeholders::_1));
	onReset->Add(std::bind(&GUI::OnLostDevice, TheGUI, std::placeholders::_1));

	TheChat = new Chat(TheGUI->getGUI()); // Initialize the chat.
	//currently mouse events don't work
	// TheServerConnect = new ServerConnect(TheGUI->getGUI()); // Initialize the server connect GUI

	TheController = new SkyrimController();
}

void Update()
{
	TheController->Update();
}



