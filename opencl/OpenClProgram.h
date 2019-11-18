//
// Created by thoth on 11/17/19.
//

#ifndef GAMEOFLIFE_OPENCLPROGRAM_H
#define GAMEOFLIFE_OPENCLPROGRAM_H


#include <string>
#include <CL/cl.hpp>

class OpenClProgram {
private:
    std::string kernel;

public:
    OpenClProgram(std::string kernel);
    ~OpenClProgram();
    static cl::Platform getPlatform();
    cl::Device getDevice();
    std::string getSource();
    cl::Program operator()();
};


#endif //GAMEOFLIFE_OPENCLPROGRAM_H
