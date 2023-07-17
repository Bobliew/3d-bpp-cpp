cmake_minimum_required(VERSION 3.0)
project(cubeBpptest)
add_executable(cubeBpptest ./test/bppCube.cc)
add_subdirectory(cubeBpp)
target_link_libraries(cubeBpptest cubeBpp)



