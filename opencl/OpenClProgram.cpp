//
// Created by thoth on 11/17/19.
//

#include "OpenClProgram.h"
#include <utility>
#include <CL/cl.hpp>
#include <fstream>
#include <iostream>

OpenClProgram::OpenClProgram(std::string kernel) : kernel(std::move(kernel)) {}

cl::Platform  OpenClProgram::getPlatform(){
    std::vector<cl::Platform> platforms;
    cl::Platform::get(&platforms);
    return platforms.front();
}

cl::Device OpenClProgram::getDevice(){
    auto platform = this->getPlatform();
    std::vector<cl::Device> devices;
    platform.getDevices(CL_DEVICE_TYPE_GPU, &devices);
    return devices.front();
}

std::string OpenClProgram::getSource(){
    std::ifstream kernelFile(this->kernel);
    std::string source(std::istreambuf_iterator<char>(kernelFile),
                       (std::istreambuf_iterator<char>()));
    return  source;
}

cl::Program OpenClProgram::operator()() {
    auto device = this->getDevice();
    auto source = this->getSource();
    cl::Program::Sources sources( 1,
            std::make_pair(source.c_str(),
            source.length() + 1));
    cl::Context context({device});
    cl::Program program(context, source);
    program.build("-cl-std=CL1.2");
    return program;
}

OpenClProgram::~OpenClProgram() {}
