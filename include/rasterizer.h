#ifndef __RASTERIZER_H__
#define __RASTERIZER_H__

#include <vector>
#include <utility>

#include "glm/glm.hpp"
#include "fragment.h"
#include "vertex.h"

using namespace std;

enum RasterizeMode{
    NONE,
    FILLING,
    LINEONLY,
    RasterizeModeNum
};

class Rasterizer{
    int width, height;
    int anti_aliasing_depth;
    RasterizeMode r_mode;
    
public:
    Rasterizer(int screen_width = 60, int screen_height = 24, RasterizeMode rm = FILLING, int aa = 1) : width(screen_width), height(screen_height), r_mode(rm), anti_aliasing_depth(aa){}
    ~Rasterizer(){}
    
    void Rasterize(const Vertex &a, const Vertex &b, vector<Fragment> &res);
    
    void Rasterize(const Vertex &p0, const Vertex &p1, const Vertex &p2, vector<Fragment> &res);
    
    void SetHW(int h, int w);
    void SetRasterizeMode(RasterizeMode rmode);
    void SetAntiAliasing(int aa);
};

#endif