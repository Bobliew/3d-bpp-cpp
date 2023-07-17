#ifndef BOX
#define BOX

#include <iostream>
#include <vector>


class Box {
public:
    Box(int T, int L, int W, int H);
    Box(int L, int W, int H);
    ~Box() {}
    void setLength(int value) { maxLength = value;}
    void setWidth(int value) { maxWidth = value;}
    void setHeight(int value) { maxHeight = value;}
    void setStartPointX(const int& value) { startPoint[0] = value;}
    void setStartPointY(const int& value) { startPoint[1] = value;}
    void setStartPointZ(const int& value) { startPoint[2] = value;}
    void setTag(const char& value) { tag = value;}
    char getTag() const{ return tag;}
    int getLength() const{ return maxLength;}
    int getWidth() const{ return maxWidth;}
    int getHeight() const{ return maxHeight;}
    int getVolume() const { return maxLength * maxWidth * maxWeight;}
    int getType() const{ return type;}
    std::vector<int> getStartPoint() const { return startPoint;}
    int getStartPointX() const{ return startPoint[0];}
    int getStartPointY() const{ return startPoint[1];}
    int getStartPointZ() const{ return startPoint[2];}

private:
    int type = -1;
    char tag;
    int maxLength;
    int maxWidth;
    int maxHeight;
    int maxWeight = 0;
    std::vector<int> startPoint = {0, 0, 0};
};


class Block {
public:
    Block(int nL, int nW, int nH, int L, int W, int H, int V);
    Block(int L, int W, int H);
    ~Block() {}
    void setLevel(const int& value) { level = value;}
    void setFillRate(const int& value) { fillRate = value;}
    void setAx(const int& value) { ax = value;}
    void setAy(const int& value) { ay = value;}
    void setLength(const int& value) { length = value;}
    void setWidth(const int& value) { width =value;}
    void setHeight(const int& value) { height = value;}
    void setBoxes(const int size) { boxes = std::vector<int> (size, 0);}
    void setStartPointX(int value) { startPoint[0] = value;}
    void setStartPointY(int value) { startPoint[1] = value;}
    void setStartPointZ(int value) { startPoint[2] = value;}
    void addBoxes(int type, int value) { boxes[type] = value;}
    void addBoxess(std::vector<int> vSimpleA, std::vector<int> vSimpleB) {
        for (int i = 0; i < boxes.size(); i++) {
            // std::cout << "Adding requirement !!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << "\n";
            boxes[i]+=vSimpleA[i];
            boxes[i]+=vSimpleB[i];
        }
    }
    void setVolume(int value) { volume = value;}
    void setTag(const char& value) { tag = value;}
    int getNl() const{ return nl;}
    int getNw() const{ return nw;}
    int getNh() const{ return nh;}
    int getLength() const { return length;}
    int getWidth() const { return width;}
    int getHeight() const { return height;}
    int getVolume() const{ return volume;}
    int getLevel() const { return level;}
    int getAx() const { return ax;}
    int getAy() const { return ay;}
    int getTag() const { return tag;}

    int getStartPointX() const{ return startPoint[0];}
    int getStartPointY() const{ return startPoint[1];}
    int getStartPointZ() const{ return startPoint[2];}

    // 这里运算符重载故意写反，这样可以直接调用sort生成降序的blockList
    bool operator<(const Block& other) const { return getVolume() > other.getVolume();}
    bool operator==(const Block& other) const { return getVolume() == other.getVolume();}
    bool operator>(const Block& other) const { return getVolume() < other.getVolume();}
    // 这两个函数的作用是一致的，但是为了增强可读性，还是保留；
    std::vector<int> require() const { return boxes;}
    std::vector<int> getBoxes() const { return boxes;}


private:
    int nl;
    int nw;
    int nh;
    int length;
    int width;
    int height;
    int level = 0;
    int volume = 0; // 实际体积
    int fillRate; // 装配率
    int ax; // 上端的x
    int ay; // 上端的y
    char tag;
    std::vector<int> boxes; // 用于贮存
    std::vector<int> startPoint = {0,0,0};


};

class Plan {
public:
    Plan(){}
    ~Plan(){}
    void setVolume( double value) { volume = value;}
    void push(const Block& value) { boxes.push_back(value);}
    double getVolume() const { return volume;}
    std::vector<Block> getBoxes() { return boxes;}
private:
    double volume = 0; // 一开始就超过了阈值，所以如果设置为0，永远会小于零
    std::vector<Block> boxes;
};



#endif
