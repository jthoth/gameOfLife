//
// Created by thoth on 11/16/19.
//
#  include <GL/gl.h>
#include "../serial/ConwayGame.h"

#ifndef GAMEOFLIFE_WINDOWS_H
#define GAMEOFLIFE_WINDOWS_H


class Windows {

private:

    ConwayGame game;
    const GLfloat left = 0.0, right = 1.0;
    const GLfloat bottom = 1.0, top = 0.0;
    GLint width, height;
    static void reload();

public:

    Windows(GLint width, GLint height, ConwayGame& game);
    ~Windows();
    void reshape(int w, int h);
    void display();
    void draw(GLfloat xSize, GLfloat ySize);
    void drawRadius(GLint i, GLint j, GLfloat xSize, GLfloat ySize);
};


#endif //GAMEOFLIFE_WINDOWS_H
