#include "GameServer.h"
#include "easylogging++.h"

void HandleCliGame_ChatRecv(const Messages::CliGame_ChatRecv& aMsg)
{
	LOG(INFO) << "Chat : " << aMsg.connectionId << " " << aMsg.message;

	Messages::GameCli_ChatSend* pMessage = new Messages::GameCli_ChatSend;
	pMessage->senderId = aMsg.connectionId;
	pMessage->message = aMsg.message;

	g_pServer->SendReliable(aMsg.connectionId, pMessage);
}