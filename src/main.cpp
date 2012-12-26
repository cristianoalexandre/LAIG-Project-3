#include <iostream>
#include <exception>

#include "TPscene.h"
#include "DemoScene.h"

#include "CGFapplication.h"
#include "GameScene.h"
#include "PickInterface.h"

using std::cout;
using std::exception;

int main(int argc, char* argv[])
{
    CGFapplication app = CGFapplication();
	GameScene* s = new GameScene();
	PickInterface* pick = new PickInterface();
	pick->setScene(s);

    try
    {
        app.init(&argc, argv);

        app.setScene(s);
        app.setInterface(pick);

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
}