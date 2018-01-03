#ifndef DIFFUSION1D_ALOGRITHM_H
#define DIFFUSION1D_ALOGRITHM_H
#include <QtWidgets>
#include <vector>
#include <QVector3D>
#include <stdio.h>
#include <stdlib.h>

class diffusion1D: public QThread
{
  Q_OBJECT
    
 public:
  diffusion1D(QObject* parent = NULL);
  ~diffusion1D();

  static diffusion1D* getInstance();

 private:
  QVector<settingParam> m_SettingParam;
  static diffusion1D* p_instance;
  
  double* m_aW;
  double* m_aE;
  double* m_aP0;
  double* m_aP;
  double* m_aL;

  unsigned int m_meshNum;

 protected:
  virtual void run();
  
}


#endif
