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
	void PopulateGameBoard(std::string p_message);
	void DisplayGameBoard(std::vector<std::string>& p_gameBoard);

public:
	 
	ClientSide();
	~ClientSide();
	int Initialize();
	void GameLoop();

};

#endif



