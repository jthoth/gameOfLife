//
// Created by thoth on 11/17/19.
//

#include <iostream>
#include "ConwayGameCl.h"
#include "OpenClProgram.h"


ConwayGameCl::ConwayGameCl(std::string kernelFile){
    OpenClProgram objProgram(kernelFile);
    this->program = objProgram();
}

ConwayGameCl::~ConwayGameCl() {}

void ConwayGameCl::operator()() {
    auto context = this->program.getInfo<CL_PROGRAM_CONTEXT>();
    auto devices = this->program.getInfo<CL_PROGRAM_DEVICES>();
    auto &device = devices.front();


    char buff[5];
    cl::Buffer memBuf(context, CL_MEM_WRITE_ONLY | CL_MEM_HOST_READ_ONLY, sizeof(buff));
    cl::Kernel kernel(program, "ConwayGame");
    kernel.setArg(0, memBuf);

    cl::CommandQueue queue(context, device);
    queue.enqueueTask(kernel);
    queue.enqueueReadBuffer(memBuf, CL_TRUE, 0, sizeof(buff), buff);
    std::cout << buff;
}
