#include "ServerSide.h"
#include <sstream>
#include <conio.h>
#include<ctime>
#include<iostream>



ServerSide::ServerSide()
{
	m_raknetController = new RakNetController();
    m_random = new CRandomMersenne(time(0));
}

ServerSide::~ServerSide()
{
	m_raknetController->Cleanup();
    delete m_raknetController;
    delete m_random;

    m_raknetController = nullptr;
    m_random = nullptr;
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
    int a_counter = 0;
    char a_key = ' ';
 
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
                   /* printf("%c\n", a_key);
                    a_ss << a_key;
                    m_raknetController->SendData(a_ss.str().c_str());
                   */ 
                    SendGameBoard();
                   // a_ss.str("");   //clear content of stringstream
                    break;
                }
                
            }
          m_message = m_raknetController->RecvData();
        }
        
       /* if (a_key == 's' && a_counter < 9)
        {
            
                int a_rand = m_random->IRandom(0, 99);
                m_raknetController->SendData(std::to_string(a_rand).c_str());
                a_counter++;
            

            
        }*/
        
     
       // int a_rand = m_random->IRandom(0, 99);
        
        if (_kbhit())
        {
            a_key = _getch();
            if (a_key == 27)
            {
                break;
            }
        }
        m_message = m_raknetController->RecvData();

       // printf("%d\n", rand);
       
           // m_raknetController->SendData(std::to_string(a_rand).c_str());
            //Sleep(1000); 
    }

}

void ServerSide::SendGameBoard()
{
    std::stringstream a_ss;
    for (int i = 0; i < 9; i++)
    {
        int a_rand = m_random->IRandom(0, 99);
        a_ss << a_rand;
        a_ss << " ";
    }

    m_raknetController->SendData(a_ss.str().c_str());

}
