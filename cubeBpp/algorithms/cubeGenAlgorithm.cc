#include "./cubeGenAlgorithm.h"
#include "../objects/objects.h"
// #include <boost/compute.hpp>
#include <boost/thread.hpp>

void Utils::GenSimpleBlock(const Box& container, const std::vector<Box>& boxList,
                    const std::vector<float>& num, std::vector<Block>& blockTable,
                    const float& size
                   ) {
    blockTable.clear();
    // 遍历boxlist中
    for (const Box& box : boxList) {
        float iOne = num[box.getType()];
        for (float nx = 1; nx <= num[iOne]; ++nx) {
            // std::cout << num[box.getType()] << "\n";
            float iTwo = iOne / nx;
            for (float ny = 1; ny <= iTwo; ++ny) {
                // std::cout << num[box.getType()] / nx << "\n";
                float iThree = iTwo / ny;
                for (float nz = 1; nz <= iThree; ++nz) {
                    // std::cout << num[box.getType()] / nx / ny<< "\n";
                    if (// 约束1：不能超过container的尺寸；
                        box.getLength() * nx <= container.getLength() &&
                        box.getWidth() * ny <= container.getWidth() &&
                        box.getHeight() * nz <= container.getHeight()
                        //
                        ) {
                        //std::cout <<"ny: " <<ny << "\n";
                        Block block = { nx, // x方向添加了多少个最简单块
                                        ny, // y方向添加了多少个最简单块
                                        nz, // z方向添加了多少个最简单块
                                        nx * box.getLength(),  // 该简单块的Length
                                        ny * box.getWidth(),   // 该简单块的Width
                                        nz * box.getHeight(),  // 该简单块的Height
                                        box.getLength() * nx * box.getWidth() * ny * box.getHeight() * nz }; // 该简单块的Volume
                        //std::cout <<"single volume" << box.getLength() * nx * box.getWidth() * ny * box.getHeight() * nz << "\n";
                        //std::cout << " nx " << nx << " ny " << ny << " nz " << nz << "\n";
                        // block的level一直为0；
                        block.setLevel(0);
                        block.setVolume(box.getLength() * nx * box.getWidth() * ny * box.getHeight() * nz);
                        // 简单块的ax,y,z和lx,y,z是一致的。
                        block.setAx(block.getLength());
                        block.setAy(block.getWidth());
                        // block.setAz(block.getHeight()); 目前不需要az
                        block.setBoxes(size);
                        // float value = nx * ny * nz;
                        // std::cout << " box.getType():  " << box.getType() << "  Value: " << value << "\n";
                        block.addBoxes(box.getType(), nx*ny*nz);
                        //std::cout << "require test Simple: "  ;
                        //for (auto i : block.require()) {
                            //std::cout << i << " ";
                        //}
                        //std::cout << "\n";
                        blockTable.push_back(block);
                        //num[box.getType()]-=(nx * ny * nz);
                    }
                }
            }
        }
    }
    std::sort(blockTable.begin(), blockTable.end());
}

