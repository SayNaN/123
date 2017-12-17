#ifndef DIFFUSION1D_ALOGRITHM_H
#define DIFFUSION1D_ALOGRITHM_H
#include <QtWidgets>
#include <QVector>
#include <QVector3D>
#include <stdio.h>
#include <stdlib.h>

struct settingParam
{
  QVector<QVector3D> coord;
  float 
};

class diffusion1D
{
  Q_OBJECT
    
 public:
  diffusion1D();
  ~diffusion1D();

 private:
  QVector<settingParam> m_SettingParam;
  
}


#endif
