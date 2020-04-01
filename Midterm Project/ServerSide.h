#pragma once
#ifndef SERVERSIDE_H
#define SERVERSIDE_H
#include "RakNetController.h"
#include "randomc.h"

class ServerSide
{
private:
	std::string m_message;
	RakNetController* m_raknetController = nullptr;
	 CRandomMersenne* m_random = nullptr;
	 void SendGameBoard(RakNet::AddressOrGUID p_peerGUID);
	 void SendRandomNumber();

public:
	ServerSide();
	~ServerSide();
	int Initialize();
	void GameLoop();
};
#endif



