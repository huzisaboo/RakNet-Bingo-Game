#include "ClientSide.h"
#include <sstream>
#include <conio.h>
#include <iostream>
#include <iterator>



ClientSide::ClientSide()
{
	m_raknetController = new RakNetController();
}

ClientSide::~ClientSide()
{
	m_raknetController->Cleanup();
    delete m_raknetController;
}

int ClientSide::Initialize()
{
	if ((!m_raknetController->Initialize()) || (!m_raknetController->CreateClient("127.0.0.1", 27022)))
	{
		return -1;
	}
	return 0;
}

void ClientSide::GameLoop()
{
    while (true)
    {
        char a_key = ' ';
        std::stringstream a_ss;

        /*while ((a_key != '\r') && (a_key != 27))
        {
            if (_kbhit())
            {
                a_key = _getch();
                if (a_key == 27)
                {
                    break;
                }
                a_ss << a_key;
                printf("%c", a_key);
            }

        }*/

        m_message = m_raknetController->RecvData();

        if (!m_message.empty())
        {
            if (m_gameBoard.size() == 0)
            {
                PopulateGameBoard(m_message);
                
                if (m_gameBoard.size() == 9)
                {
                    DisplayGameBoard();
                }
            }
        }

        if (_kbhit())
        {
            a_key = _getch();
            if (a_key == 27)
                break;
        }
        //  m_raknetController->SendData(a_ss.str().c_str());
    }

}


void ClientSide::PopulateGameBoard(std::string p_message)
{
    std::stringstream a_ss(m_message);
    std::vector<std::string> a_gameBoard(std::istream_iterator<std::string>{a_ss},
        std::istream_iterator<std::string>());

    m_gameBoard = a_gameBoard;

}

void ClientSide::DisplayGameBoard()
{
    if (m_gameBoard.size() == 9)
    {
        std::cout << "Game Board:" << std::endl;
        for (int i = 0; i < m_gameBoard.size(); i++)
        {
            if (i != 0 && i % 3 == 0)
            {
                std::cout << std::endl;
            }
            std::cout << m_gameBoard[i] << " ";
        }
        std::cout << std::endl;
    }
    
}

