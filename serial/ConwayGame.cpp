//
// Created by thoth on 11/16/19.
//

#include <ctime>
#include <cstdlib>
#include <array>
#include <iostream>
#include "ConwayGame.h"


ConwayGame::ConwayGame(const int xCells, const int yCells):
xCells(xCells), yCells(yCells),
grid(new bool *[xCells]), mask(new bool *[xCells]){
    for (size_t i = 0; i < xCells; ++i) {
        grid[i] = new bool[yCells]; mask[i] = new bool[yCells];
    }
    this->xDomain = new int [3]; this->yDomain = new int [3];
    srand((unsigned)time(NULL));

}



int ConwayGame::getTotalNeighbors(const int x, const int y) {
    return grid[x][(y - 1)%yCells] + grid[x][(y + 1)%yCells] +
           grid[getWrapCell((x - 1), xCells)][y] + grid[(x + 1)%xCells][y] +
           grid[getWrapCell((x - 1), xCells)][getWrapCell((y - 1), yCells)] +
           grid[getWrapCell((x - 1), xCells)][(y + 1)%yCells] +
           grid[(x + 1)%xCells][getWrapCell((y - 1), yCells)] +
           grid[(x + 1)%xCells][(y + 1)%yCells];
}

ConwayGame::~ConwayGame() {
    for (size_t i = 0; i < this->xCells; ++i) {
        delete [] grid[i]; delete [] mask[i];
    }
    delete [] grid; delete [] mask;
    delete [] xDomain; delete [] yDomain;
}

void ConwayGame::initialization(const double prob) {
    for(size_t i = 0; i < this->xCells; ++i) {
        for(size_t j = 0; j < this->yCells; ++j) {
            double r = (double)rand() / RAND_MAX;
            grid[i][j] = (r < prob);
        }
    }
}

void ConwayGame::iterRules() {
    for (size_t i = 0; i < this->xCells; ++i) {
        for (size_t j = 0; j < this->yCells; ++j) {
            this->mask[i][j] = computeRules(
                    this->getTotalNeighbors(i, j),
                    this->grid[i][j]);
        }
    }
    std::swap(this->mask, this->grid);
}

bool ConwayGame::getCell(const int x, const int y) {
    return this->grid[x][y];
}

bool ConwayGame::computeRules(int neighbours, bool stateCell) {
    if(stateCell){
        return neighbours == 3 || neighbours == 2;
    }
    return neighbours == 3;
}

int ConwayGame::getWrapCell(int coord, int axis) {
    return (axis + (coord % axis)) % axis;
}
