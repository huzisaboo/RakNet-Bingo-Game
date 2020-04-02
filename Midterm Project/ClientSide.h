#pragma once
#include "RakNetController.h"
#ifndef CLIENTSIDE_H
#define CLIENTSIDE_H
//#include "RakNetController.h"

class ClientSide
{
private:
	std::vector<std::string> m_gameBoard;
	std::string m_message;
	RakNetController* m_raknetController;
	bool PopulateGameBoard(std::string p_message);
	bool WinCondition();
	void DisplayGameBoard();


public:
	 
	ClientSide();
	~ClientSide();
	int Initialize();
	void GameLoop();

};

#endif