void Utils::GenComplexBlock(const Box& container,
                     const std::vector<Box>& boxList,
                     std::vector<float>& num,
                     std::vector<Block>& blockTable,
                     const float& maxLevel,
                     const float& minFillRate,
                     const float& minAreaRate,
                     float size
                    ) {
    GenSimpleBlock(container, boxList, num, blockTable, size);
    for(float level = 0; level <= maxLevel; ++level) {
        std::vector<Block> newBlockTable; // 之前的blockTable只是用于储存简单块
        // 对于ita来说，也需要初始化availA
        for (auto ita = blockTable.begin(); ita != blockTable.end(); ++ita) {
            // 在 ita的条件下为创建简单块itb设立环境；
            std::vector<float> availB = num;
            std::vector<Block> blockTableB;
            Box containerB = container;
            std::stack<Box> spaceStackB;
            std::vector bRequire = ita->require();
            Block& elemA = *ita;
            genResidualSpace(containerB, elemA, spaceStackB);
            /*
            for (float i = 0; i < bRequire.size(); ++i) {
                availB[i]-=bRequire[i];
            }
            */
            // 优化为以下代码
            std::transform(begin(availB), end(availB), begin(bRequire), begin(availB), std::minus<float>());
            GenSimpleBlock(containerB,boxList, availB, blockTableB, size);
            for (auto itb = blockTableB.begin(); itb != blockTableB.end(); ++itb) {
                // 如果ita 和 itb的requirement大于所需的。
                // 找到第一个不同的简单块；
                if ( ita->getLength() == itb->getLength() &&
                     ita->getWidth() == itb->getWidth() &&
                     ita->getHeight() == itb->getHeight()                      
                   ) {
                    continue;
                }
                // 
                if ( ita->getLevel() == level && itb->getLevel() == level) {
                    // 情况1： 沿x轴拓展复合块；
                    // 约束（a）: a.ax = a.lx; b.ax =b.lx; a.lz = b.lz;
                    // c.ax = a.ax + b.ax;
                    // c.ay = min(a.ay, b.ay);
                    // 可以放宽限制（让它在 0.95 ~ 1.05 浮动）
                    if (ita->getLength() + itb->getLength() <= container.getLength() &&
                        ((ita->getVolume()+itb->getVolume())/((ita->getLength() + itb->getLength()) *
                                               std::max(ita->getWidth(), itb->getWidth()) *
                                               std::max(ita->getHeight(), itb->getHeight()))) >= minFillRate &&
                        ita->getLength() == ita->getAx() &&
                        itb->getLength() == itb->getAx() &&
                        ita->getHeight() == itb->getHeight()
                         ) {
                    // 生成新的块（复合块）block；
                    // 未来三方向，更改xyz顺序即可；
                        Block block = Block(
                                               ita->getLength() + itb->getLength(),
                                               std::max(ita->getWidth(), itb->getWidth()),
                                               std::max(ita->getHeight(), itb->getHeight())
                            );
                        block.setBoxes(size);
                        block.addBoxess(ita->getBoxes(), itb->getBoxes());
                        //std::cout << "require test Complex1: "  ;
                        //for (auto i : block.require()) {
                        //    std::cout << i << " ";
                        //}
                        block.setAx(ita->getLength() + itb->getLength());
                        block.setAy(std::min(ita->getWidth(), itb->getWidth()));
                        block.setLevel(level+1);
                        block.setVolume(ita->getVolume() + itb->getVolume());
                        newBlockTable.push_back(block);
                    }
                    // 情况2： 沿y轴拓展复合块；
                    // 约束（b）: a.ay = a.ly; b.ay = b.ly; a.lz = b.lz;
                    // c.ax = min(a.ax, b.ax);
                    // c.ay = a.ay + b.ay;
                    if (ita->getWidth() + itb->getWidth() <=container.getWidth() &&
                       ((ita->getVolume()+itb->getVolume())/(std::max(ita->getLength(), itb->getLength()) *
                                               (ita->getWidth() + itb->getWidth())*
                                               std::max(ita->getHeight(), itb->getHeight())) >= minFillRate) &&
                        ita->getAy() == ita->getWidth() &&
                        itb->getAy() == itb->getWidth() &&
                        ita->getHeight() == itb->getHeight()
                        ) {
                        Block block = Block(
                                               std::max(ita->getLength(), itb->getLength()),
                                               ita->getWidth() + itb->getWidth(),
                                               std::max(ita->getHeight(), itb->getHeight())
                            );
                        block.setBoxes(size);
                        block.addBoxess(ita->getBoxes(), itb->getBoxes());
                        //std::cout << "require test Complex2: "  ;
                        //for (auto i : block.require()) {
                        //    std::cout << i << " ";
                        //}
                        block.setAx(std::min(ita->getLength(), itb->getLength()));
                        block.setAy(ita->getWidth() + itb->getWidth());
                        block.setLevel(level+1);
                        block.setVolume(ita->getVolume() + itb->getVolume());
                        newBlockTable.push_back(block);
                    }
                    // 情况3： 沿z轴拓展复合块;
                    // 需要满足minAreaRate的约束
                    // 约束（c）： a.ax >= b.lx; a.ay>=b.ly;
                    // c.ax = b.ax; c.ay = b.ay
                    if (ita->getHeight() + itb->getHeight() <=container.getHeight() &&
                       ((itb->getLength() * itb->getWidth()) / (ita->getLength() * ita->getWidth())>= minAreaRate) &&
                       ((ita->getVolume()+itb->getVolume())/(std::max(ita->getLength(), itb->getLength()) *
                                               (ita->getWidth() + itb->getWidth())*
                                               std::max(ita->getHeight(), itb->getHeight())) >= minFillRate) &&
                        ita->getAx() >= itb->getLength() &&
                        ita->getAy() >= itb->getWidth()                       
                       ) {
                        Block block = Block(
                                               std::max(ita->getLength(), itb->getLength()),
                                               std::max(ita->getWidth(), itb->getWidth()),
                                               ita->getHeight() + itb->getHeight()
                            );
                        block.setBoxes(size);
                        block.addBoxess(ita->getBoxes(), itb->getBoxes());
                        //std::cout << "require test Complex3: "  ;
                        //for (auto i : block.require()) {
                        //    std::cout << i << " ";
                        //}
                        block.setAx(itb->getAx());
                        block.setAy(itb->getAy());
                        block.setLevel(level+1);
                        block.setVolume(ita->getVolume() + itb->getVolume());
                        newBlockTable.push_back(block);
                    }
                }
            }
        }
        blockTable.insert(blockTable.end(), newBlockTable.begin(), newBlockTable.end());
        std::sort(blockTable.begin(), blockTable.end());
        //auto it = std::unique(blockTable.begin(), blockTable.end());
        //blockTable.erase(it, blockTable.end());
    }
}

