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

    class Vector3
    {
    public:
        Vector3() {}
        ~Vector3() {}
    
        void Deserialize(ReadBuffer* pBuffer)
        {
            pBuffer->Read_float(x);
            pBuffer->Read_float(y);
            pBuffer->Read_float(z);
        }
        void Serialize(WriteBuffer* pBuffer)
        {
            pBuffer->Write_float(x);
            pBuffer->Write_float(y);
            pBuffer->Write_float(z);
        }
    
        float x;
        float y;
        float z;
    };
    
    class Movement
    {
    public:
        Movement() {}
        ~Movement() {}
    
        void Deserialize(ReadBuffer* pBuffer)
        {
            pos.Deserialize(pBuffer);
            pBuffer->Read_float(rot);
            pBuffer->Read_float(velocity);
            pBuffer->Read_uint16(animation);
        }
        void Serialize(WriteBuffer* pBuffer)
        {
            pos.Serialize(pBuffer);
            pBuffer->Write_float(rot);
            pBuffer->Write_float(velocity);
            pBuffer->Write_uint16(animation);
        }
    
        Vector3 pos;
        float rot;
        float velocity;
        uint16_t animation;
    };
    
    class FactionInfo
    {
    public:
        FactionInfo() {}
        ~FactionInfo() {}
    
        void Deserialize(ReadBuffer* pBuffer)
        {
            pBuffer->Read_uint32(factionId);
            pBuffer->Read_char(rank);
        }
        void Serialize(WriteBuffer* pBuffer)
        {
            pBuffer->Write_uint32(factionId);
            pBuffer->Write_char(rank);
        }
    
        uint32_t factionId;
        char rank;
    };
    
    class ActorBaseData
    {
    public:
        ActorBaseData() {}
        ~ActorBaseData() {}
    
        void Deserialize(ReadBuffer* pBuffer)
        {
            pBuffer->Read_uint32(flags);
            pBuffer->Read_uint16(unk08);
            pBuffer->Read_uint16(unk0A);
            pBuffer->Read_uint16(level);
            pBuffer->Read_uint16(minLevel);
            pBuffer->Read_uint16(maxLevel);
            pBuffer->Read_uint16(unk12);
            pBuffer->Read_uint16(unk14);
            pBuffer->Read_uint16(unk16);
            pBuffer->Read_uint16(unk18);
            pBuffer->Read_uint16(unk1A);
            pBuffer->Read_uint32(unk1C);
            pBuffer->Read_uint32(voiceId);
            pBuffer->Read_uint32(unk24);
            pBuffer->Read_uint32(unk28);
            {
                uint32_t length = 0;
                pBuffer->Read_uint32(length);
                for(uint32_t i = 0; i < length; ++i)
                {
                    FactionInfo entry;
                    entry.Deserialize(pBuffer);
                    factions.push_back(entry);
                }
            }
        }
        void Serialize(WriteBuffer* pBuffer)
        {
            pBuffer->Write_uint32(flags);
            pBuffer->Write_uint16(unk08);
            pBuffer->Write_uint16(unk0A);
            pBuffer->Write_uint16(level);
            pBuffer->Write_uint16(minLevel);
            pBuffer->Write_uint16(maxLevel);
            pBuffer->Write_uint16(unk12);
            pBuffer->Write_uint16(unk14);
            pBuffer->Write_uint16(unk16);
            pBuffer->Write_uint16(unk18);
            pBuffer->Write_uint16(unk1A);
            pBuffer->Write_uint32(unk1C);
            pBuffer->Write_uint32(voiceId);
            pBuffer->Write_uint32(unk24);
            pBuffer->Write_uint32(unk28);
            {
                pBuffer->Write_uint32(static_cast<uint32_t>(factions.size()));
                for(auto entry : factions)
                {
                    entry.Serialize(pBuffer);
                }
            }
        }
    
        uint32_t flags;
        uint16_t unk08;
        uint16_t unk0A;
        uint16_t level;
        uint16_t minLevel;
        uint16_t maxLevel;
        uint16_t unk12;
        uint16_t unk14;
        uint16_t unk16;
        uint16_t unk18;
        uint16_t unk1A;
        uint32_t unk1C;
        uint32_t voiceId;
        uint32_t unk24;
        uint32_t unk28;
        std::vector<FactionInfo> factions;
    };
    
    class TESContainerData
    {
    public:
        TESContainerData() {}
        ~TESContainerData() {}
    
        void Deserialize(ReadBuffer* pBuffer)
        {
            pBuffer->Read_uint32(count);
            pBuffer->Read_uint32(formId);
            pBuffer->Read_uint32(unk00);
            pBuffer->Read_uint32(unk04);
            pBuffer->Read_float(unk08);
        }
        void Serialize(WriteBuffer* pBuffer)
        {
            pBuffer->Write_uint32(count);
            pBuffer->Write_uint32(formId);
            pBuffer->Write_uint32(unk00);
            pBuffer->Write_uint32(unk04);
            pBuffer->Write_float(unk08);
        }
    
        uint32_t count;
        uint32_t formId;
        uint32_t unk00;
        uint32_t unk04;
        float unk08;
    };
    
    class TESContainer
    {
    public:
        TESContainer() {}
        ~TESContainer() {}
    
        void Deserialize(ReadBuffer* pBuffer)
        {
            {
                uint32_t length = 0;
                pBuffer->Read_uint32(length);
                for(uint32_t i = 0; i < length; ++i)
                {
                    TESContainerData entry;
                    entry.Deserialize(pBuffer);
                    entries.push_back(entry);
                }
            }
        }
        void Serialize(WriteBuffer* pBuffer)
        {
            {
                pBuffer->Write_uint32(static_cast<uint32_t>(entries.size()));
                for(auto entry : entries)
                {
                    entry.Serialize(pBuffer);
                }
            }
        }
    
        std::vector<TESContainerData> entries;
    };
    
    class TESpellList
    {
    public:
        TESpellList() {}
        ~TESpellList() {}
    
        void Deserialize(ReadBuffer* pBuffer)
        {
            {
                uint32_t length = 0;
                pBuffer->Read_uint32(length);
                spellIds.resize(length);
                pBuffer->ReadRaw((uint8_t*)&spellIds[0], sizeof(uint32_t) * length);
            }
            {
                uint32_t length = 0;
                pBuffer->Read_uint32(length);
                formIds.resize(length);
                pBuffer->ReadRaw((uint8_t*)&formIds[0], sizeof(uint32_t) * length);
            }
            {
                uint32_t length = 0;
                pBuffer->Read_uint32(length);
                shoutIds.resize(length);
                pBuffer->ReadRaw((uint8_t*)&shoutIds[0], sizeof(uint32_t) * length);
            }
        }
        void Serialize(WriteBuffer* pBuffer)
        {
            {
                pBuffer->Write_uint32(static_cast<uint32_t>(spellIds.size()));
                pBuffer->WriteRaw((uint8_t*)&spellIds[0], sizeof(uint32_t) * (uint32_t)spellIds.size());
            }
            {
                pBuffer->Write_uint32(static_cast<uint32_t>(formIds.size()));
                pBuffer->WriteRaw((uint8_t*)&formIds[0], sizeof(uint32_t) * (uint32_t)formIds.size());
            }
            {
                pBuffer->Write_uint32(static_cast<uint32_t>(shoutIds.size()));
                pBuffer->WriteRaw((uint8_t*)&shoutIds[0], sizeof(uint32_t) * (uint32_t)shoutIds.size());
            }
        }
    
        std::vector<uint32_t> spellIds;
        std::vector<uint32_t> formIds;
        std::vector<uint32_t> shoutIds;
    };
    
    class BGSOverridePackCollection
    {
    public:
        BGSOverridePackCollection() {}
        ~BGSOverridePackCollection() {}
    
        void Deserialize(ReadBuffer* pBuffer)
        {
            pBuffer->Read_uint32(unk04);
            pBuffer->Read_uint32(unk08);
            pBuffer->Read_uint32(unk0C);
            pBuffer->Read_uint32(unk10);
        }
        void Serialize(WriteBuffer* pBuffer)
        {
            pBuffer->Write_uint32(unk04);
            pBuffer->Write_uint32(unk08);
            pBuffer->Write_uint32(unk0C);
            pBuffer->Write_uint32(unk10);
        }
    
        uint32_t unk04;
        uint32_t unk08;
        uint32_t unk0C;
        uint32_t unk10;
    };
    
    class FaceMorphs
    {
    public:
        FaceMorphs() {}
        ~FaceMorphs() {}
    
        void Deserialize(ReadBuffer* pBuffer)
        {
            {
                uint32_t length = 0;
                pBuffer->Read_uint32(length);
                options.resize(length);
                pBuffer->ReadRaw((uint8_t*)&options[0], sizeof(float) * length);
            }
            pBuffer->Read_uint32(preset0);
            pBuffer->Read_uint32(preset1);
            pBuffer->Read_uint32(preset2);
            pBuffer->Read_uint32(preset3);
        }
        void Serialize(WriteBuffer* pBuffer)
        {
            {
                pBuffer->Write_uint32(static_cast<uint32_t>(options.size()));
                pBuffer->WriteRaw((uint8_t*)&options[0], sizeof(float) * (uint32_t)options.size());
            }
            pBuffer->Write_uint32(preset0);
            pBuffer->Write_uint32(preset1);
            pBuffer->Write_uint32(preset2);
            pBuffer->Write_uint32(preset3);
        }
    
        std::vector<float> options;
        uint32_t preset0;
        uint32_t preset1;
        uint32_t preset2;
        uint32_t preset3;
    };
    
    class TESFullName
    {
    public:
        TESFullName() {}
        ~TESFullName() {}
    
        void Deserialize(ReadBuffer* pBuffer)
        {
            pBuffer->Read_string(data);
        }
        void Serialize(WriteBuffer* pBuffer)
        {
            pBuffer->Write_string(data);
        }
    
        std::string data;
    };
    
    class BGSColorForm
    {
    public:
        BGSColorForm() {}
        ~BGSColorForm() {}
    
        void Deserialize(ReadBuffer* pBuffer)
        {
            fullName.Deserialize(pBuffer);
            pBuffer->Read_uint32(abgr);
            pBuffer->Read_uint32(unk20);
        }
        void Serialize(WriteBuffer* pBuffer)
        {
            fullName.Serialize(pBuffer);
            pBuffer->Write_uint32(abgr);
            pBuffer->Write_uint32(unk20);
        }
    
        TESFullName fullName;
        uint32_t abgr;
        uint32_t unk20;
    };
    
    class Npc
    {
    public:
        Npc() {}
        ~Npc() {}
    
        void Deserialize(ReadBuffer* pBuffer)
        {
            pBuffer->Read_uint32(flags);
            pBuffer->Read_uint16(unk10);
            pBuffer->Read_uint8(formType);
            bound1.Deserialize(pBuffer);
            bound2.Deserialize(pBuffer);
            actorBaseData.Deserialize(pBuffer);
            container.Deserialize(pBuffer);
            spellList.Deserialize(pBuffer);
            pBuffer->Read_uint32(skinId);
            {
                uint32_t length = 0;
                pBuffer->Read_uint32(length);
                keywordIds.resize(length);
                pBuffer->ReadRaw((uint8_t*)&keywordIds[0], sizeof(uint32_t) * length);
            }
            pBuffer->Read_uint32(raceId);
            overridePacks.Deserialize(pBuffer);
            pBuffer->Read_uint16(unk10A);
            pBuffer->Read_uint32(classId);
            hairColor.Deserialize(pBuffer);
            pBuffer->Read_uint32(headTextureId);
            pBuffer->Read_uint32(unk114);
            pBuffer->Read_uint32(combatStyleId);
            pBuffer->Read_uint32(unk11C);
            pBuffer->Read_uint32(overlayId);
            pBuffer->Read_float(height);
            pBuffer->Read_float(weight);
            pBuffer->Read_uint32(skinFarId);
            pBuffer->Read_uint32(outfitId);
            pBuffer->Read_uint32(sleepOutfitId);
            pBuffer->Read_uint32(unk144);
            pBuffer->Read_uint32(factionId);
            {
                uint32_t length = 0;
                pBuffer->Read_uint32(length);
                headpartIds.resize(length);
                pBuffer->ReadRaw((uint8_t*)&headpartIds[0], sizeof(uint32_t) * length);
            }
            pBuffer->Read_uint8(unk151);
            pBuffer->Read_uint8(unk152);
            pBuffer->Read_uint8(unk153);
            pBuffer->Read_uint8(red);
            pBuffer->Read_uint8(green);
            pBuffer->Read_uint8(blue);
            pBuffer->Read_uint32(unk158);
            faceMorphs.Deserialize(pBuffer);
            pBuffer->Read_uint32(unk160);
        }
        void Serialize(WriteBuffer* pBuffer)
        {
            pBuffer->Write_uint32(flags);
            pBuffer->Write_uint16(unk10);
            pBuffer->Write_uint8(formType);
            bound1.Serialize(pBuffer);
            bound2.Serialize(pBuffer);
            actorBaseData.Serialize(pBuffer);
            container.Serialize(pBuffer);
            spellList.Serialize(pBuffer);
            pBuffer->Write_uint32(skinId);
            {
                pBuffer->Write_uint32(static_cast<uint32_t>(keywordIds.size()));
                pBuffer->WriteRaw((uint8_t*)&keywordIds[0], sizeof(uint32_t) * (uint32_t)keywordIds.size());
            }
            pBuffer->Write_uint32(raceId);
            overridePacks.Serialize(pBuffer);
            pBuffer->Write_uint16(unk10A);
            pBuffer->Write_uint32(classId);
            hairColor.Serialize(pBuffer);
            pBuffer->Write_uint32(headTextureId);
            pBuffer->Write_uint32(unk114);
            pBuffer->Write_uint32(combatStyleId);
            pBuffer->Write_uint32(unk11C);
            pBuffer->Write_uint32(overlayId);
            pBuffer->Write_float(height);
            pBuffer->Write_float(weight);
            pBuffer->Write_uint32(skinFarId);
            pBuffer->Write_uint32(outfitId);
            pBuffer->Write_uint32(sleepOutfitId);
            pBuffer->Write_uint32(unk144);
            pBuffer->Write_uint32(factionId);
            {
                pBuffer->Write_uint32(static_cast<uint32_t>(headpartIds.size()));
                pBuffer->WriteRaw((uint8_t*)&headpartIds[0], sizeof(uint32_t) * (uint32_t)headpartIds.size());
            }
            pBuffer->Write_uint8(unk151);
            pBuffer->Write_uint8(unk152);
            pBuffer->Write_uint8(unk153);
            pBuffer->Write_uint8(red);
            pBuffer->Write_uint8(green);
            pBuffer->Write_uint8(blue);
            pBuffer->Write_uint32(unk158);
            faceMorphs.Serialize(pBuffer);
            pBuffer->Write_uint32(unk160);
        }
    
        uint32_t flags;
        uint16_t unk10;
        uint8_t formType;
        Vector3 bound1;
        Vector3 bound2;
        ActorBaseData actorBaseData;
        TESContainer container;
        TESpellList spellList;
        uint32_t skinId;
        std::vector<uint32_t> keywordIds;
        uint32_t raceId;
        BGSOverridePackCollection overridePacks;
        uint16_t unk10A;
        uint32_t classId;
        BGSColorForm hairColor;
        uint32_t headTextureId;
        uint32_t unk114;
        uint32_t combatStyleId;
        uint32_t unk11C;
        uint32_t overlayId;
        float height;
        float weight;
        uint32_t skinFarId;
        uint32_t outfitId;
        uint32_t sleepOutfitId;
        uint32_t unk144;
        uint32_t factionId;
        std::vector<uint32_t> headpartIds;
        uint8_t unk151;
        uint8_t unk152;
        uint8_t unk153;
        uint8_t red;
        uint8_t green;
        uint8_t blue;
        uint32_t unk158;
        FaceMorphs faceMorphs;
        uint32_t unk160;
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
    
    class CliGame_PositionRecv : public Packet
    {
    public:
        CliGame_PositionRecv() {}
        ~CliGame_PositionRecv() {}
    
        void Deserialize(ReadBuffer* pBuffer)
        {
            movement.Deserialize(pBuffer);
        }
        void Serialize(WriteBuffer* pBuffer)
        {
            pBuffer->Write_uint16(CliGame_Position_Opcode);
            movement.Serialize(pBuffer);
        }
    
        Movement movement;
    };
    
    class CliGame_PlayerInitializeRecv : public Packet
    {
    public:
        CliGame_PlayerInitializeRecv() {}
        ~CliGame_PlayerInitializeRecv() {}
    
        void Deserialize(ReadBuffer* pBuffer)
        {
            player_npc.Deserialize(pBuffer);
            horse_npc.Deserialize(pBuffer);
            movement.Deserialize(pBuffer);
        }
        void Serialize(WriteBuffer* pBuffer)
        {
            pBuffer->Write_uint16(CliGame_PlayerInitialize_Opcode);
            player_npc.Serialize(pBuffer);
            horse_npc.Serialize(pBuffer);
            movement.Serialize(pBuffer);
        }
    
        Npc player_npc;
        Npc horse_npc;
        Movement movement;
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
    
    class GameCli_PositionSend : public Packet
    {
    public:
        GameCli_PositionSend() {}
        ~GameCli_PositionSend() {}
    
        void Deserialize(ReadBuffer* pBuffer)
        {
            pBuffer->Read_uint16(playerId);
            movement.Deserialize(pBuffer);
        }
        void Serialize(WriteBuffer* pBuffer)
        {
            pBuffer->Write_uint16(GameCli_Position_Opcode);
            pBuffer->Write_uint16(playerId);
            movement.Serialize(pBuffer);
        }
    
        uint16_t playerId;
        Movement movement;
    };
    
    class GameCli_PlayerAddSend : public Packet
    {
    public:
        GameCli_PlayerAddSend() {}
        ~GameCli_PlayerAddSend() {}
    
        void Deserialize(ReadBuffer* pBuffer)
        {
            pBuffer->Read_uint16(playerId);
            pBuffer->Read_string(name);
            player_npc.Deserialize(pBuffer);
            horse_npc.Deserialize(pBuffer);
            movement.Deserialize(pBuffer);
        }
        void Serialize(WriteBuffer* pBuffer)
        {
            pBuffer->Write_uint16(GameCli_PlayerAdd_Opcode);
            pBuffer->Write_uint16(playerId);
            pBuffer->Write_string(name);
            player_npc.Serialize(pBuffer);
            horse_npc.Serialize(pBuffer);
            movement.Serialize(pBuffer);
        }
    
        uint16_t playerId;
        std::string name;
        Npc player_npc;
        Npc horse_npc;
        Movement movement;
    };
    
    class GameCli_PlayerRemoveSend : public Packet
    {
    public:
        GameCli_PlayerRemoveSend() {}
        ~GameCli_PlayerRemoveSend() {}
    
        void Deserialize(ReadBuffer* pBuffer)
        {
            pBuffer->Read_uint16(playerId);
        }
        void Serialize(WriteBuffer* pBuffer)
        {
            pBuffer->Write_uint16(GameCli_PlayerRemove_Opcode);
            pBuffer->Write_uint16(playerId);
        }
    
        uint16_t playerId;
    };
    
}

#endif // MSG_CLI_GAME_HANDLER_H

