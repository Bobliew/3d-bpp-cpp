#include "./objects.h"


// definition
Box::Box(int T, int L, int W, int H)
  : type(T),
    maxLength(L),
    maxWidth(W),
    maxHeight(H){}

Box::Box(int L, int W, int H)
  : maxLength(L),
    maxWidth(W),
    maxHeight(H) {}


Block::Block(int nL, int nW, int nH, int L, int W, int H, int V)
  : nl(nL),
    nw(nW),
    nh(nH),
    length(L),
    width(W),
    height(H),
    volume(V) {}

Block::Block(int L, int W, int H)
  : length(L),
    width(W),
    height(H),
    volume(L*W*H) {}


