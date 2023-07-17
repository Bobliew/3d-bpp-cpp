add_library(cubeBpp OBJECT ./objects/objects.cc ./algorithms/cubeGenAlgorithm.cc)
target_include_directories(cubeBpp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_options(cubeBpp PRIVATE -Wall -Wextra -pedantic)
