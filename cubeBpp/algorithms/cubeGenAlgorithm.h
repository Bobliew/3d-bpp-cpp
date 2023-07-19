#ifndef CUBEGEN
#define CUBEGEN

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <stdlib.h>
#include <stack>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <random>
#include "../objects/objects.h"
#include <boost/thread.hpp>
#include <memory>

class Utils {
public:
    void GenSimpleBlock(const Box& container,
                        const std::vector<Box>& boxList,
                        const std::vector<float>& num, 
                        std::vector<Block>& blockTable,
                        const float& size
                        );

    void GenComplexBlock(const Box& container,
                         const std::vector<Box>& boxList,
                         std::vector<float>& num,
                         std::vector<Block>& blockTable,
                         const float& maxLevel,
                         const float& minFillRate,
                         const float& minAreaRate,
                         float size
                        );
    
    void genResidualSpace(const Box& space, 
                          const Block& block, 
                          std::stack<Box>& spaceStack);

    void transferSpace(std::stack<Box>& spaceStack);
 
    std::vector<Block> genBlockList(Box& space,
                                    std::vector<float>& num,
                                    const std::vector<Box>& boxList,
                                    const float& isComplex,

                                    float size);
    Plan* basicHeuristic(const Box& container,
                        const std::vector<float>& avail,
                        const std::vector<Box>& boxList, 
                        const float& isComplex);

    Plan outLoop(const float& loopTime, 
                 const float& isComplex, 
                 Box& container, 
                 std::vector<float>& avail, 
                 std::vector<Box>& boxList);

    void gen3ddata(std::vector<Box>& boxList, 
                   float tag, 
                   float L, 
                   float W, 
                   float H);

private:
    //float size; 考虑储存在util
};




#endif
