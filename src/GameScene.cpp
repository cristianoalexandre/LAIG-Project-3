#include <GL/glew.h>

#include "GameScene.h"
#include "Patch.h"
#include "FlyingDisk.h"

unsigned int LineAnimation::mili_secs = 0;
unsigned int PieceAnimation::mili_secs = 0;

int Ring::numberExistingRings = 0;

PieceAnimation* animP;

void updateTransforms(int dummy)
{
    animP->update();
    glutTimerFunc(PieceAnimation::getMiliSecs(), updateTransforms, dummy);
}

void GameScene::init()
{
    /** Enables lighting computations */
    glEnable(GL_LIGHTING);

    /** Sets up some lighting parameters */
    glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, CGFlight::background_ambient);

    /** Lights initialization */
    initCGFLights();

    /** Defines a default normal */
    glNormal3f(0, 0, 1);

    /** Materials initialization */
    materialAppearance = new CGFappearance();
    textureAppearance = new CGFappearance("../textures/pyramid.jpg", GL_REPEAT, GL_REPEAT);
    tentAppearance = new CGFappearance("../textures/tent.jpg", GL_REPEAT, GL_REPEAT);

    /** Object initialization */
    /*torus = new Board();
    p = new Piece("rook", "white");
    p->moveToCell(20);
    //model1 = new Model("../models/whitePawn.obj");

    animP = new PieceAnimation();
    animP->setPiece(p);
    animP->setMovement(32, 1, 1);
	
    /** Game declaration */

    player1 = new Player("white");
    player2 = new Player("black", CPU_EASY);

    game = new Game(player1, player2);
    selectedCellID = -1;

    game->socket->sendMsg("ready.\n");
    cout << "Ready? - " << game->socket->readMsg();
    game->reloadSocket();

    /** Animation initialization */
    PieceAnimation::setMiliSecs(10);
    //glutTimerFunc(PieceAnimation::getMiliSecs(), updateTransforms, 0);
    cout << "Update period: " << PieceAnimation::getMiliSecs() << endl;
    setUpdatePeriod(PieceAnimation::getMiliSecs());

    /** Shaders declaration*/

}

void GameScene::display()
{
    /** Clear image and depth buffer everytime we update the scene */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /** Initialize Model-View matrix as identity (no transformation */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    /** Defines the background color */
    glClearColor(0.3, 0.3, 0.3, 1.0);

    /** Apply transformations corresponding to the camera position relative to the origin */
    CGFscene::activeCamera->applyView();

    /** Draw axis */
    axis.draw();

    /** Draw lights */
    light0->draw();
    light1->draw();
    light2->draw();
    light3->draw();
    light4->draw();
    light5->draw();
    light6->draw();
    light7->draw();

    /** Setting the cullface and frontface */
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    /** Draw objects */
    game->draw();

    glutSwapBuffers();
}

