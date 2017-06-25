
#include <stdio.h>
#include <stdlib.h>

#include <utility>
#include <vector>
#include <algorithm>

#include <cmath>
#include "glm/glm.hpp"

#include "rasterizer.h"
#include "vertex.h"

#include "my_math.h"

using namespace std;

// #ifndef PII
// #define PII pair<int, int>

void Rasterizer::Rasterize(const Vertex &a, const Vertex &b, vector<Fragment> &res){
    // anti aliasing
    if (anti_aliasing_depth){
        int scale = anti_aliasing_depth << 1 | 1;
        int size = scale * scale;
        float g[height][width] = {};
        float z[height][width] = {};
        int cnt[height][width] = {};
        Rasterizer rz(width * scale, height * scale, r_mode, 0);
        Vertex aa = a; aa.x *= scale, aa.y *= scale;
        Vertex bb = b; bb.x *= scale, bb.y *= scale;
        
        vector<Fragment> temp;
        temp.clear();
        
        rz.Rasterize(aa, bb, temp);
        
        for (vector<Fragment>::iterator it = temp.begin(); it != temp.end(); it++){
            int x = it->x / scale;
            int y = it->y / scale;
            if (x >= 0 && x < width && y >= 0 && y < height) g[y][x] += it->gray, z[y][x] += it->z, cnt[y][x]++;
        }
        for (int i = 0; i < height; i++){
            for (int j = 0; j < width; j++){
                if (cnt[i][j]){
                    res.push_back(Fragment(j, i, z[i][j] / cnt[i][j], g[i][j] / scale));
                }
            }
        }
        
        return ;
    }
    /* TODO : clipping */
    {
        printf("TODO : Clipping in Line");
    }
    //printf("line %f %f %f %f\n", a.x, a.y, b.x, b.y);
    /* rasterize a line */
    int x1 = round(a.x), y1 = round(a.y), x2 = round(b.x), y2 = round(b.y), swap_flag = 0;
    if (abs(y2 - y1) > abs(x2 - x1)){
        swap_flag = 1;
        swap(x1, y1);
        swap(x2, y2);
    }
    if (x1 > x2){
        swap(x1, x2);
        swap(y1, y2);
    }
    int x = x1, y = y1;
    int yflag = y2 >= y1 ? 1 : -1;
    int judge = -(x2 - x1);
    int xdelta = 2 * (y2 - y1) * yflag;
    int ydelta = -2 * (x2 - x1);
    
    float gdelta = 1.0f / (x2 - x1) * b.gray - 1.0f / (x2 - x1) * a.gray;
    
    float zdelta = 1.0f / (x2 - x1) * b.z - 1.0f / (x2 - x1) * a.z;
    
    for (float z = a.z, gray = a.gray; x <= x2; x++, judge += xdelta, z += zdelta, gray += gdelta){
        //int z = 1.0f * (x - x1) / (x2 - x1) * 
        //printf("%d %d\n", x, y);
        if (swap_flag) res.push_back(Fragment(y, x, z, gray));
        else res.push_back(Fragment(x, y, z, gray));
        if (judge > 0){
            y += yflag;
            judge += ydelta;
        }
    }
}


