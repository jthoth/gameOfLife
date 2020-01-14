//
// Created by thoth on 1/7/20.
//

#include <string>
#include "CpuVsGpu.h"
#include "../core/ConwayGame.h"
#include <iostream>
#include <sstream>
#include <chrono>

CpuVsGpu::CpuVsGpu(const std::string& file) {
    this->connection.open(file.c_str(), std::ios::out);
    this->connection << "device,x,y,seconds\n";
}

void CpuVsGpu::operator()(int xCells, int yCells) {
    ConwayGame cpu(xCells, yCells), gpu(xCells, yCells);
    cpu.initialization(.1); gpu.initialization(.1);
    gpu.runParallel("../kernels/ConwayGame.cl");
    save(xCells, yCells, cpu, "cpu");
    save(xCells, yCells, gpu, "gpu");
}

void CpuVsGpu::save(int xCells, int yCells, ConwayGame &game, char *device) {
    std::ostringstream line;
    line << device <<","<< xCells <<","<< yCells
         <<","<< computeElapsed(game)<< '\n';
    this->connection << line.str();
}

double CpuVsGpu::computeElapsed(ConwayGame &game) {
    auto start = std::chrono::steady_clock::now();
    game.iterRules();
    auto end =  std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>
            (end - start).count()/1e6;
}

CpuVsGpu::~CpuVsGpu() {
    this->connection.close();
}