#include "RakNetController.h"
#include "MessageIdentifiers.h"
#include "RakNetTypes.h"
#include "BitStream.h"

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
	return false;
}

bool RakNetController::CreateServer(int p_serverPort)
{
	m_isServer = true;
	RakNet::SocketDescriptor sd(p_serverPort, 0);

	if (m_peer->Startup(8, &sd, 1) != RakNet::RAKNET_STARTED)
	{
		printf("Server failed to connect \n");
		return false;
	}

	m_peer->SetMaximumIncomingConnections(8);

	printf("Server started \n");
	return true;
}

bool RakNetController::CreateClient(std::string p_serverIP, int p_serverPort)
{
	m_isServer = false;

	RakNet::SocketDescriptor sd;

	if (m_peer->Startup(1, &sd, 1) != RakNet::RAKNET_STARTED)
	{
		printf("Client failed to start up\n");
		return false;
	}

	if (m_peer->Connect(p_serverIP.c_str(), p_serverPort, 0, 0) != RakNet::CONNECTION_ATTEMPT_STARTED)
	{
		printf("Client failed to connect\n");
		return false;
	}

	printf("Client started\n");
	return true;
}



bool RakNetController::SendData(const char* p_data)
{
	RakNet::BitStream a_bsOut;
	a_bsOut.Write((RakNet::MessageID)(ID_USER_PACKET_ENUM + 1));
	a_bsOut.Write(p_data);
	m_peer->Send(&a_bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, m_peerGUID, false);

	printf("Message sent\n");
	return true;
}

bool RakNetController::RecvData()
{
	for (RakNet::Packet* a_packet = m_peer->Receive(); a_packet; m_peer->DeallocatePacket(a_packet), a_packet = m_peer->Receive())
	{
		switch (a_packet->data[0])
		{
		case ID_REMOTE_CONNECTION_LOST:
			printf("Another client has lost the connection\n");
			break;

		case ID_REMOTE_NEW_INCOMING_CONNECTION:
			printf("Another client has connected\n");
			break;

		case ID_CONNECTION_REQUEST_ACCEPTED:
			printf("Connection has been accepted\n");
			m_peerGUID = a_packet->systemAddress;
			break;
			 
		case ID_NEW_INCOMING_CONNECTION:
			printf("A connection is incoming\n");
			m_peerGUID = a_packet->systemAddress;
			break;
		
		case ID_NO_FREE_INCOMING_CONNECTIONS:
			printf("The server is full\n");

		case ID_DISCONNECTION_NOTIFICATION:
			
			if (m_isServer)
				printf("A client has been disconnected\n");
			else
				printf("We have been disconnected");
			break;

		case ID_CONNECTION_LOST:
			if(m_isServer)
			printf("A client has lost the connection\n");
			else
			{
				printf("Connection Lost\n");
			}
			break;

			case ID_USER_PACKET_ENUM + 1:
			{
				RakNet::RakString a_rs;
				RakNet::BitStream a_bsIn(a_packet->data, a_packet->length, false);
				a_bsIn.IgnoreBytes(sizeof(RakNet::MessageID));

				a_bsIn.Read(a_rs);
				printf("%s\n", a_rs.C_String());
				break;
			}
			
		default:
			printf("Message with identifier %i has arrived\n", a_packet->data[0]);
			break;

		}
	}
	return true;
}
