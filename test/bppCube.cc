#include "../cubeBpp/objects/objects.h"
#include "../cubeBpp/algorithms/cubeGenAlgorithm.h"


int main(int argc, char* argv[]) {
    // 创建一个container箱子，确定长度，宽度，高度；
    /*
    Box container( 200, 200, 200);

    // 创建一个boxList，其中包含3种类型的箱子，每种箱子的数量分别是3, 2, 1
    std::vector<Box> boxList;
    boxList.emplace_back(0, 30, 10, 5);
    boxList.emplace_back(1, 20, 10, 6);
    boxList.emplace_back(2, 12, 7, 8);
    boxList.emplace_back(3, 13, 14, 15);
    boxList.emplace_back(4, 2, 5, 13);

    std::vector<int> num{2, 2, 2, 2, 2};

    // 创建一个blockTable，用于存储生成的块
    std::vector<Block> blockTable;
    int size = boxList.size();
    // 生成简单块
    // GenSimpleBlock(container, boxList, num, blockTable, size);
    // for (const Block& block : blockTable) {
    //    std::cout << " length " << block.getLength() << " width " << block.getWidth() << " height " << block.getHeight() << "\n";
    //   std::cout << "x" << block.getNl() << " y " << block.getNw() << " z " << block.getNh() << "\n";
    //}
    // 检查生成的块的数量是否正确
    // std::cout << "Simple Block Table Size: " << blockTable.size() << std::endl;

    // 生成复杂块
    //GenComplexBlock(container, boxList, num, blockTable, 3, 0.9, 0.9, num.size());
    //for (const Block& block : blockTable) {
    //    std::cout << " length " << block.getLength() << " width " << block.getWidth() << " height " << block.getHeight() << "\n";
    //}
    // 检查生成的块的数量是否正确
    //std::cout << "Complex Block Table Size: " << blockTable.size() << std::endl;
    Plan plan = basicHeuristic(container, num, boxList, 1);
    std::cout << "basicheuristic" << "" << "\n";
    int index = 0;
    // std::cout << plan.getBoxes().size() << "\n";
    for (auto i : plan.getBoxes()) {
        index ++;
        std::cout << "Block: "<< index << " Block Start Point: " << " x " << i.getStartPointX()
                  << " y " << i.getStartPointY() << " z " << i.getStartPointZ() << "  Length: "
                  << i.getLength() << " Width: " << i.getWidth() << " Height: " << i.getHeight()
                  << " \n" << "Require Vector :" ;
        for (auto element : i.require()) {
                  std::cout << element << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n \n" << " Advanced:" << "\n";
    */
    // 创建一个container箱子，确定长度，宽度，高度；
    //std::random_device rd;
    //std::srand(rd());
    //

    float randNum1 = std::atof(argv[1]);
    //float randNum2 = std::atof(argv[2]);
    Box container( 10, 20, 10);
    std::srand(randNum1);
    // 创建一个boxList，其中包含3种类型的箱子，每种箱子的数量分别是3, 2, 1

    //


    Utils utils;
    std::vector<Box> boxList;
    utils.gen3ddata(boxList, 0, 4, 2, 1);
    utils.gen3ddata(boxList, 1, 6, 2, 1);
    utils.gen3ddata(boxList, 2, 2, 3, 2);
    utils.gen3ddata(boxList, 3, 3, 1, 3);
    utils.gen3ddata(boxList, 4, 2, 1, 2);


    // unordered_map {{tag, num}}
    std::vector<int> num{1, 2, 4, 5, 5};

    // std::vector<int> num{30, 30, 30, 30, 30};

    // 创建一个blockTable，用于存储生成的块
    std::vector<Block> blockTable;
    int size = boxList.size();
    // param of sa
    int ts = 10000;
    float tf = 0.001;
    float dt = 0.95;
    int loopTime = 100;
    int isComplex = 1;
    int isLinear = 1;

    auto start_time = std::chrono::steady_clock::now();
    Plan best = utils.outLoop(ts, tf, dt, loopTime, isComplex, isLinear,
                   container, num, boxList);
    auto end_time = std::chrono::steady_clock::now();
    auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    std::cout << "程序运行时间为：" << elapsed_time.count() << " 毫秒" << std::endl;
    return 0;
}
