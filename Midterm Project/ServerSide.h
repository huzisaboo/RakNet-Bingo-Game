#pragma once
#ifndef SERVERSIDE_H
#define SERVERSIDE_H
#include "RakNetController.h"
#include "randomc.h"

class ServerSide
{
private:
	std::string m_message;

	 RakNetController* m_raknetController;
	 CRandomMersenne* m_random;
	 void SendGameBoard();

public:
	ServerSide();
	~ServerSide();
	int Initialize();
	void GameLoop();
};
#endif



