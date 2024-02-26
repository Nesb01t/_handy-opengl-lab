//
// Created by nes on 24-2-26.
//
#include "glsl-reader.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include "log.h"

std::string readShader(const std::string& path)
{
    std::ifstream file;
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        file.open(path);
        std::stringstream stream;
        stream << file.rdbuf();
        file.close();
        log(stream.str());
        return stream.str();
    }
    catch (std::ifstream::failure& e)
    {
        std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    return "";
}