void Utils::genResidualSpace(const Box& space, const Block& block, std::stack<Box>& spaceStack) {
    std::vector<Box> resSpace;
    // 设置好需要使用的变量
    float Sx = space.getLength(); // 空间x
    float Sy = space.getWidth();  // 空间y
    float Sz = space.getHeight(); // 空间z
    float Bx = block.getLength(); // 块x
    float By = block.getWidth();  // 块y
    float Bz = block.getHeight(); // 块z


    // 用一个float来记录Box所在位置；
    Box spaceZ = Box( Bx, By, Sz-Bz);
    spaceZ.setStartPofloatX(space.getStartPofloat()[0]);
    spaceZ.setStartPofloatY(space.getStartPofloat()[1]);
    spaceZ.setStartPofloatZ(space.getStartPofloat()[2]+Bz);
    spaceZ.setTag('Z');
    Box spaceX = Box( Sx-Bx, By, Sz);
    spaceX.setStartPofloatX(space.getStartPofloat()[0]+Bx);
    spaceX.setStartPofloatY(space.getStartPofloat()[1]);
    spaceX.setStartPofloatZ(space.getStartPofloat()[2]);
    spaceX.setTag('X');
    Box spaceY = Box( Sx, Sy-By, Sz);
    spaceY.setStartPofloatX(space.getStartPofloat()[0]);
    spaceY.setStartPofloatY(space.getStartPofloat()[1]+By);
    spaceY.setStartPofloatZ(space.getStartPofloat()[2]);
    spaceY.setTag('Y');
    spaceStack.push(spaceZ);
    spaceStack.push(spaceX);
    spaceStack.push(spaceY);
    /*
    std::cout << "space Z start Pofloat : " << spaceZ.getStartPofloatX() << " "
                                          << spaceZ.getStartPofloatY() << " "
                                          << spaceZ.getStartPofloatZ() << " "
                                          << "\n";
    spaceStack.push(spaceX);
    std::cout << "space X start Pofloat : " << spaceX.getStartPofloatX() << " "
                                          << spaceX.getStartPofloatY() << " "
                                          << spaceX.getStartPofloatZ() << " "
                                          << "\n";
    spaceStack.push(spaceY);
    std::cout << "space Y start Pofloat : " << spaceY.getStartPofloatX() << " "
                                          << spaceY.getStartPofloatY() << " "
                                          << spaceY.getStartPofloatZ() << " "
                                          << "\n";
    */
}


