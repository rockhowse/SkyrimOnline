// This file was generated, do not modify it !!!!  

#include "PacketHandler.h"
#include "CliGame_Handler.h"


extern void HandleCliGame_HelloRecv(const Messages::CliGame_HelloRecv& aMsg);
extern void HandleCliGame_ChatRecv(const Messages::CliGame_ChatRecv& aMsg);
extern void HandleCliGame_PositionRecv(const Messages::CliGame_PositionRecv& aMsg);
extern void HandleCliGame_PlayerInitializeRecv(const Messages::CliGame_PlayerInitializeRecv& aMsg);

namespace Messages
{
	void CliGame_Handler::HandleBuffer(ReadBuffer* pBuffer, uint16_t aOpcode, uint16_t aConnectionId)
	{
		switch(aOpcode)
		{
			case CliGame_Hello_Opcode:
			{
				CliGame_HelloRecv msg;
				msg.connectionId = aConnectionId;
				msg.Deserialize(pBuffer);
				HandleCliGame_HelloRecv(msg);
				break;
			}
			case CliGame_Chat_Opcode:
			{
				CliGame_ChatRecv msg;
				msg.connectionId = aConnectionId;
				msg.Deserialize(pBuffer);
				HandleCliGame_ChatRecv(msg);
				break;
			}
			case CliGame_Position_Opcode:
			{
				CliGame_PositionRecv msg;
				msg.connectionId = aConnectionId;
				msg.Deserialize(pBuffer);
				HandleCliGame_PositionRecv(msg);
				break;
			}
			case CliGame_PlayerInitialize_Opcode:
			{
				CliGame_PlayerInitializeRecv msg;
				msg.connectionId = aConnectionId;
				msg.Deserialize(pBuffer);
				HandleCliGame_PlayerInitializeRecv(msg);
				break;
			}
		}
	}

}
