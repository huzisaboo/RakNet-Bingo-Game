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
            if (m_gameBoard.size() == 0)        //Client has not received the game board yet 
            { 
                if (PopulateGameBoard(m_message))
                {
                    DisplayGameBoard();
                }
            }
            else if(m_gameBoard.size() == 9)    //Client has received the game board
            {
                std::cout << m_message << std::endl;
                for (int i = 0; i < m_gameBoard.size(); i++)
                {
                    if (m_gameBoard[i]._Equal(m_message))
                    {
                        std::cout << "!!!!!!!!!!!Match Found At Location "<<i+1<<" !!!!!!!!!!"<<std::endl;
                        m_gameBoard[i] = "0";
                        DisplayGameBoard();
                        if (WinCondition())
                        {
                            m_raknetController->SendData("Bingo!");
                            break;
                        }
                    }
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


bool ClientSide::PopulateGameBoard(std::string p_message)
{
    std::stringstream a_ss(p_message);
    std::vector<std::string> a_gameBoard(std::istream_iterator<std::string>{a_ss},
        std::istream_iterator<std::string>());

    m_gameBoard = a_gameBoard;

    return true;
}

bool ClientSide::WinCondition()
{
    if (std::count(m_gameBoard.begin(), m_gameBoard.end(), "0") == m_gameBoard.size())
    {
        return true;
    }

    return false;
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
        std::cout << std::endl <<std::endl;
    }
    
}

