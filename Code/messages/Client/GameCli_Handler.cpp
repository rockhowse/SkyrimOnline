/******************************************************************/
/*          This file was generated, do not modify it !!!!        */
/******************************************************************/

#include "PacketHandler.h"
#include "GameCli_Handler.h"

extern void HandleGameCli_HelloRecv(const Messages::GameCli_HelloRecv& aMsg);

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
        }
    }
}

