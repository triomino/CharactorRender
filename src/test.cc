#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <utility>
#include <vector>
#include <string>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "rasterizer.h"
#include "fragment.h"
#include "vertex.h"
#include "my_math.h"

#include "vertex_shader.h"
using namespace std;

#define width 79
#define height 38

void line();

int main(){
    line();
}

void line(){
    HANDLE handle;
    handle = GetStdHandle(STD_OUTPUT_HANDLE);
    
    //GetConsoleScreenBufferInfo
    //COORD screen_buffer_size = {width, height};
    //SetConsoleScreenBufferSize(handle, &screen_buffer_size);
    
    SMALL_RECT rc = {1, 1, width + 1, height + 1}; // plus one for '\n'
    SetConsoleWindowInfo(handle, true, &rc);
    
    
    //test
    
    // char ch[height][width + 1];
    
    // vector<Fragment> p;
    // p.clear();
    
    // Rasterizer r(width, height, FILLING, 1);
    /*r.Rasterize(3, 4, 50, 20, p);
    r.Rasterize(50, 4, 3, 20, p);
    r.Rasterize(7, 1, 60, 1, p);
    r.Rasterize(30, 6, 30, 23, p);
    r.Rasterize(40, 20, 1, 1, p);
    r.Rasterize(40, 1, 1,20, p);
    
    r.Rasterize(1,1,2,20,p);
    r.Rasterize(3,1,8,20,p);
    r.Rasterize(10,1,27,20,p);*/
    
    //Vertex v[] = {Vertex(0, 0, 0, 1.0f), Vertex(10, 0, 0, 1.0f), Vertex(50, 20, 0, 1.0f)};
    //r.Rasterize(v[0], v[1], v[2], p);
    // r.Rasterize(v[0], v[1], p);
    // r.Rasterize(v[1], v[2], p);
    // r.Rasterize(v[0], v[2], p);
    // for (int i = 0; i < height; i++){
        // for (int j = 0; j < width; j++){
            // ch[i][j] = GrayScale[0];
        // }
        // ch[i][width] = 0;
    // }
    
    // for (vector<Fragment>::iterator it = p.begin(); it != p.end(); ++it){
        // int x = it->x, y = it->y;
        // if (x >= 0 && x < width && y >= 0 && y < height){
            // if (it->gray < EPS) ch[y][x] = GrayScale[0];
            // else if (it->gray > 1 - EPS) ch[y][x] = GrayScale[MaxGrayScale - 1];
            // else ch[y][x] = GrayScale[int(MaxGrayScale * it->gray)];
        // }
    // }

    // string s = "";
    // for (int i = 0; i < height; i++){
        // /*
        // for (int j = 0; j < width; j++){
            // if (ch[i][j] == '*') {
                // SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
            // }
            // else {
                // SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY);
            // }
            // printf("%c", ch[i][j]);
        // }
        // */
        // //printf("%s\n", ch[i]);
        // s += ch[i];
        // s += '\n';
    // }
    // printf("%s", s.c_str());
    
   
        float vt[] = {2, 2, 2, 1, 
                    0, -2, 0, 1,
                    -2, 2, 0, 1,
                    2, 2, -1, 1};
                    
        float v[12 * 4];
        int tot = sizeof(v) / sizeof(v[0]);
        float *p = v;
        for (int i = 0; i < 4; i++){
            for (int j = 0; j < 4; j++){
                if (j != i){
                    for (int k = j * 4; k < j * 4 + 4; k++, p++){
                        *p = vt[k];
                    }
                }
            }
        }
        
        
    for (float angle = 0.0f; ; angle += 10.0f){
        system("CLS");
        VertexShader vs;
        vs.SetData(v, tot, 4);
        vs.AddAnalysis(Position, 0, 3);
        vs.AddAnalysis(Intensity, 3, 1);
        
        float dis = 5.0f;
        glm::vec3 eye_pos = glm::vec3(sin(glm::radians(angle)) * dis, 0.0f, cos(glm::radians(angle)) * dis);
        glm::vec3 eye_front = glm::normalize(glm::vec3(0.0f, 0.0f, 0.0f) - eye_pos);
        glm::vec3 eye_up = glm::vec3(0.0f, 1.0f, 0.0f);
        
        float eye_zoom = glm::radians(90.0f);
        float eye_width = width;
        float eye_height = height;
        
        glm::mat4 view = glm::lookAt(eye_pos, eye_pos + eye_front, eye_up);
        glm::mat4 projection = glm::perspective(eye_zoom, eye_width / eye_height, 0.1f, 10.0f);
        glm::mat4 model = glm::mat4();
        
        vs.SetMatrix(Model, model);
        vs.SetMatrix(View, view);
        vs.SetMatrix(Projection, projection);
        
        vs.DrawTriangles(0, 48);
        getchar();
    }
}