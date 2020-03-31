#include "ClientSide.h"
#include <sstream>
#include <conio.h>

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

        while ((a_key != '\r') && (a_key != 27))
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
            m_raknetController->RecvData();
        }
        if (a_key == 27)
            break;
       // int rand = m_random.IRandom(0, 99);

       // printf("%d\n", rand);

        m_raknetController->SendData(a_ss.str().c_str());

    }

}
