#pragma once
#ifndef _PURE_KLEPTOMANIA
#define _PURE_KLEPTOMANIA

#include "COLLECTIONS.h"
#include "KEYBOARD.h"
#include "RENDERER.h"

using namespace kyb;
using namespace std;

double WIDTH = 600;
double HEIGHT = 600;

int viewPortCenter[2] = {0,0};

unsigned int initSize[2] = {1,1};
world DAN(initSize);
player nathan(DAN);

renderer scene;

counter timer;
int cycles = 0;

void calculateViewPort(player character)
{
	viewPortCenter[0] = character.getPositionX() - WIDTH/2;
	viewPortCenter[1] = character.getPositionY() - HEIGHT/2;
}

void updateViewPort(player character)
{
	if((character.getPositionX() - viewPortCenter[0]) > 0.75*WIDTH)
		viewPortCenter[0] += character.getSpeed(); 
	else if((character.getPositionX() - viewPortCenter[0]) < 0.25*WIDTH)
		viewPortCenter[0]-= character.getSpeed(); 
	if((character.getPositionY() - viewPortCenter[1]) > 0.75*HEIGHT)
		viewPortCenter[1]+= character.getSpeed(); 
	else if((character.getPositionY() - viewPortCenter[1]) < 0.25*HEIGHT)
		viewPortCenter[1]-= character.getSpeed(); 
}

void display(void)
{
	glClearColor(0,0,0.1,0);
	glutInitDisplayMode(GL_DEPTH | GL_DOUBLE | GL_RGBA);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	glLoadIdentity();
	
	gluOrtho2D(viewPortCenter[0], WIDTH + viewPortCenter[0], viewPortCenter[1], HEIGHT + viewPortCenter[1]);
	glViewport(0,0,WIDTH, HEIGHT);

	updateViewPort(nathan);

	glPointSize(62);

	//glBegin(GL_POINTS);
	//glColor3f(0,1,0);
	//glVertex2i(nathan.getPositionX(), nathan.getPositionY());
	//glEnd();
	scene.render();

	glBindTexture(GL_TEXTURE_2D, scene.textureData.getTexture());

	float textureCoords[] = {0,0, 1,0, 0,1, 0,1, 1,1, 1,0};
	float playerPos[] = {nathan.getPositionX()-32,nathan.getPositionY()-32,
		nathan.getPositionX()+32,nathan.getPositionY()-32,
		nathan.getPositionX()-32,nathan.getPositionY()+32,
		nathan.getPositionX()-32,nathan.getPositionY()+32,
		nathan.getPositionX()+32,nathan.getPositionY()+32,
		nathan.getPositionX()+32,nathan.getPositionY()-32};
	float playerCol[] = {1,1,0, 1,1,0, 0,1,1, 0,1,1, 1,0,1, 1,0,1};

	//cout << scene.textureData.texture[0] << endl;
	glVertexPointer(2, GL_FLOAT, 0, playerPos);
	glColorPointer(3, GL_FLOAT, 0, playerCol);
	glTexCoordPointer(2, GL_FLOAT, 0, textureCoords);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glutPostRedisplay();
	glutSwapBuffers();
	glFlush();
}

void reshape(int x, int y)
{
	WIDTH = x, HEIGHT = y;
	calculateViewPort(nathan);
}

void idle(void)
{
	nathan.setSpeed(4);
	nathan = menuStates(nathan, DAN);
	//if(1 < cycles)
	//{
	//	nathan = menuStates(nathan, DAN);
	//	cycles = 0;
	//}
	//else cycles++;
	//timer.updateSystem();
}

void populateWorld(unsigned int txtFileSize[])
{
        string fname = "world.txt";
        string line;
        ifstream infile;

        unsigned int lineNum = 0;

        unsigned int size[] = {0,txtFileSize[1]};

        infile.open(fname);

        while(!infile.eof())
        {

                getline(infile,line);

                cout<<line<<endl;

                for (size_t i = 0; i < line.size(); i++)
                {

                        char n = line[i];

                        //cout<<"char"<<n<<endl;

                        if (n=='0'){
                                DAN.setTileLocation(size, 0);
                                size[0]++;
                                //cout<<"i should be in here 0"<<endl;
                        }
                        else if(n=='1')
                        {
                                DAN.setTileLocation(size, 1);        
                                size[0]++;
                                //cout<<"i should be in here 1"<<endl;
                        }
                }
                size[0] = 0;
                size[1]--;
        }

infile.close();
}

void main(int argv, char* argc[])
{
		resetKeys();

        tile block;
        object newBlock;

        unsigned int size[] = {5,5};

        //size of text file rows,columns
        unsigned int txtFileSize[] = {50,50};

        DAN.changePlayerStart(size);
        player greg(DAN);
        nathan = greg;

        block.changeDescription("HOORAY");
        block.changePassThrough(true);

        DAN.changeDimension(txtFileSize);

        DAN.addTile(block);
        DAN.printLog();

        populateWorld(txtFileSize);

		scene.worldToArray(DAN, 64);

        glutInit(&argv, argc);
        glutInitWindowSize(600,600);
        glutCreateWindow("Pure Kleptomania");
        glutDisplayFunc(display);
        glutIdleFunc(idle);
        glutReshapeFunc(reshape);
        glutKeyboardFunc(keyboardInput);
        glutKeyboardUpFunc(keyRelease);
        glutMainLoop();
}

#endif