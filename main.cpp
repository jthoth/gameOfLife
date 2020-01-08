#include "core/ConwayGame.h"
#include "view/Windows.h"
#include "benchmark/CpuVsGpu.h"

#include <GL/glut.h>
#include <iostream>
#include <cmath>

ConwayGame *game;
Windows *windows;

void update(int value) {
    game->iterRules(); glutPostRedisplay();
    glutTimerFunc(16, update, value);
}

void display() {windows->display();}

void reshape(int w, int h) {windows->reshape(w, h);}

void benchmark(){
    std::cout << "Init Benchmark .... ";
    CpuVsGpu benchmark("openCl.csv");
    for (int i = 6; i < 15; i++) {
        for (int j = 6; j < 15; j++) {
            benchmark(pow(2, i), pow(2, j));
        }
    }
    std::cout << "End of Benchmark !";
}

void visualization(int argc, char **argv){
    game = new ConwayGame(300, 300);
    game->runParallel("../kernels/ConwayGame.cl");
    glutInit(&argc, argv);
    game->initialization(.1);
    windows = new Windows(600, 600, *game);
    glutReshapeFunc(reshape); glutDisplayFunc(display);
    update(0); glutMainLoop();

}

int main(int argc, char **argv){

    visualization(argc, argv);
//    benchmark();

    return 0;
}

