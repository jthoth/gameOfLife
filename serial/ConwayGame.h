//
// Created by thoth on 11/16/19.
//

#ifndef GAMEOFLIFE_CONWAYGAME_H
#define GAMEOFLIFE_CONWAYGAME_H


class ConwayGame {
private:
    bool** grid, ** mask;
    int *xDomain, *yDomain;
    int getTotalNeighbors(int x, int y);

public:
    int xCells, yCells;
    ConwayGame(int xCells, int yCells);
    ~ConwayGame();
    void initialization(double prob);
    int getWrapCell(int coord, int axis);
    static bool computeRules(int neighbours, bool stateCell);
    void iterRules();
    bool getCell(int x, int y);
};


#endif //GAMEOFLIFE_CONWAYGAME_H
