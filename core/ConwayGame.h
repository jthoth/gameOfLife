//
// Created by thoth on 11/16/19.
//

#ifndef GAMEOFLIFE_CONWAYGAME_H
#define GAMEOFLIFE_CONWAYGAME_H
#include <CL/cl.hpp>

class ConwayGame {
private:
    bool *grid, *mask, parallel = false;
    int getTotalNeighbors(int x, int y);
    cl::Program program;
    cl::Context context;
    cl::Device device;

public:
    int xCells, yCells;
    ConwayGame(int xCells, int yCells);
    ~ConwayGame();
    void initialization(double prob);
    static int get(int coord, int axis);
    static bool computeRules(int neighbours, bool stateCell);
    void iterRules();
    bool getCell(int x, int y);
    void serialUpdate();
    void parallelUpdate();
    void runParallel(std::string kernelFile);

};


#endif //GAMEOFLIFE_CONWAYGAME_H
