#pragma once
#ifndef SERVERSIDE_H
#define SERVERSIDE_H
#include "RakNetController.h"
#include "randomc.h"
#include <chrono>

class ServerSide
{
private:
	std::chrono::time_point<std::chrono::system_clock> m_startTime;
	std::chrono::time_point<std::chrono::system_clock> m_endTime;
	std::chrono::duration<float> m_deltaTime;
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



