#include "RakNetController.h"
#include "MessageIdentifiers.h"
#include "RakNetTypes.h"
#include "BitStream.h"
#include <iostream>



bool RakNetController::Initialize()
{
	m_peer = RakNet::RakPeerInterface::GetInstance();

	if (!m_peer)
	{
		return false;
	}
	return true;
}

bool RakNetController::Cleanup()
{
	delete m_peer;
	m_peer = nullptr;

	std::cout << "Good Bye!" << std::endl;
	return true;
}

bool RakNetController::CreateServer(int p_serverPort)
{
	m_isServer = true;
	RakNet::SocketDescriptor sd(p_serverPort, 0);

	if (m_peer->Startup(8, &sd, 1) != RakNet::RAKNET_STARTED)
	{
		std::cout << "Server failed to connect" << std::endl;
		return false;
	}

	m_peer->SetMaximumIncomingConnections(4);

	std::cout << "Server started" << std::endl;
	return true;
}

bool RakNetController::CreateClient(std::string p_serverIP, int p_serverPort)
{
	m_isServer = false;

	RakNet::SocketDescriptor sd;

	if (m_peer->Startup(1, &sd, 1) != RakNet::RAKNET_STARTED)
	{
		std::cout << "Client failed to start up" << std::endl;
		return false;
	}

	if (m_peer->Connect(p_serverIP.c_str(), p_serverPort, 0, 0) != RakNet::CONNECTION_ATTEMPT_STARTED)
	{
		std::cout << "Client failed to connect" << std::endl;
		return false;
	}

	std::cout << "Client started" << std::endl;
	return true;
}



bool RakNetController::SendData(const char* p_data)
{
	RakNet::BitStream a_bsOut;
	a_bsOut.Write((RakNet::MessageID)(ID_USER_PACKET_ENUM + 1));
	a_bsOut.Write(p_data);

	m_peer->Send(&a_bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, m_peerGUID, false);

	std::cout << "Message sent:" << p_data << std::endl;
	return true;
}

bool RakNetController::SendDataByGUID(const char* p_data, RakNet::AddressOrGUID p_peerGUID)
{
	RakNet::BitStream a_bsOut;
	a_bsOut.Write((RakNet::MessageID)(ID_USER_PACKET_ENUM + 1));
	a_bsOut.Write(p_data);

	m_peer->Send(&a_bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, p_peerGUID, false);


	std::cout << "Message sent:" << p_data << std::endl;
	return true;
}


std::string RakNetController::RecvData()
{
	std::string a_message = "";

	for (RakNet::Packet* a_packet = m_peer->Receive(); a_packet; m_peer->DeallocatePacket(a_packet), a_packet = m_peer->Receive())
	{
		switch (a_packet->data[0])
		{
		case ID_REMOTE_CONNECTION_LOST:
			std::cout << "Another client has lost the connection" << std::endl;
			break;

		case ID_REMOTE_NEW_INCOMING_CONNECTION:
			std::cout << "Another client has connected" << std::endl;
			break;

		case ID_CONNECTION_REQUEST_ACCEPTED:
			std::cout << "Connection has been accepted" << std::endl;
			m_peerGUID = a_packet->systemAddress;
			break;

		case ID_NEW_INCOMING_CONNECTION:
			std::cout << "A connection is incoming" << std::endl;
			m_peerGUID = a_packet->systemAddress;
			m_peerGUIDs.push_back(m_peerGUID);
			break;

		case ID_NO_FREE_INCOMING_CONNECTIONS:
			std::cout << "The server is full" << std::endl;

		case ID_DISCONNECTION_NOTIFICATION:

			if (m_isServer)
				std::cout << "A client has been disconnected" << std::endl;
			else
				std::cout << "We have been disconnected" << std::endl;

			break;

		case ID_CONNECTION_LOST:
			if (m_isServer)
				std::cout << "A client has lost the connection" << std::endl;
			else
			{
				std::cout << "Connection Lost" << std::endl;
			}
			break;

		case ID_USER_PACKET_ENUM + 1:
		{
			RakNet::RakString a_rs;
			RakNet::BitStream a_bsIn(a_packet->data, a_packet->length, false);
			a_bsIn.IgnoreBytes(sizeof(RakNet::MessageID));

			a_bsIn.Read(a_rs);
			a_message = a_rs.C_String();
			break;
		}

		default:
			std::cout << "Message with identifier %i has arrived" << a_packet->data[0] << std::endl;
			break;

		}
	}

	return a_message;
}
