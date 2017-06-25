#ifndef __VERTEX_SHADER_H__
#define __VERTEX_SHADER_H__

#include <windows.h>
#include <stdio.h>
#include <vector>
#include <string>

#include "glm/glm.hpp"

#include "my_math.h"
#include "vertex.h"
#include "rasterizer.h"

using namespace std;


enum VertexDataType{
    Position,
    Intensity,
    Normal,
    Texcoord,
    VertexDataTypeNum
};

enum TransMatrix{
    Projection,
    View,
    Model,
    TransMatrixNum
};

class VertexShader{
private:
    
    float *data;
    int num, bnum;
    
    struct DataAnalysis{
        VertexDataType vdt;
        int offset;
        int size;
        DataAnalysis(VertexDataType _vdt, int _off, int _s) : vdt(_vdt), offset(_off), size(_s){}
    };
    vector<DataAnalysis> data_analysis;
    
    glm::mat4 matrix[TransMatrixNum];
    glm::mat4 trans_mat;
    
public:

    VertexShader();
    ~VertexShader();
    
    void SetData(const float *vs, int tot, int block_num);
    void AddAnalysis(VertexDataType vdt, int offset, int size);
    
    void DrawTriangles(int begin, int tot);
    
    void SetMatrix(TransMatrix tm, glm::mat4 _matrix = glm::mat4());
};

#endif