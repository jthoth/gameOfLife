//
// Created by thoth on 11/16/19.
//

#include <ctime>
#include <cstdlib>
#include <array>
#include <utility>
#include "ConwayGame.h"
#include "../opencl/OpenClProgram.h"


cl_mem_flags  INPUT_MEM = CL_MEM_READ_ONLY | CL_MEM_HOST_NO_ACCESS | CL_MEM_COPY_HOST_PTR;
cl_mem_flags  OUTPUT_MEM =  CL_MEM_WRITE_ONLY | CL_MEM_HOST_READ_ONLY;


ConwayGame::ConwayGame(const int xCells, const int yCells):
xCells(xCells), yCells(yCells),
grid(new bool [xCells * yCells]), mask(new bool [xCells * yCells]){
    srand((unsigned)time(NULL));
}

int ConwayGame::getTotalNeighbors(const int x, const int y) {
    return grid[(y - 1)%yCells + x * yCells] + grid[(y + 1)%yCells + x*yCells] +
           grid[y + get((x - 1), xCells) * yCells] +
           grid[y + (x + 1)%xCells * yCells] +
           grid[get((y - 1), yCells) +
                   get((x - 1), xCells) * yCells] +
           grid[(y + 1)%yCells + get((x - 1), xCells) * yCells] +
           grid[get((y - 1), yCells) + (x + 1) % xCells * yCells] +
           grid[(y + 1)%yCells + (x + 1)%xCells * yCells];
}

ConwayGame::~ConwayGame() {
    delete [] grid; delete [] mask;
    cl::finish();
}

void ConwayGame::initialization(const double prob) {
    for(size_t i = 0; i < this->xCells; ++i) {
        for(size_t j = 0; j < this->yCells; ++j) {
            double r = (double)rand() / RAND_MAX;
            grid[j + i * yCells] = (r < prob);
        }
    }
}

void ConwayGame::iterRules() {
    if(this->parallel)
        parallelUpdate();
    else
        serialUpdate();
}

void ConwayGame::serialUpdate() {
    for (size_t i = 0; i < xCells; ++i) {
        for (size_t j = 0; j < yCells; ++j) {
            mask[j + i * yCells] = computeRules(
                    getTotalNeighbors(i, j),
                    grid[j + i * yCells] );
        }
    }
    std::swap(mask, grid);
}

void ConwayGame::parallelUpdate() {

    size_t  size = xCells * yCells;

    cl::Buffer inGrid(context, INPUT_MEM, size, grid);
    cl::Buffer outMask(context, OUTPUT_MEM, size);


    cl::Kernel kernel(program, "ConwayGame");

    kernel.setArg(0, inGrid); kernel.setArg(1, outMask);
    kernel.setArg(2, sizeof(int), &xCells);
    kernel.setArg(3, sizeof(int), &yCells);


    cl::CommandQueue queue(context, device);
    queue.enqueueNDRangeKernel(kernel, cl::NullRange,
            cl::NDRange(xCells, yCells));

    queue.enqueueReadBuffer(outMask, CL_FALSE, 0, size, mask);


    std::swap(mask, grid);
}

bool ConwayGame::getCell(const int x, const int y) {
    return this->grid[y + x * yCells];
}

bool ConwayGame::computeRules(int neighbours, bool stateCell) {
    if(stateCell){
        return neighbours == 3 || neighbours == 2;
    }
    return neighbours == 3;
}

int ConwayGame::get(int coord, int axis) {
    return (axis + (coord % axis)) % axis;
}

void ConwayGame::runParallel(std::string kernelFile) {
    OpenClProgram objProgram(std::move(kernelFile));
    this->program = objProgram();
    this->parallel = true;
    context = this->program.getInfo<CL_PROGRAM_CONTEXT>();
    auto devices = this->program.getInfo<CL_PROGRAM_DEVICES>();
    device = devices.front();
}