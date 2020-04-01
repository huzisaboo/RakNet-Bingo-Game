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
                    if (m_raknetController->m_peerGUIDs.size() > 0)
                    {
                        for (auto a_peerGUID : m_raknetController->m_peerGUIDs)
                        {
                            SendGameBoard(a_peerGUID);
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
        
       /* if (a_key == 's' && a_counter < 9)
        {
            
                int a_rand = m_random->IRandom(0, 99);
                m_raknetController->SendData(std::to_string(a_rand).c_str());
                a_counter++;
            

            
        }*/
        
     
       // int a_rand = m_random->IRandom(0, 99);
        if (a_key == 27)
        {
            break;
        }
        else if (_kbhit())
        {
            a_key = _getch();
        }
        m_message = m_raknetController->RecvData();

       // printf("%d\n", rand);
       
           // m_raknetController->SendData(std::to_string(a_rand).c_str());
            //Sleep(1000); 
    }

}

void ServerSide::SendGameBoard(RakNet::AddressOrGUID p_peerGUID)
{
    std::stringstream a_ss;

        for (int i = 0; i < 9; i++)
        {
            int a_rand = m_random->IRandom(0, 99);
            a_ss << a_rand;
            a_ss << " ";
        }
        m_raknetController->SendDataByGUID(a_ss.str().c_str(), p_peerGUID);
    
    
}
