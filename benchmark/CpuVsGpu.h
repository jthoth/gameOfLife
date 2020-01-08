//
// Created by thoth on 1/7/20.
//

#ifndef GAMEOFLIFE_CPUVSGPU_H
#define GAMEOFLIFE_CPUVSGPU_H

#include <fstream>
#include "../core/ConwayGame.h"

class CpuVsGpu {
private:
    std::fstream connection;

public:
    explicit CpuVsGpu(const std::string& fileOutput);
    ~CpuVsGpu();
    static double computeElapsed(ConwayGame &game);
    void operator()(int xCells, int yCells);
    void save(int xCells, int yCells, ConwayGame &cpu, char *device);
};


#endif //GAMEOFLIFE_CPUVSGPU_H
