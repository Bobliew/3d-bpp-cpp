add_library(cubeBpp OBJECT ./objects/objects.cc ./algorithms/cubeGenAlgorithm.cc)
find_package(Boost REQUIRED COMPONENTS thread)



target_link_libraries(cubeBpp PRIVATE Boost::thread)
target_include_directories(cubeBpp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_options(cubeBpp PRIVATE -Wall -Wextra -pedantic)





