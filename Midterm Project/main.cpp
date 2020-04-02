#include "ServerSide.h"
#include "ClientSide.h"


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
			a_server = nullptr;
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
			a_client = nullptr;
		}
	}

	return a_retValue;
}

