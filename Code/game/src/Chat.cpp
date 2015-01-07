#include "GameServer.h"
#include "easylogging++.h"
#include "Player.h"

void HandleCliGame_ChatRecv(const Messages::CliGame_ChatRecv& aMsg)
{
	Player* pPlayer = g_pServer->GetPlayer(aMsg.connectionId);
	if (!pPlayer)
	{
		return;
	}

	LOG(INFO) << "event=player_chat connection_id=" << aMsg.connectionId << " name=" << pPlayer->GetName() << " message=\"" << aMsg.message << "\"";

	Messages::GameCli_ChatSend* pMessage = new Messages::GameCli_ChatSend;
	pMessage->senderId = aMsg.connectionId;
	pMessage->message = pPlayer->GetName() + " says: " + aMsg.message;

	if (pMessage->message.length() > 71) // Split chat message to prevent long lines in chat box for user.
	{
		for (int i = 71; i <= pMessage->message.length(); i += 71)
		{
			pMessage->message.insert(i, "\n");
		}
	}

	g_pServer->SendReliableAll(pMessage);
}