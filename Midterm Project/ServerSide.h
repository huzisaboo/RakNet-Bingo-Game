#pragma once
#ifndef SERVERSIDE_H
#define SERVERSIDE_H
#include "RakNetController.h"
#include "randomc.h"

class ServerSide
{
private:
	 RakNetController* m_raknetController;
	 CRandomMersenne* m_random;

public:
	ServerSide();
	~ServerSide();
	int Initialize();
	void GameLoop();
};
#endif



