#include "ServerSide.h"
#include <sstream>
#include <conio.h>
#include<ctime>
#include<iostream>
#include <chrono>

ServerSide::ServerSide()
{
	m_raknetController = new RakNetController();
	m_random = new CRandomMersenne(time(0));
}

ServerSide::~ServerSide()
{
	if (m_raknetController->Cleanup())
	{
		delete m_raknetController;
		delete m_random;

		m_raknetController = nullptr;
		m_random = nullptr;
	}
}

int ServerSide::Initialize()
{
	if ((!m_raknetController->Initialize()) || (!m_raknetController->CreateServer(27022)))
	{
		return -1;
	}
	return 0;
}

void ServerSide::GameLoop()
{
	char a_key = ' ';
	std::chrono::time_point<std::chrono::system_clock> a_startTime;
	std::chrono::time_point<std::chrono::system_clock> a_endTime;
	std::chrono::duration<float> a_deltaTime;

	while (true)
	{
		while ((a_key != 's') && (a_key != 27))
		{
			if (_kbhit())
			{
				a_key = _getch();
				if (a_key == 27)
				{
					break;
				}
				else if (a_key == 's')
				{
					if (m_raknetController->m_peerGUIDs.size() > 0)
					{
						for (auto a_peerGUID : m_raknetController->m_peerGUIDs)
						{
							SendGameBoard(a_peerGUID);
							a_startTime = std::chrono::system_clock::now();
						}

						break;
					}
					else
					{
						a_key = ' ';    //resetting the key so that the inner loop is not terminated unnecesarily which could happen if user presses "s"
					}                   //even though no client is connected to the server
				}

			}
			m_message = m_raknetController->RecvData();
		}

		m_message = m_raknetController->RecvData();		//Now the server would call receivedata method with respect to the outer loop since it has exited the inner
														//loop
		if (!m_message.empty() && !m_winnerDeclared)
		{
			if (m_message._Equal("Bingo!"))
			{
				std::cout << "Winner!" << std::endl;
				m_winnerDeclared = true;
			}
		}
		else if (!m_winnerDeclared)
		{
			a_endTime = std::chrono::system_clock::now();

			a_deltaTime = a_endTime - a_startTime;

			if (a_deltaTime.count() >= m_maxDurationTime)
			{
				SendRandomNumber();
				a_startTime = std::chrono::system_clock::now();
			}
		}

		if (a_key == 27)	//If ESC is pressed while being in inner loop
		{
			break;
		}
		else if (_kbhit())
		{
			a_key = _getch();
			if (a_key == 27)	// If ESC is pressed while being in inner loop
			{
				break;
			}
		}
	}

}

void ServerSide::SendGameBoard(RakNet::AddressOrGUID p_peerGUID)
{
	std::stringstream a_ss;

	for (int i = 0; i < 9; i++)
	{
		int a_rand = m_random->IRandom(10, 99);
		a_ss << a_rand;
		a_ss << " ";
	}
	m_raknetController->SendDataByGUID(a_ss.str().c_str(), p_peerGUID);

}

void ServerSide::SendRandomNumber()
{
	int a_rand = m_random->IRandom(10, 99);

	for (auto a_peerGUID : m_raknetController->m_peerGUIDs)
	{
		m_raknetController->SendDataByGUID(std::to_string(a_rand).c_str(), a_peerGUID);
	}
}
