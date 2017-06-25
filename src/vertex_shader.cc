
#include "vertex_shader.h"

VertexShader::VertexShader(){
    data = NULL;
    data_analysis.clear();
    trans_mat = glm::mat4();
    for (int i = 0; i < 3; i++){
        matrix[i] = glm::mat4();
    }
}
VertexShader::~VertexShader(){
    if (data) delete []data;
}
    
void VertexShader::SetData(const float *vs, int tot, int block_num){
    if (data) delete []data;
    data = new float[tot];
    float *p = data;
    for (int i = 0; i < tot; i++, p++, vs++){
        *p = *vs;
    }
    
    num = tot;
    bnum = block_num;
}

void VertexShader::SetMatrix(TransMatrix tm, glm::mat4 _matrix){
    if (tm < TransMatrixNum){
        matrix[int(tm)] = _matrix;
    }
    trans_mat = glm::mat4();
    for (int i = 0; i < TransMatrixNum; i++){
        trans_mat *= matrix[i];
    }
}

void VertexShader::AddAnalysis(VertexDataType vdt, int offset, int size){
    data_analysis.push_back(DataAnalysis(vdt, offset, size));
}
    
void VertexShader::DrawTriangles(int begin, int tot){
    HANDLE handle;
    handle = GetStdHandle(STD_OUTPUT_HANDLE);
    
    CONSOLE_SCREEN_BUFFER_INFO binfo;
    GetConsoleScreenBufferInfo(handle, &binfo);
    //printf("top %d bottom %d left %d right %d\n", binfo.srWindow.Top, binfo.srWindow.Bottom,  binfo.srWindow.Left,  binfo.srWindow.Right);
    
    int width = binfo.srWindow.Right - binfo.srWindow.Left;
    int height = binfo.srWindow.Bottom - binfo.srWindow.Top;
    
    vector<Vertex> vertices;
    vertices.clear();
    float *p = data + begin;
    
    vector<DataAnalysis>::iterator it;
    for (int i = 0; i + bnum <= tot; i += bnum, p += bnum){
        it = data_analysis.begin();
        Vertex temp;
        
        for (; it != data_analysis.end(); it++){
            if (it->vdt == Position){
                if (it->size == 3){
                    glm::vec4 vc(*(p + it->offset), *(p + it->offset + 1), *(p + it->offset + 2), 1.0f);
                    glm::vec4 newp = trans_mat * vc;
                    temp.x = newp.x * width / newp.w + width / 2.0f;
                    temp.y = height / 2.0f * (1.0f - newp.y / newp.w);
                    temp.z = newp.z / newp.w;
                    //printf("%f %f %f\n", newp.x / newp.w, newp.y / newp.w, newp.z / newp.w);
                }
                else if (it->size == 2){
                    temp.x = *(p + it->offset);
                    temp.y = *(p + it->offset + 1);
                    temp.z = 0.0f;
                }
                /*if (it->size >= 1) temp.x = *(p + it->offset); else temp.x = 0.0f;
                if (it->size >= 2) temp.y = *(p + it->offset + 1); else temp.y = 0.0f;
                if (it->size >= 3) temp.z = *(p + it->offset + 2); else temp.z = 0.0f;*/
            }
            else if (it->vdt == Intensity){
                temp.gray = *(p + it->offset);
            }
        }
        
        vertices.push_back(temp);
        
        //printf("%f %f %f %f\n", temp.x, temp.y, temp.z, temp.gray);
    }
    vector<Vertex>::iterator vit = vertices.begin();
    vector<Fragment>::iterator fit;
    
    // temp result
    vector<Fragment> temp;
    // processor
    Rasterizer rz(width, height, LINEONLY, 1);
    // result
    Fragment frags[height][width];
    
    for (int i = 0; i < height; i++) for (int j = 0; j < width; j++) frags[i][j].z = +INF;
    for (; vit != vertices.end() && vit + 1 != vertices.end() && vit + 2 != vertices.end(); vit += 3){
        temp.clear();
        rz.Rasterize(*vit, *(vit + 1), *(vit + 2), temp);
        //printf("test temp.size %d\n", temp.size());
        for (fit = temp.begin(); fit != temp.end(); fit++){
            //printf("%d %d %f\n", fit->x, fit->y, fit->z);
            if (fit->z > -EPS && fit->z + EPS < frags[fit->y][fit->x].z){
                //printf("%d %d\n", fit->y, fit->x);
                frags[fit->y][fit->x] = *fit;
            }
        }
    }
    
    // TODO : process Fragment shader
    
    string s = "";
    char ch[width + 1]; ch[width] = 0;
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            Fragment &p = frags[i][j];
            if (p.gray < EPS) ch[j] = GrayScale[0];
            else if (p.gray > 1.0 - EPS) ch[j] = GrayScale[MaxGrayScale - 1];
            else ch[j] = GrayScale[int(MaxGrayScale * p.gray)];
        }
        s += ch;
        s += '\n';
    }
    printf("%s", s.c_str());
}