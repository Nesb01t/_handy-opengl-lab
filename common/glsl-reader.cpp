//
// Created by nes on 24-2-26.
//
#include "glsl-reader.h"
#include <sstream>
#include <iostream>
#include <fstream>

std::string readShader(const char* path)
{
    std::ifstream file(path);
    if (!file) return {};

    file.ignore(std::numeric_limits<std::streamsize>::max());
    auto size = file.gcount();

    if (size > 0x10000) // 64KiB sanity check for shaders:
        return {};

    file.clear();
    file.seekg(0, std::ios_base::beg);

    std::stringstream sstr;
    sstr << file.rdbuf();
    file.close();

    return sstr.str();
}
