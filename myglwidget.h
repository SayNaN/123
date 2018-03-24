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
  virtual void drawAdditional();

 public slots:
  void processRes(int nIndex);

 private:
  void draw3D();
  void initShowRange();
  void setRange(double dLeft,double dRight,double dBottom,double dTop,double dNear,double dFar);
  void drawstring(const char *a);
  void getnormaldir(Vector3D oFir, Vector3D oSec, Vector3D oThr, Vector3D &oNormal);
  void corss(Vector3D oVec1, Vector3D oVec2, Vector3D &oNormal);
  void guiyi(Vector3D oSrc, Vector3D &oDes);
  void addTrangle(Vector3D strucVer[3]);

 private:
  double m_dWinWidth;
  double m_dWinHeight;
  int button_type;
  int sign;
  
  int m_nMouseX;
  int m_nMouseY;
  
  double m_dShowleft;
  double m_dShowright;
  double m_dShowbottom;
  double m_dShowtop;
  
  double m_dRangeLeft;
  double m_dRangeRight;
  double m_dRangeBottom;
  double m_dRangeTop;
  double m_dRangeNear;
  double m_dRangeFar;
  
  double m_aComat[16];
  ZTService *m_pService;
  bool m_bDrawMesh;
  bool m_bDrawGeo;
  Vector3D m_sMaxCoor;
  Vector3D m_sMinCoor;
  std::map<QString, unsinged int> m_mapPointIndex;
  std::vector<GLData> m_vecPoint;
  std::vector<Vector3N> m_vecIndex;
};

#endif
