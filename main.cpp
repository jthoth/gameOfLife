#include "serial/ConwayGame.h"
#include "view/Windows.h"

#  include <GL/glut.h>

ConwayGame game(100, 100);
Windows *windows;

void update(int value) {
    game.iterRules();
    glutPostRedisplay();
    glutTimerFunc(1000 /24, update, 0);
}

void display() {
    windows->display();
}

void reshape(int w, int h) {
    windows->reshape(w, h);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    game.initialization(.1);
    windows = new Windows(600, 600, game);

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);

    update(0);
    glutMainLoop();

    return 0;
}
