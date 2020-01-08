//
// Created by thoth on 11/16/19.
//

#include <GL/glu.h>
#include <GL/glut.h>
#include "Windows.h"
#include "../core/ConwayGame.h"

#define WHITE 1.0, 1.0, 1.0
#define BLACK 0.0, 0.0, 0.0

Windows::Windows(GLint width, GLint height, ConwayGame& game):
width(width), height(height), game(game){
    glutInitWindowSize(this->width, this->height);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Game of Life");
    glClearColor(1, 1, 1, 1);
}

void Windows::reshape(int w, int h){
    this->width = w; this->height = h;
    glViewport(0, 0, this->width, this->height);
    glMatrixMode(GL_PROJECTION); glLoadIdentity();
    gluOrtho2D(this->left, this->right,this->bottom,
            this->top);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity(); glutPostRedisplay();
}

void Windows::reload(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
}

void Windows::display() {
    this->reload();
    GLfloat xSize = (this->right - this->left) / game.xCells;
    GLfloat ySize = (this->top - this->bottom) / game.yCells;
    this->draw(xSize, ySize);
    glEnd(); glFlush();
    glutSwapBuffers();
}

Windows::~Windows() {}

void Windows::drawRadius(GLint i, GLint j, GLfloat xSize, GLfloat ySize){
    game.getCell(i, j) ? glColor3f(BLACK):glColor3f(WHITE);
    glVertex2f(i * xSize + left,    j * ySize + bottom);
    glVertex2f((i + 1.0) * xSize + left,    j * ySize + bottom);
    glVertex2f((i + 1.0) * xSize + left,(j + 1.0) * ySize + bottom);
    glVertex2f(i * xSize + left, (j + 1.0)* ySize + bottom);
}

void Windows::draw(GLfloat xSize, GLfloat ySize) {
    glBegin(GL_QUADS);
    for (GLint i = 0; i < game.xCells; ++i) {
        for (GLint j = 0; j < game.yCells; ++j) {
            this->drawRadius(i, j, xSize, ySize);
        }
    }
}

