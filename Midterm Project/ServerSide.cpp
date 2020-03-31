#include "ServerSide.h"
#include <sstream>
#include <conio.h>
#include<ctime>

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
                    printf("%c\n", a_key);
                    break;
                }
                
            }
            m_raknetController->RecvData();

        }
        
        
        m_raknetController->RecvData();
        int a_rand = m_random->IRandom(0, 99);
        
        if (_kbhit())
        {
            a_key = _getch();
            if (a_key == 27)
            {
                break;
            }
        }

       // printf("%d\n", rand);
       
            m_raknetController->SendData(std::to_string(a_rand).c_str());
            Sleep(100); 
    }
}