void GameScene::update(long t)
{
    switch (game->status)
    {
    case PICKING_1:
        cout << game->currentPlayer->getColor() << " turn to play." << endl;
        if (selectedCellID >= 0)
        {
            cout << selectedCellID << endl;
            game->firstPickedCell = selectedCellID;
            game->status = SENDING_SELECT;
            cout << "First selected cell -> " << selectedCellID << endl;
            selectedCellID = -1;
        }
        break;
    case SENDING_SELECT:
    {
        Piece * pieceInSelectedCell = game->board->findPieceInCell(game->firstPickedCell);
        if (pieceInSelectedCell == NULL)
        {
            game->status = PICKING_1;
        }
        else if (pieceInSelectedCell->getColor() != game->currentPlayer->getColor())
        {
            game->status = PICKING_1;
        }
        else
        {
            game->sendSelectMsg(pieceInSelectedCell);
            game->status = WAITING_SELECT;
        }
        break;
    }
    case WAITING_SELECT:
    {
        string msg = "";
        msg = game->socket->readMsg();

        if (msg == "")
        {
            game->status = WAITING_SELECT;
            break;
        }
        else
        {
            game->possiblePlays = game->parseSelectMsg(msg);
            game->status = PICKING_2;
            game->reloadSocket();
            break;
        }
    }
    case PICKING_2:
        if (selectedCellID >= 0)
        {
            if (selectedCellID == game->firstPickedCell)
            {
                game->status = PICKING_1;
                game->firstPickedCell = -1;
                selectedCellID = -1;
                break;
            }
            cout << selectedCellID << endl;
            game->secondPickedCell = selectedCellID;
            game->status = PLAYING;
            cout << "Second selected cell -> " << selectedCellID << endl;
            selectedCellID = -1;
        }
        break;
    case PLAYING:
    {
        for (int i = 0; i < game->possiblePlays.size(); i++)
        {
            if (game->secondPickedCell == game->possiblePlays[i]->getID())
            {
                /* Vamos mover a peça de sítio! */
                vector <int> firstPickedCellConverted = idToLinCol(game->firstPickedCell);
                vector <int> secondPickedCellConverted = idToLinCol(game->secondPickedCell);

                cout << "Creating a move..." << endl;
                Move * movingPlay = new Move(firstPickedCellConverted[0], firstPickedCellConverted[1], secondPickedCellConverted[0], secondPickedCellConverted[1], game->board->findPieceInCell(firstPickedCellConverted[0], firstPickedCellConverted[1]));

                /* Se existirem peças na célula -> finish them! */
                Piece * pieceToKill = game->board->findPieceInCell(game->possiblePlays[i]->getID());
                if (pieceToKill != NULL)
                {
                    cout << "Creating a Kill... -> Gonna kill " << pieceToKill->toLongString() << endl;
                    Kill * killingPlay = new Kill(firstPickedCellConverted[0], firstPickedCellConverted[1], secondPickedCellConverted[0], secondPickedCellConverted[1], game->board->findPieceInCell(secondPickedCellConverted[0], secondPickedCellConverted[1]));
                    game->makePlay(killingPlay);
                }

                game->makePlay(movingPlay);

                game->status = SENDING_DRAW;
                break;
            }
        }
        if (game->status == SENDING_DRAW)
            break;
        else
        {
            cerr << "Invalid play...";
            game->status = PICKING_2;
            break;
        }
    }
    case SENDING_DRAW:
        game->sendDrawMsg();
        game->status = WAITING_DRAW;
        break;
    case WAITING_DRAW:
    {
        string msg = "";
        msg = game->socket->readMsg();

        if (msg == "")
        {
            game->status = WAITING_DRAW;
            break;
        }
        else
        {
            if (game->parseDrawMsg(msg))
            {
                cout << "It's a draw. Game Over." << endl;
                game->status = DRAW;
            }
            else
            {
                cout << "No draw, game proceeds." << endl;
                game->status = SENDING_CHECKMATE_2;
            }
            game->reloadSocket();
            break;
        }
    }

    case SENDING_CHECKMATE_2:
        game->sendCheckMateMsg();
        game->status = WAITING_CHECKMATE_2;
        break;
    case WAITING_CHECKMATE_2:
    {
        string msg = "";
        msg = game->socket->readMsg();

        if (msg == "")
        {
            game->status = WAITING_CHECKMATE_2;
            break;
        }
        else
        {
            if (game->parseDrawMsg(msg))
            {
                cout << titlecase(game->currentPlayer->getColor()) << " wins. Game Over." << endl;
                if (game->currentPlayer->getColor() == "white")
                    game->status = WHITE_WIN;
                else
                    game->status = BLACK_WIN;
            }
            else
            {
                cout << "No checkmate, game proceeds." << endl;
                game->status = SENDING_CHECK_2;
            }
            game->reloadSocket();
            break;
        }
    }

    case SENDING_CHECK_2:
        game->sendCheckMsg();
        game->status = WAITING_CHECK_2;
        break;
    case WAITING_CHECK_2:
    {
        string msg = "";
        msg = game->socket->readMsg();

        if (msg == "")
        {
            game->status = WAITING_CHECK_2;
            break;
        }
        else
        {
            if (game->parseDrawMsg(msg))
            {
                cout << titlecase(game->currentPlayer->getColor()) << " are in check." << endl;
            }
            else
            {
                cout << "No check, game proceeds." << endl;
                game->status = CHANGE_PLAYER;
            }
            game->reloadSocket();
            break;
        }
    }
    case CHANGE_PLAYER:
        game->changePlayer();
        game->status = SENDING_CHECKMATE_1;
        break;
    case SENDING_CHECKMATE_1:
        game->sendCheckMateMsg();
        game->status = WAITING_CHECKMATE_1;
        break;
    case WAITING_CHECKMATE_1:
    {
        string msg = "";
        msg = game->socket->readMsg();

        if (msg == "")
        {
            game->status = WAITING_CHECKMATE_1;
            break;
        }
        else
        {
            if (game->parseDrawMsg(msg))
            {
                cout << titlecase(game->currentPlayer->getColor()) << " wins. Game Over." << endl;
                if (game->currentPlayer->getColor() == "white")
                    game->status = WHITE_WIN;
                else
                    game->status = BLACK_WIN;
            }
            else
            {
                cout << "No checkmate, game proceeds." << endl;
                game->status = SENDING_CHECK_1;
            }
            game->reloadSocket();
            break;
        }
    }
    case SENDING_CHECK_1:
        game->sendCheckMsg();
        game->status = WAITING_CHECK_1;
        break;
    case WAITING_CHECK_1:
    {
        string msg = "";
        msg = game->socket->readMsg();

        if (msg == "")
        {
            game->status = WAITING_CHECK_1;
            break;
        }
        else
        {
            if (game->parseDrawMsg(msg))
            {
                cout << titlecase(game->currentPlayer->getColor()) << " are in check." << endl;
            }
            else
            {
                cout << "No check, game proceeds." << endl;
                game->status = PICKING_1;
            }
            game->reloadSocket();
            break;
        }
    }
    }
}

