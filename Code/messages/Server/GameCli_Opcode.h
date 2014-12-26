/******************************************************************/
/*          This file was generated, do not modify it !!!!        */
/******************************************************************/

#ifndef MSG_GAME_CLI_OPCODE_H
#define MSG_GAME_CLI_OPCODE_H

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

namespace Messages
{    
    enum GameCli_Opcodes
    {
            GameCli_Hello_Opcode = 0x0000 + 0x0001,
            GameCli_Chat_Opcode = 0x0000 + 0x0003,
            GameCli_Position_Opcode = 0x0000 + 0x0005,
            GameCli_PlayerAdd_Opcode = 0x0000 + 0x0006,
            GameCli_PlayerRemove_Opcode = 0x0000 + 0x0007,
    };
}

#endif // MSG_GAME_CLI

