#ifndef DIFFUSION1D_ALOGRITHM_H
#define DIFFUSION1D_ALOGRITHM_H

class Mesh1D;

class diffusion1D: public QObject
{
  Q_OBJECT
    
 public:
  diffusion1D(ZTService *pService, QObject* parent = NULL);
  ~diffusion1D();

 private:
  void assignMesh();
  void calcCoff();
  void assignBeginningField();
  void startRun();

 private:
  QVector<settingParam> m_SettingParam;
  ZTService *m_pService;
  MeshRes* m_pData;
  GlobalParam* m_pGlobalParam;
  LocalParam* m_pLocalParam;
  Mesh1D *m_pMesher;
  
  double *m_aW;
  double *m_aE;
  double *m_aP0;
  double *m_aP;
  double *m_aP0A;
  double *m_aL;

  double *m_aArray;
  double *m_bArray;
  double *m_cArray;
  double *m_xArray;
  double *m_fArray;
  
  bool m_bStop;

 public slots:
  void doIt();

 signals:
  void oneStepFinished(int nIndex);
  
}


#endif
