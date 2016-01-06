#include "GameServer.h"
#include "easylogging++.h"
#include "Player.h"

void HandleCliGame_ChatRecv(const Messages::CliGame_ChatRecv& aMsg)
{
	// Receive chat message
	Player* pPlayer = g_pServer->GetPlayer(aMsg.connectionId);
	if (!pPlayer)
	{
		return;
	}

	LOG(INFO) << "event=player_chat connection_id=" << aMsg.connectionId << " name=" << pPlayer->GetName() << " message=\"" << aMsg.message << "\"";

	Messages::GameCli_ChatSend* pMessage = new Messages::GameCli_ChatSend;
	pMessage->senderId = aMsg.connectionId;
	pMessage->message = pPlayer->GetName() + " says: " + aMsg.message;

	g_pServer->SendReliableAll(pMessage);
}