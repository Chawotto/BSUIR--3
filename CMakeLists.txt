cmake_minimum_required(VERSION 3.29)
project(MorrS)

set(CMAKE_CXX_STANDARD 20)

add_executable(MorrS main.cpp
        user_interfaces.cpp
        user_interfaces.h
        dev_opt.cpp
        dev_opt.h
        gam_opt.cpp
        gam_opt.h
)