void Rasterizer::Rasterize(const Vertex &p0, const Vertex &p1, const Vertex &p2, vector<Fragment> &res){
    if (anti_aliasing_depth){
        int scale = anti_aliasing_depth << 1 | 1;
        int size = scale * scale;
        float g[height][width] = {};
        float z[height][width] = {};
        int cnt[height][width] = {};
        Rasterizer rz(width * scale, height * scale, r_mode, 0);
        Vertex v0 = p0; v0.x *= scale, v0.y *= scale;
        Vertex v1 = p1; v1.x *= scale, v1.y *= scale;
        Vertex v2 = p2; v2.x *= scale, v2.y *= scale;
        
        vector<Fragment> temp; temp.clear();
        rz.Rasterize(v0, v1, v2, temp);
        for (vector<Fragment>::iterator it = temp.begin(); it != temp.end(); it++){
            int x = it->x / scale;
            int y = it->y / scale;
            if (x >= 0 && x < width && y >= 0 && y < height) g[y][x] += it->gray, z[y][x] += it->z, cnt[y][x]++;
        }
        if (r_mode == FILLING){
            for (int i = 0; i < height; i++){
                for (int j = 0; j < width; j++){
                    if (cnt[i][j]){
                        res.push_back(Fragment(j, i, z[i][j] / cnt[i][j], g[i][j] / size));
                    }
                }
            }
        }
        else if (r_mode == LINEONLY){
            for (int i = 0; i < height; i++){
                for (int j = 0; j < width; j++){
                    if (cnt[i][j]){
                        res.push_back(Fragment(j, i, z[i][j] / cnt[i][j], g[i][j] / scale));
                    }
                }
            }
        }
        return;
    }
    
    // No AA
    char ch[height][width] = {};
    if (r_mode == LINEONLY){
        Vertex p[3] = {p0, p1, p2};
        vector<Fragment> line;
        line.clear();
        for (int i = 0; i < 3; i++){
            Rasterize(p[i], p[(i + 1) % 3], line);
        }
        for (vector<Fragment>::iterator it = line.begin(); it != line.end(); it++){
            ch[it->y][it->x] |= 1;
        }
        //printf("line over \n");
    }
    
    // interpolation to calculate z and gray
    float x[] = {p0.x, p1.x, p2.x, p0.x, p1.x, p2.x};
    float y[] = {p0.y, p1.y, p2.y, p0.y, p1.y, p2.y};
    float c[3], dx[3], dy[3], init[3], now[3];
    float gray, z;
    for (int i = 0; i < 3; i++){
        c[i] = 1.0f / ((y[i + 1] - y[i + 2]) * x[i] + (x[i + 2] - x[i + 1]) * y[i] + x[i + 1] * y[i +2] - x[i + 2] * y[i + 1]);
        dx[i] = (y[i + 1] - y[i + 2]) * c[i];
        dy[i] = (x[i + 2] - x[i + 1]) * c[i];
        init[i] = (x[i + 1] * y[i +2] - x[i + 2] * y[i + 1]) * c[i];
    }
    
    if (r_mode == FILLING){
        // printf("test\n");
        // for (int i = 0; i < 3; i++){
            // printf("%f%c", x[i], " \n"[i == 2]);
        // }
        // for (int i = 0; i < 3; i++){
            // printf("%f%c", y[i], " \n"[i == 2]);
        // }
        
        for (int i = 0; i < height; i++){
            now[0] = init[0], now[1] = init[1], now[2] = init[2];
            for (int j = 0; j < width; j++){
                if (now[0] > -EPS && now[0] < 1 + EPS && now[1] > -EPS && now[1] < 1 + EPS && now[2] > -EPS && now[2] < 1 + EPS){
                    //printf("%d %d\n", i, j);
                    gray = p0.gray * now[0] + p1.gray * now[1] + p2.gray * now[2];
                    z = p0.z * now[0] + p1.z * now[1] + p2.z * now[2];
                    res.push_back(Fragment(j, i, z, gray));
                }
                now[0] += dx[0], now[1] += dx[1], now[2] += dx[2];
                //printf("%f\n", now[0] + now[1] + now[2]);
            }
            init[0] += dy[0], init[1] += dy[1], init[2] += dy[2];
        }
    }
    else if (r_mode == LINEONLY){
        for (int i = 0; i < height; i++){
            now[0] = init[0], now[1] = init[1], now[2] = init[2];
            for (int j = 0; j < width; j++){
                if (ch[i][j]){
                    gray = p0.gray * now[0] + p1.gray * now[1] + p2.gray * now[2];
                    z = p0.z * now[0] + p1.z * now[1] + p2.z * now[2];
                    res.push_back(Fragment(j, i, z, gray));
                }
                now[0] += dx[0], now[1] += dx[1], now[2] += dx[2];
                //printf("%f\n", now[0] + now[1] + now[2]);
            }
            init[0] += dy[0], init[1] += dy[1], init[2] += dy[2];
        }
    }
    
}