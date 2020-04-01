#pragma once

#include <winsock2.h>
#include <string>

#include "RakPeerInterface.h"
#include <vector>

class RakNetController
{
private:
	RakNet::RakPeerInterface* m_peer = NULL;
	RakNet::AddressOrGUID m_peerGUID;
	bool m_isServer;

public:
	std::vector<RakNet::AddressOrGUID> m_peerGUIDs;
	bool Initialize();
	bool Cleanup();
	bool CreateServer(int p_serverPort);
	bool CreateClient(std::string p_serverIP, int p_serverPort);
	bool SendData(const char* p_data);
	bool SendDataByGUID(const char* p_data, RakNet::AddressOrGUID p_peerGUID);
	std::string RecvData();
};

