#ifndef CSPLINE_H
#define CSPLINE_H

#include<math.h>

class Cspline
{
 public:
  Cspline();
  ~Cspline();

  double slope_endp();
  void gen(double *xcoor,double *ycoor,int n);

  void fillet(double end_x,double end_y,double *x_coor,double *y_coor,int coor_num);

  void interpolate_r(double *res,double *x,double *y,int n,double *inter_r,int x_control_inex);
  double project(double interpo_x,int n);

 private:
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
