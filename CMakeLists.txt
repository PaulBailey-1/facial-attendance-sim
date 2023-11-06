cmake_minimum_required(VERSION 3.18)

project(Facial-Attendence-Sim)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "-O2")

set(SRCS
    src/main.cpp
   )

add_executable(fasim ${SRCS})
# target_link_libraries( fasim )
