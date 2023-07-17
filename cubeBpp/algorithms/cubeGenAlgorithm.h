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

class Utils {
public:
    void GenSimpleBlock(const Box& container,
                        const std::vector<Box>& boxList,
                        const std::vector<int>& num, 
                        std::vector<Block>& blockTable,
                        const int& size
                        );

    void GenComplexBlock(const Box& container,
                         const std::vector<Box>& boxList,
                         std::vector<int>& num,
                         std::vector<Block>& blockTable,
                         const int& maxLevel,
                         const float& minFillRate,
                         const float& minAreaRate,
                         int size
                        );
    
    void genResidualSpace(const Box& space, 
                          const Block& block, 
                          std::stack<Box>& spaceStack);

    void transferSpace(std::stack<Box>& spaceStack);
 
    std::vector<Block> genBlockList(Box& space,
                                    std::vector<int>& num,
                                    const std::vector<Box>& boxList,
                                    int& isComplex,

                                    int size);
    Plan basicHeuristic(Box& container,
                        std::vector<int>& avail,
                        const std::vector<Box>& boxList, 
                        int isComplex);

    Plan outLoop(int ts, 
                 const float& tf, 
                 const float& dt, 
                 int loopTime, 
                 int isComplex, 
                 int isLinear,
                 Box& container, 
                 std::vector<int>& avail, 
                 std::vector<Box>& boxList);

    void gen3ddata(std::vector<Box>& boxList, 
                   int tag, 
                   int L, 
                   int W, 
                   int H);

private:
    //int size; 考虑储存在util
};




#endif
