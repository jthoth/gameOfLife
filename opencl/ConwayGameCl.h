//
// Created by thoth on 11/17/19.
//

#ifndef GAMEOFLIFE_CONWAYGAMECL_H
#define GAMEOFLIFE_CONWAYGAMECL_H


#include <string>
#include <CL/cl.hpp>

class ConwayGameCl {

private:
    cl::Program program;

public:
    ConwayGameCl(std::string kernelFile);
    ~ConwayGameCl();
    void operator()();
};


#endif //GAMEOFLIFE_CONWAYGAMECL_H


/*
 *
void openClImplementation(){

    auto context = program.getInfo<CL_PROGRAM_CONTEXT>();
    auto devices = program.getInfo<CL_PROGRAM_DEVICES>();
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
 * */