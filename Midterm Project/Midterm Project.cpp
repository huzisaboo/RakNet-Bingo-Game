#include "ServerSide.h"
#include "ClientSide.h"
#include <chrono>
#include <iostream>


//static RakNetController m_rn = RakNetController();
//static CRandomMersenne m_random = CRandomMersenne(time(0));

//int Initialize(char* argv[])
//{
//    if (strcmp(argv[1], "server") == 0)
//    {
//        if ((!m_rn.Initialize()) || (!m_rn.CreateServer(27022)))
//        {
//            return -1;
//        }
//    }
//    else if (strcmp(argv[1], "client") == 0)
//    {
//        if ((!m_rn.Initialize()) || (!m_rn.CreateClient("127.0.0.1", 27022)))
//        {
//            return -1;
//        }
//    }
//
//    else
//        return -1;
//
//    return 0;
//}

//void GameLoop()
//{
//    while (true)
//    {
//        char a_key = ' ';
//        std::stringstream a_ss;
//
//        while ((a_key != '\r') && (a_key != 27))
//        {
//            if (_kbhit())
//            {
//                a_key = _getch();
//                a_ss << a_key;
//                printf("%c", a_key);
//            }
//            m_rn.RecvData();
//        }
//        if (a_key == 27)
//            break;
//       int rand = m_random.IRandom(0, 99);
//
//       printf("%d\n",rand);
//
//        m_rn.SendData(a_ss.str().c_str());
//
//    }
//}



int main(int argc, char* argv[])
{
    int a_retValue = -1;
    if (strcmp(argv[1], "server") == 0)
    {
        ServerSide* a_server = new ServerSide();
       a_retValue = a_server->Initialize();
       if (a_retValue == 0)
       {
           a_server->GameLoop();

           delete a_server;
       }
    }
    else if (strcmp(argv[1], "client") == 0)
    {
        ClientSide* a_client = new ClientSide();
        a_retValue = a_client->Initialize();
        if (a_retValue == 0)
        {
            a_client->GameLoop();

            delete a_client;
        }
    }
    
    return a_retValue;
}

