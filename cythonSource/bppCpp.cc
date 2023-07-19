#include <nlohmann/json.hpp>
#include <iostream>
#include "../cubeBpp/objects/objects.h"
#include "../cubeBpp/algorithms/cubeGenAlgorithm.h"

using json = nlohmann::json;




Box method1(std::vector<) {
    Box ans;
    
    
    return ans;
}


std::string bppCpp( const std::string& s, 
                    const float& random, 
                    const float& loopTime,
                    const float& isComplex) {
    // 将字符串传入的json数据转化为json格式；
    // 利用来自flask框架的随机数导入作为cpp的的随机数种子；
    std::srand(random);
    json j = json::parse(s);
    // 条件： containerInfo的volume是升序排列的；
    // 选箱逻辑1：尽量单个箱子完成，如果containers[i] > sum of volume of sku
    // 如果遍历到最后，则选择最大的箱子，然后先进行一次，再用blockList循环一次;
    // 选箱逻辑2：指定箱子类型；
    // 后续将对选箱逻辑进行补充；
    if (s["method"] == 1) {
        Utils utils;
        std::vector<Box> boxList;
        std::vector<float> num;
        // 创建boxList
        for (float i = 0; i < s["orderInfo"]["skuInfo"].size(); ++i) {
            utils.gen3ddata(boxList, i, s["orderInfo"]["skuInfo"][i]["Length"], 
                                        s["orderInfo"]["skuInfo"][i]["Width"],
                                        s["orderInfo"]["skuInfo"][i]["Heigght"]);
            num.append(s["orderInfo"]["skuInfo"][i]["Amount"]);
        }
    
    } else if(s["baseInfo"]["method"] == 2) {
        
    }

    Plan best = utils.outLoop(loopTime,     // 启发式循环次数 
                              isComplex,    // 是否启用复杂块
                              container,    // 容器
                              num,          // 需要装箱数量（std::vector<float>）
                              boxList);     // 货物尺寸List
    // 最后将返回的结果重新格式化为json数据；
    std::cout<< best; 
    // 新建一个json的框架，然后再往这个框架里面添加数据；


}

void tranResponse() {

}

json floaterface() {

}


// test
float main() {

}

// void 调用bppCpp,用boost的compute来并行化计算bppCPp；

