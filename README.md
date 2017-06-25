# CharactorRender
  在windows控制台中，用字符代替像素绘图。  <br>
  通过模拟OpenGL可编程管线内部渲染流程实现。
## 已粗糙实现
  无宽度的线段光栅化(Graham's algorithm)  <br>
  三角形光栅化  <br>
  简单的抗锯齿：增加采样点后取平均  <br>
  顶点着色器封装  <br>
  MVP矩阵传递  <br>
  
## 环境和依赖
  windows，除c++标准库没有其他链接库。  <br>
  glm库已经放在include中不过暂时用不到。