void Utils::transferSpace(std::stack<Box>& spaceStack) {
    std::vector<Block> stBlock;
    if(spaceStack.empty()) { return;}
    Box transBlock = spaceStack.top();
    spaceStack.pop(); // 栈顶用于转换的块；
    if (transBlock.getTag() == 'Z') { return;} //Z是一组XYZ中最早入栈的，因此是最晚出栈的；
    if(spaceStack.empty()) { return;} //理论上这个情况是不会发生的，但为了更加稳定，添加这个判断；
    Box recvBlock = spaceStack.top();
    spaceStack.pop();
    if(transBlock.getTag() == 'Y') {
        if(spaceStack.empty()) { return;}
        Box recvBlock1 = spaceStack.top();
        spaceStack.pop(); // 在这里recvBlock1必为spaceZ, recvBlock必为spaceX;
        recvBlock.setWidth(recvBlock.getWidth() + transBlock.getWidth()); // 分给spaceX
        recvBlock1.setWidth(recvBlock1.getWidth() + transBlock.getWidth()); // 分给spaceZ
        spaceStack.push(recvBlock1);
        spaceStack.push(recvBlock);
        return;
    }
    // bobliew's recipe 3, 此时必是transBlock 来自 spaceX， recvBlock来自spaceZ的情况；
    recvBlock.setLength(recvBlock.getLength() + transBlock.getLength());
    spaceStack.push(recvBlock);
    return;
    // 被转移完的块就会被抛弃，因为没有可行块能被它容纳 (调用该函数的前提)；
}

std::vector<Block> Utils::genBlockList(Box& space,
                                std::vector<float>& num,
                                const std::vector<Box>& boxList,
                                const float& isComplex,
                                float size) {
    std::vector<Block> ans;
    // 如果只使用简单块算法
    if (!isComplex) {
    // 调用GenSimpleBlock
        GenSimpleBlock( space, boxList, num, ans, size);
    } else {
    // 调用GenComplexBlock
    // 后续三个float参数分别为： maxLevel(复杂块最多由多少个简单块生成)；
    //                         minFillRate(最小的负载率，即实际体积/Block占用体积)
    //                         minAreaRate(顶层的面积 / 底层的面积)
        GenComplexBlock( space, boxList, num, ans, 0, 0.8, 0.9, size);
    }
    return ans;
}


Plan* Utils::basicHeuristic(const Box& container, const std::vector<float>& avail,
                   const std::vector<Box>& boxList, const float& isComplex) {
    Plan* plan = new Plan;
    std::stack<Box> spaceStack;
    //std::srand(std::time(nullptr));
    // 但是每次都会生成不同的blockList；
    // plan.setVolume(0);
    //std::random_device rd;
    //std::mt19937 gen(rd());
    Box containerB = container;
    std::vector<float> availB = avail;

    spaceStack.push(containerB);
    float index = 0;
    while(!spaceStack.empty()) {
        index++;
        Box space = spaceStack.top();
        spaceStack.pop();
        std::vector<Block> blockList = genBlockList(space, availB, boxList, isComplex, float(boxList.size()/6));
        if(!blockList.empty()) {
            //std::srand(std::time(nullptr)+index);
            //std::uniform_float_distribution<> dis(0, blockList.size()/3);
            //std::cout<<"rand()"<<std::rand()<<"\n";
            //std::cout << blockList.size() << "\n";
            auto block = blockList[std::rand() % (blockList.size())/2];
            //std::cout << std::rand() << "\n";
            // auto block = blockList[0];
            // 设置block的起始点；
            block.setStartPofloatX(space.getStartPofloat()[0]);
            block.setStartPofloatY(space.getStartPofloat()[1]);
            block.setStartPofloatZ(space.getStartPofloat()[2]);
            std::vector<float> vRequire = block.require();
            //float vRequireSize = vRequire.size();
            // 该部分优化为以下代码；
            /*
            for (float i = 0; i < vRequireSize; ++i) {
                //std::cout << "vRequire[i]" << vRequire[i] << "\n";
                //std::cout << "avail[i]" << avail[i] << "\n";
                avail[i]-=vRequire[i];
            }
            */
            std::transform(begin(availB), end(availB), begin(vRequire), begin(availB), std::minus<float>());

            /*
            index++;
            std::cout<< "index: "<< index << " test require: " << "\n";
            for (auto i : block.require()) {
               std::cout << i << " ";
            }
            */
            //std::cout << " test plan.getVolume(): " << plan.getVolume() << "\n";
            //std::cout << " test block.getVolume(): " << block.getVolume() << "\n";
            plan->setVolume( plan->getVolume() + block.getVolume());
            //std::cout<< "Test Test Test volume" << plan.getVolume();
            plan->push(block) ;
            genResidualSpace(space, block, spaceStack);
        } else {
        // 如果此时可行的blcokList已经空了，说明此时剩余空间不足 or blockList确实已经空了
        // 此时需要做的是再transferf一次剩余空间，如果所有剩余空间都空了，就会中断while
           transferSpace(spaceStack);
        }
    }
    //for (const Block& i : plan.getBoxes()) {
    //    volume += i.getVolume();
    //}
    //plan.setVolume(volume);
    //std::cout<< "Test basic plan volume :" << plan.getVolume() << "\n";
    return plan;

}

