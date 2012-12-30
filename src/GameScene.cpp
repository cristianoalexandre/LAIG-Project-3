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
   	float mat1_shininess = 100.0; 
	float mat1_specular[] = {0.3, 0.3, 0.3, 1.0};	/* specular reflection. */
	float mat1_diffuse[] =  {0.7, 0.7, 0.7, 1.0};	/* diffuse reflection. */
	float mat1_ambient[] =  {0.7, 0.7, 0.7, 1.0};	/* ambient reflection. */

	materialAppearance = new CGFappearance(mat1_ambient, mat1_diffuse, mat1_specular, mat1_shininess);
    textureAppearance = new CGFappearance("../textures/pyramid.jpg", GL_REPEAT, GL_REPEAT);
    tentAppearance = new CGFappearance("../textures/tent.jpg", GL_REPEAT, GL_REPEAT);
	chess1Appearance = new CGFappearance("../textures/chess1.jpg", GL_REPEAT, GL_REPEAT);
	chess2Appearance = new CGFappearance("../textures/chess2.jpg", GL_REPEAT, GL_REPEAT);
	chess3Appearance = new CGFappearance("../textures/chess3.jpg", GL_REPEAT, GL_REPEAT);
	

    /** Object initialization */
    /*torus = new Board();
    p = new Piece("rook", "white");
    p->moveToCell(20);
    //model1 = new Model("../models/whitePawn.obj");
	*/

    animP = new PieceAnimation();
   /* animP->setPiece(p);
    animP->setMovement(32, 1, 1);*
	
    /** Game declaration */

    player1 = new Player("white");
    player2 = new Player("black", CPU_EASY);

    game = new Game(player1, player2);
    selectedCellID = -1;

    game->socket->sendMsg("ready.\n");
    cout << "Ready? - " << game->socket->readMsg();
    game->reloadSocket();

	graphical_torus = new Torus(TORUS_INNER_RADIUS, TORUS_OUTER_RADIUS-TORUS_INNER_RADIUS,50,50);
	graphical_torus->setTexture(chess1Appearance);

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
	materialAppearance->apply();
	glPushMatrix();
		glScaled(SCALING_FACTOR, SCALING_FACTOR, SCALING_FACTOR);
		graphical_torus->draw();
		game->draw(); //GAME � sempre a ultima coisa a ser feito no draw pois � aplicada uma mask para as cell serem invisiveis.
	glPopMatrix();

    glutSwapBuffers();
}

