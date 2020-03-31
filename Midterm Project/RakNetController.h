#pragma once

#include <winsock2.h>
#include <string>

#include "RakPeerInterface.h"

class RakNetController
{
private:
	RakNet::RakPeerInterface* m_peer = NULL;
	RakNet::AddressOrGUID m_peerGUID;
	bool m_isServer;

public:
	bool Initialize();
	bool Cleanup();
	bool CreateServer(int p_serverPort);
	bool CreateClient(std::string p_serverIP, int p_serverPort);
	bool SendData(const char* p_data);
	bool RecvData();
};

