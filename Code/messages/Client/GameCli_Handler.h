/******************************************************************/
/*          This file was generated, do not modify it !!!!        */
/******************************************************************/

#ifndef MSG_GAME_CLI_HANDLER_H
#define MSG_GAME_CLI_HANDLER_H

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "PacketHandler.h"
#include "Packet.h"
#include <vector>
#include <string>
#include "GameCli_Opcode.h"
#include "CliGame_Opcode.h"


namespace Messages
{
    class GameCli_Handler : public PacketHandler
    {
    public:
    
        void HandleBuffer(ReadBuffer* pBuffer, uint16_t aOpcode, uint16_t aConnectionId);
    };

    class GameCli_HelloRecv : public Packet
    {
    public:
        GameCli_HelloRecv() {}
        ~GameCli_HelloRecv() {}
    
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
    
    class GameCli_ChatRecv : public Packet
    {
    public:
        GameCli_ChatRecv() {}
        ~GameCli_ChatRecv() {}
    
        void Deserialize(ReadBuffer* pBuffer)
        {
            pBuffer->Read_uint16(senderId);
            pBuffer->Read_string(message);
        }
        void Serialize(WriteBuffer* pBuffer)
        {
            pBuffer->Write_uint16(GameCli_Chat_Opcode);
            pBuffer->Write_uint16(senderId);
            pBuffer->Write_string(message);
        }
    
        uint16_t senderId;
        std::string message;
    };
    
    class CliGame_HelloSend : public Packet
    {
    public:
        CliGame_HelloSend() {}
        ~CliGame_HelloSend() {}
    
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
    
    class CliGame_ChatSend : public Packet
    {
    public:
        CliGame_ChatSend() {}
        ~CliGame_ChatSend() {}
    
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
    
}

#endif // MSG_GAME_CLI_HANDLER_H

