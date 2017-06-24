# CharactorRender
  在windows控制流中，用字符代替像素绘图。  <br>
  通过模拟OpenGL可编程管线内部渲染流程实现。
## 已粗糙实现
  无宽度的线段光栅化(Graham's algorithm)
  三角形光栅化，并插值
  简单的抗锯齿：增加采样点后取平均
## 环境和依赖
  windows，除c++标准库没有其他链接库。glm库已经放在include中不过暂时用不到。
