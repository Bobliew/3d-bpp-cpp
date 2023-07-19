#ifndef BOX
#define BOX
#include <iostream>
#include <vector>

class Box {
public:
    Box(const float& T, const float& L, const float& W, const float& H);
    Box(const float& L, const float& W, const float& H);
    ~Box() {}
    void setLength(const float& value) { maxLength = value;}
    void setWidth(const float& value) { maxWidth = value;}
    void setHeight(const float& value) { maxHeight = value;}
    void setStartPofloatX(const float& value) { startPofloat[0] = value;}
    void setStartPofloatY(const float& value) { startPofloat[1] = value;}
    void setStartPofloatZ(const float& value) { startPofloat[2] = value;}
    void setTag(const char& value) { tag = value;}
    char getTag() const{ return tag;}
    float getLength() const{ return maxLength;}
    float getWidth() const{ return maxWidth;}
    float getHeight() const{ return maxHeight;}
    float getVolume() const { return maxLength * maxWidth * maxWeight;}
    float getType() const{ return type;}
    std::vector<float> getStartPofloat() const { return startPofloat;}
    float getStartPointX() const{ return startPofloat[0];}
    float getStartPointY() const{ return startPofloat[1];}
    float getStartPointZ() const{ return startPofloat[2];}
  // 拷贝构造函数
    Box(const Box& other);
private:
    float type = -1;
    char tag;
    float maxLength;
    float maxWidth;
    float maxHeight;
    float maxWeight = 0;
    std::vector<float> startPofloat = {0, 0, 0};
};


class Block {
public:
    Block(const float& nL, const float& nW, const float& nH, const float& L, const float& W, const float& H, const float& V);
    Block(const float& L, const float& W, const float& H);
    ~Block() {}
    void setLevel(const float& value) { level = value;}
    void setFillRate(const float& value) { fillRate = value;}
    void setAx(const float& value) { ax = value;}
    void setAy(const float& value) { ay = value;}
    void setLength(const float& value) { length = value;}
    void setWidth(const float& value) { width =value;}
    void setHeight(const float& value) { height = value;}
    void setBoxes(const float size) { boxes = std::vector<float> (size, 0);}
    void setStartPofloatX(float value) { startPofloat[0] = value;}
    void setStartPofloatY(float value) { startPofloat[1] = value;}
    void setStartPofloatZ(float value) { startPofloat[2] = value;}
    void addBoxes(float type, float value) { boxes[type] = value;}
    void addBoxess(std::vector<float> vSimpleA, std::vector<float> vSimpleB) {
        float boxSize = boxes.size();
        for (float i = 0; i < boxSize; i++) {
            // std::cout << "Adding requirement !!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << "\n";
            boxes[i]+=vSimpleA[i];
            boxes[i]+=vSimpleB[i];
        }
    }
    void setVolume(const float& value) { volume = value;}
    void setTag(const char& value) { tag = value;}
    float getNl() const{ return nl;}
    float getNw() const{ return nw;}
    float getNh() const{ return nh;}
    float getLength() const { return length;}
    float getWidth() const { return width;}
    float getHeight() const { return height;}
    float getVolume() const{ return volume;}
    float getLevel() const { return level;}
    float getAx() const { return ax;}
    float getAy() const { return ay;}
    float getTag() const { return tag;}

    float getStartPointX() const{ return startPofloat[0];}
    float getStartPointY() const{ return startPofloat[1];}
    float getStartPointZ() const{ return startPofloat[2];}

    // 这里运算符重载故意写反，这样可以直接调用sort生成降序的blockList
    bool operator<(const Block& other) const { return getVolume() > other.getVolume();}
    bool operator==(const Block& other) const { return getVolume() == other.getVolume();}
    bool operator>(const Block& other) const { return getVolume() < other.getVolume();}
    // 这两个函数的作用是一致的，但是为了增强可读性，还是保留；
    std::vector<float> require() const { return boxes;}
    std::vector<float> getBoxes() const { return boxes;}


private:
    float nl;
    float nw;
    float nh;
    float length;
    float width;
    float height;
    float level = 0;
    float volume = 0; // 实际体积
    float fillRate; // 装配率
    float ax; // 上端的x
    float ay; // 上端的y
    char tag;
    std::vector<float> boxes; // 用于贮存
    std::vector<float> startPofloat = {0,0,0};


};

class Plan {
public:
    Plan(){}
    ~Plan(){}
    void setVolume( double value) { volume = value;}
    void push(const Block& value) { boxes.push_back(value);}
    double getVolume() { return volume;}
    const std::vector<Block>& getBoxes() { return boxes;}
private:
    double volume = 0.0; // 一开始就超过了阈值，所以如果设置为0，永远会小于零
    std::vector<Block> boxes;
};

#endif
