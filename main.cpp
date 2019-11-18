#include "serial/ConwayGame.h"
#include "view/Windows.h"
#include "opencl/ConwayGameCl.h"

#include <GL/glut.h>
#include <iostream>

ConwayGame game(300, 300);
Windows *windows;

void update(int value) {
    game.iterRules(); glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

void display() {windows->display();}

void reshape(int w, int h) { windows->reshape(w, h);}

void serialImplementation(int argc, char **argv){
    glutInit(&argc, argv);
    game.initialization(.1);
    windows = new Windows(600, 600, game);
    glutReshapeFunc(reshape); glutDisplayFunc(display);
    update(0); glutMainLoop();
}

void openClImplementation(){

    ConwayGameCl objGame("../kernels/ConwayGame.cl");
    objGame();

}

void cuImplementation(){
    //TODO Implementation
}

void benchmark(){
    //TODO Comparision
}

int main(int argc, char **argv)
{
    serialImplementation(argc, argv);

    return 0;
}

