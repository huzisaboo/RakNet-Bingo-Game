#pragma once
#ifndef SERVERSIDE_H
#define SERVERSIDE_H
#include "RakNetController.h"
#include "randomc.h"

class ServerSide
{
private:

	float m_maxDurationTime = 0.1f; //100 milliseconds
	bool m_winnerDeclared = false;
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