void GameScene::update(long t)
{
	if(game->anim != NULL){
		game->anim->update();
		
	}

    switch (game->status)
    {
    case PICKING_1:
		if(game->currentPlayer->getType() != HUMAN)
		{
			game->status = SEND_CPU_MSG;
			break;
		}

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
        pieceInSelectedCell = game->board->findPieceInCell(game->firstPickedCell);
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
			pieceInSelectedCell->setSelected(true);
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
	case SEND_CPU_MSG:
	{
		game->sendCPUPlayMsg();
		game->status = WAITING_CPU_ANS;
		break;
	}
	case WAITING_CPU_ANS:
	{
		string msg = "";
        msg = game->socket->readMsg();

		if (msg == "")
        {
            game->status = WAITING_CPU_ANS;
            break;
        }
        else
        {
			game->cpuPlay = game->parseCPUPlayMsg(msg);
            game->status = CPU_PLAYING;
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
				pieceInSelectedCell->setSelected(false);
                break;
            }
            cout << selectedCellID << endl;
            game->secondPickedCell = selectedCellID;
            game->status = PLAYING;
            cout << "Second selected cell -> " << selectedCellID << endl;
            selectedCellID = -1;
        }
        break;
	case CPU_PLAYING:
	{
		/* Vamos mover a peça de sítio! */
		vector <int> firstPickedCellConverted = idToLinCol(game->cpuPlay[0]->getID());
		vector <int> secondPickedCellConverted = idToLinCol(game->cpuPlay[1]->getID());

		cout << "Creating a move..." << endl;
		Move * movingPlay = new Move(firstPickedCellConverted[0], firstPickedCellConverted[1], secondPickedCellConverted[0], secondPickedCellConverted[1], game->board->findPieceInCell(firstPickedCellConverted[0], firstPickedCellConverted[1]));

		/* Se existirem peças na célula -> finish them! */
		Piece * pieceToKill = game->board->findPieceInCell(game->cpuPlay[1]->getID());
        if (pieceToKill != NULL)
        {
			cout << "Creating a Kill... -> Gonna kill " << pieceToKill->toLongString() << endl;
            Kill * killingPlay = new Kill(firstPickedCellConverted[0], firstPickedCellConverted[1], secondPickedCellConverted[0], secondPickedCellConverted[1], game->board->findPieceInCell(secondPickedCellConverted[0], secondPickedCellConverted[1]));
            game->makePlay(killingPlay);
        }

        game->makePlay(movingPlay);


	}
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
        if (game->status == SENDING_DRAW){
			pieceInSelectedCell->setSelected(false);
            break;
		}else{
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
    /* Light positions */
	float light0_pos[4] = {0.0, 0.0, 0.0, 1.0};
	float light1_pos[4] = {0.0, 18.0, 0.0, 1.0};
	float light2_pos[4] = {-12.0, 12.0, -12.0, 1.0};
	float light3_pos[4] = {-12.0, 12.0, 12.0, 1.0};
	float light4_pos[4] = {12.0, -12.0, 12.0, 1.0};
	float light5_pos[4] = {12.0, -12.0, -12.0, 1.0};
	float light6_pos[4] = {-12.0, -12.0, -12.0, 1.0};
	float light7_pos[4] = {-12.0, -12.0, 12.0, 1.0};

	/* light values - same for every light */
	float ambient[] =   {2.0, 2.0, 2.0, 1.0}; // sem componente ambiente
	float diffuse[] =   {6.0, 6.0, 6.0, 1.0};
	float specular[] =  {6.0, 6.0, 6.0, 1.0};
	float kc = 0.0;
	float kl = 1.0;
	float kq = 0.0;
	GLfloat dir[3] = {-1.0,0.0,-1.0};

	light0 = new CGFlight(GL_LIGHT0, light0_pos);
	light0->setAmbient(ambient);
	light0->setDiffuse(diffuse);
	light0->setSpecular(specular);
	light0->setKc(kc);
	light0->setKl(kl);
	light0->setKq(kq);
	light0->enable();

	light1 = new CGFlight(GL_LIGHT1, light1_pos);
	light1->setAmbient(ambient);
	light1->setDiffuse(diffuse);
	light1->setSpecular(specular);
	light1->setKc(kc);
	light1->setKl(kl);
	light1->setKq(kq);
	light1->enable();

	light2 = new CGFlight(GL_LIGHT2, light2_pos);
	light2->setAmbient(ambient);
	light2->setDiffuse(diffuse);
	light2->setSpecular(specular);
	light2->setKc(kc);
	light2->setKl(kl);
	light2->setKq(kq);
	light2->enable();

	light3 = new CGFlight(GL_LIGHT3, light3_pos);
	light3->setAmbient(ambient);
	light3->setDiffuse(diffuse);
	light3->setSpecular(specular);
	light3->setKc(kc);
	light3->setKl(kl);
	light3->setKq(kq);
	light3->enable();

	light4 = new CGFlight(GL_LIGHT4, light4_pos);
	light4->setAmbient(ambient);
	light4->setDiffuse(diffuse);
	light4->setSpecular(specular);
	light4->setKc(kc);
	light4->setKl(kl);
	light4->setKq(kq);
	light4->enable();

	light5 = new CGFlight(GL_LIGHT5, light5_pos);
	light5->setAmbient(ambient);
	light5->setDiffuse(diffuse);
	light5->setSpecular(specular);
	light5->setKc(kc);
	light5->setKl(kl);
	light5->setKq(kq);
	light5->enable();

	light6 = new CGFlight(GL_LIGHT6, light6_pos);
	light6->setAmbient(ambient);
	light6->setDiffuse(diffuse);
	light6->setSpecular(specular);
	light6->setKc(kc);
	light6->setKl(kl);
	light6->setKq(kq);
	light6->enable();

	light7 = new CGFlight(GL_LIGHT7, light7_pos);
	light7->setAmbient(ambient);
	light7->setDiffuse(diffuse);
	light7->setSpecular(specular);
	light7->setKc(kc);
	light7->setKl(kl);
	light7->setKq(kq);
	light7->enable();
}

void GameScene::activateTexture(int i){


	switch(i)
	{
	case 0:
		{
			graphical_torus->setTexture(chess1Appearance);
			//illumination->setBaseTexture("../textures/chess1.jpg");
			break;
		}
	case 1:
		{
			graphical_torus->setTexture(chess2Appearance);
			//illumination->setBaseTexture("../textures/chess2.jpg");
			break;
		}
	case 2:
		{
			graphical_torus->setTexture(chess3Appearance);

			//illumination->setBaseTexture("../textures/chess3.jpg");
			break;
		}
	}
}