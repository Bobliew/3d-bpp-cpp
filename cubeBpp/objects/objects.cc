#include "./objects.h"


// definition
Box::Box(const float& T, const float& L, const float& W, const float& H)
  : type(T),
    maxLength(L),
    maxWidth(W),
    maxHeight(H){}

Box::Box(const float& L, const float& W, const float& H)
  : maxLength(L),
    maxWidth(W),
    maxHeight(H) {}

    // 拷贝构造函数
Box::Box(const Box& other)
  : type(other.getType()),
    tag(other.getTag()),
    maxLength(other.getLength()),
    maxWidth(other.getWidth()),
    maxHeight(other.getHeight()),
    startPofloat({other.getStartPointX(),
                  other.getStartPointY(),
                  other.getStartPointZ()})
{
}

Block::Block(const float& nL, const float& nW, const float& nH, const float& L, const float& W, const float& H, const float& V)
  : nl(nL),
    nw(nW),
    nh(nH),
    length(L),
    width(W),
    height(H),
    volume(V) {}

Block::Block(const float& L, const float& W, const float& H)
  : length(L),
    width(W),
    height(H),
    volume(L*W*H) {}


