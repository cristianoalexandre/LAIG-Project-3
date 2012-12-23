#include <iostream>
#include <exception>

#include "CGFapplication.h"
#include "Socket.h"
#include "GameScene.h"

using namespace std;

int main(int argc, char* argv[])
{    
/*
	CGFapplication app = CGFapplication();

	try
	{
		app.init(&argc, argv);

		app.setScene(new GameScene());
		app.setInterface(new CGFinterface());

		app.run();

	}
	catch (GLexception& ex)
	{
		cout << "Erro: " << ex.what();
		return -1;
	}
	catch (exception& ex)
	{
		cout << "Erro inesperado: " << ex.what();
		return -1;
	}

	return 0;
 */
   
	Socket sock = Socket("127.0.0.1",60001);

	sock.sendMsg("ready.\n");
	string ans = sock.readMsg();
	cout << ans << endl;

	cin.get();
	
}