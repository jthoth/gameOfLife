//
// Created by thoth on 1/7/20.
//

#include <string>
#include "CpuVsGpu.h"
#include "../core/ConwayGame.h"
#include <sys/time.h>
#include <iostream>
#include <sstream>

typedef unsigned long long timestamp_t;

static timestamp_t get_timestamp (){
    struct timeval now;  gettimeofday (&now, NULL);
    return  now.tv_usec + (timestamp_t)now.tv_sec * 1000000;
}

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

void CpuVsGpu::save(int xCells, int yCells, ConwayGame &cpu, char *device) {
    std::ostringstream line;
    line << device <<","<< xCells <<","<< yCells
         <<","<< computeElapsed(cpu)<< '\n';
    this->connection << line.str();
}

double CpuVsGpu::computeElapsed(ConwayGame &game) {
    timestamp_t t0 = get_timestamp();
    game.iterRules();
    timestamp_t t1 = get_timestamp();
    return (t1 - t0) / 1000000.0L;
}

CpuVsGpu::~CpuVsGpu() {
    this->connection.close();
}