Plan Utils::outLoop(const float& loopTime, 
                    const float& isComplex,
                    Box& container, 
                    std::vector<float>& avail, 
                    std::vector<Box>& boxList) {

    Box containerB = container;
    std::vector<float> availB = avail;

    /* 常规循环
    Plan plan = basicHeuristic(containerB, availB, boxList, isComplex);
    Plan best = plan;
    std::cout<< "start plan volume: " << plan.getVolume() << "\n" ;

    
    for (float i = 0; i < loopTime; ++i) {
        Box containerB = container;
        std::vector<float> availB = avail;
        // float randomIndex = dis(gen);
        Plan newPlan = basicHeuristic(containerB, availB, boxList, isComplex);
        std::cout<< "newPlan volume: " << newPlan.getVolume() << "\n" ;

        if (best.getVolume() < newPlan.getVolume()) {
            best = newPlan;
        }
    }
    */

    // 设定boost可使用的线程数；
    boost::thread_group threads;
    std::vector<std::unique_ptr<Plan>> plans;
    for( int i = 1; i < loopTime; ++i) {
        threads.create_thread([this, &plans, containerB, availB, boxList, isComplex] {
            std::unique_ptr<Plan> plan(basicHeuristic(containerB, availB, boxList, isComplex));
            plans.push_back(std::move(plan));
        });
    }



    threads.join_all();
    Plan* bestt = nullptr;
    double best_volume = std::numeric_limits<double>::min();
    for (const auto& plan : plans) {
        if (plan->getVolume() > best_volume) {
            bestt = plan.get();
            best_volume = plan->getVolume();
        }
    }

    Plan best = *bestt;
 
    std::cout << " The best volume is : " << best.getVolume() << "  m^3" "\n";
    float index = 0;
    float totalVolume = 0;
    // std::cout << plan.getBoxes().size() << "\n";

    for (auto i : best.getBoxes()) {
        index ++;
        totalVolume += i.getVolume();
        std::cout << "Block: "<< index << " Block Start Pofloat: " << " x " << i.getStartPointX()
                  << " y " << i.getStartPointY() << " z " << i.getStartPointZ() << "  Length: "
                  << i.getLength() << " Width: " << i.getWidth() << " Height: " << i.getHeight()
                  << " Block Volume: " << i.getVolume()
                  << " \n" << "Require Vector :" ;
        for (auto element : i.require()) {
                  std::cout << element << " ";
        }
        std::cout << "\n";
    }
    std::cout << " totalVolume: " << totalVolume;
    return best;

}

void Utils::gen3ddata(std::vector<Box>& boxList, float tag, float L, float W, float H) {
    boxList.emplace_back(tag,  L,  W,  H);
    boxList.emplace_back(tag,  L,  H,  W);
    boxList.emplace_back(tag,  W,  L,  H);
    boxList.emplace_back(tag,  W,  H,  L);
    boxList.emplace_back(tag,  H,  L,  W);
    boxList.emplace_back(tag,  H,  W,  L);
}


