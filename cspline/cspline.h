#ifndef CSPLINE_H
#define CSPLINE_H

#include<math.h>

class Cspline
{
 public:
  Cspline();
  Cspline(double* arrayX, double* arrayY, int n);
  ~Cspline();

  void setParams(double* arrayX, double* arrayY, int n);
  // 根据输入的x坐标求y坐标
  double getYCoor(double interpo_x,int n);

 private:
  // 生成三次参数养条曲线
  void gen();
  void freeAndNil(double *array);
  void release();
  void initArray();

 private:
  int m_nCount;
  double *x,*y,*s;
  double *ax,*bx,*cx,*dx;
  double *ay,*by,*cy,*dy;
  double *Mx,*My;
  double *slope;
};



#endif
