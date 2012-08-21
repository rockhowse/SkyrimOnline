#pragma once

// IMPORTANT !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// The opcode is the CRC-32 of the opcode's name !!!!
// Do it here: http://www.lammertbies.nl/comm/info/crc-calculation.html
// If you don't I WILL KILL YOU !!!!!

namespace Opcode{
	typedef const uint32_t __opcode;

	// Client opcodes
	// Proxy server
	static __opcode CMSG_REQUEST_SIGNATURE = 0x21655AE0;
	static __opcode CMSG_REQUEST_INTRODUCE_CONNECTION = 0x5DF86B99;
	// Game server
	static __opcode CMSG_SERVICE_ACK = 0x4E81BB18;
	static __opcode CMSG_SERVICE_REQUEST = 0x1333B5AC;
	static __opcode CMSG_REQUEST_CLOSE = 0xD99EAF83;
	static __opcode CMSG_CHARACTER_INFO = 0x4A4C9B79;
	static __opcode CMSG_MOVE_AND_LOOK = 0xA75B65DE;
	static __opcode CMSG_ENTER_REGION = 0xF1AF2295;

	static __opcode CMSG_MOUNT_SPAWN = 0xF506ED0B;
	static __opcode CMSG_MOUNT_REMOVE = 0xFA379B89;

	static __opcode CMSG_CHAT_MESSAGE = 0x984F5B6F;

	// Server opcodes
	// Proxy server
	static __opcode SMSG_REQUEST_INTRODUCE_CONNECTION = 0x8433682B;
	static __opcode SMSG_REQUEST_SIGNATURE = 0x889210A1;
	// Game server
	static __opcode SMSG_GAMEOBJECT = 0x5D3A6D92;
	static __opcode SMSG_SIGNATURE_RESPONSE = 0x5AC19F25;
	static __opcode SMSG_CLIENT_INFORMATION = 0x6524768C;

	static __opcode SMSG_SERVER_ADDRESS = 0xC2FCBCD3;

	static __opcode SMSG_PLAYER_SPAWN = 0xA40BEDC5;
	static __opcode SMSG_PLAYER_MOUNT_SPAWN = 0x0E20D04A;
	static __opcode SMSG_PLAYER_MOUNT_REMOVE = 0xFB17CCB2;
	static __opcode SMSG_PLAYER_MOVE_AND_LOOK = 0x1651ACAD;
	static __opcode SMSG_CHARACTER_REMOVE = 0xB08AC9A9;
	static __opcode SMSG_CHARACTER_ENTER_AREA = 0x747354E6;

	static __opcode SMSG_CHAT_MESSAGE = 0x8F1EC212;

	// Packet type

	static __opcode CMSG_PACKET = 0x0;
	static __opcode SMSG_PACKET = 0x0;
	static __opcode CMSG_PING = 0x1;
	static __opcode SMSG_PING = 0x2;
	static __opcode SMSG_HANDSHAKE = 0x3;
	static __opcode CMSG_HANDSHAKE = 0x4;
}