GameScene::~GameScene()
{
    delete light0;
    delete light1;
    delete light2;
    delete light3;
    delete light4;
    delete light5;
    delete light6;
    delete light7;
    delete game;
}

void GameScene::initCGFLights()
{
    float light0_pos[4] = {-10.0, 12.0, -10.0, 1.0};
    light0 = new CGFlight(GL_LIGHT0, light0_pos);
    light0->enable();

    float light1_pos[4] = {10.0, -12.0, -10.0, 1.0};
    light1 = new CGFlight(GL_LIGHT1, light1_pos);
    light1->enable();

    float light2_pos[4] = {-10.0, 12.0, 10.0, 1.0};
    light2 = new CGFlight(GL_LIGHT2, light2_pos);
    light2->enable();

    float light3_pos[4] = {10.0, -12.0, 10.0, 1.0};
    light3 = new CGFlight(GL_LIGHT3, light3_pos);
    light3->enable();

    float light4_pos[4] = {-10.0, -12.0, -10.0, 1.0};
    light4 = new CGFlight(GL_LIGHT4, light4_pos);
    light4->enable();

    float light5_pos[4] = {-10.0, -12.0, 10.0, 1.0};
    light5 = new CGFlight(GL_LIGHT5, light5_pos);
    light5->enable();

    float light6_pos[4] = {10.0, 12.0, -10.0, 1.0};
    light6 = new CGFlight(GL_LIGHT6, light6_pos);
    light6->enable();

    float light7_pos[4] = {10.0, 12.0, 10.0, 1.0};
    light7 = new CGFlight(GL_LIGHT7, light7_pos);
    light7->enable();
}