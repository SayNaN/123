#ifndef THREED_DISPLAY_H
#define THREED_DISPLAY_H
#include<QOpenGLFunctions_1_1>

struct Vector3N
{
  unsinged int fir;
  unsinged int sec;
  unsinged int thr;
}

struct Vector3D
{
  double x;
  double y;
  double z;
};
struct Vector4D
{
  double x;
  double y;
  double z;
  double a;
};
struct GLData
{
  Vector3D point;
  Vector3D normal;
  Vector3D normalization;
  Vector4D color;
};


class MyGLWidget : public QOpenGLWidget, public QOpenGLFunctions_1_1
{
  Q_OBJECT
 public:
  MyGLWidget(ZTService *pService, QWidget *parent);
  ~MyGLWidget(){};

  void cleardisplay();
  void drawGeomDisplay();
  void drawMeshDisplay();
  void pushBuffer(Vector3D oFir, Vector3D oSec, Vector3D oThr);
  
 protected:
  void initializeGL();
  void resizeGL(int w, int h);
  void paintGL();
  void wheelEvent(QWheelEvent* event);
  void mousePressEvent(QMouseEvent *e);
  void mouseMoveEvent(QMouseEvent *event);

 public slots:
  void processRes(int nIndex);

 private:
  void draw3DGrid();
  void draw3DGeo();
  void init_showrange();
  void set_range(double left,double right,double bottom,double top,double near,double far);
  void drawstring(const char *a);

 private:
  double width_fun,height_fun;
  int button_type;
  int mousex,mousey;
  int sign;
  double showleft,showright,showbottom,showtop;
  double rangeleft,rangeright,rangebottom,rangetop,rangenear,rangefar;
  double comat[16];
  ZTService *m_pService;
  bool drawMesh;
  bool drawGeo;
  Vector3D structMaxCoor;
  Vector3D structMinCoor;
  std::map<QString, unsinged int> mapPointIndex;
  std::vector<GLData> vecPoint;
  std::vector<Vector3N> vecIndex;
};

#endif
