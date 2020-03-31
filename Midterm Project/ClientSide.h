#pragma once
#include "RakNetController.h"
#ifndef CLIENTSIDE_H
#define CLIENTSIDE_H
//#include "RakNetController.h"

class ClientSide
{
private:
	RakNetController* m_raknetController;

public:
	 
	ClientSide();
	~ClientSide();
	int Initialize();
	void GameLoop();

};

#endif



