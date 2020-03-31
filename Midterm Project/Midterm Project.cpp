#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <sstream>
#include "RakNetController.h"


static RakNetController m_rn = RakNetController();


int Initialize(char* argv[])
{
    if (strcmp(argv[1], "server") == 0)
    {
        if ((!m_rn.Initialize()) || (!m_rn.CreateServer(27022)))
        {
            return -1;
        }
    }
    else if (strcmp(argv[1], "client") == 0)
    {
        if ((!m_rn.Initialize()) || (!m_rn.CreateClient("127.0.0.1", 27022)))
        {
            return -1;
        }
    }

    else
        return -1;

    return 0;
}

void GameLoop()
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
                a_ss << a_key;
                printf("%c", a_key);
            }
            m_rn.RecvData();
        }
        if (a_key == 27)
            break;

        m_rn.SendData(a_ss.str().c_str());
    }
}



int main(int argc, char* argv[])
{
    int a_retValue = Initialize(argv);

    if (a_retValue == 0)
    {
        GameLoop();
        m_rn.Cleanup();
    }
    return a_retValue;
}

