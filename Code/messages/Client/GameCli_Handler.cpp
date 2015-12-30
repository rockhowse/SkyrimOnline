// This file was generated, do not modify it !!!!  

#include "PacketHandler.h"
#include "GameCli_Handler.h"


extern void HandleGameCli_HelloRecv(const Messages::GameCli_HelloRecv& aMsg);
extern void HandleGameCli_ChatRecv(const Messages::GameCli_ChatRecv& aMsg);
extern void HandleGameCli_PositionRecv(const Messages::GameCli_PositionRecv& aMsg);
extern void HandleGameCli_PlayerAddRecv(const Messages::GameCli_PlayerAddRecv& aMsg);
extern void HandleGameCli_PlayerRemoveRecv(const Messages::GameCli_PlayerRemoveRecv& aMsg);

namespace Messages
{
	void GameCli_Handler::HandleBuffer(ReadBuffer* pBuffer, uint16_t aOpcode, uint16_t aConnectionId)
	{
		switch(aOpcode)
		{
			case GameCli_Hello_Opcode:
			{
				GameCli_HelloRecv msg;
				msg.connectionId = aConnectionId;
				msg.Deserialize(pBuffer);
				HandleGameCli_HelloRecv(msg);
				break;
			}
			case GameCli_Chat_Opcode:
			{
				GameCli_ChatRecv msg;
				msg.connectionId = aConnectionId;
				msg.Deserialize(pBuffer);
				HandleGameCli_ChatRecv(msg);
				break;
			}
			case GameCli_Position_Opcode:
			{
				GameCli_PositionRecv msg;
				msg.connectionId = aConnectionId;
				msg.Deserialize(pBuffer);
				HandleGameCli_PositionRecv(msg);
				break;
			}
			case GameCli_PlayerAdd_Opcode:
			{
				GameCli_PlayerAddRecv msg;
				msg.connectionId = aConnectionId;
				msg.Deserialize(pBuffer);
				HandleGameCli_PlayerAddRecv(msg);
				break;
			}
			case GameCli_PlayerRemove_Opcode:
			{
				GameCli_PlayerRemoveRecv msg;
				msg.connectionId = aConnectionId;
				msg.Deserialize(pBuffer);
				HandleGameCli_PlayerRemoveRecv(msg);
				break;
			}
		}
	}

}
