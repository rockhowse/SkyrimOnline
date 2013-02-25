#pragma once

enum{
	kGamePort = 14596,
	kProtocolVersion = 2
};

enum{
	kClientChatMessage = 'ccha',
	kClientInitialData = 'cida',
	kClientPlayerMoveState = 'cpmv',
	kClientMountState = 'cmos'
};

enum{
	kServerChatMessage = 'scha',
	kServerServiceResponse = 'sser',
	kServerWorldState = 'swst',
	kServerModRegistration = 'smre'
};