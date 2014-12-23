/******************************************************************/
/*          This file was generated, do not modify it !!!!        */
/******************************************************************/

#ifndef MSG_CLI_GAME_HANDLER_H
#define MSG_CLI_GAME_HANDLER_H

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "PacketHandler.h"
#include "Packet.h"
#include <vector>
#include <string>
#include "CliGame_Opcode.h"
#include "GameCli_Opcode.h"


namespace Messages
{
    class CliGame_Handler : public PacketHandler
    {
    public:
    
        void HandleBuffer(ReadBuffer* pBuffer, uint16_t aOpcode, uint16_t aConnectionId);
    };

    class CliGame_HelloRecv : public Packet
    {
    public:
        CliGame_HelloRecv() {}
        ~CliGame_HelloRecv() {}
    
        void Deserialize(ReadBuffer* pBuffer)
        {
            pBuffer->Read_string(name);
        }
        void Serialize(WriteBuffer* pBuffer)
        {
            pBuffer->Write_uint16(CliGame_Hello_Opcode);
            pBuffer->Write_string(name);
        }
    
        std::string name;
    };
    
    class CliGame_ChatRecv : public Packet
    {
    public:
        CliGame_ChatRecv() {}
        ~CliGame_ChatRecv() {}
    
        void Deserialize(ReadBuffer* pBuffer)
        {
            pBuffer->Read_string(message);
        }
        void Serialize(WriteBuffer* pBuffer)
        {
            pBuffer->Write_uint16(CliGame_Chat_Opcode);
            pBuffer->Write_string(message);
        }
    
        std::string message;
    };
    
    class GameCli_HelloSend : public Packet
    {
    public:
        GameCli_HelloSend() {}
        ~GameCli_HelloSend() {}
    
        void Deserialize(ReadBuffer* pBuffer)
        {
            pBuffer->Read_uint16(version);
        }
        void Serialize(WriteBuffer* pBuffer)
        {
            pBuffer->Write_uint16(GameCli_Hello_Opcode);
            pBuffer->Write_uint16(version);
        }
    
        uint16_t version;
    };
    
    class GameCli_ChatSend : public Packet
    {
    public:
        GameCli_ChatSend() {}
        ~GameCli_ChatSend() {}
    
        void Deserialize(ReadBuffer* pBuffer)
        {
            pBuffer->Read_string(message);
        }
        void Serialize(WriteBuffer* pBuffer)
        {
            pBuffer->Write_uint16(GameCli_Chat_Opcode);
            pBuffer->Write_string(message);
        }
    
        std::string message;
    };
    
}

#endif // MSG_CLI_GAME_HANDLER_H

