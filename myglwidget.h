#ifndef THREED_DISPLAY_H
#define THREED_DISPLAY_H
#include<QtWidgets>
#include<QOpenGLFunctions_1_1>
#include"data_container.h"

class MyGLWidget : public QOpenGLWidget, public QOpenGLFunctions_1_1
{
  Q_OBJECT
 public:
  MyGLWidget(QWidget *parent,Data_Container *DB);
  ~MyGLWidget(){};
  Data_Container *data;

  bool drawMesh;
  bool drawGeo;
  void cleardisplay();
  void drawGeomDisplay();
  void drawMeshDisplay();
  
 protected:
  void initializeGL();
  void resizeGL(int w, int h);
  void paintGL();
  void wheelEvent(QWheelEvent* event);
  void mousePressEvent(QMouseEvent *e);
  void mouseMoveEvent(QMouseEvent *event);

 private:
  void draw3DGrid();
  void draw3DGeo();
  void init_showrange();
  void set_range(double left,double right,double bottom,double top,double near,double far);
  double width_fun,height_fun;
  int button_type;
  int mousex,mousey;
  int sign;
  double showleft,showright,showbottom,showtop;
  double rangeleft,rangeright,rangebottom,rangetop,rangenear,rangefar;
  double comat[16];
  void drawstring(const char *a);
};

#endif
